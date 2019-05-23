/*
 * KEYPAD.inc
 *
 *  Created: 08/12/2018 12:33:39 ?
 *   Author: toshiba
 */ 
.EQU KEY_DDR = DDRA
.EQU KEY_PORT = PORTA
.EQU KEY_PIN = PINA



KEY_INIT:
	
	push R25
	LDI R25,0XF0	  // DIRECTION (ROWS(OUT), COLUMNS(INPUT))
	OUT KEY_DDR,R25 // DIRECTION
	pop R25

RET

GET_KEY:
push R25
	LDI R25,0X0F //ALL ROWS -->0
	OUT KEY_PORT,R25

	KEY_CHECK:
		NOP
		IN R25,KEY_PIN //R25 =read 0f columns r25=0x0(columns read)
		ANDI R25,0X0F //mask unused bits
		CPI R25,0x0F		
		BRNE KEY_CHECK  //repeat if r25 != 0x0f (y3ni feh al bdaya feh column 2ryalo zero m3 2n mfee4 7aga mt8ota)

	wait_key_pressed:
		NOP
		IN R25,KEY_PIN //R25 =read 0f columns r25=0x0(columns read)
		ANDI R25,0X0F  //mask unused bits
		CPI R25,0x0F		
		BREQ wait_key_pressed

		IN R25,KEY_PIN //R25 =read 0f columns r25=0x0(columns read)
		ANDI R25,0X0F  //mask unused bits
		CPI R25,0x0F		
		BREQ wait_key_pressed
		

	                 /*BUTTON IS PRESSED*/
		/*Check row0*/
		LDI R25,0b01111111
		OUT KEY_PORT,R25 //row 0-->0

		IN R25,KEY_PIN //R25 =read 0f columns r25=0x0(columns read)
		ANDI R25,0X0F  //mask unused bits
		CPI R25,0X0F
		BRNE ROW0
		//JMP CHECK_ROW1
		
				//row0 _______________________________________________________________________________________________//
				ROW0:
						IN R25,KEY_PIN	//R25 =read 0f columns r25=0x0(columns read)
						ANDI R25,0X0F  //mask unused bits

						CPI R25,0b00000111 /*cmp ll (column reads ) m3 al 7ala al mafrood a 2raya tkon 3lahaw f3ln lw kan al pressed button fe col0*/
						BREQ row0_col0

						CPI R25,0b00001011
						BREQ row0_col1

						CPI R25,0b00001101
						BREQ row0_col2

						CPI R25,0b00001110
						BREQ row0_col3
						JMP CHECK_ROW1
						

				/*row0*/
				row0_col0:
					LDI R25,'1'
					LDI r23,1
					MOV R31,R25
					LDI R30,'n'
					JMP SKIP

				row0_col1:
					LDI R25,'2'
					LDI r23,2
					MOV R31,R25
					LDI R30,'n'
					JMP SKIP

				row0_col2:
					LDI R25,'3'
					LDI r23,3
					MOV R31,R25
					LDI R30,'n'
					JMP SKIP

				row0_col3:
					LDI R25,'+'//A
					MOV R31,R25
					LDI R30,'+'
					JMP SKIP

		//_________________________________________________________________________________________________________//

		/*Check row1*/
	    CHECK_ROW1:

		LDI R25,0b10111111
		OUT KEY_PORT,R25 //row 1-->0

		IN R25,KEY_PIN //R25 =read 0f columns r25=0x0(columns read)
		ANDI R25,0X0F  //mask unused bits
		CPI R25,0X0F
		BRNE ROW1
		//JMP CHECK_ROW2
				//row1 _______________________________________________________________________________________________//
				ROW1:
						IN R25,KEY_PIN	//R25 =read 0f columns r25=0x0(columns read)
						ANDI R25,0X0F  //mask unused bits

						CPI R25,0b00000111 /*cmp ll (column reads ) m3 al 7ala al mafrood a 2raya tkon 3lahaw f3ln lw kan al pressed button fe col0*/
						BREQ row1_col0

						CPI R25,0b00001011
						BREQ row1_col1

						CPI R25,0b00001101
						BREQ row1_col2

						CPI R25,0b00001110
						BREQ row1_col3
						JMP CHECK_ROW2

						JMP SKIP
		
				/*row1*/
				row1_col0:
					LDI R25,'4'
					LDI r23,4
					MOV R31,R25
					LDI R30,'n'
					JMP SKIP

				row1_col1:
					LDI R25,'5'
					LDI r23,5
					MOV R31,R25
					LDI R30,'n'
					JMP SKIP

				row1_col2:
					LDI R25,'6'
					LDI r23,6
					MOV R31,R25
					LDI R30,'n'
					JMP SKIP

				row1_col3:
					LDI R25,'-'    //B
					MOV R31,R25
					LDI R30,'-'
					JMP SKIP
				//_________________________________________________________________________________________________________//


		/*Check row2*/
	    CHECK_ROW2:
		LDI R25,0b11011111
		OUT KEY_PORT,R25 //row 2-->0

		IN R25,KEY_PIN //R25 =read 0f columns r25=0x0(columns read)
		ANDI R25,0X0F  //mask unused bits
		CPI R25,0X0F
		BRNE ROW2
		//JMP CHECK_ROW3

				//row2 _______________________________________________________________________________________________//
				ROW2:
						IN R25,KEY_PIN	//R25 =read 0f columns r25=0x0(columns read)
						ANDI R25,0X0F  //mask unused bits

						CPI R25,0b00000111 /*cmp ll (column reads ) m3 al 7ala al mafrood a 2raya tkon 3lahaw f3ln lw kan al pressed button fe col0*/
						BREQ row2_col0

						CPI R25,0b00001011
						BREQ row2_col1

						CPI R25,0b00001101
						BREQ row2_col2

						CPI R25,0b00001110
						BREQ row2_col3
						JMP CHECK_ROW3
						JMP SKIP

		
				/*row2*/
				row2_col0:
					LDI R25,'7'
					LDI r23,7
					MOV R31,R25
					LDI R30,'n'
					JMP SKIP

				row2_col1:
					LDI R25,'8'
					LDI r23,8
					MOV R31,R25
					LDI R30,'n'
					JMP SKIP

				row2_col2:
					LDI R25,'9'
					LDI r23,9
					MOV R31,R25
					LDI R30,'n'
					JMP SKIP

				row2_col3:
					LDI R25,'^'//C
					MOV R31,R25
					LDI R30,'^'
					JMP SKIP

				//______________________________________________________________________________________________________//

		/*Check row3*/
		CHECK_ROW3:
		LDI R25,0b11101111
		OUT KEY_PORT,R25 //row 3-->0

		IN R25,KEY_PIN //R25 =read 0f columns r25=0x0(columns read)
		ANDI R25,0X0F  //mask unused bits
		CPI R25,0X0F
		BRNE ROW3
		//JMP skip
				//row3____________________________________________________________________________________________//
			

				ROW3:
						IN R25,KEY_PIN	//R25 =read 0f columns r25=0x0(columns read)
						ANDI R25,0X0F  //mask unused bits

						CPI R25,0b00000111 /*cmp ll (column reads ) m3 al 7ala al mafrood a 2raya tkon 3lahaw f3ln lw kan al pressed button fe col0*/
						BREQ row3_col0

						CPI R25,0b00001011
						BREQ row3_col1

						CPI R25,0b00001101
						BREQ row3_col2

						CPI R25,0b00001110
						BREQ row3_col3

						JMP SKIP

				/*row3*/
				row3_col0:
					LDI R25,'*'
					MOV R31,R25
					LDI R30,'*'
					JMP SKIP

				row3_col1:
					LDI R25,'0'
					LDI r23,0
					MOV R31,R25
					LDI R30,'n'
					JMP SKIP

				row3_col2:
					LDI R25,'=' //#
					MOV R31,R25
					LDI R30,'='
					JMP SKIP

				row3_col3:
					LDI R25,'D'
					MOV R31,R25
					LDI R30,'D'

	/*CLR first1
	CLR first2			
	CLR second1
	CLR second2
	CLR total1
	CLR total2
	CLR total3
	CLR total4
	LCD_sendInstruction CLEAR
					LCD_sendInstruction set_display_address
		*/			JMP SKIP
		



				/*____________________________________________________________________________________________________________________________________*/
		          /*i know the row & the column*/ /*detect char*/

		
		                   /* get the char*/


		SKIP:
		pop R25
RET