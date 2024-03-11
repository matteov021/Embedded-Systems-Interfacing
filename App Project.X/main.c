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
#include "attribute.h"
#include "delay.h"

#define LOCKED 0
#define CHAR1 1
#define CHAR2 2
#define NUM 3
#define UNLOCKED 4
#define SPECIAL 5
#define NEWPASSWORD 6
#define ERROR 7

#define PB1 PORTAbits.RA2
#define PB2 PORTAbits.RA4
#define PB3 PORTBbits.RB4
#define LED2 LATAbits.LATA6
#define LED LATBbits.LATB8

uint16_t state = LOCKED;
uint16_t timeout;
int ADC_password = 5;
int ADC_temp;
char password1 = 'a';
char password2 = 'b';
char password3 = 'c';
char character;

extern uint16_t CNFlag;
extern uint8_t RXFlag;
extern uint16_t ADC_val_scaled;

extern uint16_t Flag1;
extern uint16_t Flag2;
extern uint16_t Flag3;

uint32_t PWM_count = 512;

int main(void) {
    
    InitIO();                               // Initialize IO 
    InitUART2();                            // Initialize UART2 module
    newClk(500);                            // Set CLK to 500 KHz
    ClearUART();                            // Clear UART
    
    Disp2String("Welcome! Enter 1st Character: ");      // Upon Program Start
    
    while(1){   
        switch(state){
            case LOCKED:
                PWM_count = 512;
                LED = 1;
                Idle();
                if(RXFlag == 1){                                                            // Run If Input Detected                                                           // Reset RX Flag 
                    character = RecvUartChar();                                             // Store Input Into Array
                    if(character == password1){                                             // Check If First Character Is First Password Character
                        Disp2String("\r\nCorrect 1st Character. Enter 2nd Character: ");    // Display Correct Message
                        state = CHAR1;                                                      // Change To State CHAR1
                    }
                    else{
                        Disp2String("\r\nIncorrect 1st Character, Press PB2 To Restart");   // Display Error Message
                        state = ERROR;                                                      // Change To Error State
                    }
                } 
                break;
            
            case CHAR1:
                if(RXFlag == 0){
                    delay_ms(488);  // 0.5s (1s is 975)
                    timeout = timeout + 1;
                    if(timeout > 100){                                                      // 50 Blinks
                        ClearUART();
                        Disp2String("Session Timeout, Please Press PB2 To Restart");
                        state = ERROR;
                    }
                }
                if(RXFlag == 1){                                                            // Run If Input Detected 
                    timeout = 0;                                                            // Clear Timeout
                    character = RecvUartChar();                                             // Store Input Into Array
                    if(character == password2){                                             // Check If Second Character Is Second Password Character
                        Disp2String("\r\nCorrect 2st Character. Enter 3nd Character: ");    // Display Correct Message
                        state = CHAR2;                                                      // Change To State CHAR1
                    }
                    else{
                        Disp2String("\r\nIncorrect 2nd Character, Press PB2 To Restart");   // Display Error Message
                        state = ERROR;                                                      // Change To Error State
                    }
                } 
                break;
            
            case CHAR2:               
                if(RXFlag == 0){
                    delay_ms(244); // 0.25s
                    timeout = timeout + 1;
                    if(timeout > 100){                                                      // 50 Blinks
                        ClearUART();
                        Disp2String("Session Timeout, Please Press PB2 To Restart");
                        state = ERROR;
                    }
                }
                if(RXFlag == 1){                                                            // Run If Input Detected 
                    timeout = 0;                                                            // Clear Timeout
                    character = RecvUartChar();                                             // Store Input Into Array
                    if(character == password3){                                             // Check If Third Character Is Third Password Character
                        Disp2String("\r\nCorrect 3rd Character.\r\n");                      // Display Correct Message
                        state = NUM;                                                        // Change To State NUM
                    }
                    else{
                        Disp2String("\r\nIncorrect 3rd Character, Press PB2 To Restart.");  // Display Error Message
                        state = ERROR;                                                      // Change To Error State
                    }
                } 
                break;
            
            case NUM:
                displayBar();
                if(Flag2){
                    Flag2 = 0;
                    if(ADC_val_scaled == ADC_password){
                        Disp2String("Correct Unlock Number. Entering Unlocked State...");       // Display Correct Message
                        ClearUART();                                                            // Clear UART Screen
                        Disp2String("Device Unlocked");                                         // Display Correct Message                        
                        Disp2String("\r\nPress PB1 To Lock System.");                           // Display Correct Message
                        Disp2String("\r\nPress PB2 To Enter A New Password.");                  // Display Correct Message
                        Disp2String("\r\nPress PB3 To Enter Special Mode.");                    // Display Correct Message
                        state = UNLOCKED;                                                       // Go To Unlocked State
                    }
                    else{
                        Disp2String("\r\nIncorrect Unlock Number, Press PB2 To Restart.");      // Display Error Message
                        state = ERROR;                                                          // Change To Error State 
                    }
                }
                else{
                    delay_ms(1);
                    timeout = timeout + 1;
                    if(timeout > 100){                                                          // 50 Blinks
                        ClearUART();
                        Disp2String("Session Timeout, Please Press PB2 To Restart");
                        state = ERROR;
                    }
                }
                break;
            
            case UNLOCKED:
                LED = 0;                                                                        // Set LED OFF
                timeout = 0;                                                                    // Clear Timeout
                if(Flag1){                                                                      // Locked State
                    Flag1 = 0;
                    ClearUART();
                    Disp2String("Locking System...");                                           // Display Correct Message
                    ClearUART();                                                                // Clear UART
                    Disp2String("Welcome! Enter 1st Character: ");                              // Reset System
                    state = LOCKED;
                }
                
                if(Flag2){                                                                      // Password State
                    Flag2 = 0;
                    ClearUART();                                                                // Clear UART
                    Disp2String("Please Enter First Character: ");                              // Display Password Changing Message                   
                    state = NEWPASSWORD;                                                        // Change State
                }

                if(Flag3){
                    Flag3 = 0;
                    Disp2String("\r\nEntering Special Mode... ");                                   // Display Password Changing Message   
                    ClearUART();                                                                    // ClearUART
                    Disp2Dec((PWM_count * 100) / 1023);                                             // Increment PWM_Count
                    Disp2String("%");                                                               // Display 50% Initial
                    ClearUART();
                    state = SPECIAL;
                }
                
                break;             
            
            case NEWPASSWORD:               
                password1 = RecvUartChar();                                                   // Save First Character
                Disp2String("\r\nFirst Character Saved. Please Enter Second Character: ");
                password2 = RecvUartChar();                                                   // Save Second Character
                Disp2String("\r\nSecond Character Saved. Please Enter Third Character: ");                  
                password3 = RecvUartChar();                                                   // Save Third Character
                Disp2String("\r\nThird Character Saved. Please Enter New ADC Number: ");                 
                
                ADC_temp = RecvUartChar();                                                     // Temp Value
                if(ADC_temp >= 48 && ADC_temp <= 57)                                           // Check If New ADC Input is 0-9
                    ADC_password = ADC_temp - 48;                                              // Assign ADC to decimal conversion
                else
                    Disp2String("\r\nADC Number Has Not Been Saved Please Enter A Digit Between 0 and 9.");
                
                Disp2String("\r\nPassword Has Been Changed Successfully.");
                Disp2String("\r\nReturning To Locked State...");                  
                ClearUART();                                                        // Clear UART
                ClearUART();
                ClearUART();
                Disp2String("Welcome! Enter 1st Character: ");
                state = LOCKED;                                                     // Return To Locked State
                break;
            
            case SPECIAL:
                
                PWM(PWM_count);                                                         // Call PWM Module
               
                if(Flag3 && PWM_count < 920){
                    Flag3 = 0;
                    PWM_count += 100;                                                   // Display % Value
                    Disp2Dec((PWM_count * 100) / 1023);                                 // Increment PWM_Count
                    Disp2String("%");                                                   // Display %
                    ClearUART();
                }
                else 
                    Flag3 = 0;
                if(Flag2 && PWM_count > 110){
                    Flag2 = 0;
                    PWM_count -= 100;                                                   // Decrement PWM_Count
                    Disp2Dec((PWM_count * 100) / 1023);                                 // Display % Value
                    Disp2String("%");                                                   // Display %
                    ClearUART();
                }
                else 
                    Flag2 = 0;                                                          // Clear Flag
                if(Flag1){
                    Flag1 = 0;                                                          // Reset Flag
                    OC1CONbits.OCM = 0;                                                 // Turn Off PWM Module For LED OFF
                    Disp2String("\r\nReturning To Locked State");
                    ClearUART();
                    Disp2String("Welcome! Enter 1st Character: ");
                    state = LOCKED;                                                     // Lock System
                }
                else 
                    Flag1 = 0;
                    
                break;
            
            case ERROR:
                LED = 0;                                                                         // Clear LED 
                timeout = 0;                                                                     // Clear Timeout
                if(Flag2){                                                                       // Locked State
                    Flag2 = 0;                                                                   // Reset Flag2 
                    Disp2String("\r\nResetting System...");                                      // Display Correct Message
                    ClearUART();                                                                 // Clear UART
                    Disp2String("Welcome! Enter 1st Character: ");                               // Reset System
                    state = LOCKED;
                }
                break;             
        }    
    }
    return 0;
}
