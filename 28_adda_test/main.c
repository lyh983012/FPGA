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

int main()
{
	initPIO();
	while(1){
		us i;
		for(i=1;i<16;i++){
			usleep(500000);
			setData_0(i,1);
			setData_0(i-1,0);
			usleep(500000);
		}
		printf("Hello from Nios II!\n");
		PIO_0_DATA=0xFFFF;
		usleep(500000);
		PIO_0_DATA=0;
	}
  return 0;
}
