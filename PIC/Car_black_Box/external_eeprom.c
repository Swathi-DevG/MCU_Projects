/*
 * File:   external_eeprom.c
 * Author: %<%Swathi G%>%
 *
 * Created on 27 January, 2024, 3:12 PM
 */

#include "external_eeprom.h"
#include "i2c.h"
void  write_ex_eeprom(unsigned char address, unsigned char data)
{
    i2c_start();
    i2c_write(SLAVE_WRITE_EX);
    i2c_write(address);
    i2c_write(data);
    i2c_stop();
    for(int i=3000;i--;);
}

unsigned char read_ex_eeprom(unsigned char address)
{
    unsigned char data;
    i2c_start();
    i2c_write(SLAVE_WRITE_EX);
    i2c_write(address);
    i2c_rep_start();
    i2c_write(SLAVE_READ_EX);
    data=i2c_read(0);
    i2c_stop();
    return data;
}