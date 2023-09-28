/* 
 * File:   hal_timer0.c
 * Author: Mahmoud Elgendy
 *
 * Created on September 27, 2023, 7:11 AM
 */
#include "mcal_timer0.h"

#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static volatile void (* TIMER0_InterruptHandler)(void) = NULL;
#endif
static inline STD_ReturnType timer0_prescaler_config(const timer0_t *timer);
static inline STD_ReturnType timer0_mode_select(const timer0_t *timer);
static inline STD_ReturnType timer0_register_size_config(const timer0_t *timer);
static uint16 timer0_preload = 0;

/**
 * 
 * @param timer
 * @return 
 */
STD_ReturnType Timer0_Init(const timer0_t *timer) {
    STD_ReturnType ret = E_OK;
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        TIMER0_MODULE_DISABLE();
        timer0_prescaler_config(timer);
        timer0_mode_select(timer);
        timer0_register_size_config(timer);
        TMR0H = (timer->timer0_preload_value) >> 8;
        TMR0L = (uint8) (timer->timer0_preload_value);
        timer0_preload = timer->timer0_preload_value;
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER0_InterruptEnable();
        TIMER0_InterruptClearFlag();
        TIMER0_InterruptHandler = timer->TIMER0_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if (INTERRUPT_HIGH_PRIORITY == timer->priority) {
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER0_HighPrioritySet();
        } else if (INTERRUPT_LOW_PRIORITY == timer->priority) {
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER0_LowPrioritySet();
        } else {
            /*Nothing*/
        }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        TIMER0_MODULE_ENABLE();
    }
    return ret;
}

/**
 * 
 * @param timer
 * @return 
 */
STD_ReturnType Timer0_DeInit(const timer0_t *timer) {
    STD_ReturnType ret = E_OK;
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        TIMER0_MODULE_DISABLE();
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER0_InterruptDisable();
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
STD_ReturnType Timer0_Write_Value(const timer0_t *timer, uint16 value) {
    STD_ReturnType ret = E_OK;
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        TMR0H = (value) >> 8;
        TMR0L = (uint8) (value);
    }
    return ret;
}

/**
 * 
 * @param timer
 * @param value
 * @return 
 */
STD_ReturnType Timer0_Read_Value(const timer0_t *timer, uint16 *value) {
    STD_ReturnType ret = E_OK;
    if ((NULL == timer) || (NULL == value)) {
        ret = E_NOT_OK;
    } else {
        uint8 l_tmr0l = 0, l_tmr0h = 0;
        l_tmr0l = TMR0L;
        l_tmr0h = TMR0H;
        *value = (l_tmr0h << 8) + l_tmr0l;
    }
    return ret;
}

void TIMER0_ISR(void) {
    TIMER0_InterruptClearFlag();
    TMR0H = (timer0_preload) >> 8;
    TMR0L = (uint8) (timer0_preload);
    if (TIMER0_InterruptHandler) {
        TIMER0_InterruptHandler();
    }
}

/**
 * 
 * @param timer
 * @return 
 */
static inline STD_ReturnType timer0_prescaler_config(const timer0_t *timer) {
    STD_ReturnType ret = E_OK;
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        if (TIMER0_PRESCALER_ENABLE_CFG == timer->prescaler_enable) {
            TIMER0_PRESCALER_ENABLE();
            T0CONbits.T0PS = timer->prescaler_value;
        } else if (TIMER0_PRESCALER_DISABLE_CFG == timer->prescaler_enable) {
            TIMER0_PRESCALER_DISABLE();
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
static inline STD_ReturnType timer0_mode_select(const timer0_t *timer) {
    STD_ReturnType ret = E_OK;
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        if (TIMER0_TIMER_MODE == timer->timer0_mode) {
            TIMER0_TIMER_MODE_ENABLE();
        } else if (TIMER0_COUNTER_MODE == timer->timer0_mode) {
            TIMER0_COUNTER_MODE_ENABLE();
            if (TIMER0_RISING_EDGE_CFG == timer->timer0_counter_edge) {
                TIMER0_RISING_EDGE_ENABLE();
            } else if (TIMER0_FALLING_EDGE_CFG == timer->timer0_counter_edge) {
                TIMER0_FALLING_EDGE_ENABLE();
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
static inline STD_ReturnType timer0_register_size_config(const timer0_t *timer) {
    STD_ReturnType ret = E_OK;
    if (NULL == timer) {
        ret = E_NOT_OK;
    } else {
        if (TIMER0_8BIT_REGISTER_MODE == timer->timer0_register_size) {
            TIMER0_8BIT_REGISTER_MODE_ENABLE();
        } else if (TIMER0_16BIT_REGISTER_MODE == timer->timer0_register_size) {
            TIMER0_16BIT_REGISTER_MODE_ENABLE();
        } else {
            /*Nothing*/
        }
    }
    return ret;
}