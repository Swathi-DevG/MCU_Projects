#include <xc.h>
#include "main.h"
#include "external_eeprom.h"
extern unsigned char time[9],key,address;
extern unsigned char *events[]={"ON","GN","G1","G2","G3","G4","GR"," C"};
extern int event_pos,log_c,log;
extern unsigned short adc_val;
void store_event(void)
{
    if(log_c<10)    //on every store increment count until 9
        log_c++;
    address=16*log++;
    //SAVING TIME TO LOG
    int i=0;        //store the time event and speed 
    write_ex_eeprom(address+0x00,time[0]);
    write_ex_eeprom(address+0x01,time[1]);
    write_ex_eeprom(address+0x02,':');
    write_ex_eeprom(address+0x03,time[3]);
    write_ex_eeprom(address+0x04,time[4]);  
    write_ex_eeprom(address+0x05,':');
    write_ex_eeprom(address+0x06,time[6]);
    write_ex_eeprom(address+0x07,time[7]);
    write_ex_eeprom(address+0x08,' ');
    //SAVING EVENT TO LOG
    write_ex_eeprom(address+0x09,events[event_pos][0]);
    write_ex_eeprom(address+0x0A,events[event_pos][1]);
    write_ex_eeprom(address+0x0B,' ');
    //SAVING SPEED TO LOG
    write_ex_eeprom(address+0x0C,(adc_val/10)+'0');
    write_ex_eeprom(address+0x0D,(adc_val%10)+'0');
    if(log>9)   //on completion of logs replace from start by setting log index to 0
    {
        log=0;
        address=0x00;
    }
}
