/* 
 * File:   mcal_external_interrupt.c
 * Author: Mahmoud Elgendy
 *
 * Created on August 26, 2023, 5:31 PM
 */
#include "mcal_external_interrupt.h"

static STD_ReturnType Interrupt_INTX_Enable(const interrupt_INTX_t *int_obj);
static STD_ReturnType Interrupt_INTX_Disable(const interrupt_INTX_t *int_obj);
static STD_ReturnType Interrupt_INTX_Priority_Init(const interrupt_INTX_t *int_obj);
static STD_ReturnType Interrupt_INTX_Edge_Init(const interrupt_INTX_t *int_obj);
static STD_ReturnType Interrupt_INTX_Pin_Init(const interrupt_INTX_t *int_obj);

/**
 * 
 * @param int_obj
 * @return 
 */
STD_ReturnType Interrupt_INTX_Init(const interrupt_INTX_t *int_obj) {
    STD_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {

    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
STD_ReturnType Interrupt_INTX_DeInit(const interrupt_INTX_t *int_obj) {
    STD_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {

    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
STD_ReturnType Interrupt_RBTX_Init(const interrupt_RBX_t *int_obj) {
    STD_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {

    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
STD_ReturnType Interrupt_RBTX_DeInit(const interrupt_RBX_t *int_obj) {
    STD_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {

    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static STD_ReturnType Interrupt_INTX_Enable(const interrupt_INTX_t *int_obj) {
    STD_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_INT0:
                EX_INT0_INTERRUPT_ENABLE();
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EX_INT1_INTERRUPT_ENABLE();
                break;
            case INTERRUPT_EXTERNAL_INT2:
                EX_INT2_INTERRUPT_ENABLE();
                break;
            default: break;
        }
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static STD_ReturnType Interrupt_INTX_Disable(const interrupt_INTX_t *int_obj) {
    STD_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_INT0:
                EX_INT0_INTERRUPT_DISABLE();
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EX_INT1_INTERRUPT_DISABLE();
                break;
            case INTERRUPT_EXTERNAL_INT2:
                EX_INT2_INTERRUPT_DISABLE();
                break;
            default: break;
        }
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

static STD_ReturnType Interrupt_INTX_Priority_Init(const interrupt_INTX_t *int_obj) {
    STD_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_INT1:
                switch (int_obj->priority) {
                    case INTERRUPT_LOW_PRIORITY:
                        EX_INT1_LOW_PRIORITY_SET();
                        break;
                    case INTERRUPT_HIGH_PRIORITY:
                        EX_INT1_HIGH_PRIORITY_SET();
                        break;
                    default: break;
                }
                break;
            case INTERRUPT_EXTERNAL_INT2:
                switch (int_obj->priority) {
                    case INTERRUPT_LOW_PRIORITY:
                        EX_INT2_LOW_PRIORITY_SET();
                        break;
                    case INTERRUPT_HIGH_PRIORITY:
                        EX_INT2_HIGH_PRIORITY_SET();
                        break;
                    default: break;
                }
                break;
            default: break;
        }
    }
    return ret;
}
#endif

/**
 * 
 * @param int_obj
 * @return 
 */
static STD_ReturnType Interrupt_INTX_Edge_Init(const interrupt_INTX_t *int_obj) {
    STD_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_INT0:
                switch (int_obj->edge) {
                    case INTERRUPT_FALLING_EDGE:
                        EX_INT0_FALLING_EDGE_SET();
                        break;
                    case INTERRUPT_RISING_EDGE:
                        EX_INT0_RISING_EDGE_SET();
                        break;
                    default: break;
                }
                break;
            case INTERRUPT_EXTERNAL_INT1:
                switch (int_obj->edge) {
                    case INTERRUPT_FALLING_EDGE:
                        EX_INT1_FALLING_EDGE_SET();
                        break;
                    case INTERRUPT_RISING_EDGE:
                        EX_INT1_RISING_EDGE_SET();
                        break;
                    default: break;
                }
                break;
            case INTERRUPT_EXTERNAL_INT2:
                switch (int_obj->edge) {
                    case INTERRUPT_FALLING_EDGE:
                        EX_INT2_FALLING_EDGE_SET();
                        break;
                    case INTERRUPT_RISING_EDGE:
                        EX_INT2_RISING_EDGE_SET();
                        break;
                    default: break;
                }
                break;
            default: break;
        }
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static STD_ReturnType Interrupt_INTX_Pin_Init(const interrupt_INTX_t *int_obj) {
    STD_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        gpio_pin_direction_intialize(&(int_obj->mcu_pin));
    }
    return ret;
}
