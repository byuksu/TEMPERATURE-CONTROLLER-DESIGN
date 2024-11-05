#include "TM4C123GH6PM.h"
extern void SendData(unsigned long data);
void WriteText(void) {
    // Enable command mode
    GPIOB->DATA &= ~0x08; // Low for command mode PA7

    // X and Y addresses for the start of the text
    SendData(0x80); // Setting X coordinate
    SendData(0x40); // Setting Y coordinate

    // Switch to data mode
    GPIOB->DATA |= 0x08; // High for data mode PA7
	//LT:
	
		SendData(0xf8); 
    SendData(0x80); 
    SendData(0x80); // L
    SendData(0x80); 
    SendData(0x00); 
    SendData(0x00); 
	SendData(0x08);
	SendData(0x08); // T
		SendData(0b11111000); 
	SendData(0x08); 
	SendData(0x08);
	 SendData(0x00);
	 SendData(0b01010000);// :
	 

	 
	 //HT:
	 GPIOB->DATA &= ~0x08; // Low for command mode PA7

    // X and Y addresses for the start of the text
    SendData(0x80); // Setting X coordinate
    SendData(0x42); // Setting Y coordinate

    // Switch to data mode
    GPIOB->DATA |= 0x08; // High for data mode PA7
		
		SendData(0xf8); 
    SendData(0x20); 
    SendData(0x20); // H
    SendData(0xf8); 
    SendData(0x00); 
    SendData(0x00); 
	SendData(0x08);
	SendData(0x08); // T
		SendData(0b11111000); 
	SendData(0x08); 
	SendData(0x08);
	 SendData(0x00);
	 SendData(0b01010000);// :


	 	 GPIOB->DATA &= ~0x08; // Low for command mode PA7
     // X and Y addresses for the start of the text
    SendData(0x80); // Setting X coordinate
    SendData(0x44); // Setting Y coordinate

    // Switch to data mode
    GPIOB->DATA |= 0x08; // High for data mode PA7
		
				SendData(0xf8); 
    SendData(0x88); 
    SendData(0x88); // C
    SendData(0x88); 
    SendData(0x00); 
    SendData(0x00); 
	SendData(0x08);
	SendData(0x08); // T
		SendData(0b11111000); 
	SendData(0x08); 
	SendData(0x08);
	 SendData(0x00);
	 SendData(0b01010000);// :
	 
    
/*

    // R
    SendData(0xFE);
		SendData(0x12);
		SendData(0x32);
		SendData(0x52);
		SendData(0x8C);
		SendData(0x00);
	SendData(0x00);
	// B
SendData(0xFE);
SendData(0x92);
SendData(0x92);
SendData(0x92);
SendData(0x6C);
SendData(0x00);

	SendData(0x00);
	// I
SendData(0x82);
SendData(0xFE);
SendData(0x82);
SendData(0x00);

// F
SendData(0x00);
SendData(0xFE);
SendData(0x12);
SendData(0x12);
SendData(0x12);
SendData(0x02);
SendData(0x00);
// U
SendData(0x00);
SendData(0x7E);
SendData(0x80);
SendData(0x80);
SendData(0x7E);
SendData(0x00);
// C
SendData(0x00);
SendData(0x7E);
SendData(0x82);
SendData(0x82);
SendData(0x44);
SendData(0x00);
// K
SendData(0x00);
SendData(0xFE);
SendData(0x08);
SendData(0x14);
SendData(0x22);
SendData(0xC0);
SendData(0x00);

	SendData(0x00);
		SendData(0x00);
			SendData(0x00);
				SendData(0x00);
					SendData(0x00);
						SendData(0x00);

// O
SendData(0b00011000);
SendData(0b00100100);
SendData(0b01000010);
SendData(0b01000010);
SendData(0b01000010);
SendData(0b00100100);
SendData(0b00011000);
SendData(0x00);
    
// F
SendData(0x00);
SendData(0xFE);
SendData(0x12);
SendData(0x12);
SendData(0x12);
SendData(0x02);
SendData(0x00);
// F
SendData(0x00);
SendData(0xFE);
SendData(0x12);
SendData(0x12);
SendData(0x12);
SendData(0x02);
SendData(0x00);
*/
}
