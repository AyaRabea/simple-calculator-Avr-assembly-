/*
 * CALC.inc
 *
 *  Created: 20/12/2018 08:35:53 ?
 *   Author: toshiba
 */ 
 /*
 name : MULT16x10_ADDr23 
 parameter : @0-->nu*m1(low) ,@1--> num1(high)
 function :  (first2:first1)*10+(number readed from lcd(stored in r23))
 return : value in (first2:first1)
 */
 .MACRO MULT16x10_ADDr23 

	push r17
	PUSH R2
	PUSH R3
	push r16
			ldi r16,0

			LDI r17,10
	        MUL @0,r17
			            
		    MOVW R3:R2,R1:R0 

			MUL @1,r17          
			ADD R3,R0          
			
			movw @1:@0, R3:R2

			ADD @0,r23         
			ADC @1,r16        

			
	pop r17
	POP R2
	POP R3
	pop r16

 .ENDMACRO
 /*---------------------------------------------------------------------------------------------------*/
  /*
 name : MULT16x16 
 parameter : @0-->num1(low) ,@1 -->num1(high), @2-->num2(low) ,@3-->num2(high), @4-->total1 ,@5 -->total2, @6-->total3 ,@7-->total4
 function :  (first2:first1)*(second2:second1)
 return : value in (total4:total3:total2:total1)
 */
 .MACRO MULT16x16 
	
		CLR ZERO             
        MUL @1,@3            
        MOVW @7:@6,R1:R0 

		
        MUL @0,@2           
	  

        MOVW @5:@4,R1:R0 

		
        MUL @1,@2            
		

        ADD @5,R0         
        ADC @6,R1         
        ADC @7,R2       

		
        MUL @3,@0           

        ADD @5,R0          
        ADC @6,R1          
        ADC @7,R2       

		MOVW @1:@0,@5:@4


 .ENDMACRO

 /*-------------------------------------------------------------------------------------------------------------------*/
 
  /*
 name : ADD16x16_2 
 parameter : @0-->num1(low) ,@1 -->num1(high), @2-->num2(low) ,@3-->num2(high), @4-->total1 ,@5 -->total2, @6-->total3 ,@7-->total4
 function :  (first2:first1) + (second2:second1)
 return : value in (total4:total3:total2:total1)
 */
 .MACRO ADD16x16_2 
		
		CLR ZERO
		
		movw @5:@4,@1:@0
		

		ADD @4,@2
		ADC @5,@3
		ADC @6,ZERO
		ADC @7,ZERO

		MOVW @1:@0,@5:@4
		
		
 .ENDMACRO
 /*-----------------------------------------------------------------------------------------------------------------------*/
  /*
 name : ADD16x16
 parameter : @0-->num1(low) ,@1 -->num1(high), @2-->num2(low) ,@3-->num2(high), @4-->total1 ,@5 -->total2, @6-->total3 ,@7-->total4
 function :  call ADD_FIRSTNEG (which make addition with all statues)
 return : value in (total4:total3:total2:total1)
 */
 .MACRO ADD16x16 
		
		CLR ZERO
		ADD_FIRSTNEG @0,@1,@2,@3,@4,@5,@6,@7		
		

 .ENDMACRO
 
 /*---------------------------------------------------------------------------------------------------------------------*/
 /*
 name : ADD_FIRSTNEG
 parameter : @0-->num1(low) ,@1 -->num1(high), @2-->num2(low) ,@3-->num2(high), @4-->total1 ,@5 -->total2, @6-->total3 ,@7-->total4
 function :  if first num is neg --> neg(first2:first1) then (first2:first1)-(second2:second1)---> make neg(total4:total3:total2:total1)
			else
			(first2:first1)+(second2:second1)
 return : value in (total4:total3:total2:total1)
 */
 .MACRO ADD_FIRSTNEG 

	PUSH R24
	CLR ZERO
	
		tst @1
	BREQ end_negative_2_
	BRPL end_negative_2_
		com @1
		com @0
		LDI R24,1
		ADD @0,R24
		ADC @1,ZERO
		SUB16x16 @0,@1,@2,@3,@4,@5,@6,@7
		/*get 2's complement of result*/
		com @4
		com @5
		com @6
		com @7
		ldi r24,1
		add @4,r24
		adc @5,ZERO
		adc @6,ZERO
		adc @7,ZERO
		/*-------------*/
		JMP end_negative_test_1
	end_negative_2_:
		ADD16x16_2 @0,@1,@2,@3,@4,@5,@6,@7
		JMP end_negative_test_1
		/*--------------------------*/
		

	end_negative_test_1:
	POP R24

 .ENDMACRO
 /*---------------------------------------------------------------------------------------------------------------------*/
 /*
 name : MULT_FIRSTNEG
 parameter : @0-->num1(low) ,@1 -->num1(high), @2-->num2(low) ,@3-->num2(high), @4-->total1 ,@5 -->total2, @6-->total3 ,@7-->total4

 function :  if first num is neg --> neg(first2:first1) then (first2:first1)*(second2:second1)---> make neg(total4:total3:total2:total1)
			else
			(first2:first1)*(second2:second1)

 return : value in (total4:total3:total2:total1)
 */

 .MACRO MULT_FIRSTNEG 

	PUSH R24
	CLR ZERO
	
		tst @1
	BREQ MUL_3ADYA
	BRPL MUL_3ADYA
		com @1
		com @0
		LDI R24,1
		ADD @0,R24
		ADC @1,ZERO
		MULT16x16 @0,@1,@2,@3,@4,@5,@6,@7
		/*get 2's complement of result*/
		com @4
		com @5
		com @6
		com @7
		ldi r24,1
		add @4,r24
		adc @5,ZERO
		adc @6,ZERO
		adc @7,ZERO

		MOVW @1:@0,@5:@4
		/*-------------*/
		JMP end_negative_t
	MUL_3ADYA:
		 MULT16x16 @0,@1,@2,@3,@4,@5,@6,@7
		JMP end_negative_t
		/*--------------------------*/
		

	end_negative_t:
	POP R24

 .ENDMACRO
 /*---------------------------------------------------------------------------------------------------------------------*/

  /*
 name : SUB16x16
 parameter : @0-->num1(low) ,@1 -->num1(high), @2-->num2(low) ,@3-->num2(high), @4-->total1 ,@5 -->total2, @6-->total3 ,@7-->total4
 function :  (first2:first1)-(second2:second1)
 return : value in (total4:total3:total2:total1)
 */

 .MACRO SUB16x16 

		CLR ZERO
		movw @5:@4,@1:@0
		
		SUB @4,@2
		SBC @5,@3
		SBC @6,ZERO
		SBC @7,ZERO
    
		MOVW @1:@0,@5:@4
 .ENDMACRO

  /*---------------------------------------------------------------------------------------------------------------------*/

  /*
 name : power16x16
 parameter : @0-->num1(low) ,@1 -->num1(high), @2-->num2(low) ,@3-->num2(high), @4-->total1 ,@5 -->total2, @6-->total3 ,@7-->total4
 function :  get power --> (first2:first1)^(second2:second1)  
 return : value in (total4:total3:total2:total1)
 */

 .MACRO power16x16 
 
	CLR ZERO
	push r24
	 /* check zero */

	check_two @2,@3
	BRNE check_one
		/*power is zero*/
	ldi r24,1
	mov @4,r24

	ldi r24,0
	mov @5,r24

	ldi r24,0
	mov @6,r24

	ldi r24,0
	mov @7,r24

	MOVW @1:@0,@5:@4

	jmp power_end

		/* check one */
	check_one:
	cpi second2,0
	brne power_code

	cpi second1,1
	brne power_code

		ldi @2,1
		ldi @3,0
		MULT_FIRSTNEG @0,@1,@2,@3,@4,@5,@6,@7
		jmp power_end
		/*original power code*/

	power_code:
		movw @5:@4 , @1:@0

		ldi r24,1
		sub @2,r24
		sbc @3,ZERO

	//movw c1:c,@3:@2
	mov c,@2
	mov c1,@3
	movw @3:@2,@1:@0 //second hold the base

loop:

	check_two c,c1
	BREQ power_end
     
	 movw @1:@0,@5:@4
      
	MULT16x16 @0,@1,@2,@3,@4,@5,@6,@7

	ldi r24,1
	sub c,r24
	sbc c1,ZERO
	jmp loop



		/*end original power code*/
	power_end:

	pop r24
 .ENDMACRO

 /*---------------------------------------------------------------------------------------------------------------------*/

  /*
 name : check_two
 parameter : @0-->num1(low) ,@1 -->num1(high)
 function :  check if number is zero or not  
 no return (just affect flags)
 */
 .MACRO check_two 
	
	tst @0
	brne NotEqual

	tst @1
	brne NotEqual

	
	NotEqual:
.ENDMACRO
