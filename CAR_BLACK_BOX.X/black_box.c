/*
 * File:   black_box.c
 * Author: ARPITHA J
 *
 * Created on 30 December, 2024, 9:56 PM
 */

#include "black_box.h"

#define XTAL__FREAQ 20000000
unsigned int ind = 0; //Global variable for index intial zero
unsigned char speed = 0; //Global variable for speed intial zero
unsigned char key; //Global variable for key 
unsigned char count = 0; //Global variable for count intial zero
extern char once; //Global variable for once intial zero
unsigned int min, hour, sec;
unsigned char time[9]; //Global variable for time array
unsigned char gear[9][3] = {"ON", "GN", "G1", "G2", "G3", "G4", "G5", "GR", "C "}; //Global variable for gear 
unsigned char menu[4][20] = {"   VIEW LOG      ", "   CLEAR LOG    ", "   SET LOG      ", "   DOWNLOAD LOG "}; //Global variable for menu array

void view_dashboard(void) //Fun defination view dashboard
{
    clcd_print("TIME      EV  SP", LINE1(0)); //In clcd 1st line print
    clcd_print(time, LINE2(0));
    clcd_print(gear[ind], LINE2(10)); //In clcd  when switch is pressed change the gear index in line2(10)
    unsigned char key = read_matrix_keypad(1); //Call the matrix keypad

    get_time(); //call the get time function
    if (key == 1) //If Pressed SW1  
    {
        if (ind == 8) // Index is equal to 8 
            ind = 1; // Index is one becoz it should not decrease or increase
        else if (ind < 7)//else if ind < 7 increase the index
            ind++;
        event_store(); //When ever SW preseed event fun call becoz store the events
    } else if (key == 2) //If Pressed SW2 
    {
        if (ind == 8) // Index is equal to 8
            ind = 1; // Index is one becoz it should not decrease or increase
        else if (ind > 1)//else if ind > 7 decrease the index
            ind--;
        event_store(); //When ever SW preseed event fun call becoz store the events
    } else if (key == 3) //If Pressed SW3 means collision happens
    {
        ind = 8; //index is 8 
        event_store(); //When ever SW preseed event fun call becoz store the events
    }
    speed = read_adc() / 10.33; //call the read_adc function for speed return the value by convert 0 to 99 we use 10.33
    clcd_putch((speed / 10) + '0', LINE2(14)); //Its return 2 digit value so we get 1st value by using putch line2(14)
    clcd_putch((speed % 10) + '0', LINE2(15)); //Its return 2 digit value so we get 1st value by using putch line2(15)

    if (key == 11) //When SW 11 pressed
    {
        state = e_main_menu; //enetr the main menu its display the menu
    }

}

void display_main_menu(void) ////Fun defination display main menu
{
    static char star_flag = 0, ind_menu, menu_pos = 0; //static variables

    if (star_flag == 0) //if star flag is equal to 0
    {
        clcd_putch('*', LINE1(0)); //line1 will * printed
        clcd_putch(' ', LINE2(0)); //line2 will space printed
    } else {
        clcd_putch(' ', LINE1(0)); //line1 will space printed
        clcd_putch('*', LINE2(0)); //line2 will * printed
    }
    if (key == 1) //if SW 1 pressed
    {
        if (ind_menu > 0) //index menu less than zero decrease the index menu
        {
            ind_menu--;
        }
        if (star_flag == 1) //Then star flag is equal to one make it as zero
            star_flag = 0;
        else {
            if (menu_pos > 0)//else menu position less than zero decrease the menu_pos
                menu_pos--;
        }
    } else if (key == 2) //if SW 2 pressed
    {
        if (ind_menu < 3) //index menu less than three increase the index menu
        {
            ind_menu++;
        }
        if (star_flag == 0) //Then star flag is equal to one make it as 1
            star_flag = 1;
        else {
            if (menu_pos < 2)//else menu position less than two increase the menu_pos
                menu_pos++;
        }
    }

    clcd_print(menu[menu_pos], LINE1(1)); //clcd print menu of menupostion in line1
    clcd_print(menu[menu_pos + 1], LINE2(1)); //clcd print menu of menupostion in line2 menas next index

    if (key == 11) //if Sw11 pressed 
    {
        state = ind_menu + 2; // 1st tym index will zero go to 2 index and when index 1 that is 3 state
    }
//    if(key == 11)
//    {
//        state = e_main_menu;
//    }
    else if(key == 12)
    {
        CLEAR_DISP_SCREEN;
        state = e_dashboard;
    }
}

void event_store(void) //Fun defination event store
{
    unsigned char store[10]; //declare the store the array for events 
    unsigned int address; //declare the variables
    unsigned int i;

    store[0] = time[0]; // store of 0 index fecth the value of time of 0
    store[1] = time[1]; // store of 1 index fecth the value of time of 1
    store[2] = time[3]; // store of 2 index fecth the value of time of 3
    store[3] = time[4]; // store of 3 index fecth the value of time of 4
    store[4] = time[6]; // store of 4 index fecth the value of time of 6
    store[5] = time[7]; // store of 5 index fecth the value of time of 7
    store[6] = gear[ind][0]; // store of 6 index fecth the value of gear of 0 of 0
    store[7] = gear[ind][1]; // store of 7 index fecth the value of gear of 0 of 1
    store[8] = speed / 10 + '0'; // store of 8 index fecth the value of speed of 1st digit
    store[9] = speed % 10 + '0'; // store of 8 index fecth the value of speed of 2nd digit

    if (count == 10) //We store 10 events if count as 10 
    {
        address = 0X00; // initial address is 0

        for (i = 0; i < 90; i++) //Loop runs < 90
        {
            write_external_eeprom(address, read_external_eeprom(address + 10)); //write the event in external eeprom 10 digits of event
            address++; // increase address
        }
        count = 9; //when loop exit count as 9 becoz next data will point to 10 address than swap the address
    }

    for (i = 0; i < 10; i++) //loop runs 0 to 9
    {
        write_external_eeprom(count * 10 + i, store[i]); //write the data digit by digit data will bwe store of array
    }
    count++; // increase the count
}

void view_log(void) //Fun defination of view log
{
    unsigned char j = 0, i = 0; //declare the variables
    static unsigned int address = 0X00, once = 1, ind = 0; //declare the static variables
    static unsigned char view[10][17] = {}; //declare the static variable of array
    clcd_print("# TIME     EV SP", LINE1(0)); //in clcd 1st line will print this
    if (once) // if once means true
    {
        for (i = 0; i < count; i++) //loop runs less than count
        {
            j = 0; //j is zero
            view[i][j] = i + '0'; //clcd is 1st index means serial no printed
            for (j = 1; j < 16; j++) //loop runs < 16 we have clcd 16 digits
            {
                if (j == 1 || j == 10 || j == 13) //if j == 1, 10, 13
                {
                    view[i][j] = ' '; // view log will be space
                } else if (j == 4 || j == 7) // if j == 4, 7
                {
                    view[i][j] = ':'; // view log will be colon
                } else {
                    view[i][j] = read_external_eeprom(address++); // else fecth the values in external eeprom
                }
            }
            view[i][j] = '\0'; // add the null chacter
        }
        once = 0; // once make it as 0 
    }

    if (key == 1 && ind < count - 1) // if SW1 and index will be count - 1 increase the index
    {
        ind++;
    } else if (key == 2 && ind > 0) // if SW2 and index will be > 0 decrease the index
    {
        ind--;
    }
    if (key == 12) // if SW 12 exit enter the main menu
    {
        state = e_main_menu;
        once = 1; // once is 1 becoz agian loop runs
        ind = 0; // index also 0 index start
        address = 0; // address is also 0
    }
    if (count == 0) // if there is no data menas count is zero
    {
        CLEAR_DISP_SCREEN; //clear display
        clcd_print("NO LOG R PRESENT", LINE1(0)); //clcd print no log are present
        clcd_print("                ", LINE2(0));
        for (unsigned long int delay = 500; delay--;) //clcd print no log are present
            for (unsigned long int delay1 = 1000; delay1--;);
        state = e_main_menu; //again go back to main menu

    } else {
        clcd_print(view[ind], LINE2(0)); // otherwise diplay the data
    }
}

void download_log(void) //Fun defination
{
    unsigned char j = 0, i = 0; // declare the variables
    static unsigned int address = 0X00; // declare the static variables
    unsigned char download_view[10][17]; //// declare the variable array
    puts("# TIME     EV SP\n\r"); //In tera term appliaction display
    for (i = 0; i < count; i++) //loop runs less than count
    {
        j = 0; //j is zero
        download_view[i][j] = i + '0'; //clcd is 1st index means serial no printed
        for (j = 1; j < 16; j++) //loop runs < 16 we have clcd 16 digits
        {
            if (j == 1 || j == 10 || j == 13) //if j == 1, 10, 13
            {
                download_view[i][j] = ' '; //view log will be space
            } else if (j == 4 || j == 7) // if j == 4, 7
            {
                download_view[i][j] = ':'; // view log will be colon
            } else {
                download_view[i][j] = read_external_eeprom(address++); // else fecth the values in external eeprom
            }
        }
        download_view[i][j] = '\0'; // add the null chacter
    }

    if (count == 0) // if there is no data menas count is zero
    {
        CLEAR_DISP_SCREEN; //clear display
        clcd_print("NO LOG R PRESENT", LINE1(0)); //clcd print no log are present
        clcd_print("                ", LINE2(0));
        for (unsigned long int delay = 500; delay--;) //make it delay sometimes
            for (unsigned long int delay1 = 1000; delay1--;);
        puts("NO LOG R PRESENT"); //In tera term display No logs are present
        puts("\n\r"); //next line
    } else {
        for (unsigned int i = 0; i < count; i++) //otherwise loop will run < count
        {
            puts(download_view[i]); // in tera term array of i times 
            puts("\n\r"); // next line
        }
        CLEAR_DISP_SCREEN; //clear display
        clcd_print("  DOWNLOAD LOG  ", LINE1(0)); // in clcd print when download log pressed message will print
        clcd_print("  SUCCESSFULLY  ", LINE2(0)); // Download log successfully
        for (unsigned long int delay = 500; delay--;) //make it delay sometimes
            for (unsigned long int delay1 = 1000; delay1--;);
    }
    state = e_main_menu; //go back to main menu
    address = 0; //address as zero
}

void clear_log(void) // Fun defination claer log
{
    count = 0; // if count as zero all data will erase 
    clcd_print("   CLEAR LOG   ", LINE1(0)); // in clcd print when clear log pressed message will print
    clcd_print("  SUCCESSFULLY  ", LINE2(0)); //clear log  successfully
    for (unsigned long int delay = 500; delay--;) //make it delay sometimes
        for (unsigned long int delay1 = 1000; delay1--;);
    state = e_main_menu; //go back to main menu
}

void set_time(void) //Fun defination set time
{

//    CLEAR_DISP_SCREEN; //clear display
    static int time_flag = 0, flag = 0; //declare static variables
    static unsigned int delay; //declare variables

    if (flag == 0) // if flag is equal to 0 only print what time is that value print
    {
        clcd_print("HH:MM:SS", LINE1(0)); //display the time at once
        hour = read_ds1307(HOUR_ADDR); //read hour in time
        hour = (((hour >> 4) * 10) + (hour & 0x0F)); //it gives bcd value so convert into int
        min = read_ds1307(MIN_ADDR); //read min in time
        min = (((min >> 4) * 10) + (min & 0x0F)); //it gives bcd value so convert into int
        sec = read_ds1307(SEC_ADDR); //read sec in time
        sec = (((sec >> 4)*10) + (sec & 0x0F)); //it gives bcd value so convert into int
        flag = 1; //flag as one

    }

    if (delay++ < 2000) //if delay less than 1000
    {
        clcd_putch((hour / 10) + '0', LINE2(0)); // it print hour 1st digit
        clcd_putch((hour % 10) + '0', LINE2(1)); // it print hour 2nd digit
        clcd_putch(':', LINE2(2)); //add a colon
        clcd_putch((min / 10) + '0', LINE2(3)); // it print min 1st digit
        clcd_putch((min % 10) + '0', LINE2(4)); // it print min 2nd digit
        clcd_putch(':', LINE2(5)); //add a colon
        clcd_putch((sec / 10) + '0', LINE2(6)); // it print sec 1st digit
        clcd_putch((sec % 10) + '0', LINE2(7)); // it print sec 2nd digit
    } else if (delay++ < 4000) //else if less than 2000
    {
        if (time_flag == 0)//if time flag is equal to zero add a hour blink
        {
            clcd_putch(' ', LINE2(0));
            clcd_putch(' ', LINE2(1));
        } else if (time_flag == 1)//if time flag is equal to one add a minute blink
        {
            clcd_putch(' ', LINE2(3));
            clcd_putch(' ', LINE2(4));
        } else//else add a sec blink
        {
            clcd_putch(' ', LINE2(6));
            clcd_putch(' ', LINE2(7));
        }
    } else {
        delay = 0; //delay as zero
    }

    if (key == 11)//if SW11 pressed
    {
        write_ds1307(HOUR_ADDR, (((hour / 10) << 4) | hour % 10)); //write hour into a main menu
        write_ds1307(MIN_ADDR, (((min / 10) << 4) | min % 10)); //write min into a main menu
        write_ds1307(SEC_ADDR, (((sec / 10) << 4) | sec % 10)); //write sec into a main menu
        state = e_main_menu;
        flag = 0;
    }
    else if (key == 10)//if SW12 pressed flag as zero
    {
        state = e_main_menu;
        flag = 0;
    }
//    state = e_main_menu; // go back to main menu

    if (key == 1)//if SW1 pressed
    {
        if (time_flag == 0)//if time flag is equal to zero hour increase
        {
            if (hour == 23) //if hour is 23 reset the hour
                hour = 0;
            hour++;
        }

        if (time_flag == 1)//if time flag is equal to one min increase
        {
            if (min == 59)//if min is 59 reset the min
                min = 0;
            min++;
        }

        if (time_flag == 2)//if time flag is equal to two sec increase
        {
            if (sec == 59)//if sec is 59 reset the sec
                sec = 0;
            sec++;
        }
    }
    if (key == 2)//if SW2 pressed change the fields
    {
        if (time_flag++ == 2)
            time_flag = 0;
    }
    clcd_print("        ", LINE2(8));
    clcd_print("        ", LINE1(8));
}