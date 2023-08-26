/* 
 * File:   ecu_7_segment.h
 * Author: Mahmoud Elgendy
 *
 * Created on August 11, 2023, 3:12 PM
 */

#ifndef ECU_7_SEGMENT_H
#define	ECU_7_SEGMENT_H

/* Section : Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section : Macro Declaration */
#define SEVEN_SEGMENT_PIN_0 0
#define SEVEN_SEGMENT_PIN_1 1
#define SEVEN_SEGMENT_PIN_2 2
#define SEVEN_SEGMENT_PIN_3 3

/* Section : Macro Function Declaration */

/* Section : Data Type Declaration */
typedef enum{
    SEVEN_SEGMENT_COMMON_CATHOD,
    SEVEN_SEGMENT_COMMON_ANODE        
}segment_type_t;

typedef struct {
    pin_config_t segment_pins[4];
    segment_type_t  segment_type;
}segment_t;

/* Section : Function Declaration */
STD_ReturnType seven_segment_initialize(const segment_t *segment);
STD_ReturnType seven_segment_write_number(const segment_t *segment, uint8 number);

#endif	/* ECU_7_SEGMENT_H */

