/* 
 * File:   mcal_eeprom.h
 * Author: Mahmoud Elgendy
 *
 * Created on August 31, 2023, 10:43 PM
 */
#include "mcal_eeprom.h"

/**
 * 
 * @param bAdd
 * @param bData
 * @return 
 */
STD_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData) {
    STD_ReturnType ret = E_OK;
    uint8 Global_Interrupt_Status = INTCONbits.GIE;
    EEADRH = (uint8) ((bAdd >> 8)& 0x03);
    EEADR = (uint8) (bAdd & 0xFF);
    EEDATA = bData;
    EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
    EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
    EECON1bits.WREN = ALLOW_WRITE_CYCLES_FLASH_EEPROM;
    INTERRUPT_GlobalInterruptDisable();
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = INITIATE_DATA_EEPROM_WRITE_ERASE;
    while (EECON1bits.WR);
    EECON1bits.WREN = INHIBTS_WRITE_CYCLES_FLASH_EEPROM;
    INTCONbits.GIE = Global_Interrupt_Status;
    return ret;
}

/**
 * 
 * @param bAdd
 * @param bData
 * @return 
 */
STD_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData) {
    STD_ReturnType ret = E_OK;
    if (NULL == bData) {
        ret = E_NOT_OK;
    } else {
        EEADRH = (uint8) ((bAdd >> 8)& 0x03);
        EEADR = (uint8) (bAdd & 0xFF);
        EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
        EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
        EECON1bits.RD = INITIATE_DATA_EEPROM_READ;
        NOP();
        NOP();
        *bData = EEDATA;
    }
    return ret;
}