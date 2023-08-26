/* 
 * File:   ecu_led.c
 * Author: Mahmoud Elgendy
 *
 * Created on August 2, 2023, 11:01 PM
 */
#include "ecu_led.h"
/**
 * 
 * @param led
 * @return 
 */
STD_ReturnType led_initialize(const led_t *led) {
    STD_ReturnType ret = E_OK;
    pin_config_t pin_obj={
      .port=led->port_name,
      .pin=led->pin,
      .direction=GPIO_DIRECTION_OUTPUT,
      .logic=led->led_status
    };
    if (NULL == led) {
        ret = E_NOT_OK;
    } else {
        gpio_pin_intialize(&pin_obj);
    }
    return ret;
}
/**
 * 
 * @param led
 * @return 
 */
STD_ReturnType led_on(const led_t *led) {
    STD_ReturnType ret = E_OK;
    if (NULL == led) {
        ret = E_NOT_OK;
    } else {
       pin_config_t pin_obj={
      .port=led->port_name,
      .pin=led->pin,
      .direction=GPIO_DIRECTION_OUTPUT,
      .logic=led->led_status
    };
        gpio_pin_write_logic(&pin_obj,GPIO_HIGH);
    }
    return ret;
}
/**
 * 
 * @param led
 * @return 
 */
STD_ReturnType led_off(const led_t *led) {
    STD_ReturnType ret = E_OK;
    
    if (NULL == led) {
        ret = E_NOT_OK;
    } else {
       pin_config_t pin_obj={
      .port=led->port_name,
      .pin=led->pin,
      .direction=GPIO_DIRECTION_OUTPUT,
      .logic=led->led_status
    };
        gpio_pin_write_logic(&pin_obj,GPIO_LOW);
    }
    return ret;
}
/**
 * 
 * @param led
 * @return 
 */
STD_ReturnType led_toggle(const led_t *led) {
    STD_ReturnType ret = E_OK;
    if (NULL == led) {
        ret = E_NOT_OK;
    } else {
       pin_config_t pin_obj={
      .port=led->port_name,
      .pin=led->pin,
      .direction=GPIO_DIRECTION_OUTPUT,
      .logic=led->led_status
    };
        gpio_pin_toggle_logic(&pin_obj);
    }
    return ret;
}