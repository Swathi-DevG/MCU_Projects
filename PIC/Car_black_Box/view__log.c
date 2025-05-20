#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "external_eeprom.h"
#include "digital_keypad.h"

extern unsigned char key, prekey, v_address;
extern int log_v, log_c,scroll;
extern int flag,m,d_flag;

void view_log(void) {
    if(d_flag==1){      //print log when only log index is changed 
    clcd_print("#   Time   EV SP",LINE1(0));
    clcd_putch(log_v+'0',LINE2(0));
    clcd_putch(read_ex_eeprom(v_address+0x00),LINE2(2));
    clcd_putch(read_ex_eeprom(v_address+0x01),LINE2(3));
    clcd_putch(read_ex_eeprom(v_address+0x02),LINE2(4));
    clcd_putch(read_ex_eeprom(v_address+0x03),LINE2(5));
    clcd_putch(read_ex_eeprom(v_address+0x04),LINE2(6));
    clcd_putch(read_ex_eeprom(v_address+0x05),LINE2(7));
    clcd_putch(read_ex_eeprom(v_address+0x06),LINE2(8));
    clcd_putch(read_ex_eeprom(v_address+0x07),LINE2(9));
    clcd_putch(read_ex_eeprom(v_address+0x08),LINE2(10));
    clcd_putch(read_ex_eeprom(v_address+0x09),LINE2(11));
    clcd_putch(read_ex_eeprom(v_address+0x0A),LINE2(12));
    clcd_putch(read_ex_eeprom(v_address+0x0B),LINE2(13));
    clcd_putch(read_ex_eeprom(v_address+0x0C),LINE2(14));
    clcd_putch(read_ex_eeprom(v_address+0x0D),LINE2(15));
    d_flag=0;
    }
    key = read_digital_keypad(LEVEL);   //read dkp
    static int delay=0;
    if (key != ALL_RELEASED) {  //if any switch is pressed
        delay++;    //increment delay
        prekey = key;
        if (delay>100 && delay<=200){   //on long press
            delay = 0;
            if (prekey == SW5) {    //of sw5
                clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
                __delay_ms(1000);
                flag = 0;   //move to dashboard
                m=0;
            }
        }
    } else if (delay > 0 && delay <= 100) { //on short press
        delay = 0;
        if (prekey == SW5) {    //if sw5
            d_flag=1;
            if(scroll==1)   //if scroll 1 scroll down the logs till last log then change direction
            {
                if(log_v==0)
                    scroll=0;
                else
                {
                    log_v--;
                    v_address-=16;
                }
            }
            if(scroll==0)   //if scroll 0 scroll up the logs till first log then change direction
            {
                if(log_v==log_c-1)
                    scroll=1;
                else{
                    log_v++;
                    v_address+=16;
                }
            }   
        }
        
    }
}
    
  