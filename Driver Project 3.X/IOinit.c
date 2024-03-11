/*
 * File:   IOinit.c
 *
 * Created on October 18, 2023, 12:30 PM
 */

#include "xc.h"

// Define Inputs As PB1, PB2, PB3 For RA2, RB4, RA4 Respectively
#define PB1 PORTAbits.RA2 
#define PB2 PORTAbits.RA4
#define PB3 PORTBbits.RB4 
#define LED LATBbits.LATB8

void IOinit(){

    TRISB = 0x0010; // 0b0000000000010000 RB8 (Out), RB4 (In)
    TRISA = 0x14; // 0b00010100 RA4 (In), RA2 (In)
    AD1PCFG = 0x0010; // Forces Digital I/O Instead Of Analog On RA2 
    CNPU1bits.CN0PUE = 1; // Set Pull Up On RA4
    CNPU1bits.CN1PUE = 1; // Set Pull Up On RB4
    CNPU2bits.CN30PUE = 1; // Set Pull Up On RA2
    LED = 0; // Initialize LED To 0
    
    return;
}

void IOcheck(){

    while (PB1 == 0){ // Check RA2 Pressed        
        if ((PB2 & PB3) == 0) // Check If Other PB Are Pressed & Break
            break; 
        delay_ms(3906); // For 0.5s
    }    
    
    while (PB2 == 0){ // Check RA4 Pressed        
        if ((PB1 & PB3) == 0) // Check If Other PB Are Pressed & Break
            break;
        delay_ms(7813); // For 1s
    }    
    
    while (PB3 == 0){ // Check RB4 Pressed        
        if ((PB2 & PB1) == 0) // Check If Other PB Are Pressed & Break
            break;
        delay_ms(39063); // 5s        
    }    

    while (((PB1 | PB2) & (PB1 | PB3) & (PB2 | PB3)) == 0) // Check If Multiple PB Are Pressed 
        delay_ms(8); // For 0.001s
    
    LED = 0; // Set LED State OFF By Default
    
    return;
}
