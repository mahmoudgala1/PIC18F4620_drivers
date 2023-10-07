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

#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define TIMER2_InterruptDisable()   (PIE1bits.TMR2IE=0)
#define TIMER2_InterruptEnable()    (PIE1bits.TMR2IE=1)
#define TIMER2_InterruptClearFlag() (PIR1bits.TMR2IF=0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
#define TIMER2_HighPrioritySet()    (IPR1bits.TMR2IP=1)
#define TIMER2_LowPrioritySet()     (IPR1bits.TMR2IP=0)
#endif
#endif

#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define TIMER3_InterruptDisable()   (PIE2bits.TMR3IE=0)
#define TIMER3_InterruptEnable()    (PIE2bits.TMR3IE=1)
#define TIMER3_InterruptClearFlag() (PIR2bits.TMR3IF=0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
#define TIMER3_HighPrioritySet()    (IPR2bits.TMR3IP=1)
#define TIMER3_LowPrioritySet()     (IPR2bits.TMR3IP=0)
#endif
#endif

#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define CCP1_InterruptDisable()   (PIE1bits.CCP1IE=0)
#define CCP1_InterruptEnable()    (PIE1bits.CCP1IE=1)
#define CCP1_InterruptClearFlag() (PIR1bits.CCP1IF=0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
#define CCP1_HighPrioritySet()    (IPR1bits.CCP1IP=1)
#define CCP1_LowPrioritySet()     (IPR1bits.CCP1IP=0)
#endif
#endif

#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define CCP2_InterruptDisable()   (PIE2bits.CCP2IE=0)
#define CCP2_InterruptEnable()    (PIE2bits.CCP2IE=1)
#define CCP2_InterruptClearFlag() (PIR2bits.CCP2IF=0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
#define CCP2_HighPrioritySet()    (IPR2bits.CCP2IP=1)
#define CCP2_LowPrioritySet()     (IPR2bits.CCP2IP=0)
#endif
#endif
/* Section : Data Type Declaration */

/* Section : Function Declaration */

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

