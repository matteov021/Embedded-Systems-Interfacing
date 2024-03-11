/*
 * File:   Project1.c
 *
 * Created on September 19, 2023, 8:58 AM
 */

#include "xc.h"

#define PIN1 PORTAbits.RA0
#define PIN2 PORTAbits.RA1
#define PIN3 PORTAbits.RA4
#define PIN4 PORTAbits.RA6

// Display LED's Based On Digit Number
void display (int digit){
    
    if (digit == 0)
        LATB = 0b0000000000000000; // 0 On    
    else if (digit == 1)
        LATB = 0b0000000000000001; // 1 On
    else if (digit == 2)
        LATB = 0b0000000000000011; // 2 On
    else if (digit == 3)
        LATB = 0b0000000000000111; // 3 On    
    else if (digit == 4)
        LATB = 0b0000000000010111; // 4 On    
    else if (digit == 5)
        LATB = 0b0000000010010111; // 5 On  
    else if (digit == 6)
        LATB = 0b0000000110010111; // 6 On    
    else if (digit == 7)
        LATB = 0b0000001110010111; // 7 On    
    else if (digit == 8)
        LATB = 0b0001001110010111; // 8 On    
    else if (digit == 9)
        LATB = 0b0011001110010111; // 9 On
}

int main(void) {

    // Setup Variables And In/Out Pins
    // Output Using 0,1,2,4,7,8,9,12,13
    // Input Using 0,1,4,6
    TRISB = 0b0000000000000000; 
    TRISA = 0b01010011;
     
    // Define UCID
    int32_t num = 301404070;
    
    // Generate An Array For The UCID
    // Get The Right Most Digit -> Append To Array -> Remove Right Most Digit -> Repeat Until All Digits Are Consumed
    int arr[9];
    for (int i = 8; i >= 0; i--) {
        arr[i] = num % 10;
        num /= 10;
    }
    int break_point = 0;
    // Concatenate User Input To Decimal Form (Take The 4 Binary Values And Combine RA0(MSB))
    // Check User Input And Use As Index For UCID Array (Only 9 Or Less Will Run Through Display)
    while(1){
        int concat_input = (PIN1 << 3) | (PIN2 << 2) | (PIN3 << 1) | PIN4;
            if (concat_input > 9 || concat_input == 0){
                LATB = 0b0000000000000000; // Displays 0 For Anything Not In A Possible Index >9 or 0
            }
            else{
                display(arr[concat_input - 1]); // Display Index Of User Input (Ex. 0001 Displays MSB Of UCID)
            }
    }
    
    return 0;
}
