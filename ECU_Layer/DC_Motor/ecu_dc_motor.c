/* 
 * File:   ecu_dc_motor.c
 * Author: Mahmoud Elgendy
 *
 * Created on August 10, 2023, 11:52 PM
 */
#include "ecu_dc_motor.h"
/**
 * 
 * @param _dc_motor
 * @return 
 */
STD_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor){
    STD_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
        ret =E_NOT_OK;
    }else{
        gpio_pin_intialize(&(_dc_motor->dc_motor_pin_1));
        gpio_pin_intialize(&(_dc_motor->dc_motor_pin_2));
    }
    return ret;
}
/**
 * 
 * @param _dc_motor
 * @return 
 */
STD_ReturnType dc_motor_move_forword(const dc_motor_t *_dc_motor){
    STD_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
        ret =E_NOT_OK;
    }else{
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin_1),GPIO_HIGH);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin_2),GPIO_LOW);
    }
    return ret;
}
/**
 * 
 * @param _dc_motor
 * @return 
 */
STD_ReturnType dc_motor_move_reverse(const dc_motor_t *_dc_motor){
    STD_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
        ret =E_NOT_OK;
    }else{
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin_1),GPIO_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin_2),GPIO_HIGH);
    }
    return ret;
}
/**
 * 
 * @param _dc_motor
 * @return 
 */
STD_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor){
    STD_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
        ret =E_NOT_OK;
    }else{
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin_1),GPIO_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin_2),GPIO_LOW);
    }
    return ret;
}