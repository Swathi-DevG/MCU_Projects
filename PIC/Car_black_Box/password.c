#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "digital_keypad.h"
#include "timers.h"

extern char pass[5];
extern int i=0,attempt=0,sec=59,m=0,press,count_3,flag;
static delay1;
static char user_pass[5];
void password(void)
{
    if (i != 4) 
    {
        press = 1;      //make press 1 when you try to enter password to count pass of 3 seconds
        clcd_print("Enter Password", LINE1(0));
        char key = read_digital_keypad(STATE);  //read dkp
        if (key == SW5) {   //if sw5 pressed
            press = 0;  //reset press and count
            count_3 = 0;
            clcd_putch('*', LINE2(4 + i));
            __delay_ms(50);
            user_pass[i] = '0'; //update user password with 0
            i++;

        } else if (key == SW6) {       //if sw6 pressed
            press = 0;  
            count_3 = 0;
            clcd_putch('*', LINE2(4 + i));
            __delay_ms(50);
            user_pass[i] = '1';     //update user password with 1
            i++;
        }
    }
    if (i == 4 && attempt != 3) //if 4 field entered
    {
        press = 0;
        count_3 = 0;
        if (compare(pass, user_pass)) //comparing password
        {
            clcd_write(CLEAR_DISP_SCREEN, INST_MODE); //on success printing password success
            clcd_print("Login Successful", LINE1(0));
            __delay_ms(1000);
            clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
            i = 0;
            m = 0;
            attempt = 0;
            sec = 59;
            flag = 2;

        } else {
            attempt++; //on wrong attempt
            sec = 59;
            clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
            if (attempt < 3) {
                clcd_print(" Wrong Password ", LINE1(0)); //displaying wrong password
                clcd_print(" Attempts left ", LINE2(0));
                clcd_putch('0' + (3 - attempt), LINE2(15));
                __delay_ms(500);
                i = 0;
                clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
            }
        }
    }
    if (attempt == 3) { //if 3 attempts completed 
        clcd_print("Wait for ", LINE1(0));  //block user for 1 minutes
        clcd_putch(sec / 10 + '0', LINE2(4));   //display seconds
        clcd_putch(sec % 10 + '0', LINE2(5));
        clcd_print("Sec", LINE2(7));
        if (sec == 0) { //after wait go back to dashboard
            clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
            sec = 59;
            i = 0;
            attempt = 0;
            flag = 0;
        }
    }
}
