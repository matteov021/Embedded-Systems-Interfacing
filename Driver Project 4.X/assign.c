/*
 * File:   assign.c
 * Created on November 3, 2023, 1:18 PM
 */

#include "xc.h"
#include "assign.h"

#define DEBOUNCE while(count < 750)(count++); count = 0;
#define PB1 PORTAbits.RA2
#define PB2 PORTAbits.RA4
#define PB3 PORTBbits.RB4
#define LED LATBbits.LATB8
#define PB1S PB1_state
#define PB2S PB2_state
#define PB3S PB3_state
#define S0 0
#define S1 1
extern uint16_t PB1_state;
extern uint16_t PB2_state;
extern uint16_t PB3_state;
extern uint16_t flag1;
extern uint16_t flag2;
extern uint16_t flag3;
uint16_t state = S0;
uint16_t count = 0;

void IOAssign(){
    
    DEBOUNCE;               // De-bounce for inputs to stabilize
    PB1S = PB1;             // Check PB1 For Press, Assign a State (0 For Press)
    PB2S = PB2;             // Check PB2 For Press, Assign a State (0 For Press)
    PB3S = PB3;             // Check PB3 For Press, Assign a State (0 For Press)
       
    if(state == S0){        // Fast Mode Loop (S0)
        
        if((PB1S | PB2S | PB3S) == 0){                  // Check All 3 PB Press
            Disp2String("Switching State...\n\r");      
            Disp2String("Slow Mode: IDLE\n\r");
            T2CONbits.TON = 0;                          // Turn Of Timer
            LED = 0;                                    // Turn Off LED
            state = S1;                                 // Switch State To S1
            ClearIO();                                  // Clear IO
            ClearFlag();                                // Clear Flags
        }    
        
        if((!PB1S & !PB2S & PB3S) | (!PB1S & PB2S & !PB3S) | (PB1S & !PB2S & !PB3S)){           // Check For 2PB Pressed
            T2CONbits.TON = 0;                                                                  // Turn Off Timer
            LED = 1;                                                                            // Turn On LED
            SetFlag();                                                                          // Set All Flags To 1
            if(PB1S)                                                                            // Check For PB2 & PB3
                Disp2String("Fast Mode: PB2 and PB3 are pressed\n\r");  
            if(PB2S)                                                                            // Check For PB2 & PB3
                Disp2String("Fast Mode: PB1 and PB3 are pressed\n\r"); 
            if(PB3S)                                                                            // Check For PB2 & PB3
                Disp2String("Fast Mode: PB1 and PB2 are pressed\n\r"); 
            ClearIO();                                                                          // Clear IO
        }
                
        if(PB1S == 0 & flag1){                                                                  // Check PB1 Pressed and flag = 1
            ClearFlag();                                                                        // Clear all flags (Used for module above)
            Disp2String("Fast Mode: IDLE\n\r");                                                 // Display Idle Mode
            T2CONbits.TON = 0;                                                                  // Turn Timer Off
            LED = 0;                                                                            // Turn off LED for idle
        }else if(PB1S == 0 & !flag1){                                                           // Check PB1 pressed and flag = 0
            Disp2String("Fast Mode: PB1 Is Pressed\n\r");                                       // Display mode
            ClearFlag();                                                                        // Clear flags
            delay_ms(244);                                                                      // Call Delay (Solved with PR2 * (2/FCLK) * 256 = Delay
            flag1 = 1;                                                                          // Set flag To 1
        }                                                                                       
                                                                                                // Everything above applies to all other modules / PB Presses for fast and slow mode
        if(PB2S == 0 & flag2){
            ClearFlag();
            Disp2String("Fast Mode: IDLE\n\r");
            T2CONbits.TON = 0;
            LED = 0;
        }else if(PB2S == 0 & !flag2){
            Disp2String("Fast Mode: PB2 Is Pressed\n\r"); 
            ClearFlag();
            delay_ms(488);
            flag2 = 1;
        }

        if(PB3S == 0 & flag3){
            ClearFlag();
            Disp2String("Fast Mode: IDLE\n\r");
            T2CONbits.TON = 0;
            LED = 0;
        }else if(PB3S == 0 & !flag3){
            Disp2String("Fast Mode: PB3 Is Pressed\n\r"); 
            ClearFlag();
            delay_ms(975); // 1 Sec Time
            flag3 = 1;
        }   
    }
    
    else{                                   // Slow Mode Loop (S1)
        if((PB1S | PB2S | PB3S) == 0){
            Disp2String("Switching State...\n\r");
            Disp2String("Fast Mode: IDLE\n\r");
            T2CONbits.TON = 0;
            LED = 0;
            state = S0;
            ClearIO();
            ClearFlag();
        }    
        
        if(PB1S == 0 & flag1){
            ClearFlag();
            Disp2String("Slow Mode: IDLE\n\r");
            T2CONbits.TON = 0;
            LED = 0;
        }else if(PB1S == 0 & !flag1){
            Disp2String("Slow Mode: PB1 Is Pressed\n\r"); 
            ClearFlag();
            delay_ms(4875);
            flag1 = 1;
        }

        if(PB2S == 0 & flag2){
            ClearFlag();
            Disp2String("Slow Mode: IDLE\n\r");
            T2CONbits.TON = 0;
            LED = 0;
        }else if(PB2S == 0 & !flag2){
            Disp2String("Slow Mode: PB2 Is Pressed\n\r"); 
            ClearFlag();
            delay_ms(2925);
            flag2 = 1;
        }  
    }
    
    return;
}
