/* 
 * File:   uart.h
 * Author: ARPITHA J
 *
 * Created on 7 January, 2025, 7:15 PM
 */

#ifndef SCI_H
#define SCI_H

//Macro for transmit and recieve
#define RX_PIN					TRISC7
#define TX_PIN					TRISC6

//Fun declarations
void init_uart(void);
void putch(unsigned char byte);
int puts(const char *s);


#endif

