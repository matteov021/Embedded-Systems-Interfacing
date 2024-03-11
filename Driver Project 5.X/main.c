/*
 * File:   main.c
 *
 * Created on November 2, 2023, 9:26 AM
 */

#pragma config FWDTEN = OFF             // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit)) RECOMMENDED
#pragma config FNOSC = FRCDIV           // Oscillator Select (8 MHz FRC oscillator with divide-by-N (FRCDIV))
#pragma config IESO = ON                // Internal External Switch Over bit (Internal External Switchover mode enabled (Two-Speed Start-up enabled))
#pragma config POSCMOD = NONE           // Primary Oscillator Configuration bits (Primary oscillator disabled)
#pragma config OSCIOFNC = ON            // CLKO Enable Configuration bit (CLKO output signal is active on the OSCO pin)
#pragma config POSCFREQ = HS            // Primary Oscillator Frequency Range Configuration bits (Primary oscillator/external clock input frequency greater than 8 MHz)
#pragma config SOSCSEL = SOSCHP         // SOSC Power Selection Configuration bits (Secondary oscillator configured for high-power operation)
#pragma config FCKSM = CSECMD           // Clock Switching and Monitor Selection (Clock switching is enabled, Fail-Safe Clock Monitor is disabled)
#pragma config ICS = PGx2               // ICD Pin Placement Select bits (PGC2/PGD2 are used for programming and debugging the device) Enables Stepping Debugger

#include <xc.h>
#include "clkChange.h"
#include "uart.h"
#include "IO.h"
#include "ADC.h"

int main(void) {
    
    AD1PCFG = 0xFFFF;    // Initialize Digital IO
    InitUART2();         // Initialize UART2 module
    newClk(32);          // Set CLK to 32 KHz
    
    while(1)
    {
        displayBar();    // Function that displays bar graph
    }
    return 0;
}
