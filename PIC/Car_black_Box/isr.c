#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "digital_keypad.h"
void __interrupt() isr(void)
{
    extern int attempt,press,sec,i,flag,count_3;
    extern unsigned char key;
    static unsigned long int count=0,count1=0;
    
    if (TMR0IF == 1)
    {
        /* TMR0 Register valur + 6 (offset count to get 250 ticks) + 2 Inst Cycle */
        TMR0 = TMR0 + 6 + 2;
        if(attempt==3 && ++count==20000)
        {
            count=0;
            
            sec--;
        }
        if(press==1 && ++count1==20000)
        {
            count_3++;
            count1=0;
        }
        
        if(count_3==3)
        {
            flag=0;
            i=0;
            attempt=0;
            press=0;
            count_3=0;
        }
        TMR0IF = 0;
    }
}