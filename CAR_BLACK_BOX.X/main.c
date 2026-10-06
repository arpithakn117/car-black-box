/*
 * File:   main.c
 * Author: ARPITHA J
 *
 * Created on 30 December, 2024, 8:59 AM
 */

#include "black_box.h"

State_t state;

void init_config() {

    state = e_dashboard;

}
unsigned char key;

void main(void) {
    init_config(); //Functions calls
    init_matrix_keypad();
    init_clcd();
    init_adc();
    init_uart();
    init_i2c();
    init_ds1307();

    while (1) {
        // Detect key press
        key = read_matrix_keypad(1);

        switch (state) {
            case e_dashboard:
                // Display dashboard
                view_dashboard();
                break;

            case e_main_menu:
                // Display dashboard
                display_main_menu();
                break;

            case e_view_log:
                // Display dashboard
                view_log();
                break;

            case e_download_log:
                download_log();
                break;

            case e_clear_log:
                clear_log();
                break;                 
                                      
            case e_set_time:
                set_time();
                break;

        }

    }

}
