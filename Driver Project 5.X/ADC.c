/*
 * File:   ADC.c
 *
 * Created on November 22, 2023, 11:52 AM
 */

#include "ADC.h"
#include "uart.h"

uint16_t do_ADC(void)
{
    uint16_t ADCvalue;          // Hold ADC converted digital output ADC1BUF0
    
                                // Configure ADC by setting bits in AD1CON1
    AD1CON1bits.ADON = 1;       // Turn on ADC
    AD1CON1bits.FORM = 0;       // Integer Output
    AD1CON1bits.SSRC = 7;       // Auto Conversion -> Internal Counter Ends Sampling
    AD1CON1bits.ASAM = 0;       // Sampling begins when SAMP bit is set
    
                                // Configure ADC by setting bits in AD1CON2
    AD1CON2bits.VCFG = 0b000;   // Selects AVDD, AVSS as Vref
    AD1CON2bits.CSCNA = 0;      // Input Scan Disabled
    AD1CON2bits.BUFM = 0;       // One 16 word buffer
    AD1CON2bits.ALTS = 0;       // Always uses MUX A input
    
                                // Configure ADC by setting bits in AD1CON3
    AD1CON3bits.ADRC = 0;       // Use system clock
    AD1CON3bits.SAMC = 10;      // Sample time = 1/10 * signal being sampled

    AD1CHSbits.CH0NA = 0;       // Channel 0 negative input is VR-
    AD1CHSbits.CH0SA = 5;       // Channel 0 positive input is AN5
    
    AD1PCFGbits.PCFG5 = 0;      // Configure ADC Pin
    
    AD1CON1bits.SAMP = 1;       // Start Sampling, Conversion is automatic

    while(AD1CON1bits.DONE == 0)  // Wait until sampling finishes
    {}
    ADCvalue = ADC1BUF0;          // ADC output is stored in ADC1BUF0
    AD1CON1bits.SAMP = 0;         // Stop sampling
    AD1CON1bits.ADON = 0;         // Turn off ADC
    return (ADCvalue);            // Returns 10 bit ADC output stored in ADC1BIF0
}
