#include <xc.h>
#include "main.h"
#include "ds1307.h"
#include "clcd.h"
#include "digital_keypad.h"

extern unsigned char time[9],clock_reg[3];
extern int time_flag,flag,m,t_flag;
static int blink = 0,hr,min,sec;
char prekey;

void reset_time(void) {
    if(t_flag==1)
    {
        get_time(clock_reg); // HH MM SS
        display_time(clock_reg);    //get time 
        time_flag = 2;
        hr = (int) (time[0] - 48)*10 + (int) (time[1] - 48);    //store time in hr min sec
        min = (int) (time[3] - 48)*10 + (int) (time[4] - 48);
        sec = (int) (time[6] - 48)*10 + (int) (time[7] - 48);
        t_flag=0;
    }
    clcd_print("TIME (HH:MM:SS) ", LINE1(0));
    if(blink++<=5)
    {
        clcd_putch(hr/10+'0',LINE2(0));     //diplay hh:mm:ss by blinking selected field
        clcd_putch(hr%10+'0', LINE2(1));
        clcd_putch(':',LINE2(2));
        clcd_putch(min/10+'0', LINE2(3));
        clcd_putch(min%10+'0', LINE2(4));
        clcd_putch(':', LINE2(5));
        clcd_putch(sec/10+'0', LINE2(6));
        clcd_putch(sec%10+'0', LINE2(7));
    }
    else if(blink<=10)
    {
        if (time_flag == 0) 
            clcd_print("  ",LINE2(0));
        else if (time_flag == 1)
            clcd_print("  ",LINE2(3));
        else if (time_flag == 2) 
            clcd_print("  ",LINE2(6));
    }
    else if(blink>10)
        blink=0;
    char key = read_digital_keypad(LEVEL);  //read dkp
    static int delay=0;
    if (key != ALL_RELEASED) //is any swicth pressed
    {
        delay++;    //inc delay
        prekey = key;//store key in prekey
        if (delay>10 && delay<=100) //on long press
        {
            delay = 0;
            if (prekey == SW5)  //if sw5 pressed write time to rtc
            {
                write_ds1307(HOUR_ADDR,((hr/10)<<4)|(hr%10));
                write_ds1307(MIN_ADDR,((min/10)<<4)|(min%10));
                write_ds1307(SEC_ADDR,((sec/10)<<4)|(sec%10));
                flag=0;
                m=0;
            }
        }
    } 
    else if (delay > 0 && delay <= 10) //on short press
    {
        delay = 0;
        if (prekey == SW5) //if key is sw5
        {
            if (time_flag == 0)        //if field is hr 
                hr=(hr+1)%24;             //increment hr
            else if (time_flag == 1)   //if field is min
                min=(min+1)%60;          //increment min
            else if (time_flag == 2)   //if field is sec
                sec=(sec+1)%60;          //increment sec

        }
        else if(prekey==SW6)    //if key is sw6
            time_flag=(time_flag+1)%3;  //move field to next
    }
    
    

}