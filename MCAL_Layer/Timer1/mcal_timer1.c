/* 
 * File:   mcal_timer1.c
 * Author: Mahmoud Elgendy
 *
 * Created on September 28, 2023, 1:50 AM
 */
#include "mcal_timer1.h"

#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static volatile void (* TIMER1_InterruptHandler)(void) = NULL;
#endif
static inline STD_ReturnType timer1_mode_select(const timer1_t *timer);
static inline STD_ReturnType timer1_register_size_config(const timer1_t *timer);
static inline STD_ReturnType timer1_osc_mode(const timer1_t *timer);
static uint16 timer1_preload = 0;

/**
 * 
 * @param timer
 * @return 
 */
STD_ReturnType Timer1_Init(const timer1_t *timer) {
    STD_ReturnType ret = E_OK;
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        TIMER1_MODULE_DISABLE();
        timer1_mode_select(timer);
        timer1_register_size_config(timer);
        timer1_osc_mode(timer);
        TIMER1_PRESCALER_SELECT(timer->timer1_prescaler_value);
        TMR1H = (timer->timer1_preload_value) >> 8;
        TMR1L = (uint8) (timer->timer1_preload_value);
        timer1_preload = timer->timer1_preload_value;
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER1_InterruptEnable();
        TIMER1_InterruptClearFlag();
        TIMER1_InterruptHandler = timer->TIMER1_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if (INTERRUPT_HIGH_PRIORITY == timer->priority) {
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER1_HighPrioritySet();
        } else if (INTERRUPT_LOW_PRIORITY == timer->priority) {
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER1_LowPrioritySet();
        } else {
            /*Nothing*/
        }
#else
        INTERRUPT_PeripheralInterruptEnable();
        INTERRUPT_GlobalInterruptEnable();
#endif
#endif
        TIMER1_MODULE_ENABLE();
    }
    return ret;
}

/**
 * 
 * @param timer
 * @return 
 */
STD_ReturnType Timer1_DeInit(const timer1_t *timer) {
    STD_ReturnType ret = E_OK;
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        TIMER1_MODULE_DISABLE();
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER1_InterruptDisable();
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
STD_ReturnType Timer1_Write_Value(const timer1_t *timer, uint16 value) {
    STD_ReturnType ret = E_OK;
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        TMR1H = (value) >> 8;
        TMR1L = (uint8) (value);
    }
    return ret;
}

/**
 * 
 * @param timer
 * @param value
 * @return 
 */
STD_ReturnType Timer1_Read_Value(const timer1_t *timer, uint16 *value) {
    STD_ReturnType ret = E_OK;
    if (NULL == timer || NULL == value) {
        ret = E_NOT_OK;
    } else {
        uint8 l_tmr1l = 0, l_tmr1h = 0;
        l_tmr1l = TMR1L;
        l_tmr1h = TMR1H;
        *value = (l_tmr1h << 8) + l_tmr1l;
    }
    return ret;
}

void TIMER1_ISR(void) {
    TIMER1_InterruptClearFlag();
    TMR1H = (timer1_preload) >> 8;
    TMR1L = (uint8) (timer1_preload);
    if (TIMER1_InterruptHandler) {
        TIMER1_InterruptHandler();
    }
}

/**
 * 
 * @param timer
 * @return 
 */
static inline STD_ReturnType timer1_mode_select(const timer1_t *timer) {
    STD_ReturnType ret = E_OK;
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        if (TIMER1_TIMER_MODE == timer->timer1_mode) {
            TIMER1_TIMER_MODE_ENABLE();
        } else if (TIMER1_COUNTER_MODE == timer->timer1_mode) {
            TIMER1_COUNTER_MODE_ENABLE();
            if (TIMER1_ASYNC_COUNTER_MODE == timer->timer1_counter_mode) {
                TIMER1_ASYNC_COUNTER_MODE_ENABLE();
            } else if (TIMER1_SYNC_COUNTER_MODE == timer->timer1_counter_mode) {
                TIMER1_SYNC_COUNTER_MODE_ENABLE();
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
static inline STD_ReturnType timer1_register_size_config(const timer1_t *timer) {
    STD_ReturnType ret = E_OK;
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        if (TIMER1_RW_REG_8BIT_MODE == timer->timer1_reg_rw_mode) {
            TIMER1_RW_REG_8BIT_MODE_ENABLE();
        } else if (TIMER1_RW_REG_16BIT_MODE == timer->timer1_reg_rw_mode) {
            TIMER1_RW_REG_16BIT_MODE_ENABLE();
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
static inline STD_ReturnType timer1_osc_mode(const timer1_t *timer) {
    STD_ReturnType ret = E_OK;
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        if (TIMER1_OSCILLATOR_ENABLE == timer->timer1_osc_cfg) {
            TIMER1_OSC_HW_ENABLE();
        } else if (TIMER1_OSCILLATOR_DISABLE == timer->timer1_osc_cfg) {
            TIMER1_OSC_HW_DISABLE();
        } else {
            /*Nothing*/
        }
    }
    return ret;
}