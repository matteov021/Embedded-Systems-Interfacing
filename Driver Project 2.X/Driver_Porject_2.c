/*
 * File: driver_project_2.c
 * Group : 4
 * Lab B01
 * Created on September 29, 2023, 8:48 AM
 */

#include "xc.h"
// Define Inputs As PB1, PB2, PB3 For RA2, RB4, RA4 Respectively
#define PB1 PORTAbits.RA2 
#define PB2 PORTAbits.RA4
#define PB3 PORTBbits.RB4 

int main(void) {
    
    TRISB = 0x0010; // 0b0000000000010000 RB8 (Out), RB4 (In)
    TRISA = 0x14; // 0b00010100 RA4 (In), RA2 (In)
    uint32_t count = 0; // Initialize a count variable as 32 bit
    CNPU1bits.CN0PUE = 1; // Set Pull Up On RA4
    CNPU1bits.CN1PUE = 1; // Set Pull Up On RB4
    CNPU2bits.CN30PUE = 1; // Set Pull Up On RA2
    AD1PCFG = 0x0010; // Forces Digital I/O Instead Of Analog On RA2 
         
    while(1){    

        LATBbits.LATB8 = 0; // Turn Off LED
        while (PB1 == 0){ // Check RA2 Pressed        
            if ((PB2 & PB3) == 0) // Check If Other PB Are Pressed & Break
                break;        
            LATBbits.LATB8 ^= 1; // Flip LED State ON / OFF   
            while (count < 80000){ // 8Mhz @ 0.5s
                count++; // Waste Time
            }
            count = 0; // Reset Count
        }
    
        while (PB2 == 0){ // Check RA4 Pressed        
            if ((PB1 & PB3) == 0) // Check If Other PB Are Pressed & Break
                break;        
            LATBbits.LATB8 ^= 1; // Flip LED State ON / OFF   
            while (count < 160000){ // 8Mhz @ 1s
                count++; // Waste Time
            }
            count = 0; // Reset Count
        }
    
        while (PB3 == 0){ // Check RB4 Pressed        
            if ((PB1 & PB2) == 0) // Check If Other PB Are Pressed & Break
                break;        
            LATBbits.LATB8 ^= 1; // Flip LED State ON / OFF   
            while (count < 320000){ // 8Mhz @ 2s
                count++; // Waste Time
            }
            count = 0; // Reset Count
        }              

        while (((PB1 | PB2) & (PB1 | PB3) & (PB2 | PB3)) == 0) // Check If Multiple PB Are Pressed
                LATBbits.LATB8 = 1; // Turn LED ON       
    }   
    return 0;
}
