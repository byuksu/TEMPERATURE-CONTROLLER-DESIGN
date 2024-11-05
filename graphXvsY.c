#include "TM4C123GH6PM.h"


extern void SendData(unsigned long data);	
extern void delay(int n);
//extern void clear(void);
extern void graphXY(void);
extern void WriteText(void) ;

extern void clearGraph(void);

void graphXvsY(float *Temp){
	clearGraph();
	
	for(int i=0;i<30;i++){
		
	int bank=(int)(Temp[i]/8+1);
	if(bank>6){
		return;
	}
	
	int pixels=(int)Temp[i];
	pixels=pixels%8;
    GPIOB->DATA &= ~0x08; // Low for command mode PA7
    // Set position for smiley face
    SendData(171+i); // Setting X coordinate 0 to 83
	
    SendData(0x40-bank+6); // Setting Y coordinate 0 to 5

    // Enable data mode
    GPIOB->DATA |= 0x08; // High for data mode PA7
		if(pixels==0&&bank==1){
		SendData(0b00010000);
		} else if(pixels==1&&bank==1){
		SendData(0b00011000);
		} else if(pixels==2&&bank==1){
		SendData(0b00010100);
		} else if(pixels==3&&bank==1){
		SendData(0b00010010);
		} else if(pixels==4&&bank==1){
		SendData(0b00010001);
		} else if(pixels==0&&bank==2){
		SendData(0b10000000);
		} else if(pixels==1&&bank==2){
		SendData(0b01000000);
		} else if(pixels==2&&bank==2){
		SendData(0b00100000);
		} else if(pixels==3&&bank==2){
		SendData(0b00010000);
		} else if(pixels==4&&bank==2){
		SendData(0b00001000);
		} else if(pixels==5&&bank==2){
		SendData(0b00000100);
		} else if(pixels==6&&bank==2){
		SendData(0b00000010);
		} else if(pixels==7&&bank==2){
		SendData(0b00000001);
		} else if(pixels==0&&bank==3){
		SendData(0b10000000);
		} else if(pixels==1&&bank==3){
		SendData(0b01000000);
		} else if(pixels==2&&bank==3){
		SendData(0b00100000);
		} else if(pixels==3&&bank==3){
		SendData(0b00010000);
		} else if(pixels==4&&bank==3){
		SendData(0b00001000);
		} else if(pixels==5&&bank==3){
		SendData(0b00000100);
		} else if(pixels==6&&bank==3){
		SendData(0b00000010);
		} else if(pixels==7&&bank==3){
		SendData(0b00000001);
		} else if(pixels==0&&bank==4){
		SendData(0b10000000);
		} else if(pixels==1&&bank==4){
		SendData(0b01000000);
		} else if(pixels==2&&bank==4){
		SendData(0b00100000);
		} else if(pixels==3&&bank==4){
		SendData(0b00010000);
		} else if(pixels==4&&bank==4){
		SendData(0b00001000);
		} else if(pixels==5&&bank==4){
		SendData(0b00000100);
		} else if(pixels==6&&bank==4){
		SendData(0b00000010);
		} else if(pixels==7&&bank==4){
		SendData(0b00000001);
		} else if(pixels==0&&bank==5){
		SendData(0b10000000);
		} else if(pixels==1&&bank==5){
		SendData(0b01000000);
		} else if(pixels==2&&bank==5){
		SendData(0b00100000);
		} else if(pixels==3&&bank==5){
		SendData(0b00010000);
		} else if(pixels==4&&bank==5){
		SendData(0b00001000);
		} else if(pixels==5&&bank==5){
		SendData(0b00000100);
		} else if(pixels==6&&bank==5){
		SendData(0b00000010);
		} else if(pixels==7&&bank==5){
		SendData(0b00000001);
		}

		else if(pixels==0&&bank==6){
		SendData(0b10000000);
		} else if(pixels==1&&bank==6){
		SendData(0b01000000);
		} else if(pixels==2&&bank==6){
		SendData(0b00100000);
		} else if(pixels==3&&bank==6){
		SendData(0b00010000);
		} else if(pixels==4&&bank==6){
		SendData(0b00001000);
		} else if(pixels==5&&bank==6){
		SendData(0b00000100);
		} else if(pixels==6&&bank==6){
		SendData(0b00000010);
		} else if(pixels==7&&bank==6){
		SendData(0b00000001);
		}
	}
delay(1000);
}