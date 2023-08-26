/* 
 * File:   ecu_7_segment.c
 * Author: Mahmoud Elgendy
 *
 * Created on August 11, 2023, 3:12 PM
 */
#include "ecu_7_segment.h"

/**
 * 
 * @param segment
 * @return 
 */
STD_ReturnType seven_segment_initialize(const segment_t *segment) {
    STD_ReturnType ret = E_OK;
    if (NULL == segment) {
        ret = E_NOT_OK;
    } else {
        gpio_pin_intialize(&(segment->segment_pins[SEVEN_SEGMENT_PIN_0]));
        gpio_pin_intialize(&(segment->segment_pins[SEVEN_SEGMENT_PIN_1]));
        gpio_pin_intialize(&(segment->segment_pins[SEVEN_SEGMENT_PIN_2]));
        gpio_pin_intialize(&(segment->segment_pins[SEVEN_SEGMENT_PIN_3]));
    }
    return ret;
}

/**
 * 
 * @param segment
 * @param number
 * @return 
 */
STD_ReturnType seven_segment_write_number(const segment_t *segment, uint8 number) {
    STD_ReturnType ret = E_OK;
    if ((NULL == segment) && ((number < 0) || (number > 9))) {
        ret = E_NOT_OK;
    } else {
        gpio_pin_write_logic(&(segment->segment_pins[SEVEN_SEGMENT_PIN_0]), (number) & 0x01);
        gpio_pin_write_logic(&(segment->segment_pins[SEVEN_SEGMENT_PIN_1]), (number >> 1)  & 0x01);
        gpio_pin_write_logic(&(segment->segment_pins[SEVEN_SEGMENT_PIN_2]), (number >> 2)  & 0x01);
        gpio_pin_write_logic(&(segment->segment_pins[SEVEN_SEGMENT_PIN_3]), (number >> 3)  & 0x01);
    }
    return ret;
}