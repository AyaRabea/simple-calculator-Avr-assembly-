/*
 * def_reg.inc
 *
 *  Created: 26/12/2018 10:48:16 ?
 *   Author: toshiba
 */ 

 .DEF first1 = R18
.DEF first2 = R19

.DEF op = R22

.DEF second1 = R20
.DEF second2 = R21

.DEF total1 = R12
.DEF total2 = R13
.DEF total3 = R14
.DEF total4 = R15


//.DEF count = R2

//R31 : 2RAYT AL KEYPAD
//R30:RKM WLA L2
//r23 4yla al rkm

/* itoa */
.DEF ZERO=R2

.DEF neg_check = R11

.DEF REM1 = R7            ;To hold first-byte of remainder
.DEF REM2 = R8            ;To hold second-byte of remainder
.DEF REM3 = R9            ;To hold third-byte of remainder
.DEF REM4 = R10            ;To hold fourth-byte of remainder

.DEF    C = R5           ;Bit Counter
.DEF    C1 = R6           ;Bit Counter