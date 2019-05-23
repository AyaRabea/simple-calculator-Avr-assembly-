/*
 * LCD_MODULE.inc
 *
 *  Created: 29/11/2018 01:44:27 ?
 *   Author: toshiba
 */ 
 .INCLUDE "Micro_Configration.INC"

 .EQU RS = 1
 .EQU RW = 2
 .EQU EN = 3
 ; PORT D
 .EQU LCD_DATA_DDR_IO = DDRD_IO
 .EQU LCD_DATA_PORT_OUT = PORTD_OUTPUT
 .EQU LCD_DATA_PIN_INPUT = PIND_INPUT
 ;PORT C
 .EQU LCD_CONTROL_DDR_IO = DDRB_IO
 .EQU LCD_CONTROL_PORT_OUT = PORTB_OUTPUT
 .EQU LCD_CONTROL_PIN_INPUT = PINB_INPUT
 .EQU ENDRAM = $085D  // MAFROOD 5F

 //intructions

 .EQU CLEAR = 0X01
 .EQU CURSOR_ON_BLINK = 0X0E
 .EQU MATRIX_8BIT = 0X38
 .EQU set_display_address = 0X80


 //STACK
 //.EQU STACKPL = $3D   //STACK POINTER LOW 
 //.EQU STACKPH = $3E   //STACK POINTER HIGH 


 //MACROS

 .MACRO LCD_sendInstruction  ;instruction address(@0)
	PUSH R16
	LDI R16,@0
	
	SBI LCD_CONTROL_PORT_OUT,EN
	
	CBI LCD_CONTROL_PORT_OUT,RS
	CBI LCD_CONTROL_PORT_OUT,RW
	
	OUT LCD_DATA_PORT_OUT , R16

	CALL SDelay

	CBI LCD_CONTROL_PORT_OUT,EN
	CALL Delay_100us
	POP R16
 .ENDMACRO
 

 

 .MACRO LCD_displayChar ;REGISTER (@0)
		PUSH R16
		MOV	R16,@0
		
		SBI LCD_CONTROL_PORT_OUT,EN
		SBI LCD_CONTROL_PORT_OUT,RS
		CBI LCD_CONTROL_PORT_OUT,RW
		
		OUT LCD_DATA_PORT_OUT , R16
		//MOV R31 , R16

		CALL SDelay

		CBI LCD_CONTROL_PORT_OUT,EN
		CALL Delay_100us
		POP R16
	
 .ENDMACRO

 //END MACROS

  //PROCEDURE

  LCD_init:   ;void
	             
	PUSH R21
	LDI R21,0b11111111
	OUT LCD_DATA_DDR_IO , R21        //make data pins output

	
	OUT LCD_CONTROL_DDR_IO , R21     //make control pins output

	CBI LCD_CONTROL_PORT_OUT ,EN      //EN=0

	LCD_sendInstruction MATRIX_8BIT
	CALL Delay_2ms

	LCD_sendInstruction CURSOR_ON_BLINK
	CALL Delay_2ms

	LCD_sendInstruction CLEAR
	CALL Delay_2ms

	
	POP R21
 RET

 
 SDelay : 
	nop
	nop
	ret

Delay_100us :
	PUSH R17  //momkan nms7ha
	LDI R17,60
	D0:
		CALL SDelay
		DEC R17
		BRNE D0
	POP R17   //momkan nms7ha
	ret

Delay_2ms :
	PUSH R17  //momkan nms7ha
	LDI R17,20
	D1:
		CALL Delay_100us
		DEC R17
		BRNE D1
	POP R17   //momkan nms7ha
	ret


