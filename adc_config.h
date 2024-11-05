#include <TM4C123GH6PM.h>

void ADCConfig(void);

void ADCConfig(void){
	SYSCTL->RCGCADC		|=(1<<0);	 	//Enable Clock for the ADC0 
	SYSCTL->RCGCGPIO	|=(1<<4);	 	//Activate clock for the GPIOE
	__ASM("NOP");
	__ASM("NOP");
	__ASM("NOP");
	GPIOE->AFSEL			|=(1<<3);   //PE3 is configured to be used for its alternate function
	GPIOE->AMSEL			|=(1<<3);		//Enable the analog functionality
	ADC0->ACTSS				&=~(1<<3);		//Disable SS3 for configuration
	ADC0->EMUX				&=~(15<<12);//Disable EM3, for software triggering
	ADC0->SSMUX3			&=~(15<<0);	//Clear the bitfield corresponding to MUX0 and write nothing to wait for AIN0
	//ADC0->SSMUX3			|=(1<<3)|(1<<1);		//Write 10 for AIN0
///////////Q4
	//ADC0->SSCTL3			|=(1<<2)|(1<<1);		//set IE0 and IEND0  (For Q4 clear END0)
///////////////
	ADC0->SSCTL3			|=(1<<2);		//set IE0 to show RIS 
	ADC0->PC					|=(1<<0);		//SET FOR 125kSps
	
	//ADC0->ACTSS				|=(1<<3);		//Enable ADC
	//ADC0->PSSI				|=(1<<3);		//start sampling

}