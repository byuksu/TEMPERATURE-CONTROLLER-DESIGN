#include "TM4C123GH6PM.h"
void SendData(unsigned long data) {
    
		SSI2->DR = data;	// Store data into SSI0_DR
		unsigned long temp1;	


    do {
        // Load SSI0_SR address into temp
				temp1 = SSI2->SR & 0x10;
        // looking to SSI Busy Bit
        // if it is zero the SSI is idle.
        // Wait until transmit is done
    } while ((temp1 & 0x10) == 0x10);

}