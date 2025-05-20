#include <xc.h>
#include "main.h"
#include "uart.h"
#include "external_eeprom.h"

extern unsigned char v_address;
extern int log_v, log_c;
extern int flag,m;

void download_log(void)
{
    unsigned char download[17];     //declare array to store each log
    log_v=0;
    v_address=0x00;
    while(log_v<log_c)  //travesre through each log
    {
        download[0]=log_v+'0';
        download[1]=' ';
        int i=0;
        while(i<14) //read and store each char from log to array
        {
            download[2+i]=read_ex_eeprom(v_address+i);
            i++;
        }
        download[16]='\0';
        puts(download);     //print array through uart
        putchar('\n');
        putchar('\r');
        v_address+=16;
        log_v++;     
    }
    flag=2; //after downloading log go back to menu
    m=0;
}