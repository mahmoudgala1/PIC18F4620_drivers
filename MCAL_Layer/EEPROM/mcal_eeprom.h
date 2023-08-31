/* 
 * File:   mcal_eeprom.h
 * Author: Mahmoud Elgendy
 *
 * Created on August 31, 2023, 10:43 PM
 */

#ifndef MCAL_EEPROM_H
#define	MCAL_EEPROM_H

/* Section : Includes */
#include "../Interrupt/mcal_internal_interrupt.h"

/* Section : Macro Declaration */
#define ACCESS_FLASH_PROGRAM_MEMORY  1
#define ACCESS_EEPROM_PROGRAM_MEMORY 0
#define ACCESS_CONFIG_BITS           1
#define ACCESS_FLASH_EEPROM_MEMORY   0
#define ALLOW_WRITE_CYCLES_FLASH_EEPROM   1
#define INHIBTS_WRITE_CYCLES_FLASH_EEPROM 0
#define INITIATE_DATA_EEPROM_WRITE_ERASE  1
#define DATA_EEPROM_WRITE_ERASE_COMPLETED 0
#define INITIATE_DATA_EEPROM_READ         1

/* Section : Macro Function Declaration */

/* Section : Data Type Declaration */

/* Section : Function Declaration */
STD_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData);
STD_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData);
#endif	/* MCAL_EEPROM_H */

