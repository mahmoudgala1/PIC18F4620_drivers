/* 
 * File:   mcal_timer2.c
 * Author: Mahmoud Elgendy
 *
 * Created on September 28, 2023, 11:02 PM
 */
#include "mcal_timer2.h"

#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void (* TIMER2_InterruptHandler)(void) = NULL;
#endif
static uint8 timer2_preload = 0;

/**
 * 
 * @param timer
 * @return 
 */
STD_ReturnType Timer2_Init(const timer2_t *timer) {
    STD_ReturnType ret = E_OK;
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        TIMER2_MODULE_DISABLE();
        T2CONbits.T2CKPS = timer->timer2_prescaler_value;
        T2CONbits.TOUTPS = timer->timer2_postscaler_value;
        TMR2 = timer->timer2_preload_value;
        timer2_preload = timer->timer2_preload_value;
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER2_InterruptEnable();
        TIMER2_InterruptClearFlag();
        TIMER2_InterruptHandler = timer->TIMER2_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if (INTERRUPT_HIGH_PRIORITY == timer->priority) {
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER2_HighPrioritySet();
        } else if (INTERRUPT_LOW_PRIORITY == timer->priority) {
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER2_LowPrioritySet();
        } else {
            /*Nothing*/
        }
#else
        INTERRUPT_PeripheralInterruptEnable();
        INTERRUPT_GlobalInterruptEnable();
#endif
#endif
        TIMER2_MODULE_ENABLE();
    }
    return ret;
}

/**
 * 
 * @param timer
 * @return 
 */
STD_ReturnType Timer2_DeInit(const timer2_t *timer) {
    STD_ReturnType ret = E_OK;
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        TIMER2_MODULE_DISABLE();
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER2_InterruptDisable();
#endif
    }
    return ret;
}

/**
 * 
 * @param timer
 * @param value
 * @return 
 */
STD_ReturnType Timer2_Write_Value(const timer2_t *timer, uint8 value) {
    STD_ReturnType ret = E_OK;
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        TMR2 = value;
    }
    return ret;
}

/**
 * 
 * @param timer
 * @param value
 * @return 
 */
STD_ReturnType Timer2_Read_Value(const timer2_t *timer, uint8 *value) {
    STD_ReturnType ret = E_OK;
    if (NULL == timer || NULL == value) {
        ret = E_NOT_OK;
    } else {
        *value = TMR2;
    }
    return ret;
}

void TIMER2_ISR(void) {
    TIMER2_InterruptClearFlag();
    TMR2 = timer2_preload;
    if (TIMER2_InterruptHandler) {
        TIMER2_InterruptHandler();
    }
}