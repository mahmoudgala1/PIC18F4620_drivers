/* 
 * File:   mcal_external_interrupt.h
 * Author: Mahmoud Elgendy
 *
 * Created on August 26, 2023, 5:31 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/* Section : Includes */
#include "mcal_interrupt_config.h"

/* Section : Macro Declaration */

/* Section : Macro Function Declaration */
#if EXTERNAL_INTERRUPT_INTX_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define EX_INT0_INTERRUPT_ENABLE()           (INTCONbits.INT0IE=1)
#define EX_INT0_INTERRUPT_DISABLE()          (INTCONbits.INT0IE=0)
#define EX_INT0_INTERRUPT_CLEAR_FLAG()       (INTCONbits.INT0IF=0)
#define EX_INT0_RISING_EDGE_SET()            (INTCON2bits.INTEDG0=1)
#define EX_INT0_FALLING_EDGE_SET()           (INTCON2bits.INTEDG0=0)

#define EX_INT1_INTERRUPT_ENABLE()           (INTCON3bits.INT1IE=1)
#define EX_INT1_INTERRUPT_DISABLE()          (INTCON3bits.INT1IE=0)
#define EX_INT1_INTERRUPT_CLEAR_FLAG()       (INTCON3bits.INT1IF=0)
#define EX_INT1_RISING_EDGE_SET()            (INTCON2bits.INTEDG1=1)
#define EX_INT1_FALLING_EDGE_SET()           (INTCON2bits.INTEDG1=0)

#define EX_INT2_INTERRUPT_ENABLE()           (INTCON3bits.INT2IE=1)
#define EX_INT2_INTERRUPT_DISABLE()          (INTCON3bits.INT2IE=0)
#define EX_INT2_INTERRUPT_CLEAR_FLAG()       (INTCON3bits.INT2IF=0)
#define EX_INT2_RISING_EDGE_SET()            (INTCON2bits.INTEDG2=1)
#define EX_INT2_FALLING_EDGE_SET()           (INTCON2bits.INTEDG2=0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

#define EX_INT1_HIGH_PRIORITY_SET() (INTCON3bits.INT1IP=1)
#define EX_INT1_LOW_PRIORITY_SET()  (INTCON3bits.INT1IP=0)

#define EX_INT2_HIGH_PRIORITY_SET() (INTCON3bits.INT2IP=1)
#define EX_INT2_LOW_PRIORITY_SET()  (INTCON3bits.INT2IP=0)

#endif

#endif

#if EXTERNAL_INTERRUPT_ONCHANGE_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define EX_RBX_INTERRUPT_ENABLE()     (INTCONbits.RBIE=1)
#define EX_RBX_INTERRUPT_DISABLE()     (INTCONbits.RBIE=0)
#define EX_RBX_INTERRUPT_CLEAR_FLAG() (INTCONbits.RBIF=0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

#define EX_RBX_HIGH_PRIORITY_SET() (INTCON2bits.RBIP=1)
#define EX_RBX_LOW_PRIORITY_SET() (INTCON2bits.RBIP=0)

#endif

#endif

/* Section : Data Type Declaration */
typedef enum {
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RISING_EDGE
} interrupt_INTX_edge;

typedef enum {
    INTERRUPT_EXTERNAL_INT0 = 0,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2
} interrupt_INTX_source;

typedef struct {
    void (* EXT_InterruptHandel)(void);
    pin_config_t mcu_pin;
    interrupt_INTX_edge edge;
    interrupt_INTX_source source;
    interrupt_priority_cfg priority;
} interrupt_INTX_t;

typedef struct {
    void (* EXT_InterruptHandler_High)(void);
    void (* EXT_InterruptHandler_Low)(void);
    pin_config_t mcu_pin;
    interrupt_priority_cfg priority;
} interrupt_RBX_t;

/* Section : Function Declaration */
STD_ReturnType Interrupt_INTX_Init(const interrupt_INTX_t *int_obj);
STD_ReturnType Interrupt_INTX_DeInit(const interrupt_INTX_t *int_obj);
STD_ReturnType Interrupt_RBX_Init(const interrupt_RBX_t *int_obj);
STD_ReturnType Interrupt_RBX_DeInit(const interrupt_RBX_t *int_obj);

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

