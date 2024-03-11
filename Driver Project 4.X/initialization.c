/*
 * File:   Initialization.c
 *
 * Created on November 3, 2023, 1:08 PM
 */

#include "xc.h"
#include "initialization.h"
#define LED LATBbits.LATB8

void ClkInit(){                     // Initialize Clock To 500kHz
    SRbits.IPL = 7;
    CLKDIVbits.RCDIV = 0;
    __builtin_write_OSCCONH(0x66);  // Clock set to 500kHZ
    __builtin_write_OSCCONL(0x01);
    OSCCONbits.OSWEN = 1;
    while(OSCCONbits.OSWEN == 1){}
    SRbits.IPL = 0;
}

void InitIO(){

    TRISBbits.TRISB4 = 1;    // Set RB4 to Input
    TRISBbits.TRISB8 = 0;    // Set RB8 to output
    TRISA = 0x14;            // 0b00010100 RA4 (In), RA2 (In)
    AD1PCFG = 0xFFFF;        // Forces Digital I/O Instead Of Analog 
    LED = 0;                 // Initialize LED To 0
    CNPU1bits.CN0PUE = 1;    // Set Pull Up On RA4
    CNPU1bits.CN1PUE = 1;    // Set Pull Up On RB4
    CNPU2bits.CN30PUE = 1;   // Set Pull Up On RA2
    CNEN1bits.CN0IE = 1;     // Enable CN on CN0
    CNEN1bits.CN1IE = 1;     // Enable CN on CN1
    CNEN2bits.CN30IE = 1;    // Enable CN on CN30
    IPC4bits.CNIP = 6;       // Set CN Priority
    IFS1bits.CNIF = 0;       // Clear CN Interrupt Flag
    IEC1bits.CNIE = 1;       // Enable CN Interrupts
}
