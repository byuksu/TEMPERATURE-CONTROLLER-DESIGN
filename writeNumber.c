#include "TM4C123GH6PM.h"
extern void SendData(unsigned long data);
void determineChar(int numberToBePrinted);
void writeNumber(double Temp, int y);

void writeNumber(double Temp, int y){
	int data, ones,tens,hundreds;
	data = (int) (Temp*10);
	hundreds=data/100;
	tens=(data-100*hundreds)/10;
	
	ones=data%10;
		
// Enable command mode
    GPIOB->DATA &= ~0x08; // Low for command mode PA7
		SendData(0x8f); // Setting X coordinate
	if(y==0){
    SendData(0x40); // Setting Y coordinate
} else if(y==1){
    SendData(0x42); // Setting Y coordinate
} else if(y==2){
    SendData(0x44); // Setting Y coordinate
}
    // Switch to data mode
    GPIOB->DATA |= 0x08; // High for data mode PA7
	
	determineChar(hundreds);
	determineChar(tens);
	SendData(0b10000000);
	determineChar(ones);
return;

}

void determineChar(int numberToBePrinted){
		switch (numberToBePrinted) {
    case 0:
						SendData(0x00);
						SendData(0x7C);
						SendData(0xA2);
						SendData(0x92);     //0
						SendData(0x8A);
						SendData(0x7C);
						SendData(0x00);
        break;
    case 1:
        SendData(0b00000000);
				SendData(0b00000000);
				SendData(0b10001000);
				SendData(0b10000100);
				SendData(0b11111110);   //1
				SendData(0b10000000);
				SendData(0b10000000);
				SendData(0b00000000);
        break;
    case 2:
        SendData(0x00);
				SendData(0x84);
				SendData(0xC2);
				SendData(0xA2);
				SendData(0x92);
				SendData(0x8C);
				SendData(0x00);
        break;
		case 3:
        SendData(0x00);
				SendData(0x44);
				SendData(0x82);
				SendData(0x92);
				SendData(0x92);
				SendData(0x6C);
				SendData(0x00);
        break;
		case 4:
        SendData(0x00);
				SendData(0x30);
				SendData(0x28);
				SendData(0x24);
				SendData(0xFE);
				SendData(0x20);
				SendData(0x00);
        break;
		case 5:
        SendData(0x00);
				SendData(0x5E);
				SendData(0x92);
				SendData(0x92);
				SendData(0x92);
				SendData(0x62);
				SendData(0x00);
        break;
		case 6:
        SendData(0x00);
				SendData(0x7C);
				SendData(0x92);
				SendData(0x92);
				SendData(0x92);
				SendData(0x64);
				SendData(0x00);
        break;
		case 7:
        SendData(0x00);
				SendData(0x02);
				SendData(0xE2);
				SendData(0x12);
				SendData(0x0A);
				SendData(0x06);
				SendData(0x00);
        break;
		case 8:
        SendData(0x00);
				SendData(0x6C);
				SendData(0x92);
				SendData(0x92);
				SendData(0x92);
				SendData(0x6C);
				SendData(0x00);
        break;
		case 9:
        SendData(0x00);
				SendData(0x4C);
				SendData(0x92);
				SendData(0x92);
				SendData(0x92);
				SendData(0x7C);
				SendData(0x00);
        break;
    default:
        return;
	}
}