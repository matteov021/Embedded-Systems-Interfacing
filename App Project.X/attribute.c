/*
 * File:   attribute.c
 *
 * Created on November 3, 2023, 1:16 PM
 */

#include "xc.h"
#include "attribute.h"
#define WAIT while(count2 < 750)(count2++); count2 = 0;

#define SPECIAL 5
#define PB1 PORTAbits.RA2
#define PB2 PORTAbits.RA4
#define PB3 PORTBbits.RB4
#define LED LATBbits.LATB8

uint16_t CNFlag = 0;
uint16_t Flag1 = 0;
uint16_t Flag2 = 0;
uint16_t Flag3 = 0;
uint16_t count2;
extern uint16_t state;

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void){
    IFS0bits.T2IF = 0;                  // Clear T2 Flag
    if(state == SPECIAL)                    
        T2CONbits.TON = 0;              // Start Timer
    else{
        LED ^= 1;                       // Flip LED
        T2CONbits.TON = 0;              // Start Timer 
    }    
}

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void){
    IFS1bits.CNIF = 0;              // Clear CN Interrupt Flag
    WAIT
    if(!PB1)
        Flag1 = 1;
    if(!PB2)
        Flag2 = 1;
    if(!PB3)
        Flag3 = 1;

}
