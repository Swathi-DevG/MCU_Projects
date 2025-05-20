/*
 * File:   main.c
 * Name:   Swathi G
 * Date:   10-04-2024
 */

#include <xc.h>
#include "main.h"
#include "adc.h"
#include "clcd.h"
#include "digital_keypad.h"
#include "i2c.h"
#include "ds1307.h"
#include "external_eeprom.h"
#include "timers.h"
#include "uart.h"
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

unsigned char clock_reg[3],time[9],key,address=0x00,prekey,v_address,pass[5];
unsigned char *events[8]={"ON","GN","G1","G2","G3","G4","GR"," C"};
unsigned char *menu[5]={"View log       ","Clear log      ","Download log   ","Reset time    ","Change password"};
unsigned short adc_val;
int event_pos=0,flag=0;
int log,log_v=0,log_c=0,scroll;
int i=0,attempt=0,sec=59,m=0,v_flag=0,press,count_3,d_flag=0;
int new_flag=0,time_flag,t_flag;

int compare(char *p,char *u_p)   //function to compare password and user password
{
    while(*p && *u_p)
    {
        if(*p++!=*u_p++)
            return 0;
    }
    return 1;
}

void read_pass_from_mem(void)
{
    if(read_ex_eeprom(0xA0)==1) //if password present in external eeprom
    {
        pass[0]=read_ex_eeprom(0xA1);   //read and store password in array
        pass[1]=read_ex_eeprom(0xA2);
        pass[2]=read_ex_eeprom(0xA3);
        pass[3]=read_ex_eeprom(0xA4);
    }
    else
    {
        pass[0]='0';    //else store '0' to password
        pass[1]='0';
        pass[2]='0';
        pass[3]='0';
    }
    pass[4]='\0';
}
static void init_config(void) {
    init_clcd();
    init_adc();
    init_timer0();
    init_digital_keypad();
    init_i2c(100000);
    init_ds1307();
    init_uart(9600);
    PEIE=1;
    GIE=1;
    
}

void main(void) {

    init_config();
    
    while (1) 
    {
        read_pass_from_mem();   //read password from memory
        if(flag==0) //if flag is 0 go to dahboard
        {
            dashboard();
        }
        else if(flag==1)    //if flag is 1 go to login page
        {
            password();
        }
        else if(flag==2)    //if flag is 2 go to menu page
        {
            display_menu();
        }
        else if(flag==3)    //if flag is 3 go to function of selected menu
        {
            enter_menu();
        }
    }
    return;
}
