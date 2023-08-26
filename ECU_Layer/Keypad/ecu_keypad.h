/* 
 * File:   ecu_keypad.h
 * Author: Mahmoud Elgendy
 *
 * Created on August 13, 2023, 10:16 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* Section : Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section : Macro Declaration */
#define MAX_ROW_PINS 4
#define MAX_COLUMN_PINS 4
#define NOT_PRESSED 0xFF
/* Section : Macro Function Declaration */

/* Section : Data Type Declaration */
typedef struct {
    pin_config_t keypad_row_pins[MAX_ROW_PINS];
    pin_config_t keypad_column_pins[MAX_COLUMN_PINS];
} keypad_t;
/* Section : Function Declaration */
STD_ReturnType keypad_initialize(const keypad_t *keypad);
STD_ReturnType keypad_get_value(const keypad_t *keypad, uint8 *value);

#endif	/* ECU_KEYPAD_H */

