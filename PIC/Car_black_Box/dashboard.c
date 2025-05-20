#include <xc.h>
#include "main.h"
#include "adc.h"
#include "clcd.h"
#include "digital_keypad.h"
#include "i2c.h"
#include "ds1307.h"

extern unsigned short adc_val;
extern unsigned char clock_reg[3],key,*events[8],time[9];
extern int event_pos,v_flag,flag;

void dashboard(void) 
{
    //displaying time
    clcd_print(" Time     EV  SP", LINE1(0));
    get_time(clock_reg); // HH MM SS
    display_time(clock_reg);
    clcd_print(time, LINE2(0));
    //displaying event
    clcd_print(events[event_pos], LINE2(10));
    //displaying speed
    adc_val = read_adc(CHANNEL0) / 10.33;
    clcd_putch((adc_val / 10) + '0', LINE2(14));
    clcd_putch((adc_val % 10) | '0', LINE2(15));
    key = read_digital_keypad(STATE);   
    if (key == SW1) {   //if SW1 pressed event is Collision
        event_pos = 7;
        store_event();
        v_flag = 1;
    } else if (key == SW2) {  //if SW2 pressed event is incremented
        v_flag = 1;
        if (event_pos < 6) {
            event_pos++;
            store_event();
        } else if (event_pos == 7) {    
            event_pos = 1;
        }
    } else if (key == SW3) {  //if SW3 pressed event is decremented
        v_flag = 1;
        if (event_pos > 1 && event_pos != 7) {
            event_pos--;
            store_event();
        } else if (event_pos == 7) {
            event_pos = 1;
        }
    } else if (key == SW4) {    //if SW1 pressed entering password mode
        clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
        flag = 1;
    }
}
