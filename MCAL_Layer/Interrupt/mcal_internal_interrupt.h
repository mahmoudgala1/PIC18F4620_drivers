/* 
 * File:   mcal_internal_interrupt.h
 * Author: Mahmoud Elgendy
 *
 * Created on August 26, 2023, 5:30 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/* Section : Includes */
#include "mcal_interrupt_config.h"

/* Section : Macro Declaration */

/* Section : Macro Function Declaration */
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define ADC_InterruptDisable()   (PIE1bits.ADIE=0)
#define ADC_InterruptEnable()    (PIE1bits.ADIE=1)
#define ADC_InterruptClearFlag() (PIR1bits.ADIF=0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
#define ADC_HighPrioritySet()  (IPR1bits.ADIP=1)
#define ADC_LowPrioritySet()   (IPR1bits.ADIP=0)
#endif
#endif

#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define TIMER0_InterruptDisable()   (INTCONbits.TMR0IE=0)
#define TIMER0_InterruptEnable()    (INTCONbits.TMR0IE=1)
#define TIMER0_InterruptClearFlag() (INTCONbits.TMR0IF=0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
#define TIMER0_HighPrioritySet()    (INTCON2bits.TMR0IP=1)
#define TIMER0_LowPrioritySet()     (INTCON2bits.TMR0IP=0)
#endif
#endif

#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define TIMER1_InterruptDisable()   (PIE1bits.TMR1IE=0)
#define TIMER1_InterruptEnable()    (PIE1bits.TMR1IE=1)
#define TIMER1_InterruptClearFlag() (PIR1bits.TMR1IF=0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
#define TIMER1_HighPrioritySet()    (IPR1bits.TMR1IP=1)
#define TIMER1_LowPrioritySet()     (IPR1bits.TMR1IP=0)
#endif
#endif
/* Section : Data Type Declaration */

/* Section : Function Declaration */

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

