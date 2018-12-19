/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include <unistd.h>
#include "pio.h"
#include "lcd.h"
#include "source.h"

int main()
{
	initialize_lcd();
	initPIO();
	clear();
	draw_word(hallo,6);
	usleep(5000000);
	clear();
	draw_screen(back_ground);
	while(1){
		us i;
		int page;
		int seg;
		page=0;
		for(i=0;i<16;i++){
			setData_0(i,1);
			usleep(50000);
			setData_0(i,0);
			usleep(50000);
			printf("%d\n",i);
			draw_xy(30+i,30+i,1);
		}
		printf("Hello from Nios II!\n");
		PIO_0_DATA=0xFFFF;
		usleep(500000);
		PIO_0_DATA=0;
		clear();
		draw_screen(back_ground);
	}
  return 0;
}


