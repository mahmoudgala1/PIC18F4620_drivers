/* 
 * File:   mcal_timer2.h
 * Author: Mahmoud Elgendy
 *
 * Created on September 28, 2023, 11:02 PM
 */

#ifndef MCAL_TIMER2_H
#define	MCAL_TIMER2_H

/* Section : Includes */
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/* Section : Macro Declaration */
#define TIMER2_PRESCALER_DIV_BY_1  0x00
#define TIMER2_PRESCALER_DIV_BY_4  0x01
#define TIMER2_PRESCALER_DIV_BY_16 0x02

#define TIMER2_POSTSCALER_DIV_BY_1   0x00
#define TIMER2_POSTSCALER_DIV_BY_2   0x01
#define TIMER2_POSTSCALER_DIV_BY_3   0x02
#define TIMER2_POSTSCALER_DIV_BY_4   0x03
#define TIMER2_POSTSCALER_DIV_BY_5   0x04
#define TIMER2_POSTSCALER_DIV_BY_6   0x05
#define TIMER2_POSTSCALER_DIV_BY_7   0x06
#define TIMER2_POSTSCALER_DIV_BY_8   0x07
#define TIMER2_POSTSCALER_DIV_BY_9   0x08
#define TIMER2_POSTSCALER_DIV_BY_10  0x09
#define TIMER2_POSTSCALER_DIV_BY_11  0x0A
#define TIMER2_POSTSCALER_DIV_BY_12  0x0B
#define TIMER2_POSTSCALER_DIV_BY_13  0x0C
#define TIMER2_POSTSCALER_DIV_BY_14  0x0D
#define TIMER2_POSTSCALER_DIV_BY_15  0x0E
#define TIMER2_POSTSCALER_DIV_BY_16  0x0F
/* Section : Macro Function Declaration */
#define TIMER2_MODULE_ENABLE()  (T2CONbits.TMR2ON=1)
#define TIMER2_MODULE_DISABLE() (T2CONbits.TMR2ON=0)

/* Section : Data Type Declaration */
typedef struct {
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* TIMER2_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint8 timer2_preload_value;
    uint8 timer2_postscaler_value : 4;
    uint8 timer2_prescaler_value : 2;
    uint8 timer2_reserved : 2;
} timer2_t;
/* Section : Function Declaration */
STD_ReturnType Timer2_Init(const timer2_t *timer);
STD_ReturnType Timer2_DeInit(const timer2_t *timer);
STD_ReturnType Timer2_Write_Value(const timer2_t *timer, uint8 value);
STD_ReturnType Timer2_Read_Value(const timer2_t *timer, uint8 *value);

#endif	/* MCAL_TIMER2_H */

