/* 
 * File:   mcal_external_interrupt.c
 * Author: Mahmoud Elgendy
 *
 * Created on August 26, 2023, 5:31 PM
 */
#include "mcal_external_interrupt.h"

static void(*INT0_InterruptHandler)(void) = NULL;
static void(*INT1_InterruptHandler)(void) = NULL;
static void(*INT2_InterruptHandler)(void) = NULL;

static void(*RB4_InterruptHandler_High)(void) = NULL;
static void(*RB4_InterruptHandler_Low)(void) = NULL;
static void(*RB5_InterruptHandler_High)(void) = NULL;
static void(*RB5_InterruptHandler_Low)(void) = NULL;
static void(*RB6_InterruptHandler_High)(void) = NULL;
static void(*RB6_InterruptHandler_Low)(void) = NULL;
static void(*RB7_InterruptHandler_High)(void) = NULL;
static void(*RB7_InterruptHandler_Low)(void) = NULL;

static STD_ReturnType INT0_SetInterruptHandler(void(*InterruptHandler)(void));
static STD_ReturnType INT1_SetInterruptHandler(void(*InterruptHandler)(void));
static STD_ReturnType INT2_SetInterruptHandler(void(*InterruptHandler)(void));

static STD_ReturnType Interrupt_INTX_Enable(const interrupt_INTX_t *int_obj);
static STD_ReturnType Interrupt_INTX_Disable(const interrupt_INTX_t *int_obj);
static STD_ReturnType Interrupt_INTX_Priority_Init(const interrupt_INTX_t *int_obj);
static STD_ReturnType Interrupt_INTX_Edge_Init(const interrupt_INTX_t *int_obj);
static STD_ReturnType Interrupt_INTX_Pin_Init(const interrupt_INTX_t *int_obj);
static STD_ReturnType Interrupt_INTX_Clear_Falg(const interrupt_INTX_t *int_obj);
static STD_ReturnType Interrupt_INTX_SetInterruptHandler(const interrupt_INTX_t *int_obj);

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
        ret = Interrupt_INTX_Disable(int_obj);
        ret = Interrupt_INTX_Clear_Falg(int_obj);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        ret = Interrupt_INTX_Priority_Init(int_obj);
#endif
        ret = Interrupt_INTX_Edge_Init(int_obj);
        ret = Interrupt_INTX_Pin_Init(int_obj);
        ret = Interrupt_INTX_SetInterruptHandler(int_obj);
        ret = Interrupt_INTX_Enable(int_obj);
    }
    return ret;
}

void INT0_ISR(void) {
    EX_INT0_INTERRUPT_CLEAR_FLAG();
    if (INT0_InterruptHandler) {
        INT0_InterruptHandler();
    }
}

void INT1_ISR(void) {
    EX_INT1_INTERRUPT_CLEAR_FLAG();
    if (INT1_InterruptHandler) {
        INT1_InterruptHandler();
    }
}

void INT2_ISR(void) {
    EX_INT2_INTERRUPT_CLEAR_FLAG();
    if (INT2_InterruptHandler) {
        INT2_InterruptHandler();
    }
}

void RB4_ISR(uint8 RB4_Source) {
    EX_RBX_INTERRUPT_CLEAR_FLAG();
    if (0 == RB4_Source) {
        if (RB4_InterruptHandler_High) {
            RB4_InterruptHandler_High();
        }
    } else if (1 == RB4_Source) {
        if (RB4_InterruptHandler_Low) {
            RB4_InterruptHandler_Low();
        }
    } else {
        /*NoThing*/
    }
}

void RB5_ISR(uint8 RB5_Source) {
    EX_RBX_INTERRUPT_CLEAR_FLAG();
    if (0 == RB5_Source) {
        if (RB5_InterruptHandler_High) {
            RB5_InterruptHandler_High();
        }
    } else if (1 == RB5_Source) {
        if (RB5_InterruptHandler_Low) {
            RB5_InterruptHandler_Low();
        }
    } else {
        /*NoThing*/
    }
}

void RB6_ISR(uint8 RB6_Source) {
    EX_RBX_INTERRUPT_CLEAR_FLAG();
    if (0 == RB6_Source) {
        if (RB6_InterruptHandler_High) {
            RB6_InterruptHandler_High();
        }
    } else if (1 == RB6_Source) {
        if (RB6_InterruptHandler_Low) {
            RB6_InterruptHandler_Low();
        }
    } else {
        /*NoThing*/
    }
}

void RB7_ISR(uint8 RB7_Source) {
    EX_RBX_INTERRUPT_CLEAR_FLAG();
    if (0 == RB7_Source) {
        if (RB7_InterruptHandler_High) {
            RB7_InterruptHandler_High();
        }
    } else if (1 == RB7_Source) {
        if (RB7_InterruptHandler_Low) {
            RB7_InterruptHandler_Low();
        }
    } else {
        /*NoThing*/
    }
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
        ret = Interrupt_INTX_Disable(int_obj);
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
STD_ReturnType Interrupt_RBX_Init(const interrupt_RBX_t *int_obj) {
    STD_ReturnType ret = E_NOT_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        /* This routine clears the interrupt disable for the external interrupt, RBx */
        EX_RBX_INTERRUPT_DISABLE();
        /* This routine clears the interrupt flag for the external interrupt, RBx */
        EX_RBX_INTERRUPT_CLEAR_FLAG();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
        INTERRUPT_PriorityLevelsEnable();
        if (INTERRUPT_LOW_PRIORITY == int_obj->priority) {
            /* This macro will enable low priority global interrupts. */
            INTERRUPT_GlobalInterruptLowEnable();
            /* This routine set the RBx External Interrupt Priority to be Low priority */
            EX_RBX_LOW_PRIORITY_SET();
        } else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority) {
            /* This macro will enable high priority global interrupts. */
            INTERRUPT_GlobalInterruptHighEnable();
            /* This routine set the RBx External Interrupt Priority to be High priority */
            EX_RBX_HIGH_PRIORITY_SET();
        } else {
            /* Nothing */
        }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        /* Initialize the RBx pin to be input */
        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
        /* Initialize the call back functions */
        switch (int_obj->mcu_pin.pin) {
            case GPIO_PIN4:
                RB4_InterruptHandler_High = int_obj->EXT_InterruptHandler_High;
                RB4_InterruptHandler_Low = int_obj->EXT_InterruptHandler_Low;
                break;
            case GPIO_PIN5:
                RB5_InterruptHandler_High = int_obj->EXT_InterruptHandler_High;
                RB5_InterruptHandler_Low = int_obj->EXT_InterruptHandler_Low;
                break;
            case GPIO_PIN6:
                RB6_InterruptHandler_High = int_obj->EXT_InterruptHandler_High;
                RB6_InterruptHandler_Low = int_obj->EXT_InterruptHandler_Low;
                break;
            case GPIO_PIN7:
                RB7_InterruptHandler_High = int_obj->EXT_InterruptHandler_High;
                RB7_InterruptHandler_Low = int_obj->EXT_InterruptHandler_Low;
                break;
            default:
                ret = E_NOT_OK;
        }
        /* This routine sets the interrupt enable for the external interrupt, RBx */
        EX_RBX_INTERRUPT_ENABLE();
        ret = E_OK;
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
STD_ReturnType Interrupt_RBX_DeInit(const interrupt_RBX_t *int_obj) {
    STD_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        EX_RBX_INTERRUPT_DISABLE();
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
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
                INTERRUPT_GlobalInterruptHighEnable();
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EX_INT0_INTERRUPT_ENABLE();
                break;
            case INTERRUPT_EXTERNAL_INT1:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
                INTERRUPT_PriorityLevelsEnable();
                if (INTERRUPT_LOW_PRIORITY == int_obj->priority) {
                    INTERRUPT_GlobalInterruptLowEnable();
                } else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority) {
                    INTERRUPT_GlobalInterruptHighEnable();
                } else {
                    /* Nothing */
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EX_INT1_INTERRUPT_ENABLE();
                break;
            case INTERRUPT_EXTERNAL_INT2:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
                INTERRUPT_PriorityLevelsEnable();
                if (INTERRUPT_LOW_PRIORITY == int_obj->priority) {
                    INTERRUPT_GlobalInterruptLowEnable();
                } else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority) {
                    INTERRUPT_GlobalInterruptHighEnable();
                } else {
                    /* Nothing */
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EX_INT2_INTERRUPT_ENABLE();
                break;
            default: ret = E_NOT_OK;
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

/**
 * 
 * @param int_obj
 * @return 
 */
static STD_ReturnType Interrupt_INTX_Clear_Falg(const interrupt_INTX_t *int_obj) {
    STD_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_INT0:
                EX_INT0_INTERRUPT_CLEAR_FLAG();
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EX_INT1_INTERRUPT_CLEAR_FLAG();
                break;
            case INTERRUPT_EXTERNAL_INT2:
                EX_INT2_INTERRUPT_CLEAR_FLAG();
                break;
            default: break;
        }
    }
}

/**
 * 
 * @param InterruptHandler
 * @return 
 */
static STD_ReturnType INT0_SetInterruptHandler(void(*InterruptHandler)(void)) {
    STD_ReturnType ret = E_OK;
    if (NULL == InterruptHandler) {
        ret = E_NOT_OK;
    } else {
        INT0_InterruptHandler = InterruptHandler;
    }
}

/**
 * 
 * @param InterruptHandler
 * @return 
 */
static STD_ReturnType INT1_SetInterruptHandler(void(*InterruptHandler)(void)) {
    STD_ReturnType ret = E_OK;
    if (NULL == InterruptHandler) {
        ret = E_NOT_OK;
    } else {
        INT1_InterruptHandler = InterruptHandler;
    }
}

/**
 * 
 * @param InterruptHandler
 * @return 
 */
static STD_ReturnType INT2_SetInterruptHandler(void(*InterruptHandler)(void)) {
    STD_ReturnType ret = E_OK;
    if (NULL == InterruptHandler) {
        ret = E_NOT_OK;
    } else {
        INT2_InterruptHandler = InterruptHandler;
    }
}

/**
 * 
 * @param int_obj
 * @return 
 */
static STD_ReturnType Interrupt_INTX_SetInterruptHandler(const interrupt_INTX_t *int_obj) {
    STD_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_INT0:
                INT0_SetInterruptHandler(int_obj->EXT_InterruptHandel);
                break;
            case INTERRUPT_EXTERNAL_INT1:
                INT1_SetInterruptHandler(int_obj->EXT_InterruptHandel);
                break;
            case INTERRUPT_EXTERNAL_INT2:
                INT2_SetInterruptHandler(int_obj->EXT_InterruptHandel);
                break;
            default: break;
        }
    }
}