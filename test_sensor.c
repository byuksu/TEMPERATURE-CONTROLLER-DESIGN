#include <TM4C123GH6PM.h>
#include <string.h>

#include "pulse_green.h"
#include "adc_config.h"
//#include "mosfet_driver_config.h"

//#include "SSI_INIT.C"
//#include "clear.c"
//#include "delay.C"
//#include "graphXY.c"
//#include "SendData.c"


#define temperatureAddressMSB 	0xFA
#define dig_T1									0x88
#define	dig_T2									0x8A
#define dig_T3									0x8C
#define	maxTemperature					50.0f
#define minTemperature					0.0f

signed int temperatureArray[128];
float temperatureInCelsiusArray[30];
signed int adcData=0;
unsigned int preADCData=0;
unsigned short dig_T1Data=0;
short					 dig_T2Data=0;
short					 dig_T3Data=0;
signed long	totalOf128=0;
double var1;
double var2;
double temperature;
double temperatureinCelsius;
double lowTreshold=0.0;
double highTreshold=0.0;
unsigned int ADCInputLow=0;
unsigned int ADCInputHigh=0;
unsigned int temperatureinInputFormat=0;
int index=0;
int isFull=0;

void SysTick_Handler(void);
void TIMER0A_Handler (void);
void GPIOF_Handler (void);

extern unsigned int getSlaveId(void);
extern void sensorConfig(void);
extern void resetSensor(void);
extern unsigned int readSensorFromGivenAddress(int address, int dataLength);
extern void configureSensor(void);
void measureTemperature(void);
float calculateCelsiusEquivalentofSensor(signed long data);

extern void writeNumber(double Temp, int y);
extern void SSI_INIT(void);
extern void delay(int n);
extern void SendData(unsigned long data);	
extern void WriteText(void) ;
extern void clear(void);
extern void graphXY(void);
extern void graphXvsY(int *Temp);

int main(void){
	SSI_INIT();
	clear();
	WriteText();
	graphXY();
	sensorConfig();
	configureSensor();
	dig_T1Data=readSensorFromGivenAddress(dig_T1,2);
	dig_T2Data=readSensorFromGivenAddress(dig_T2,2);
	dig_T3Data=readSensorFromGivenAddress(dig_T3,2);
	for(int i=0;i<128;i++){
		adcData=readSensorFromGivenAddress(temperatureAddressMSB,3)>>4;
		
		temperatureArray[i]=adcData;
		totalOf128+=adcData;
	}
	
	timerConfig();
	pushButtonConfig();
	ADCConfig();
	
	SysTick->LOAD=250000;
	SysTick->VAL=0;
	SysTick->CTRL|=0x7;
	//mosfetDriverConfig();
	while(1){
		//writeNumber(lowTreshold,0);
		//writeNumber(highTreshold,1);
		
	}
}

float calculateCelsiusEquivalentofSensor(signed long data){
	var1=((data*1.0)/(16384.0)-(dig_T1Data*1.0)/1024.0)*(dig_T2Data*1.0);
	var2=(((data*1.0)/(131072.0)-(dig_T1Data*1.0)/8192.0)*((data*1.0)/(131072.0)-(dig_T1Data*1.0)/8192.0))*(dig_T3Data*1.0);
	temperature=(var1+var2)/2;
	temperatureinCelsius=temperature/5120.0;
	temperatureinInputFormat = (unsigned int)((temperatureinCelsius / 50.0f) * 0xFFF);
	return temperatureinCelsius;
}

void measureTemperature(void){
	adcData=readSensorFromGivenAddress(temperatureAddressMSB,3)>>4;
		totalOf128+=adcData;
		totalOf128-=temperatureArray[1];
		memmove(temperatureArray, temperatureArray + 1, 127 * sizeof(signed int));	
		temperatureArray[127]=adcData;
		if(index==30){
			index--;
			memmove(temperatureInCelsiusArray,temperatureInCelsiusArray+1,30*sizeof(float));
			
		}else{
			temperatureInCelsiusArray[index++]=calculateCelsiusEquivalentofSensor(totalOf128/128);
		}
}

void SysTick_Handler(void){      ///PA3: Heater			PA2:Cooler
	if(ADCInputHigh>0){
		if((ADCInputHigh-temperatureinInputFormat)>0xFFF){
				SysTick->LOAD=250000;
				GPIOF->DATA&=~((1<<3)|(1<<1));
				GPIOF->DATA|=(1<<2);
				GPIOA->DATA&=~(1<<3);
				GPIOA->DATA |= (1<<2);
		}else if((temperatureinInputFormat-ADCInputLow)>0xFFF){
			SysTick->LOAD=250000;
			GPIOF->DATA&=~((1<<3)|(1<<2));
			GPIOF->DATA|=(1<<1);
			GPIOA->DATA&=~(1<<2);
			GPIOA->DATA |= (1<<3);
		}else{
			GPIOA->DATA &=~((1<<2)|(1<<3));
			GPIOF->DATA &= ~((1<<2)|(1<<1));
			if(GPIOF->DATA & 0x8){
					SysTick->LOAD=ADCInputHigh-temperatureinInputFormat;
					GPIOF->DATA &=~(1<<3);
			}else{
					SysTick->LOAD=temperatureinInputFormat-ADCInputLow;
					GPIOF->DATA|=(1<<3);
			}
		}
	}
	
	return;
}

void TIMER0A_Handler (void){
	measureTemperature();
	writeNumber(temperatureinCelsius,2);
	graphXvsY(temperatureInCelsiusArray);
}

void GPIOF_Handler (void){
	ADC0->ACTSS				|=(1<<3);		//Enable ADC
	ADC0->PSSI				|=(1<<3);		//start sampling
	if(GPIOF->DATA & 0x1){
		while((GPIOF->DATA & 0x10)!=0x10);
		while(GPIOF->DATA & 0x10){
			ADCInputLow=ADC0->SSFIFO3;
			lowTreshold = (double)(ADCInputLow * (50.0 / 0xFFF));
			writeNumber(lowTreshold,0);
		}
	}else{
		while((GPIOF->DATA & 0x1)!=0x1);
		while(GPIOF->DATA & 0x1){
			ADCInputHigh=ADC0->SSFIFO3;
			 highTreshold= (double)(ADCInputHigh * (50.0 / 0xFFF));
			writeNumber(highTreshold,1);
		}
	}
	GPIOF->ICR |= (1<<0)|(1<<4);
	for(int i=0; i<100000;i++);
}
