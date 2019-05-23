/*
 * convert_to_string.inc
 *
 *  Created: 23/12/2018 06:32:20 ?
 *   Author: toshiba
 */ 



.MACRO DIV3210 /*  @0-->total1 ,@1 -->total2 , @2-->total3 ,@3-->total4   */

	PUSH R24
		
	DIV3216:
			CLR ZERO
			
			LDI R24,33         
			MOV C,r24
			SUB REM1,REM1    
			CLR REM2         
			CLR REM3          
			CLR REM4          
	LOOP:	ROL @0          
			ROL @1        
			ROL @2          
			ROL @3         
			DEC C             
			BREQ DONE        
			ROL REM1          
			ROL REM2         
			ROL REM3         
			ROL REM4         
			LDI R24,10
			SUB REM1,R24       
			SBC REM2,ZERO      
			SBC REM3,ZERO    
			SBC REM4,ZERO     
			BRCC SKIP       
			LDI R24,10
			ADD REM1,R24     
			ADC REM2,ZERO      
			ADC REM3,ZERO    
			ADC REM4,ZERO    
			CLC               
			RJMP LOOP        
	SKIP:	SEC               
			RJMP LOOP
	DONE:
	
	POP R24

.ENDMACRO

   /*-----------------------------------------------------------------------------------------------------------------*/

.MACRO DIV1610 /*  @0-->total1 ,@1 -->total2  */

	PUSH R24
	CLR ZERO

   DIV1616:
       LDI R24,17
        MOV C,R24          ;Load bit counter
        SUB REM1,REM1     ;Clear Remainder and Carry
        CLR REM2          ;
LOO:   ROL @0          ;Shift the answer to the left
        ROL @1          ;
        DEC C             ;Decrement Counter
        BREQ DON        ;Exit if sixteen bits done
        ROL REM1          ;Shift remainder to the left
        ROL REM2          ;
		LDI R24,10
        SUB REM1,R24       ;Try to subtract divisor from remainder
        SBC REM2,ZERO
         BRCC SKI        ;If the result was negative then
		 LDI R24,10
        ADD REM1,R24       ;reverse the subtraction to try again
        ADC REM2,ZERO       ;
        CLC               ;Clear Carry Flag so zero shifted into A 
         RJMP LOO        ;Loop Back
SKI:   SEC               ;Set Carry Flag to be shifted into A
         RJMP LOO
DON:

POP R24

.ENDMACRO

   /*------------------------------------------------------------------------------------------------------------------*/
.MACRO convert_display /*  @0-->total1 ,@1 -->total2 , @2-->total3 ,@3-->total4   */

	push R24
	LDI R24,1
	MOV neg_check,R24
	
	ldi R24,'\0' // M4 3ARFa lah 7to hna
	st Y+,R24

	check @0,@1,@2,@3
	BRNE code
		
		ldi r24,'0'
		st Y+,r24

		jmp display_part

	code:
	/*tst @3

	brpl not_neg 
		clr neg_check
		MULT32xminus1 @0,@1,@2,@3
*/
	
	negative_test @0,@1,@2,@3
	not_neg:
	while_not_zero:

		check @0,@1,@2,@3
		BREQ jmp_end
		BRNE loop

	jmp_end:
		jmp end_while

	loop:

		DIV3210 @0,@1,@2,@3
		ldi r24,'0'
		add rem1,r24
		st Y+,rem1
		jmp while_not_zero
			

	

	end_while:

		LDI R24,1
		CP neg_check,R24
		BREQ display_part //if neg_check =0 branch to dispay

			 //negative if neg_check = 1
			ldi R24,'-'
			st Y+,R24


	display_part :

		CALL DISPLAY_RES


	POP R24

.ENDMACRO


    /*-----------------------------------------------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------------------------------------------------*/

.MACRO convert_display2 /*  @0-->total1 ,@1 -->total2 , @2-->total3 ,@3-->total4   */

	CLR ZERO
	push R24
	LDI R24,1
	MOV neg_check,R24
	
	ldi R24,'\0' // M4 3ARFa lah 7to hna
	st Y+,R24

	check_two @0,@1
	BRNE code
		
		ldi r24,'0'
		st Y+,r24

		jmp display_part

	code:
	/*tst @1

	brpl not_neg 
		clr neg_check
		MULT32xminus1_2 @0,@1
*/
	negative_test2 @0,@1

	not_neg:
	while_not_zero:

		check_two @0,@1
		BREQ jmp_end
		BRNE loop

	jmp_end:
		jmp end_while

	loop:

		DIV1610 @0,@1
		ldi r24,'0'
		add rem1,r24
		st Y+,rem1
		jmp while_not_zero
			

	

	end_while:

		LDI R24,1
		CP neg_check,R24
		BREQ display_part //if neg_check =0 branch to dispay

			 //negative if neg_check = 1
			ldi R24,'-'
			st Y+,R24


	display_part :

		CALL DISPLAY_RES


	POP R24

.ENDMACRO


    /*-----------------------------------------------------------------------------------------------------------*/

	


.MACRO check /*  @0-->total1 ,@1 -->total2 , @2-->total3 ,@3-->total4   */ /*ht7t al natg fe al ans (h4eel 7tt al n2l al fe a 2wal)*/
	
	tst @0
	brne NotEqual

	tst @1
	brne NotEqual

	tst @2
	brne NotEqual

	tst @3
	brne NotEqual


	NotEqual:
.ENDMACRO

		 /*-----------------------------------------------------------------------------------------------------*/

.MACRO negative_test /*  @0-->total1 ,@1 -->total2 , @2-->total3 ,@3-->total4   */
	PUSH R24
	CLR ZERO
	tst @3
	BREQ total4_iszero
	BRPL end_negative
		com @3
		com @2
		com @1
		com @0
		LDI R24,1
		ADD @0,R24
		ADC @1,ZERO
		ADC @2,ZERO
		ADC @3,ZERO
		CLR ZERO
		MOV neg_check,ZERO
		JMP end_negative_test
	end_negative:
		JMP end_negative_test

		/*-------------------------------*/
	total4_iszero:
	tst @2
	BREQ total3_iszero
	BRPL end_negative1
		com @2
		com @1
		com @0
		LDI R24,1
		ADD @0,R24
		ADC @1,ZERO
		ADC @2,ZERO
		ADC @3,ZERO
		CLR ZERO
		MOV neg_check,ZERO
		JMP end_negative_test
	end_negative1:
		JMP end_negative_test
		/*--------------------------*/
		total3_iszero:
		tst @1
	BREQ total2_iszero
	BRPL end_negative2
		com @1
		com @0
		LDI R24,1
		ADD @0,R24
		ADC @1,ZERO
		ADC @2,ZERO
		ADC @3,ZERO
		CLR ZERO
		MOV neg_check,ZERO
		JMP end_negative_test
	end_negative2:
		JMP end_negative_test
		/*--------------------------*/
		total2_iszero:
		tst @0
	BREQ total1_iszero
	BRPL end_negative3
		com @0
		LDI R24,1
		ADD @0,R24
		ADC @1,ZERO
		ADC @2,ZERO
		ADC @3,ZERO
		CLR ZERO
		MOV neg_check,ZERO
		JMP end_negative_test
	end_negative3:
		JMP end_negative_test
		/*--------------------------*/
	total1_iszero:
	end_negative_test:
	POP R24
.ENDMACRO
		 /*------------------------------------------------------------------------------------------------------*/
 /*-----------------------------------------------------------------------------------------------------*/

.MACRO negative_test2 /*  @0-->total1 ,@1 -->total2   */
	PUSH R24
	CLR ZERO
	
		tst @1
	BREQ t2_iszero
	BRPL end_negative_2
		com @1
		com @0
		LDI R24,1
		ADD @0,R24
		ADC @1,ZERO
		CLR ZERO
		MOV neg_check,ZERO //m4 hn7tagha fe al add de ll 3rd bs 
		JMP end_negative_test_
	end_negative_2:
		JMP end_negative_test_
		/*--------------------------*/
		t2_iszero:
		tst @0
	BREQ t1_iszero
	BRPL end_negative_1
		com @0
		LDI R24,1
		ADD @0,R24
		ADC @1,ZERO
		CLR ZERO
		MOV neg_check,ZERO
		JMP end_negative_test_
	end_negative_1:
		JMP end_negative_test_
		/*--------------------------*/
	t1_iszero:
	end_negative_test_:
	POP R24
.ENDMACRO
		 /*------------------------------------------------------------------------------------------------------*/


.MACRO MULT32xminus1 /*  @0-->total1 ,@1 -->total2 , @2-->total3 ,@3-->total4   *//* ht7t al natg fe al ans (h4eel 7tt al n2l al fe a 2wal)*/
	PUSH R24
	CLR ZERO

	com @0
	com @1
	com @2
	com @3

	LDI R24,1
	ADD @0,R24
	ADC @1,ZERO
	ADC @2,ZERO
	ADC @3,ZERO

	POP R24
.ENDMACRO

/*-----------------------------------------------------------------------------------------------------*/
.MACRO MULT32xminus1_2 /*  @0-->first1 ,@1 -->first2*/

	PUSH R24
	CLR ZERO

	com @0
	com @1
	

	LDI R24,1
	ADD @0,R24
	ADC @1,ZERO

.ENDMACRO

 /*-----------------------------------------------------------------------------------------------------*/
DISPLAY_RES:

	DEC YL
	Ld R24,Y
	
	CPI R24,'\0'
	BREQ RETURN

		LCD_displayChar R24
		jmp DISPLAY_RES

	
	RETURN:

	LDI YL,LOW(final_ans)
	LDI YH,HIGH(final_ans)

ret