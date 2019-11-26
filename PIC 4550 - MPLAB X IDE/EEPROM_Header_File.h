/* 
 * File:   EEPROM_Header_File.h
 * Author: lucas
 *
 * Created on 22 de Novembro de 2019, 17:27
 */

#ifndef EEPROM_HEADER_FILE_H
#define	EEPROM_HEADER_FILE_H

void EEPROM_Write(int,char);        /* Write byte to EEPROM data memory */
char EEPROM_Read(int);              /* Read Byte From EEPROM data memory */
void EEPROM_WriteString(int,char*); /* Write byte to EEPROM data memory */

#endif	/* EEPROM_HEADER_FILE_H */

