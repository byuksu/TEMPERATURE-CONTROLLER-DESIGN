I2C1				EQU		0x40021000
MCAR				EQU		0x020
MDR					EQU		0x008
MTPR				EQU		0x00C
MSA					EQU		0x000
MCS					EQU		0x004
	
slaveAddress		EQU		0x77
slaveId				EQU		0xD0
resetAddress		EQU		0xE0
resetData			EQU		0xB6
ctrl_meas			EQU		0xF4
config				EQU		0xF5

	
            AREA        sdata, DATA, READONLY
            THUMB
;***************************************************************
; Program section                         
;***************************************************************
;LABEL      DIRECTIVE   VALUE       COMMENT
            AREA        main, READONLY, CODE
            THUMB 
            EXPORT      getSlaveId      ; Make available

getSlaveId
			;Write slave address for start of I2C and transmit mode
			LDR	R3,=(I2C1+MSA)
			LDR	R1,=slaveAddress
			LSL	R1,#1
			STR	R1,[R3]
			
			;Write address from which data will be read
			LDR	R3,=(I2C1+MDR)
			LDR	R1,=slaveId
			STR	R1,[R3]
			
			;START - RUN - STOP
			LDR	R3,=(I2C1+MCS)
			LDR	R1,=0x3
			STR	R1,[R3]
			
			PUSH	{LR}
			BL	waitResponse
			POP{LR}
			
			;configure for receive
			LDR	R3,=(I2C1+MSA)
			LDR R1,=slaveAddress
			LSL	R1,#1
			ADD	R1,#1
			STR	R1,[R3]
			
			;it is tested and determined to be required for the stable communication 
			LDR	R2,=100000
delay		SUBS R2,#1
			BNE	delay
			
			;START - RUN - STOP
			LDR	R3,=(I2C1+MCS)
			LDR R1,=0x7
			STR	R1,[R3]
			
			PUSH	{LR}
			BL waitResponse
			POP		{LR}
			
			LDR	R1,=(I2C1+MDR)
			LDR	R0,[R1]
						
			BX LR
			ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;				

			EXPORT      resetSensor      ; Make available
resetSensor
			;Write slave address for start of I2C and transmit mode
			LDR	R3,=(I2C1+MSA)
			LDR	R1,=slaveAddress
			LSL	R1,#1
			STR	R1,[R3]
			
			;Write address from which data will be read
			LDR	R3,=(I2C1+MDR)
			LDR	R1,=resetAddress
			STR	R1,[R3]
			
			;START - RUN 
			LDR	R3,=(I2C1+MCS)
			LDR	R1,=0x3
			STR	R1,[R3]
			
			;wait master to finish sending
			PUSH	{LR}
			BL	waitResponse
			POP		{LR}
			
			PUSH	{LR}
			BL	delay2ms
			POP		{LR}
			
			;configure for receive
			LDR	R3,=(I2C1+MDR)
			LDR R1,=resetData
			STR	R1,[R3]
			
			;RUN - STOP
			LDR	R3,=(I2C1+MCS)
			LDR R1,=0x5
			STR	R1,[R3]
			
			PUSH	{LR}			
			BL waitResponse
			POP		{LR}
			
			BX LR
			ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

			EXPORT      readSensorFromGivenAddress      ; Make available
readSensorFromGivenAddress
;;		r5: Register Address     r6: Data long to be received

			MOV	R5,R0
			MOV	R6,R1
			
			;Write slave address for start of I2C and transmit mode
			LDR	R3,=(I2C1+MSA)
			LDR	R1,=slaveAddress
			LSL	R1,#1
			STR	R1,[R3]
			
			;Write address from which data will be read
			LDR	R3,=(I2C1+MDR)
			MOV	R1,R5
			STR	R1,[R3]
			
			;START - RUN - STOP
			LDR	R3,=(I2C1+MCS)
			LDR	R1,=0x3
			STR	R1,[R3]
			
			;check 
			PUSH	{LR}			
			BL waitResponse
			POP		{LR}
			
			;configure for receive
			LDR	R3,=(I2C1+MSA)
			LDR R1,=slaveAddress
			LSL	R1,#1
			ADD	R1,#1
			STR	R1,[R3]
			
			PUSH	{LR}
			BL	delay2ms
			POP		{LR}
			
			LDR	R3,=(I2C1+MCS)
			LDR	R1,=0xB
			STR	R1,[R3]
			
			MOV	R0,#0
			
			PUSH	{LR}			
			BL waitResponse
			POP		{LR}
			
			LDR	R1,=(I2C1+MDR)
			LDR	R2,[R1]
			;;Store the data to associated bits
			ORR	R0,R2
			
			SUBS	R6,#1
			
AGAIN		PUSH	{LR}
			BL	delay2ms
			POP		{LR}
			
			LSL	R0,#8
			
			;START - RUN - STOP
			LDR	R3,=(I2C1+MCS)
			SUBS R6,#1
			ADD	R6,#1
			BNE	ACK
			LDR	R1,=0x5
			B NACK
ACK			LDR R1,=0x9
			
NACK		STR	R1,[R3]
			
			PUSH	{LR}			
			BL waitResponse
			POP		{LR}
			
			LDR	R1,=(I2C1+MDR)
			LDR	R2,[R1]
			;;Store the data to associated bits
			ORR	R0,R2
			
			SUBS R6,#1
			BNE	AGAIN
			
			BX LR
			ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

			EXPORT      configureSensor      ; Make available
configureSensor
;Write slave address for start of I2C and transmit mode
			LDR	R3,=(I2C1+MSA)
			LDR	R1,=slaveAddress
			LSL	R1,#1
			STR	R1,[R3]
			
			;Write address from which data will be read
			LDR	R3,=(I2C1+MDR)
			LDR	R1,=ctrl_meas
			STR	R1,[R3]
			
			;START - RUN 
			LDR	R3,=(I2C1+MCS)
			LDR	R1,=0x3
			STR	R1,[R3]
			
			;wait master to finish sending
			PUSH	{LR}			
			BL waitResponse
			POP		{LR}
						
			PUSH	{LR}
			BL	delay2ms
			POP		{LR}
			
			;Write address from which data will be read
			LDR	R3,=(I2C1+MDR)
			LDR	R1,=0x23
			STR	R1,[R3]
			
			LDR	R3,=(I2C1+MCS)
			LDR	R1,=0x1
			STR	R1,[R3]
			
			PUSH	{LR}			
			BL waitResponse
			POP		{LR}
			
			PUSH	{LR}
			BL	delay2ms
			POP		{LR}
			
			LDR	R3,=(I2C1+MDR)
			LDR	R1,=config
			STR	R1,[R3]
			
			PUSH	{LR}			
			BL waitResponse
			POP		{LR}
			
			PUSH	{LR}
			BL	delay2ms
			POP		{LR}
			
			;Write address from which data will be read
			LDR	R3,=(I2C1+MDR)
			LDR	R1,=0x3C
			STR	R1,[R3]
			
			LDR	R3,=(I2C1+MCS)
			LDR	R1,=0x5
			STR	R1,[R3]
			
			PUSH	{LR}			
			BL waitResponse
			POP		{LR}
			
			BX LR
			ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

			EXPORT      waitResponse      ; Make available
waitResponse
wai			LDR R1,[R3]
			TST	R1,#1
			BNE	wai
			
			BX LR
			ENDP
				
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

			EXPORT      delay2ms      ; Make available
delay2ms
			LDR	R2,=100000
delayy		SUBS R2,#1
			BNE	delayy
			
			BX LR
			ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

            ALIGN
            END
