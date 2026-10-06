/* 
 * File:   i2c.h
 * Author: ARPITHA J
 *
 * Created on 9 January, 2025, 9:36 AM
 */

#ifndef I2C_H
#define I2C_H

//Fun declarations
void init_i2c(void);
void i2c_start(void);
void i2c_rep_start(void);
void i2c_stop(void);
void i2c_write(unsigned char data);
unsigned char i2c_read(void);

#endif
