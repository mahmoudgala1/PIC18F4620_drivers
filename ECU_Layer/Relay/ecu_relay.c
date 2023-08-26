/* 
 * File:   ecu_relay.c
 * Author: Mahmoud Elgendy
 *
 * Created on August 10, 2023, 11:00 PM
 */

#include "ecu_relay.h"

/**
 * 
 * @param _relay
 * @return 
 */
STD_ReturnType relay_initialize(const relay_t *_relay){
    STD_ReturnType ret = E_OK;
    if(NULL == _relay){
        ret = E_NOT_OK;
    }else{
        gpio_pin_intialize(&(_relay->relay_pin));
    }
    return ret;
}
/**
 * 
 * @param _relay
 * @return 
 */
STD_ReturnType relay_turn_on(const relay_t *_relay){
    STD_ReturnType ret = E_OK;
    if(NULL == _relay){
        ret = E_NOT_OK;
    }else{
        gpio_pin_write_logic(&(_relay->relay_pin),GPIO_HIGH);
    }
    return ret;
}
/**
 * 
 * @param _relay
 * @return 
 */
STD_ReturnType relay_turn_off(const relay_t *_relay){
    STD_ReturnType ret = E_OK;
    if(NULL == _relay){
        ret = E_NOT_OK;
    }else{
         gpio_pin_write_logic(&(_relay->relay_pin),GPIO_LOW);
    }
    return ret;
}