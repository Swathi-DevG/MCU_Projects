#include "main.h"
#include <xc.h>
#include "external_eeprom.h"
#include "clcd.h"
#include "digital_keypad.h"

extern unsigned char pass[5];
extern int flag,new_flag;
static p_i;
void enter_pass(char *pass) 
{
    char key = read_digital_keypad(STATE);  //Reading dkps
    if (key == SW5)     //if sw5 pressed
    {
        clcd_putch('*', LINE2(4 + p_i));    //display *
        __delay_ms(50);
        pass[p_i] = '0';    //update pass string with '0'
        p_i++;  //increment index
    } 
    else if (key == SW6) //if sw6 pressed
    {
        clcd_putch('*', LINE2(4 + p_i));    //display *
        __delay_ms(50);
        pass[p_i] = '1';    //update pass with '1'
        p_i++;  //increment index
    }
    if(p_i==4)  //if index reaches four
    {
        pass[4]='\0';   //add null char to string
        p_i=0;  //make 0
        new_flag++; //inc new flag
        clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
    }
}

void change_password(void) {
    char new_pass[5], re_pass[5];
    if(new_flag==1) //if new flag 1 ask for new password
    {
        clcd_print("Enter New Passwd",LINE1(0));
        enter_pass(new_pass);
    }
    else if(new_flag==2) //if new flag 2 ask for re-enter new password
    {
        clcd_print("ReEnter new Pass",LINE1(0));
        enter_pass(re_pass);
    }
    else{
        if(compare(new_pass,re_pass))   //else compare both pass if matched
        {
            write_ex_eeprom(0xA0,1);    //write it to external eeprom
            write_ex_eeprom(0xA1,new_pass[0]);
            write_ex_eeprom(0xA2,new_pass[1]);
            write_ex_eeprom(0xA3,new_pass[2]);
            write_ex_eeprom(0xA4,new_pass[3]);
            clcd_print("Change Password",LINE1(0));
            clcd_print(" SUCCESSFUL ",LINE2(0));
            __delay_ms(500);
            clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
            flag=0;
        }
        else
        {
            clcd_print("Change Password",LINE1(0));     //if not matched display error message on clcd
            clcd_print("  FAILED  ",LINE2(0));
            __delay_ms(500);
            clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
            flag=2;
        }
    }

}
