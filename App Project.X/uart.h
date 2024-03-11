// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef UART_H
#define	UART_H

#include <xc.h> // include processor files - each processor file is guarded.  

void InitUART2(void);
void Disp2String(char *str);
void XmitUART2(char CharNum, unsigned int repeatNo);
void RecvUart(char* input, uint8_t buf_size);
char RecvUartChar(void);
void Disp2Hex(unsigned int DispData);
void Disp2Dec(uint16_t Dec_num);
void ClearUART(void);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

