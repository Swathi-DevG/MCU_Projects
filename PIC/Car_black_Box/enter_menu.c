#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "uart.h"

extern char address;
extern int m,v_flag,log_c,flag;

void no_logs(void)
{
    clcd_print("  NO LOGS ",LINE1(0));
    clcd_print(" AVAILABLE ",LINE2(0));
    __delay_ms(1000);
    clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
    flag=0;
    m=0;
}

void enter_menu(void) {
    if (m == 0) {           //if m=0 view log
        if (v_flag == 1)
            view_log();
        else
            no_logs();
    } else if (m == 1) {
        if (v_flag == 1) {  //if m=1 and v_flag=1 clear log
            clcd_print(" CLEARED LOG", LINE1(0));
            clcd_print(" SUCCESSFULLY ", LINE2(0));
            __delay_ms(1000);
            clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
            v_flag = 0;
            log_c = 0;
            address = 0x00;
            flag = 0;
        } else
            no_logs();  //else display no logs available
    } else if (m == 2) {    //if m=2 download log through UART
        if (log_c > 0) {
            clcd_print("DOWNLOADING", LINE1(0));
            puts("DOWNLOAD Started");
            putchar('\n');
            putchar('\r');
            download_log();
            clcd_print("DOWNLOAD END", LINE1(0));
            puts("DOWNLOAD Ended\n\r");
        } else
            no_logs();
    } else if (m == 3)  //if m=3 reset time
    {
        reset_time();
    }
    else if (m == 4) {  //if m=4 change password
        change_password();
    }
}
