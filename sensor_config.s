SYSCTL		EQU		0x400FE000
SysTick		EQU		0xE000E000
STCTRL		EQU		0x010
STRELOAD	EQU		0x014
STCURRENT	EQU		0x018
RCGCGPIO	EQU		0x608
RCGCI2C		EQU		0x620
GPIOA		EQU		0x40004000
DEN			EQU		0x51C
AFSEL		EQU		0x420
PCTL		EQU		0x52C
AMSEL		EQU		0x528
ODR			EQU		0x50C
PUR			EQU		0x510
I2C1		EQU		0x40021000
MCAR		EQU		0x020
MDR			EQU		0x008
MTPR		EQU		0x00C
MSA			EQU		0x000
MCS			EQU		0x004

	
            AREA        sdata, DATA, READONLY
            THUMB

;***************************************************************
; Program section                         
;***************************************************************
;LABEL      DIRECTIVE   VALUE       COMMENT
            AREA        main, READONLY, CODE
            THUMB
            ;EXTERN      OutStr      ; Reference external subroutine 
            EXPORT      sensorConfig      ; Make available

sensorConfig 
			;Enable Clock for GPIOA
			LDR	R0, =(SYSCTL+RCGCGPIO)
			LDR	R1,[R0]
			ORR	R1,#1
			STR	R1,[R0]
			
			;Enable clock for I2C1
			LDR	R0,=(SYSCTL+RCGCI2C)
			LDR	R1,[R0]
			ORR	R1,#0x2
			STR	R1,[R0]
			
			;For clock stabilization
			NOP
			NOP
			NOP
			
			;Enable Port A6 & A7
			LDR	R0,=(GPIOA+DEN)
			LDR	R1,[R0]
			ORR	R1,#0xC0
			STR	R1,[R0]
			
			;Choose Alternate function for Port A6 & A7
			LDR	R0,=(GPIOA+AFSEL)
			LDR	R1,[R0]
			ORR	R1,#0xC0
			STR	R1,[R0]
			
			;Disable Analog Functionality
			LDR	R0,=(GPIOA+AMSEL)
			LDR	R1,[R0]
			AND	R1,#0x0
			STR	R1,[R0]
			
			;Adjust associated bir fields for PA6 & PA7 for I2C comm
			LDR	R0,=(GPIOA+PCTL)
			LDR	R1,[R0]
			AND	R1,#0x00FFFFFF
			ORR	R1,#0x33000000
			STR	R1,[R0]
			
			;Configure PA7 (SDA) as open-drain
			LDR	R0,=(GPIOA+ODR)
			LDR	R1,[R0]
			ORR	R1,#0x80
			STR	R1,[R0]
			
			;LDR	R0,=(GPIOA+PUR)
			;LDR	R1,[R0]
			;ORR	R1,#0x80
			;STR	R1,[R0]
			
			;Enable master 
			LDR	R0,=(I2C1+MCAR)
			LDR	R1,=0x00000010
			STR	R1,[R0]
			
			;Adjust clock for 400kHz
			LDR	R0,=(I2C1+MTPR)
			LDR	R1,=0x5
			STR	R1,[R0]
			
			BX LR
			ENDP
            ALIGN
            END