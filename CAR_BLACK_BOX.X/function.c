/*
 * File:   function.c
 * Author: ARPITHA J
 *
 * Created on 30 December, 2024, 10:28 PM
 */

#include "black_box.h"

void init_adc() {
    CHS3 = 0; //channel 4
    CHS2 = 1;
    CHS1 = 0;
    CHS0 = 0;

    GO = 0; //no conversion

    ADON = 1; //adc enabled

    VCFG1 = 0; //no ref vg
    VCFG0 = 0;

    PCFG3 = 1; //make an4 as analog
    PCFG2 = 0;
    PCFG1 = 1;
    PCFG0 = 0;

    ADFM = 1; //right justified

    ADCS2 = 0; //0.625Mhz of adc conversion clk
    ADCS1 = 1;
    ADCS0 = 0;

    ACQT2 = 1; //8 Tad(12.86usec ACQ time)
    ACQT1 = 0;
    ACQT0 = 0;
}

unsigned short read_adc() {
    GO = 1; //initiate conversion
    while (GO); //wait till conversion complete
    return ADRESL | (ADRESH << 8); //fetch value from adc reg
}

void init_matrix_keypad() {
    TRISB = 0X1E;
    RBPU = 0;
    RB5 = RB6 = RB7 = 1;
}

unsigned char scan_key() {
    RB5 = 0;
    RB6 = RB7 = 1;
    if (RB1 == 0)
        return 1;
    else if (RB2 == 0)
        return 4;
    else if (RB3 == 0)
        return 7;
    else if (RB4 == 0)
        return 10;
    RB6 = 0;
    RB5 = RB7 = 1;
    if (RB1 == 0)
        return 2;
    else if (RB2 == 0)
        return 5;
    else if (RB3 == 0)
        return 8;
    else if (RB4 == 0)
        return 11;
    RB7 = 0;
    RB6 = RB5 = 1;
    if (RB1 == 0)
        return 3;
    else if (RB2 == 0)
        return 6;
    else if (RB3 == 0)
        return 9;
    else if (RB4 == 0)
        return 12;
    else
        return 0XFF;
}

unsigned char read_matrix_keypad(unsigned char detection) {
    static unsigned char once = 1;
    unsigned char key = scan_key();
    if (detection == 0)//level
    {

        return key;
    } else if (detection == 1)//edge
    {
        if (key != 0XFF && once) {
            once = 0;
            return key;
        } else if (key == 0XFF) {
            once = 1;
        }
        //        return 0XFF;
    }
    return 0XFF;
}
unsigned char clock_reg[3];
extern unsigned char time[9];

void get_time(void) {
    clock_reg[0] = read_ds1307(HOUR_ADDR);
    clock_reg[1] = read_ds1307(MIN_ADDR);
    clock_reg[2] = read_ds1307(SEC_ADDR);
    //    char time[9];
    if (clock_reg[0] & 0x40) {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
        time[1] = '0' + (clock_reg[0] & 0x0F);
    } else {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
        time[1] = '0' + (clock_reg[0] & 0x0F);
    }
    time[2] = ':';
    time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
    time[4] = '0' + (clock_reg[1] & 0x0F);
    time[5] = ':';
    time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
    time[7] = '0' + (clock_reg[2] & 0x0F);
    time[8] = '\0';

    //    clcd_print(time,LINE2(0));
}
