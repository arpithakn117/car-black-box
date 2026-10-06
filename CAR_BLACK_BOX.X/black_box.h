/* 
 * File:   black_box.h
 * Author: ARPITHA J
 *
 * Created on 30 December, 2024, 9:00 AM
 */


#ifndef BLACK_BOX_H
#define BLACK_BOX_H

#include <xc.h>
#include "clcd.h"
#include "eepromm.h"
#include "uart.h"
#include "i2c.h"
#include "ds_1307.h"

//Enum for switch case

typedef enum {
    e_dashboard, e_main_menu, e_view_log, e_clear_log, e_set_time, e_download_log
} State_t;


extern State_t state; // App state

//Function declarations
void init_adc();
unsigned short read_adc();
void init_matrix_keypad();
unsigned char scan_key();
unsigned char read_matrix_keypad(unsigned char detection);
void get_time(void);
void display_time(void);

//Dashboard function declaration
void view_dashboard(void);

//Storing events function declaration
void event_store(void);

//main menu function declaration
void display_main_menu(void);

//View log function declaration
void view_log(void);

//Reading events function declaration
void event_reader(void);

//Set time function declaration
void set_time(void);

//Download log function _decleration
void download_log(void);

//Clear log function declaration
void clear_log(void);

#endif