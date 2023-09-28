/* 
 * File:   hal_timer0.h
 * Author: Mahmoud Elgendy
 *
 * Created on September 27, 2023, 7:11 AM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/* Section : Includes */
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/* Section : Macro Declaration */
#define TIMER0_PRESCALER_ENABLE_CFG  0x01
#define TIMER0_PRESCALER_DISABLE_CFG 0x00

#define TIMER0_RISING_EDGE_CFG  0x01
#define TIMER0_FALLING_EDGE_CFG 0x00

#define TIMER0_TIMER_MODE 0x01
#define TIMER0_COUNTER_MODE 0x00

#define TIMER0_8BIT_REGISTER_MODE 0x01
#define TIMER0_16BIT_REGISTER_MODE 0x00

/* Section : Macro Function Declaration */
#define TIMER0_PRESCALER_ENABLE()    (T0CONbits.PSA=0)
#define TIMER0_PRESCALER_DISABLE()   (T0CONbits.PSA=1)

#define TIMER0_RISING_EDGE_ENABLE()  (T0CONbits.T0SE=0)
#define TIMER0_FALLING_EDGE_ENABLE() (T0CONbits.T0SE=1)

#define TIMER0_TIMER_MODE_ENABLE()   (T0CONbits.T0CS=0)
#define TIMER0_COUNTER_MODE_ENABLE() (T0CONbits.T0CS=1)

#define TIMER0_8BIT_REGISTER_MODE_ENABLE()  (T0CONbits.T08BIT=1)
#define TIMER0_16BIT_REGISTER_MODE_ENABLE() (T0CONbits.T08BIT=0)

#define TIMER0_MODULE_ENABLE() (T0CONbits.TMR0ON=1)
#define TIMER0_MODULE_DISABLE() (T0CONbits.TMR0ON=0)

/* Section : Data Type Declaration */
typedef enum {
    TIMER0_PRESCALER_DIV_BY_2,
    TIMER0_PRESCALER_DIV_BY_4,
    TIMER0_PRESCALER_DIV_BY_8,
    TIMER0_PRESCALER_DIV_BY_16,
    TIMER0_PRESCALER_DIV_BY_32,
    TIMER0_PRESCALER_DIV_BY_64,
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256
} timer0_prescaler_select_t;

typedef struct {
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* TIMER0_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    timer0_prescaler_select_t prescaler_value;
    uint16 timer0_preload_value;
    uint8 prescaler_enable : 1;
    uint8 timer0_counter_edge : 1;
    uint8 timer0_mode : 1;
    uint8 timer0_register_size : 1;
    uint8 timer0_reserved : 4;
} timer0_t;
/* Section : Function Declaration */
STD_ReturnType Timer0_Init(const timer0_t *timer);
STD_ReturnType Timer0_DeInit(const timer0_t *timer);
STD_ReturnType Timer0_Write_Value(const timer0_t *timer, uint16 value);
STD_ReturnType Timer0_Read_Value(const timer0_t *timer, uint16 *value);
#endif	/* HAL_TIMER0_H */

