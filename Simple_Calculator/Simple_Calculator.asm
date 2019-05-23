/*
 * Simple_Calculator.asm
 *
 *  Created: 23/05/2019 11:58:23 ?
 *   Author: toshiba
 */ 

 jmp start

.INCLUDE "LCD_MODULE.inc"
.INCLUDE "KEYPAD.inc"
.INCLUDE "CALC.inc"
.INCLUDE "convert_to_string.inc"
.include "def_reg.inc"


        /*----------------------------------------------------------------------*/
.dseg
final_ans: .byte 13

       /*------------------------------------------------------------------------*/
.cseg
start:
	PUSH R20
	LDI R20,HIGH(ENDRAM)
	OUT SPH,R20                    

	LDI R20,LOW(ENDRAM)
	OUT SPL,R20
	POP R20

	LDI YL,LOW(final_ans)
	LDI YH,HIGH(final_ans)

	CALL main


/*____________________________________________________________________________________*/

main:  
	
	
	CALL void_SETUP
	CALL void_LOOP
		
	
RET //END MAIN

/*________________________VOID SETUP____________________________________________________________*/

void_SETUP:

	
	//LDI count,1
	LDI first1,0
	LDI first2,0

	LDI second1,0
	LDI second2,0

	CLR total1
	CLR total2
	CLR total3
	CLR total4

	CALL LCD_init
	CALL KEY_INIT
	
RET

/*_________________________VOID LOOP___________________________________________________________*/

void_LOOP:
	

	first_num:
		CALL GET_KEY //r31 feha al key_pressed , r30 ='n' if num presses otherwise r30=operation
		LCD_displayChar r31
		CPI R30,'n'
		BRNE IS_OP
			MULT16x10_ADDr23 first1,first2
			jmp first_num

	IS_OP:
		mov op,r31	
		CLR second1
		CLR second2
		CLR total1
		CLR total2
		CLR total3
		CLR total4

			second_num:
				CALL GET_KEY //r31 feha al key_pressed , r30 ='n' if num presses otherwise r30=operation
				LCD_displayChar r31
				CPI R30,'n'
				BRNE equal//htt3dl
					MULT16x10_ADDr23 second1,second2
					jmp second_num
					

	equal:
		/*CPI OP,'+'
		BRNE mult_check
			jmp addition
		mult_check:

			jmp multiplication
			*/
		CPI OP,'+'
		BRNE check_mult
		JMP addition
check_mult:
		CPI OP,'*'
		BRNE check_sub
		jmp multiplication
check_sub:
		CPI OP,'-'
		BRNE check_power
		jmp subtraction
check_power:
		CPI OP,'^'
		BRNE check_others
		jmp power

check_others:
		jmp others

		addition:
			ADD16x16 first1,first2,second1,second2,total1,total2,total3,total4
			//MOVW total2:total1 , first2:first1

				/*h3rd first1,first2 (clear lcd -->display result)*/
					
					convert_display total1,total2,total3,total4

				/*5ls al 3rd*/

			CALL GET_KEY //r31 feha al key_pressed , r30 ='n' if num presses otherwise r30=operation
			LCD_sendInstruction CLEAR
			LCD_sendInstruction set_display_address
			
			CPI R30,'n'
			BRNE hnkml_OP

				LCD_displayChar r31
				MOV first1,R23
				CLR first2
				CLR total1
				CLR total2
				CLR total3
				CLR total4
				JMP first_num
			hnkml_OP:
				
				clr total3
				clr total4

				
				        
				MOVW total2:total1 , first2:first1
				
				convert_display2 total1,total2
				LCD_displayChar r31

				jmp IS_OP

		multiplication:
			
				//MULT16x16 first1,first2,second1,second2,total1,total2,total3,total4
				MULT_FIRSTNEG first1,first2,second1,second2,total1,total2,total3,total4

					/*h3rd first1,first2 (clear lcd -->display result)*/
						
						convert_display total1,total2,total3,total4

					/*5ls al 3rd*/
				CALL GET_KEY //r31 feha al key_pressed , r30 ='n' if num presses otherwise r30=operation

				LCD_sendInstruction CLEAR
				LCD_sendInstruction set_display_address
				CPI R30,'n'
				BRNE OP_MUL
					LCD_displayChar r31
					MOV first1,R23
					CLR first2
					CLR total1
					CLR total2
					CLR total3
					CLR total4
				
					JMP first_num
				OP_MUL:
					
					jmp hnkml_OP

		subtraction:

				SUB16x16 first1,first2,second1,second2,total1,total2,total3,total4
				
					/*h3rd first1,first2 (clear lcd -->display result)*/
						
						convert_display total1,total2,total3,total4

					/*5ls al 3rd*/
				CALL GET_KEY //r31 feha al key_pressed , r30 ='n' if num presses otherwise r30=operation

				LCD_sendInstruction CLEAR
				LCD_sendInstruction set_display_address
				CPI R30,'n'
				BRNE OP_SUB
					LCD_displayChar r31
					MOV first1,R23
					CLR first2
					CLR total1
					CLR total2
					CLR total3
					CLR total4
				
					JMP first_num
				OP_SUB:
					
					jmp hnkml_OP

		power:

			power16x16 first1,first2,second1,second2,total1,total2,total3,total4
				
					/*h3rd first1,first2 (clear lcd -->display result)*/
						
						convert_display total1,total2,total3,total4

					/*5ls al 3rd*/
				CALL GET_KEY //r31 feha al key_pressed , r30 ='n' if num presses otherwise r30=operation

				LCD_sendInstruction CLEAR
				LCD_sendInstruction set_display_address
				CPI R30,'n'
				BRNE OP_power
					LCD_displayChar r31
					MOV first1,R23
					CLR first2
					CLR total1
					CLR total2
					CLR total3
					CLR total4
				
					JMP first_num
				OP_power:
					
					jmp hnkml_OP
		others:
			CALL void_SETUP

jmp void_LOOP
RET


