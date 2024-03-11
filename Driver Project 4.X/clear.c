/*
 * File:   clear.c
 *
 * Created on November 3, 2023, 1:13 PM
 */

#include "xc.h"
#include "clear.h"

#define PB1S PB1_state
#define PB2S PB2_state
#define PB3S PB3_state
uint16_t PB1_state = 0;
uint16_t PB2_state = 0;
uint16_t PB3_state = 0;
uint16_t flag1 = 0;
uint16_t flag2 = 0;
uint16_t flag3 = 0;

void ClearIO(){              // Set All PB States to 1 (Pulled Up By Default)
    PB1S = 1;
    PB2S = 1;
    PB3S = 1;
    return;
}

void ClearFlag(){            // Set All Flags To 0
    flag1 = 0;
    flag2 = 0;
    flag3 = 0;
    return;
}

void SetFlag(){             // Set All Flags To 1
    flag1 = 1;
    flag2 = 1;
    flag3 = 1;
    return;
}
