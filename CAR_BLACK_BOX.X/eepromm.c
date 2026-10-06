/*
 * File:   eepromm.c
 * Author: ARPITHA J
 *
 * Created on 6 January, 2025, 7:49 AM
 */


#include "black_box.h"
#define SLAVE_READ		0xA1
#define SLAVE_WRITE		0xA0

void write_external_eeprom(unsigned char address, unsigned char data) {
    i2c_start();
    i2c_write(SLAVE_WRITE);
    i2c_write(address);
    i2c_write(data);
    i2c_stop();
    for (unsigned int delay = 3000; delay > 0; delay--);
}

unsigned char read_external_eeprom(unsigned char address) {
    unsigned char data;

    i2c_start();
    i2c_write(SLAVE_WRITE);
    i2c_write(address);
    i2c_rep_start();
    i2c_write(SLAVE_READ);
    data = i2c_read();
    i2c_stop();

    return data;
}