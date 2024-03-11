/*
 * File:   dp_4.c
 * Created on October 27, 2023, 11:20 AM
 */

#pragma config FNOSC = FRCDIV           // Oscillator Select (8 MHz FRC oscillator with divide-by-N (FRCDIV))
#pragma config IESO = ON                // Internal External Switch Over bit (Internal External Switchover mode enabled (Two-Speed Start-up enabled))
#pragma config POSCMOD = NONE           // Primary Oscillator Configuration bits (Primary oscillator disabled)
#pragma config OSCIOFNC = OFF           // CLKO Enable Configuration bit (CLKO output signal is active on the OSCO pin)
#pragma config POSCFREQ = HS            // Primary Oscillator Frequency Range Configuration bits (Primary oscillator/external clock input frequency greater than 8 MHz)
#pragma config SOSCSEL = SOSCHP         // SOSC Power Selection Configuration bits (Secondary oscillator configured for high-power operation)
#pragma config FCKSM = CSECMD           // Clock Switching and Monitor Selection (Clock switching is enabled, Fail-Safe Clock Monitor is disabled)
#pragma config ICS = PGx2               // ICD Pin Placement Select bits (PGC2/PGD2 are used for programming and debugging the device)

#include "xc.h"
#include "uart.h"
#include "initialization.h"
#include "clear.h"
#include "attribute.h"
#include "assign.h"
#include "delay.h"

#define S0 0
#define S1 1
extern uint16_t state;
extern uint16_t CNflag;
    
int main(void) {
    
    ClkInit();                                  // Configure Clock
    InitUART2();                                // Initialize UART
    InitIO();                                   // Initialize IO
    Disp2String("Fast Mode: IDLE\n\r");         // Default Fast Mode
    
    while(1){
        switch(state){
            case S0:
                Idle();                         // Idle And Wait For Next Input
                if(CNflag == 1){                // Run If Input Detected
                    CNflag = 0;                 // Reset Flag
                    IOAssign();                 // Call Checking Function
                } 
                break;

            case S1:
                Idle();                         // Idle And Wait For Next Input
                if(CNflag == 1){                // Run If Input Detected
                    CNflag = 0;                 // Reset Flag
                    IOAssign();                 // Call Checking Function
                }
                break;
        }                
    }
    
    return 0;
}