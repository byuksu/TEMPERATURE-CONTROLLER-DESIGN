/*Pulse_init.h file
Function for creating a pulse train using interrupts
Uses Channel 0, and a 1Mhz Timer clock (_TAPR = 15)
Uses Timer0A to create pulse train on PF2
*/

#include "TM4C123GH6PM.h"
void timerConfig(void);
void pushButtonConfig(void);

void timerConfig(void){
	volatile int *NVIC_EN0 					= (volatile int*) 0xE000E100;
	volatile int *NVIC_PRI4 				= (volatile int*) 0xE000E410;
	
	SYSCTL->RCGCTIMER							 |=0x01; // Start timer0
	__ASM("NOP");
	__ASM("NOP");
	__ASM("NOP");
	TIMER0->CTL							 			 &=0xFFFFFFFE; //Disable timer during setup
	TIMER0->CFG											=0x04;  //Set 16 bit mode
	TIMER0->TAMR										=0x02; // set to periodic, count down
	TIMER0->TAILR										=2400000; //Set interval
	TIMER0->IMR											=0x01; //Enable timeout intrrupt	
	
	//Timer0A is interrupt 19
	//Interrupt 16-19 are handled by NVIC register PRI4
	//Interrupt 19 is controlled by bits 31:29 of PRI4
	*NVIC_PRI4 										 &=0x00FFFFFF; //Clear interrupt 19 priority
	*NVIC_PRI4 										 |=0xC0000000; //Set interrupt 19 priority to 6
	//NVIC has to be neabled
	//Interrupts 0-31 are handled by NVIC register EN0
	//Interrupt 19 is controlled by bit 19
	*NVIC_EN0										   |=(1<<19);
	
	//Enable timer
	TIMER0->CTL									   |=0x03; // bit0 to enable and bit 1 to stall on debug
}

void pushButtonConfig(void){
	volatile int *NVIC_EN0 					= (volatile int*) 0xE000E100;
	volatile int *NVIC_PRI7 				= (volatile int*) 0xE000E41C;
	
	SYSCTL->RCGCGPIO 							 |= 0x20; // turn on bus clock for GPIOF
	GPIOF->LOCK											=0x4C4F434B;	//Unlock the GPIOF
	GPIOF->CR 											= 0x01;		//Enable Configuration
	__ASM("NOP");
	__ASM("NOP");
	__ASM("NOP");
	//Port Configuration
	GPIOF->DEN    						  	 |= (1<<3)|(1<<0)|(1<<4)|(1<<2)|(1<<1);  // Enable PF3 & PF0 & PF4 pin as a digital pin 
  GPIOF->AFSEL		 								= 0;  // Regular port function
	GPIOF->PCTL			 								= 0;  // No alternate function
	GPIOF->AMSEL		 								= 0; //Disable analog

	GPIOF->DIR       							 |= (1<<3)|(1<<1)|(1<<2); //set GREEN & BLUE & RED pin as a digital output pin
	///Interrupt Configuration
	GPIOF->IS											 &=~((1<<0)|(1<<4));			//edge sensitive
	GPIOF->IBE										 &=~((1<<0)|(1<<4));	//not both edges
	GPIOF->IEV										 &=~((1<<0)|(1<<4));	//low level
	GPIOF->IM 										 |= (1<<4)|(1<<0);		//Enable interrupt
	GPIOF->PUR										 |=(1<<0)|(1<<4);			//Enable Pull-up
	GPIOF->DATA										 |=8;
	GPIOF->ICR |= (1<<0)|(1<<4);
	
	*NVIC_PRI7 										 &=~(0xFF<<16); //Clear interrupt 30 priority  //Set interrupt 30 priority to 0
	//NVIC has to be neabled
	//Interrupts 0-31 are handled by NVIC register EN0
	//Interrupt 19 is controlled by bit 19
	*NVIC_EN0					 |=(1<<30);
}


