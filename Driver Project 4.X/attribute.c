/*
 * File:   attribute.c
 *
 * Created on November 3, 2023, 1:16 PM
 */

#include "xc.h"
#include "attribute.h"

#define PB1 PORTAbits.RA2
#define PB2 PORTAbits.RA4
#define PB3 PORTBbits.RB4
#define LED LATBbits.LATB8
uint16_t CNflag = 0;

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void){
    IFS0bits.T2IF = 0;              // Clear T2 Flag
    LED ^= 1;                       // Flip LED
}

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void){
    IFS1bits.CNIF = 0;              // Clear CN Interrupt Flag
    if(!PB1 || !PB2 || !PB3)        // Set CNflag if any input is pressed
        CNflag = 1;
}
