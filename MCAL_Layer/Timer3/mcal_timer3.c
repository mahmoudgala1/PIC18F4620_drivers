/* 
 * File:   mcal_timer3.c
 * Author: Mahmoud Elgendy
 *
 * Created on September 29, 2023, 1:42 AM
 */
#include "mcal_timer3.h"

#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static volatile void (* TIMER3_InterruptHandler)(void) = NULL;
#endif
static inline STD_ReturnType timer3_mode_select(const timer3_t *timer);
static inline STD_ReturnType timer3_register_size_config(const timer3_t *timer);
static uint16 timer3_preload = 0;

/**
 * 
 * @param timer
 * @return 
 */
STD_ReturnType Timer3_Init(const timer3_t *timer) {
    STD_ReturnType ret = E_OK;
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        TIMER3_MODULE_DISABLE();
        timer3_mode_select(timer);
        timer3_register_size_config(timer);
        TIMER3_PRESCALER_SELECT(timer->timer3_prescaler_value);
        TMR3H = (timer->timer3_preload_value) >> 8;
        TMR3L = (uint8) (timer->timer3_preload_value);
        timer3_preload = timer->timer3_preload_value;
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER3_InterruptEnable();
        TIMER3_InterruptClearFlag();
        TIMER3_InterruptHandler = timer->TIMER3_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if (INTERRUPT_HIGH_PRIORITY == timer->priority) {
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER3_HighPrioritySet();
        } else if (INTERRUPT_LOW_PRIORITY == timer->priority) {
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER3_LowPrioritySet();
        } else {
            /*Nothing*/
        }
#else
        INTERRUPT_PeripheralInterruptEnable();
        INTERRUPT_GlobalInterruptEnable();
#endif
#endif
        TIMER3_MODULE_ENABLE();
    }
    return ret;
}

/**
 * 
 * @param timer
 * @return 
 */
STD_ReturnType Timer3_DeInit(const timer3_t *timer) {
    STD_ReturnType ret = E_OK;
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        TIMER3_MODULE_DISABLE();
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER3_InterruptDisable();
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
STD_ReturnType Timer3_Write_Value(const timer3_t *timer, uint16 value) {
    STD_ReturnType ret = E_OK;
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        TMR3H = (value) >> 8;
        TMR3L = (uint8) (value);
    }
    return ret;
}

/**
 * 
 * @param timer
 * @param value
 * @return 
 */
STD_ReturnType Timer3_Read_Value(const timer3_t *timer, uint16 *value) {
    STD_ReturnType ret = E_OK;
    if (NULL == timer || NULL == value) {
        ret = E_NOT_OK;
    } else {
        uint8 l_tmr3l = 0, l_tmr3h = 0;
        l_tmr3l = TMR3L;
        l_tmr3h = TMR3H;
        *value = (l_tmr3h << 8) + l_tmr3l;
    }
    return ret;
}

void TIMER3_ISR(void) {
    TIMER3_InterruptClearFlag();
    TMR1H = (timer3_preload) >> 8;
    TMR1L = (uint8) (timer3_preload);
    if (TIMER3_InterruptHandler) {
        TIMER3_InterruptHandler();
    }
}

/**
 * 
 * @param timer
 * @return 
 */
static inline STD_ReturnType timer3_mode_select(const timer3_t *timer) {
    STD_ReturnType ret = E_OK;
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        if (TIMER3_TIMER_MODE == timer->timer3_mode) {
            TIMER3_TIMER_MODE_ENABLE();
        } else if (TIMER3_COUNTER_MODE == timer->timer3_mode) {
            TIMER3_COUNTER_MODE_ENABLE();
            if (TIMER3_ASYNC_COUNTER_MODE == timer->timer3_counter_mode) {
                TIMER3_ASYNC_COUNTER_MODE_ENABLE();
            } else if (TIMER3_SYNC_COUNTER_MODE == timer->timer3_counter_mode) {
                TIMER3_SYNC_COUNTER_MODE_ENABLE();
            } else {
                /*Nothing*/
            }
        } else {
            /*Nothing*/
        }
    }
    return ret;
}

/**
 * 
 * @param timer
 * @return 
 */
static inline STD_ReturnType timer3_register_size_config(const timer3_t *timer) {
    STD_ReturnType ret = E_OK;
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        if (TIMER3_RW_REG_8BIT_MODE == timer->timer3_reg_rw_mode) {
            TIMER3_RW_REG_8BIT_MODE_ENABLE();
        } else if (TIMER3_RW_REG_16BIT_MODE == timer->timer3_reg_rw_mode) {
            TIMER3_RW_REG_16BIT_MODE_ENABLE();
        } else {
            /*Nothing*/
        }
    }
    return ret;
}


