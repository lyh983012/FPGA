#include<system.h>

typedef struct
{
unsigned long int DATA;
unsigned long int DIRECTION;
unsigned long int INTERRUPT_MASK;
unsigned long int EDGE_CAPTURE;
}PIO_STR;


#ifndef _LCD
#define _LCD
#define LCD_CS ((PIO_STR *) LCD_CS_BASE)
#define LCD_SCL ((PIO_STR *) LCD_SCL_BASE)
#define LCD_A0 ((PIO_STR *) LCD_A0_BASE)
#define LCD_SI ((PIO_STR *) LCD_SI_BASE)
#endif /* _LCD */



void data_send(unsigned char dat) {
unsigned char i;
	 LCD_CS->DATA=0;
	 LCD_SCL->DATA=0;
	for(i=0;i<8;i++){
		if(dat&0x80)
			LCD_SI->DATA=1;
		else
			LCD_SI->DATA=0;
		dat<<=1;
		LCD_SCL->DATA=0;
		LCD_SCL->DATA=1;
	}
	LCD_CS->DATA=1;
}
/*
* === FUNCTION ======================================== * Name: write_command
* Description: A0为低时，写命令字，
* ===================================================== */
void write_command(unsigned char com) {
	LCD_A0->DATA=0;
	data_send(com);
 }
/*
* === FUNCTION ======================================== * Name: write_data
* Description: A0为高时，写数据
* ===================================================== */
void write_data(unsigned char dat) {
    LCD_A0->DATA = 1;
    data_send(dat);
}
/*
 * === FUNCTION ======================================== * Name: set_x
* Description: 讴置列地址
* ===================================================== */
 void set_x(unsigned char x) {
write_command(x>>4|0x10);
write_command(x&0xf); }
/*
* === FUNCTION ========================================
*
*
*
* Description: 讴置页地址 一共8页
* ===================================================== */
void set_y(unsigned char y) {
	write_command(y|0xb0);
}
/*
* === FUNCTION ========================================
Name: set_y
*
* Description: 清屏
* =====================================================
Name: clear
 */
void clear(void) {
int seg; int page;
for(page=0;page<8;page++){
		set_y(page);//讴置页地址，一共8页
		set_x(0x00);//讴置列地址为0
		for(seg=0;seg<128;seg++){
			write_data(0);
		}
	}
}
/*
* === *
* Description: 显示一张128*64癿图片
* =====================================================
FUNCTION ======================================== Name: draw_screen
 */
void draw_screen(unsigned char *p) {
int seg; int page;
for(page=0;page<8;page++){
	set_y(page);//讴置页地址，一共8页
	set_x(0x00);//讴置列地址为0
			for(seg=0;seg<128;seg++){
					write_data(*p++);
			}
		}
}

void draw_word(unsigned char *p,int n) {

int word;
for(word=0;word<n;word++){
	int seg;
	set_x(10+word*16);
	set_y(4);
	for(seg=0;seg<16;seg++){
			write_data(*p++);
	}
	set_x(10+word*16);
	set_y(3);
	for(seg=0;seg<16;seg++){
			write_data(*p++);
		}
	}
}

void draw_xy(int x,int y,int black){
	if(black==1){
		set_x(x);
		set_y(y/8);
		int del,i;
		del=1;
		for(i=0;i<y%8;i++)
			del<<=1;
		write_data(del);
	}
}
/*
* === *
* Description: LCD刜始化，刜始化凼数由厂商提供，相关讴置请查询datasheet
* =====================================================
FUNCTION ======================================== Name: initialize_lcd
 */
void initialize_lcd(void) {
write_command(0xaf); //ON DISPLAY
write_command(0x40); //STAR DISPLAY
write_command(0xa0); //ADC NORMAL
write_command(0xa6); //Display Normal
write_command(0xa4); //CLEAR
write_command(0xa2); //1/9BIAS
write_command(0xc8); //COMMON OUTPUT DIRECTION
write_command(0x2f); //POWER CONTROL
write_command(0x24); //RESISTER RATIO
write_command(0x81); //VOLUM MODE SET
write_command(0x24); //RESISTER RATIO
}

