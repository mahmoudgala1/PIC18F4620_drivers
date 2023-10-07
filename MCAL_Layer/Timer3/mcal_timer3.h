/* 
 * File:   mcal_timer3.h
 * Author: Mahmoud Elgendy
 *
 * Created on September 29, 2023, 1:42 AM
 */

#ifndef MCAL_TIMER3_H
#define	MCAL_TIMER3_H

/* Section : Includes */
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/* Section : Macro Declaration */
#define TIMER3_TIMER_MODE   0x00
#define TIMER3_COUNTER_MODE 0x01

#define TIMER3_ASYNC_COUNTER_MODE 0x01
#define TIMER3_SYNC_COUNTER_MODE  0x00

#define TIMER3_PRESCALER_DIV_BY_1 0x00
#define TIMER3_PRESCALER_DIV_BY_2 0x01
#define TIMER3_PRESCALER_DIV_BY_4 0x02
#define TIMER3_PRESCALER_DIV_BY_8 0x03

#define TIMER3_RW_REG_8BIT_MODE  0x01
#define TIMER3_RW_REG_16BIT_MODE 0x00

/* Section : Macro Function Declaration */
#define TIMER3_MODULE_ENABLE()  (T3CONbits.TMR3ON=1)
#define TIMER3_MODULE_DISABLE() (T3CONbits.TMR3ON=0)

#define TIMER3_TIMER_MODE_ENABLE()   (T3CONbits.TMR3CS=0)
#define TIMER3_COUNTER_MODE_ENABLE() (T3CONbits.TMR3CS=1)

#define TIMER3_RW_REG_8BIT_MODE_ENABLE()  (T3CONbits.RD16=0)
#define TIMER3_RW_REG_16BIT_MODE_ENABLE() (T3CONbits.RD16=1)

#define TIMER3_ASYNC_COUNTER_MODE_ENABLE() (T3CONbits.NOT_T3SYNC=1)
#define TIMER3_SYNC_COUNTER_MODE_ENABLE()  (T3CONbits.NOT_T3SYNC=0)

#define TIMER3_PRESCALER_SELECT(_PRESCALER_)  (T3CONbits.T3CKPS=_PRESCALER_)

/* Section : Data Type Declaration */
typedef struct {
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* TIMER3_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint16 timer3_preload_value;
    uint8 timer3_prescaler_value : 2;
    uint8 timer3_mode : 1;
    uint8 timer3_counter_mode : 1;
    uint8 timer3_reg_rw_mode : 1;
    uint8 timer3_reserved : 3;
} timer3_t;
/* Section : Function Declaration */
STD_ReturnType Timer3_Init(const timer3_t *timer);
STD_ReturnType Timer3_DeInit(const timer3_t *timer);
STD_ReturnType Timer3_Write_Value(const timer3_t *timer, uint16 value);
STD_ReturnType Timer3_Read_Value(const timer3_t *timer, uint16 *value);

#endif	/* MCAL_TIMER3_H */

