/* 
 * File:   external_eeprom.h
 * Author: HP
 *
 * Created on 27 January, 2024, 3:13 PM
 */

#ifndef EXTERNAL_EEPROM_H
#define	EXTERNAL_EEPROM_H
#define SLAVE_WRITE_EX    0XA0
#define SLAVE_READ_EX      0XA1 
void  write_ex_eeprom(unsigned char address, unsigned char data);
unsigned char read_ex_eeprom(unsigned char address);

#endif	/* EXTERNAL_EEPROM_H */

