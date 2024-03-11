/*
 * File:   IO.c
 *
 * Created on November 22, 2023, 7:40 PM
 */

#include "xc.h"
#include "IO.h"
#include "uart.h"
#include "ADC.h"

int flag;
extern uint8_t RXFlag;
char character;

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
    
    for(int i = 0;i<num;i++)
    {
        array[i] = '#';      // Add # based on number count to the array
    }
    array[num] = '\0';       // Fill end of array with null
    
    // Check if RXFlag is a 1. This means a keyboard input is detected
    // Call RecvUartChar to store and return the character into 'character'
    // Check if character is 'x' or 'd' and set a flag for each state
    // If character is not 'x' or 'd', display error and do not change the flag
    
    if(RXFlag == 1){        
        character = RecvUartChar();
        if(character == 'x'){
            flag = 1;
            ClearUART();
        }
        else if(character == 'd'){
            flag = 0;
            ClearUART();
        }    
        else{
        Disp2String("Please Press 'x' Or 'd' To Switch Format\r\n");
        ClearUART();
        }
    }
    
    // If flag == 1, use hex display
    // If flag == 0, use decimal display
    
    if(flag == 1){
        Disp2String(array);          // Display # Bar Graph
        Disp2Hex(ADC_val);           // Display analog input in hex
        ClearUART();                 // Clear UART Display
    }
    else{
        Disp2String(array);          // Display # Bar Graph
        Disp2Dec(ADC_val);           // Display analog input in decimal
        ClearUART();                 // Clear UART Display
    }  
}
