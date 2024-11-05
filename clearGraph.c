#include "TM4C123GH6PM.h"
extern SendData(unsigned long data);
void clearGraph(void){
   
	// Enable command mode
    GPIOB->DATA &= ~0x08; // Low for command mode PB3
    
    SendData(171);// Setting X coordinate
    SendData(0x41); // Setting Y coordinate

    // Enable data mode
    GPIOB->DATA |= 0x08; // High for data mode PB3
    
	for(int i=0;i<30;i++){
    SendData(0b00000000);
		}
	    GPIOB->DATA &= ~0x08; // Low for command mode PB3
    
    SendData(171);// Setting X coordinate
    SendData(0x42); // Setting Y coordinate

    // Enable data mode
    GPIOB->DATA |= 0x08; // High for data mode PB3
    
	for(int j=0;j<30;j++){
    SendData(0b00000000);
		}
	       GPIOB->DATA &= ~0x08; // Low for command mode PB3
    
    SendData(171);// Setting X coordinate
    SendData(0x43); // Setting Y coordinate

    // Enable data mode
    GPIOB->DATA |= 0x08; // High for data mode PB3
    
	for(int k=0;k<30;k++){
    SendData(0b00000000);
		}
	       GPIOB->DATA &= ~0x08; // Low for command mode PB3
    
    SendData(171);// Setting X coordinate
    SendData(0x44); // Setting Y coordinate

    // Enable data mode
    GPIOB->DATA |= 0x08; // High for data mode PB3
    
	for(int l=0;l<30;l++){
    SendData(0b00000000);
		}
	   
	       GPIOB->DATA &= ~0x08; // Low for command mode PB3
    
    SendData(171);// Setting X coordinate
    SendData(0x45); // Setting Y coordinate

    // Enable data mode
    GPIOB->DATA |= 0x08; // High for data mode PB3
    
	for(int m=0;m<30;m++){
    SendData(0b00010000);
		}
	   
	
}