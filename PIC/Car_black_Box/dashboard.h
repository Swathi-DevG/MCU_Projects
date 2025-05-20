/*
 * File:   dashboard.h
 * Author: %<%Swathi G%>%
 *
 * Created on 8 February, 2024, 4:59 PM
 */


#include <xc.h>
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT disabled)

static void init_config(void) {
    //write initialization code here

}

void main(void) {
    init_config();
    while (1) {
        //write application code here
    }
    return;
}
