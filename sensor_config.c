#include "sensor_config.h"
#include <TM4C123GH6PM.h>

void sensorConfig(void){
	//Enable Port A & I2C  Clock
	SYSCTL->RCGCGPIO |= (1<<0);
	SYSCTL->RCGCI2C |= (1<<1);
	__ASM("NOP");
	__ASM("NOP");
	__ASM("NOP");
	
	//Enable PA6 & PA7 digitally
	GPIOA->DEN |= (1<<6)|(1<<7);
	
	//Set alternate functions for PA6 & PA7
	GPIOA->AFSEL |=(1<<6)|(1<<7);
	
	//Set port control registers for PA6 & PA7 accordingly 
	GPIOA->PCTL &= ~((15<<24)|(15<<28));
	GPIOA->PCTL |= (3<<24)|(3<<28);

	
	//Enable Open-Drain for PA7
	GPIOA->ODR |= (1<<7);
	//GPIOA->PUR |= (1<<7);
	
	//Initialize I2C Master
	I2C1->MCR = 0x00000010;
	
	//Set I2CMTPR based on the following equation
	/* TPR = (SYSTEM_CLOCK/(2*(SCL_HP + SCL_LP)*SCL_CLK))-1
		 TPR = 48MHz/(100000*20)-1 = 23
	*/
	I2C1->MTPR=0x00000017;
}