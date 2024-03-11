/*
 * File:   IO.c
 *
 * Created on November 22, 2023, 7:40 PM
 */

#include "xc.h"
#include "IO.h"
#include "uart.h"
#include "ADC.h"

#define LED LATBbits.LATB8
#define LED2 LATAbits.LATA6
#define WAIT while(count < 20000)(count++); count = 0;

uint16_t count;
uint16_t ADC_val_scaled;
extern uint8_t RXFlag;
extern uint16_t CNFlag;

void InitIO(){ 
    TRISBbits.TRISB4 = 1;    // Set RB4 to Input
    TRISBbits.TRISB8 = 0;    // Set RB8 to output
    TRISAbits.TRISA2 = 1;    // Set RA2 As Input
    TRISAbits.TRISA4 = 1;    // Set RA4 As Input
    TRISAbits.TRISA6 = 0;
    AD1PCFG = 0xFFFF;        // Forces Digital I/O Instead Of Analog 
    LED = 0;                 // Initialize LED To 0
    LED2 = 0;                // Initialize LED To 0
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

void displayBar(){
    uint16_t ADC_val = do_ADC(); // Call ADC To Get Analog -> Digital Value Of Input
    uint16_t num;                // Number for Converting ADC Value to Bar Graph amount   
    
    if(ADC_val == 0)
    {
        num = 1;                // Default case if ADC returns 0
    }
    else
    {
        num = (ADC_val/32);  // Convert ADC to number (Max analog = 1023 and Max # = 32)
    }
    char array[num+2];       // Array to store amount of # For Bar Graph 
    
    for(int i = 0; i < num; i++)
    {
        array[i] = '#';      // Add # based on number count to the array
    }
    array[num] = '\0';                          // Fill end of array with null
    ADC_val_scaled = ((ADC_val * 9)/ 1023);     // Scale ADC Value So It Is 0-9
    Disp2String("Enter Unlock Number\r\n");     // Display Enter Unlock Message
    Disp2String(array);                         // Display #
    Disp2Dec(ADC_val_scaled);                   // display analog input in decimal
    WAIT
    ClearUART(); 
}

void PWM(uint16_t count){

    T2CONbits.T32 = 0;              // 16 Bit Timer
    T2CONbits.TCKPS = 1;            // 8 Pre-scaler
    IPC1bits.T2IP = 7;              // Set Priority For Timer
    IFS0bits.T2IF = 0;              // Reset the Timer 2 Flag
    IEC0bits.T2IE = 1;              // Enable Timer Interrupts
    T2CONbits.TCS = 0;              // Set the Use of the Internal Clock
    T2CONbits.TSIDL = 0;            // Operate in Idle Mode  
    TMR2 = 0;                       // Set TMR2 = 0
    OC1CON = 0x0006;                // Set Output Compare On OC1
    OC1CONbits.OCM = 6;             // Set Output Compare On OC1
    PR2 = 1023;                     // Period Register For Timer
    OC1R = 512;                     // Initial Duty
    OC1RS = count;                  // Duty Cycle
    T2CONbits.TON = 1;              // Start Timer 
    Idle();                         // Idle Mode

        
}
