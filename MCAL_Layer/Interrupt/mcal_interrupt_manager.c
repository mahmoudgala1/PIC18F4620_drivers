/* 
 * File:   mcal_interrupt_manager.c
 * Author: Mahmoud Elgendy
 *
 * Created on August 26, 2023, 5:35 PM
 */
#include "mcal_external_interrupt.h"
#include "mcal_interrupt_manager.h"
volatile static uint8 RB4_Flag = 1, RB5_Flag = 1, RB6_Flag = 1, RB7_Flag = 1;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE ==INTERRUPT_FEATURE_ENABLE

void __interrupt() InterruptManagerHigh(void) {
    if ((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF)) {
        INT0_ISR();
    } else {
        /*NoThing*/
    }
    if ((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF)) {
        INT2_ISR();
    } else {
        /*NoThing*/
    }

}

void __interrupt(low_priority) InterruptManagerLow(void) {
    if ((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF)) {
        INT1_ISR();
    } else {
        /*NoThing*/
    }
}
#else

void __interrupt() InterruptManager(void) {
    if ((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF)) {
        INT0_ISR();
    } else {
        /*NoThing*/
    }
    if ((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF)) {
        INT1_ISR();
    } else {
        /*NoThing*/
    }
    if ((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF)) {
        INT2_ISR();
    } else {
        /*NoThing*/
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB4 == GPIO_HIGH) && (1 == RB4_Flag)) {
        RB4_Flag = 0;
        RB4_ISR(0);
    } else {
        /*NoThing*/
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB4 == GPIO_LOW)&& (0 == RB4_Flag)) {
        RB4_Flag = 1;
        RB4_ISR(1);
    } else {
        /*NoThing*/
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB5 == GPIO_HIGH) && (1 == RB5_Flag)) {
        RB5_Flag = 0;
        RB5_ISR(0);
    } else {
        /*NoThing*/
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB5 == GPIO_LOW)&& (0 == RB5_Flag)) {
        RB5_Flag = 1;
        RB5_ISR(1);
    } else {
        /*NoThing*/
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB6 == GPIO_HIGH) && (1 == RB6_Flag)) {
        RB6_Flag = 0;
        RB6_ISR(0);
    } else {
        /*NoThing*/
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB6 == GPIO_LOW)&& (0 == RB6_Flag)) {
        RB6_Flag = 1;
        RB6_ISR(1);
    } else {
        /*NoThing*/
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB7 == GPIO_HIGH) && (1 == RB7_Flag)) {
        RB7_Flag = 0;
        RB7_ISR(0);
    } else {
        /*NoThing*/
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB7 == GPIO_LOW)&& (0 == RB7_Flag)) {
        RB7_Flag = 1;
        RB7_ISR(1);
    } else {
        /*NoThing*/
    }
}
#endif