/* 
 * File:   ecu_led.h
 * Author: Mahmoud Elgendy
 *
 * Created on August 2, 2023, 11:01 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section : Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section : Macro Declaration */

/* Section : Macro Function Declaration */

/* Section : Data Type Declaration */
typedef enum {
    LED_OFF,
    LED_ON
} led_status_t;

typedef struct {
    uint8 port_name : 4;
    uint8 pin : 3;
    uint8 led_status : 1;
} led_t;
/* Section : Function Declaration */
STD_ReturnType led_initialize(const led_t *led);
STD_ReturnType led_on(const led_t *led);
STD_ReturnType led_off(const led_t *led);
STD_ReturnType led_toggle(const led_t *led);


#endif	/* ECU_LED_H */

