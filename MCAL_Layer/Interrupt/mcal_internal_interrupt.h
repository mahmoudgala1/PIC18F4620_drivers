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
/* Section : Data Type Declaration */

/* Section : Function Declaration */

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

