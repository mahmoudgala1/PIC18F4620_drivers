/* 
 * File:   mcal_timer1.h
 * Author: Mahmoud Elgendy
 *
 * Created on September 28, 2023, 1:50 AM
 */

#ifndef MCAL_TIMER1_H
#define	MCAL_TIMER1_H

/* Section : Includes */
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* Section : Macro Declaration */
#define TIMER1_TIMER_MODE   0x00
#define TIMER1_COUNTER_MODE 0x01

#define TIMER1_ASYNC_COUNTER_MODE 0x01
#define TIMER1_SYNC_COUNTER_MODE  0x00

#define TIMER1_RW_REG_8BIT_MODE  0x01
#define TIMER1_RW_REG_16BIT_MODE 0x00

#define TIMER1_OSCILLATOR_ENABLE  0x01
#define TIMER1_OSCILLATOR_DISABLE 0x01

#define TIMER1_PRESCALER_DIV_BY_1 0x00
#define TIMER1_PRESCALER_DIV_BY_2 0x01
#define TIMER1_PRESCALER_DIV_BY_4 0x02
#define TIMER1_PRESCALER_DIV_BY_8 0x03

/* Section : Macro Function Declaration */
#define TIMER1_TIMER_MODE_ENABLE()   (T1CONbits.TMR1CS=0)
#define TIMER1_COUNTER_MODE_ENABLE() (T1CONbits.TMR1CS=1)

#define TIMER1_RW_REG_8BIT_MODE_ENABLE()  (T1CONbits.RD16=0)
#define TIMER1_RW_REG_16BIT_MODE_ENABLE() (T1CONbits.RD16=1)

#define TIMER1_MODULE_ENABLE()  (T1CONbits.TMR1ON=1)
#define TIMER1_MODULE_DISABLE() (T1CONbits.TMR1ON=0)

#define TIMER1_ASYNC_COUNTER_MODE_ENABLE() (T1CONbits.NOT_T1SYNC=1)
#define TIMER1_SYNC_COUNTER_MODE_ENABLE()  (T1CONbits.NOT_T1SYNC=0)

#define TIMER1_OSC_HW_ENABLE()  (T1CONbits.T1OSCEN=1)
#define TIMER1_OSC_HW_DISABLE() (T1CONbits.T1OSCEN=0)

#define TIMER1_PRESCALER_SELECT(_PRESCALER_)  (T1CONbits.T1CKPS=_PRESCALER_)

#define TIMER1_SYSTEM_CLK_STATUS() (T1CONbits.T1RUN) 

/* Section : Data Type Declaration */
typedef struct {
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* TIMER1_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint16 timer1_preload_value;
    uint8 timer1_prescaler_value : 2;
    uint8 timer1_mode : 1;
    uint8 timer1_counter_mode : 1;
    uint8 timer1_osc_cfg : 1;
    uint8 timer1_reg_rw_mode : 1;
    uint8 timer1_reserved : 2;
} timer1_t;
/* Section : Function Declaration */
STD_ReturnType Timer1_Init(const timer1_t *timer);
STD_ReturnType Timer1_DeInit(const timer1_t *timer);
STD_ReturnType Timer1_Write_Value(const timer1_t *timer, uint16 value);
STD_ReturnType Timer1_Read_Value(const timer1_t *timer, uint16 *value);

#endif	/* MCAL_TIMER1_H */

