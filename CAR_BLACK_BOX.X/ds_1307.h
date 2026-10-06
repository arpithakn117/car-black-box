/* 
 * File:   ds_1307.h
 * Author: ARPITHA J
 *
 * Created on 10 January, 2025, 8:27 AM
 */

#ifndef Ds_1307_H
#define Ds_1307_H
//Macro for Slave read & write Address
#define SLAVE_READ1		0xD1
#define SLAVE_WRITE1		0xD0

//Macro for all address
#define SEC_ADDR		0x00
#define MIN_ADDR		0x01
#define HOUR_ADDR		0x02
#define DAY_ADDR		0x03
#define DATE_ADDR		0x04
#define MONTH_ADDR		0x05
#define YEAR_ADDR		0x06
#define CNTL_ADDR		0x07

//Fun declarations
void init_ds1307(void);
void write_ds1307(unsigned char address1, unsigned char data);
unsigned char read_ds1307(unsigned char address1);

#endif