#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "digital_keypad.h"

extern unsigned char *menu[5],v_address;
extern int m,log_v,t_flag,scroll,d_flag,flag,new_flag;
static int delay1;
static char prekey;


void display_menu(void)
{
    if (m < 4) {
        clcd_putch('*', LINE1(0));  //if m<4 display * in line1
        clcd_print(menu[m], LINE1(1));      //display menu contents
        clcd_print(menu[m + 1], LINE2(1));  
    } else {
        clcd_putch('*', LINE2(0));  //if m>=4 display * in line2
        clcd_print(menu[m - 1], LINE1(1));  //display menu contents
        clcd_print(menu[m], LINE2(1));
    }
    char key = read_digital_keypad(LEVEL);  //read dkps
    if (key != ALL_RELEASED) {  //if any switch detected
        delay1++;       //inc delay
        prekey = key;   //store key in prekey
        if (delay1 > 10 && delay1 <= 100) {     //if long press
            if (prekey == SW5) {    //and sw5 clear display and make go to menu
                clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
                __delay_ms(1000);
                t_flag=1;
                log_v = 0;
                v_address = 0x00;
                scroll = 0;
                d_flag = 1;
                flag = 3;
                new_flag = 1;

            } else if (prekey == SW6) {  //and sw5 clear display and make go to dashboard
                clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
                flag = 0;
            }
            delay1 = 0;
        }
    } else if (delay1 > 0 && delay1 <= 10) {    //if short press
        delay1 = 0;
        if (prekey == SW5) {    //if sw5 scroll up menu
            if (m != 0) {
                m--;
                clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
            }
        } else if (prekey == SW6) {     //if sw6 sroll down menu
            if (m != 4) {
                m++;
                clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
            }
        }
    }
}