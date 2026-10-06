/*
 * File:   clcd.c
 * Author: ARPITHA J
 *
 * Created on 30 December, 2024, 10:00 PM
 */

#include "black_box.h"

//DATA 

void clcd_write(unsigned char byte, unsigned char control_bit) {
    CLCD_RS = control_bit; //RS=0;//RW IS INITIAL AS 0 NO NEED
    CLCD_PORT = byte; //PORTD = DATA 2ND POS

    /* Should be atleast 200ns */
    CLCD_EN = HI; //E=1;
    CLCD_EN = LO; //E=0;

    PORT_DIR = INPUT; //TRISD7=1;
    CLCD_RW = HI; //RW=1;
    CLCD_RS = INSTRUCTION_COMMAND; //RS=0

    do {
        CLCD_EN = HI; //E=1;
        CLCD_EN = LO; //E=0;
    } while (CLCD_BUSY); //WHILE(RD7)

    CLCD_RW = LO; //RW=0;
    PORT_DIR = OUTPUT; //TRISD7=0;
}

void init_clcd() {
    /* Set PortD as output port for CLCD data */
    TRISD = 0x00; // DATA LINES
    /* Set PortC as output port for CLCD control */
    TRISC = TRISC & 0xF8; //CLEAR TRISC2,1,0 = 0

    CLCD_RW = LO; //RC0 = 0, SELECT THE WRITE OPERATION


    /* Startup Time for the CLCD controller */
    __delay_ms(30); //DELAY 30SEC MORE THAN 20SEC

    /* The CLCD Startup Sequence */
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND); //FUNTION OF CLCD 0X33 , 0... LSB BIT IS NOT MAN MSB IS MUST 3 => 30
    __delay_us(4100);
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND);
    __delay_us(100);
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND);
    __delay_us(1);

    CURSOR_HOME; //clcd_write(0x02, INSTRUCTION_COMMAND)//0X02, 0
    __delay_us(100);
    TWO_LINE_5x8_MATRIX_8_BIT; //clcd_write(0x38, 0)
    __delay_us(100);
    CLEAR_DISP_SCREEN; //clcd_write(0x01, 0)
    __delay_us(500);
    DISP_ON_AND_CURSOR_OFF; //clcd_write(0x0C, 0)
    __delay_us(100);
}

void clcd_print(const unsigned char *data, unsigned char addr) {
    clcd_write(addr, INSTRUCTION_COMMAND); //WRITE 0X80+2, 0=>2ND POS//ADDRESS//FOR INST IS 0
    while (*data != '\0')//UPTO NULL CHAR
    {
        clcd_write(*data++, DATA_COMMAND); //('K', 1)//DATA
    }
}

void clcd_putch(const unsigned char data, unsigned char addr) {
    clcd_write(addr, INSTRUCTION_COMMAND); //WRITE 0X80+2, 0=>2ND POS
    clcd_write(data, DATA_COMMAND); //('K', 1)FOR DATA IS 1
}
