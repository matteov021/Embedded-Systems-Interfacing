/*
 * File:   delay.c
 *
 * Created on October 18, 2023, 12:43 PM
 */

#include "xc.h"

void delay_ms(uint16_t count){
    
    T2CONbits.T32 = 0; // 16 Bit Timer
    T2CONbits.TCKPS = 3; // 256 Pre-scaler
    IFS0bits.T2IF = 0; // Reset the Timer 2 Flag
    IEC0bits.T2IE = 1; // Enable Timer Interrupts
    T2CONbits.TCS = 0; // Set the Use of the Internal Clock
    T2CONbits.TSIDL = 0; // Operate in Idle Mode
   
    PR2 = count;
    TMR2 = 0;
    T2CONbits.TON = 1;
    Idle();
  
    return;
}
