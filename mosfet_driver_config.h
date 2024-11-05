#include <TM4C123GH6PM.h>


void mosfetDriverConfig(void);

void mosfetDriverConfig(void){
	GPIOA->DEN    						  	 |= (1<<2)|(1<<3);  // Enable PF3 & PF0 & PF4 pin as a digital pin 
  GPIOA->AFSEL		 								= 0;  // Regular port function
	GPIOA->DIR       							 |= (1<<2)|(1<<3); //set GREEN & BLUE & RED pin as a digital output pin
	GPIOA->DATA										 &= ~((1<<2)|(1<<3));
}