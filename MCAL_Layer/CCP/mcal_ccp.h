/* 
 * File:   mcal_ccp1.h
 * Author: Mahmoud Elgendy
 *
 * Created on October 5, 2023, 11:35 AM
 */

#ifndef MCAL_CCP1_H
#define	MCAL_CCP1_H

/* Section : Includes */
#include "mcal_ccp1_cfg.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* Section : Macro Declaration */
#define CCP_MODULE_DISABLE                0x00
#define CCP_CAPTURE_MODE_1_FALLING_EDGE   0x04
#define CCP_CAPTURE_MODE_1_RISING_EDGE    0x05
#define CCP_CAPTURE_MODE_4_RISING_EDGE    0x06
#define CCP_CAPTURE_MODE_16_RISING_EDGE   0x07
#define CCP_COMPARE_MODE_SET_PIN_LOW      0x08
#define CCP_COMPARE_MODE_SET_PIN_HIGH     0x09
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH  0x02
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT 0x0A
#define CCP_COMPARE_MODE_GEN_EVENT        0x0B
#define CCP_PWM_MODE                      0x0C

#define CCP_COMPARE_NOT_READY 0x00
#define CCP_COMPARE_READY     0x01

#define CCP_CAPTURE_NOT_READY 0x00
#define CCP_CAPTURE_READY     0x01

/* Section : Macro Function Declaration */
#define CCP1_SET_MODE(_CONFIG) (CCP1CONbits.CCP1M=_CONFIG)
#define CCP2_SET_MODE(_CONFIG) (CCP2CONbits.CCP2M=_CONFIG)

/* Section : Data Type Declaration */
typedef enum {
    CCP_CAPTURE_MODE_SELECTED = 0,
    CCP_COMPARE_MODE_SELECTED,
    CCP_PWM_MODE_SELECTED
} ccp_mode_t;

typedef union {

    struct {
        uint8 ccpr_low;
        uint8 ccpr_high;
    };

    struct {
        uint16 ccpr_16bit;
    };
} ccp_reg_t;

typedef enum {
    CCP1_INST = 0,
    CCP2_INST
} ccp_inst_t;

typedef enum {
    CCP1_CCP2_TIMER3 = 0,
    CCP1_TIMER1_CCP2_TIMER3,
    CCP1_CCP2_TIMER1
} ccp_capture_compare_timer_t;

typedef struct {
    ccp_inst_t ccp_inst;
    ccp_mode_t ccp_mode;
    uint8 ccp_mode_variant;
    ccp_capture_compare_timer_t ccp_capture_compare_timer;
    pin_config_t ccp_pin;
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* CCP1_InterruptHandler)(void);
    interrupt_priority_cfg CCP1_priority;
#endif
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* CCP2_InterruptHandler)(void);
    interrupt_priority_cfg CCP2_priority;
#endif
#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED)

#endif
#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED)

#endif
#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)
    uint32 PWM_Frequency;
    uint8 ccp_postscaler_value : 4;
    uint8 ccp_prescaler_value : 2;
#endif
} ccp_t;

/* Section : Function Declaration */
STD_ReturnType CCP_Init(const ccp_t *ccp_obj);
STD_ReturnType CCP_DeInit(const ccp_t *ccp_obj);
#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED)
STD_ReturnType CCP_IsCaptureDataReady(const ccp_t *ccp_obj, uint8 *capture_status);
STD_ReturnType CCP_Capture_Mode_Read_Value(const ccp_t *ccp_obj, uint16 *capture_value);
#endif
#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED)
STD_ReturnType CCP_IsCompareComplete(const ccp_t *ccp_obj, uint8 *compare_status);
STD_ReturnType CCP_Compare_Mode_Set_Value(const ccp_t *ccp_obj, uint16 compare_value);
#endif
#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)
STD_ReturnType CCP_PWM_Set_Duty(const ccp_t *ccp_obj, const uint8 duty);
STD_ReturnType CCP_PWM_Start(const ccp_t *ccp_obj);
STD_ReturnType CCP_PWM_Stop(const ccp_t *ccp_obj);
#endif

#endif	/* MCAL_CCP1_H */

