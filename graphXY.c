#include "TM4C123GH6PM.h"
extern void SendData(unsigned long data);	
void graphXY(void){
	//origin x=0x85
	//			 y=0x45
	
	// Enable command mode
    GPIOB->DATA &= ~0x08; // Low for command mode PA7
    // Set position for smiley face
    SendData(165); // Setting X coordinate 0 to 83
    SendData(0x40); // Setting Y coordinate 0 to 5

    // Enable data mode
    GPIOB->DATA |= 0x08; // High for data mode PA7

	// yline
SendData(0b00000000);
SendData(0b00000000);
SendData(0b01000000);
SendData(0b00100000);
SendData(0b00010000);
SendData(0b11111000);
SendData(0b00010000);
SendData(0b00100000);
SendData(0b01000000);
// T
SendData(0b00000000);
SendData(0b00000010);
SendData(0b00000010);
SendData(0b01111110);
SendData(0b00000010);
SendData(0b00000010);


// E
SendData(0b00000000);
SendData(0b01111110);
SendData(0b01001010);
SendData(0b01001010);
SendData(0b01001010);
SendData(0b01000010);

// M
SendData(0b00000000);
SendData(0b01111110);
SendData(0b00000100);
SendData(0b00001000);
SendData(0b00000100);
SendData(0b01111110);

// P
SendData(0b00000000);
SendData(0b01111110);
SendData(0b00010010);
SendData(0b00010010);
SendData(0b00010010);
SendData(0b00001100);
SendData(0b00000000);
SendData(0b10000000);
SendData(0b01100000);
// T
SendData(0b00000000);
SendData(0b00000010);
SendData(0b00000010);
SendData(0b01111110);
SendData(0b00000010);
SendData(0b00000010);

	// y
	/*
SendData(0b00000000);
SendData(0b00000000);
SendData(0b00000000);
SendData(0b00000100);
SendData(0b00001000);
SendData(0b01110000);
SendData(0b00001000);
SendData(0b00000100);
SendData(0b00000000);
*/		// Enable command mode
    GPIOB->DATA &= ~0x08; // Low for command mode PA7
    // Set position for smiley face
    SendData(165); // Setting X coordinate 0 to 83
    SendData(0x41); // Setting Y coordinate 0 to 5

    // Enable data mode
    GPIOB->DATA |= 0x08; // High for data mode PA7

// yline
SendData(0b00000000);
SendData(0b00000000);
SendData(0b00000000);
SendData(0b00000000);
SendData(0b00000000);
SendData(0b11111111);
		// Enable command mode
    GPIOB->DATA &= ~0x08; // Low for command mode PA7
    // Set position for smiley face
    SendData(165); // Setting X coordinate 0 to 83
    SendData(0x42); // Setting Y coordinate 0 to 5

    // Enable data mode
    GPIOB->DATA |= 0x08; // High for data mode PA7
// yline
SendData(0b00000000);
SendData(0b00000000);
SendData(0b00000000);
SendData(0b00000000);
SendData(0b00000000);
SendData(0b11111111);
// Enable command mode
    GPIOB->DATA &= ~0x08; // Low for command mode PA7
    // Set position for smiley face
    SendData(165); // Setting X coordinate 0 to 83
    SendData(0x43); // Setting Y coordinate 0 to 5

    // Enable data mode
    GPIOB->DATA |= 0x08; // High for data mode PA7
// yline
SendData(0b00000000);
SendData(0b00000000);
SendData(0b00000000);
SendData(0b00000000);
SendData(0b00000000);
SendData(0b11111111);
// Enable command mode
    GPIOB->DATA &= ~0x08; // Low for command mode PA7
    // Set position for smiley face
    SendData(165); // Setting X coordinate 0 to 83
    SendData(0x44); // Setting Y coordinate 0 to 5

    // Enable data mode
    GPIOB->DATA |= 0x08; // High for data mode PA7
// yline
SendData(0b00000000);
SendData(0b00000000);
SendData(0b00000000);
SendData(0b00000000);
SendData(0b00000000);
SendData(0b11111111);
// Enable command mode
    GPIOB->DATA &= ~0x08; // Low for command mode PA7
    // Set position for smiley face
    SendData(165); // Setting X coordinate 0 to 83
    SendData(0x45); // Setting Y coordinate 0 to 5

    // Enable data mode
    GPIOB->DATA |= 0x08; // High for data mode PA7
// yline
SendData(0b00000000);
SendData(0b00000000);
SendData(0b00000000);
SendData(0b00000000);
SendData(0b00000000);
SendData(0b00011111);

// Enable command mode
    GPIOB->DATA &= ~0x08; // Low for command mode PA7
    // Set position for smiley face
    SendData(198); // Setting X coordinate 0 to 83
    SendData(0x44); // Setting Y coordinate 0 to 5

    // Enable data mode
    GPIOB->DATA |= 0x08; // High for data mode PA7
		SendData(0b00000000);
		SendData(0b00001000);
		SendData(0b00001000);
		SendData(0b11111110);
		SendData(0b10001000);
		SendData(0b01001000);
		SendData(0b00000000);
		SendData(0b10000000);
		SendData(0b01100000);
		SendData(0b00000000);
		SendData(0b01000100);
		SendData(0b10001010);
		SendData(0b10010010);
		SendData(0b01100100);
		
/*
// x
SendData(0b00000000);
SendData(0b01111110);
SendData(0b00000100);
SendData(0b00001000);
SendData(0b00000100);
SendData(0b01111110);
*/
// Enable command mode
    GPIOB->DATA &= ~0x08; // Low for command mode PA7
    // Set position for smiley face
    SendData(170); // Setting X coordinate 0 to 83
    SendData(0x45); // Setting Y coordinate 0 to 5

    // Enable data mode
    GPIOB->DATA |= 0x08; // High for data mode PA7
// xline
SendData(0b00001111);
for(int i=0;i<35;i++)
SendData(0b00010000);
SendData(0b10010010);
SendData(0b01010100);
SendData(0b00111000);
SendData(0b00010000);


}