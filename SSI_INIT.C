#include "TM4C123GH6PM.h"
extern SendData(unsigned long data);
extern void delay(int n);
void SSI_INIT(void) {
	//GPIO Configuration:

    SYSCTL->RCGCGPIO|= 0x02; // turn on bus clock for GPIOB
		__ASM("NOP");
		__ASM("NOP");
		__ASM("NOP");
		GPIOB->DEN|= 0xFC;
		GPIOB->DIR|= 0xBC;
		GPIOB->AFSEL|= 0xF0;
		GPIOB->PCTL= 0x22220000;
	//SPI Configuration:
		SYSCTL->RCGCSSI|= 0x04;   //Enable the clock for SSI2
		unsigned long temp;	
    do{
        temp = SYSCTL->PRSSI;
    } while ((temp & 0x04) != 0x04); //Wait for the SSI2 peripheral to be ready

		SSI2->CR1=0x00;	//Disable the SPI interface (CR1)
		SSI2->CPSR=0x02;	//Set the clock rate of the SPI Clock CPSR
		SSI2->CR0=0x09C7;	//Set the clock rate of the SPI Clock CR0
		//	SCR=9
		//	data size is 8-bits
		//	Freescale mode 
		
		SSI2->CC=0x05; //	PIOSC 
		SSI2->CR1|= 0x02; //SSI operation is enabled.
    __asm("NOP");
    __asm("NOP");
    __asm("NOP");
    __asm("NOP");
    __asm("NOP");
    __asm("NOP");

    // NOKIA 5110 Configuration:
		GPIOB->DATA &= 0xFFFFFFFB;	// Low for reset connected to PB2
    delay(200);
		//for(int i=0; i<2500000;i++);
		GPIOB->DATA |= 0x04;	// High for reset connected to PB2
		//Set H=1 for Extended Command Mode, V=0 for Horizontal Addressing
		GPIOB->DATA &= 0xFFFFFFF7;	// low PB3, enable command mode
		SendData(0x21);	// H=1 Extended command mode activated
		SendData(0xBF);	// Voltage Operation (Vop)
		SendData(0x05);	// Temperature is set as upper limit
		SendData(0x13);	//  Set voltage bias value as 0x13
		SendData(0x20);	// H=0 basic command mode is activated
		SendData(0x0C);	// normal mode is activated
		SendData(0x80);	// setting position X = 0
		SendData(0x40);	// setting position Y = 0
		GPIOB->DATA |= 0x08;	// High for data mode PB3
}

