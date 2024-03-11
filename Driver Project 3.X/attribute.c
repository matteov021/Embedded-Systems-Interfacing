/*
 * File:   delay.c
 *
 * Created on October 18, 2023, 12:43 PM
 */

#include "xc.h"

#define LED LATBbits.LATB8

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void){

    IFS0bits.T2IF = 0; // Clear T2 Flag 
    T2CONbits.TON = 0; // Turn Timer Off Due To Holding Button & Polling Inputs
    LED ^= 1; // Flip LED State
}
