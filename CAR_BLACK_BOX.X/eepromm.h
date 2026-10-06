/* 
 * File:   eepromm.h
 * Author: ARPITHA J
 *
 * Created on 4 January, 2025, 6:58 PM
 */

#ifndef External_H
#define External_H
//Macro for Slave read & write Address
#define SLAVE_READ		0xA1
#define SLAVE_WRITE		0xA0

//Macro for all address
//#define SEC_ADDR		0x00
//#define MIN_ADDR		0x01
//#define HOUR_ADDR		0x02
//#define DAY_ADDR		0x03
//#define DATE_ADDR		0x04
//#define MONTH_ADDR		0x05
//#define YEAR_ADDR		0x06
//#define CNTL_ADDR		0x07

//Fun declarations
void write_external_eeprom(unsigned char address1, unsigned char data);
unsigned char read_external_eeprom(unsigned char address1);

#endif