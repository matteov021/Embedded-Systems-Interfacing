/*
 * File:   delay.c
 *
 * Created on November 3, 2023, 1:21 PM
 */

#include "xc.h"
#include "delay.h"

void delay_ms(uint16_t count){      // Need to make it so count can be used for new counting intervals   
    T2CONbits.T32 = 0;              // 16 Bit Timer
    T2CONbits.TCKPS = 3;            // 256 Pre-scaler
    IPC1bits.T2IP = 7;              // Set Priority For Timer
    IFS0bits.T2IF = 0;              // Reset the Timer 2 Flag
    IEC0bits.T2IE = 1;              // Enable Timer Interrupts
    T2CONbits.TCS = 0;              // Set the Use of the Internal Clock
    T2CONbits.TSIDL = 0;            // Operate in Idle Mode  
    PR2 = count;                    // Set PR2 to integer for timing
    TMR2 = 0;                       // Set TMR2 = 0
    T2CONbits.TON = 1;              // Start Timer 
    Idle();                         // Idle until the next interrupt, which should be another button press 
    
    return;
}   
