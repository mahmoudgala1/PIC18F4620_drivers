/*
 * File:   hal_gpio.c
 * Author: Mahmoud Elgendy
 *
 * Created on August 2, 2023, 10:48 PM
 */
#include "hal_gpio.h"

volatile uint8 *tris_registers[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
volatile uint8 *port_registers[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};
volatile uint8 *lat_registers [] = {&LATA, &LATB, &LATC, &LATD, &LATE};

/**
 * 
 * @param _pin_config
 * @return 
 */
STD_ReturnType gpio_pin_intialize(const pin_config_t *_pin_config) {
    STD_ReturnType ret = E_OK;
    if ((NULL == _pin_config) && (_pin_config->pin > PORT_PIN_MAX_NUMBER - 1)) {
        ret = E_NOT_OK;
    } else {
        gpio_pin_direction_intialize(_pin_config);
        gpio_pin_write_logic(_pin_config, _pin_config->logic);
    }
    return ret;
}

/**
 * 
 * @param _pin_config
 * @return 
 */
STD_ReturnType gpio_pin_direction_intialize(const pin_config_t *_pin_config) {
    STD_ReturnType ret = E_OK;
    if ((NULL == _pin_config) && (_pin_config->pin > PORT_PIN_MAX_NUMBER - 1)) {
        ret = E_NOT_OK;
    } else {
        switch (_pin_config->direction) {
            case GPIO_DIRECTION_INPUT:
                SET_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
                break;
            case GPIO_DIRECTION_OUTPUT:
                CLEAR_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
                break;
            default:
                ret = E_NOT_OK;
        }
    }
    return ret;
}

/**
 * 
 * @param _pin_config
 * @param direction_status
 * @return 
 */
STD_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config, direction_t *direction_status) {
    STD_ReturnType ret = E_OK;
    if ((NULL == _pin_config) && (NULL == direction_status) && (_pin_config->pin > PORT_PIN_MAX_NUMBER)) {
        ret = E_NOT_OK;
    } else {
        *direction_status = READ_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
    }
    return ret;
}

/**
 * 
 * @param _pin_config
 * @param logic
 * @return 
 */
STD_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic) {
    STD_ReturnType ret = E_OK;
    if ((NULL == _pin_config) && (_pin_config->pin > PORT_PIN_MAX_NUMBER - 1)) {
        ret = E_NOT_OK;
    } else {
        switch (logic) {
            case GPIO_LOW:
                CLEAR_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
                break;
            case GPIO_HIGH:
                SET_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
                break;
            default:
                ret = E_NOT_OK;
        }
    }
    return ret;
}

/**
 * 
 * @param _pin_config
 * @param logic
 * @return 
 */
STD_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic) {
    STD_ReturnType ret = E_OK;
    if ((NULL == _pin_config) && (_pin_config->pin > PORT_PIN_MAX_NUMBER - 1)) {
        ret = E_NOT_OK;
    } else {
        *logic = READ_BIT(*port_registers[_pin_config->port], _pin_config->pin);
    }
    return ret;
}

/**
 * 
 * @param _pin_config
 * @return 
 */
STD_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config) {
    STD_ReturnType ret = E_OK;
    if ((NULL == _pin_config) && (_pin_config->pin > PORT_PIN_MAX_NUMBER - 1)) {
        ret = E_NOT_OK;
    } else {
        TOGGLE_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
    }
    return ret;
}

/**
 * 
 * @param port
 * @param direction
 * @return 
 */
STD_ReturnType gpio_port_direction_intialize(port_index_t port, uint8 direction) {
    STD_ReturnType ret = E_OK;

    if (port > PORT_MAX_NUMBER - 1) {
        ret = E_NOT_OK;
    } else {
        *tris_registers[port] = direction;
    }

    return ret;
}

/**
 * 
 * @param port
 * @param direction_status
 * @return 
 */
STD_ReturnType gpio_port_get_direction_status(port_index_t port, uint8 *direction_status) {
    STD_ReturnType ret = E_OK;

    if ((port > PORT_MAX_NUMBER - 1) && (NULL == direction_status)) {
        ret = E_NOT_OK;
    } else {
        *direction_status = *tris_registers[port];
    }

    return ret;
}

/**
 * 
 * @param port
 * @param logic
 * @return 
 */
STD_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic) {
    STD_ReturnType ret = E_OK;

    if (port > PORT_MAX_NUMBER - 1) {
        ret = E_NOT_OK;
    } else {
        *lat_registers[port] = logic;
    }

    return ret;
}

/**
 * 
 * @param port
 * @param logic
 * @return 
 */
STD_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic) {
    STD_ReturnType ret = E_OK;

    if ((port > PORT_MAX_NUMBER - 1) && (NULL == logic)) {
        ret = E_NOT_OK;
    } else {
        *logic = *port_registers[port];
    }

    return ret;
}

/**
 * 
 * @param port
 * @return 
 */
STD_ReturnType gpio_port_toggle_logic(port_index_t port) {
    STD_ReturnType ret = E_OK;

    if (port > PORT_MAX_NUMBER - 1) {
        ret = E_NOT_OK;
    } else {
        *lat_registers[port] ^= 0xFF;
    }

    return ret;
}