/* 
 * File:   mcal_ccp1.c
 * Author: Mahmoud Elgendy
 *
 * Created on October 5, 2023, 11:35 AM
 */
#include "mcal_ccp1.h"

static void CCP_Interrupt_Config(const ccp_t *ccp_obj);
static void CCP_Capture_Mode_Config(const ccp_t *ccp_obj);
static void CCP_Capture_Compare_Mode_Timer_Select(const ccp_t *ccp_obj);
static void CCP_Compare_Mode_Config(const ccp_t *ccp_obj);
static void CCP_PWM_Mode_Config(const ccp_t *ccp_obj);

#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (* CCP1_InterruptHandler)(void) = NULL;
#endif
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (* CCP2_InterruptHandler)(void) = NULL;
#endif

/**
 * 
 * @param ccp_obj
 * @return 
 */
STD_ReturnType CCP_Init(const ccp_t *ccp_obj) {
    STD_ReturnType ret = E_OK;
    if (NULL == ccp_obj) {
        ret = E_NOT_OK;
    } else {
        if (CCP1_INST == ccp_obj->ccp_inst) {
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
        } else if (CCP2_INST == ccp_obj->ccp_inst) {
            CCP2_SET_MODE(CCP_MODULE_DISABLE);
        } else {
            /*Nothing*/
        }
        if (CCP_CAPTURE_MODE_SELECTED == ccp_obj->ccp_mode) {
#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED)
            CCP_Capture_Mode_Config(ccp_obj);
            CCP_Capture_Compare_Mode_Timer_Select(ccp_obj);
#endif
        } else if (CCP_COMPARE_MODE_SELECTED == ccp_obj->ccp_mode) {
#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED)
            CCP_Compare_Mode_Config(ccp_obj);
            CCP_Capture_Compare_Mode_Timer_Select(ccp_obj);
#endif
        } else if (CCP_PWM_MODE_SELECTED == ccp_obj->ccp_mode) {
#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)
            CCP_PWM_Mode_Config(ccp_obj);
#endif
        } else {
            /*Nothing*/
        }
        gpio_pin_intialize(&(ccp_obj->ccp_pin));
        CCP_Interrupt_Config(ccp_obj);
    }
    return ret;
}

/**
 * 
 * @param ccp_obj
 * @return 
 */
STD_ReturnType CCP_DeInit(const ccp_t *ccp_obj) {
    STD_ReturnType ret = E_OK;
    if (NULL == ccp_obj) {
        ret = E_NOT_OK;
    } else {
        if (CCP1_INST == ccp_obj->ccp_inst) {
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            CCP1_InterruptDisable();
#endif
        } else if (CCP2_INST == ccp_obj->ccp_inst) {
            CCP2_SET_MODE(CCP_MODULE_DISABLE);
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            CCP2_InterruptDisable();
#endif
        } else {
            /*Nothing*/
        }
    }
    return ret;
}

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED)

/**
 * 
 * @param capture_status
 * @return 
 */
STD_ReturnType CCP_IsCaptureDataReady(const ccp_t *ccp_obj, uint8 *capture_status) {
    STD_ReturnType ret = E_OK;
    if (NULL == capture_status) {
        ret = E_NOT_OK;
    } else {
        if (CCP1_INST == ccp_obj->ccp_inst) {
            if (CCP_CAPTURE_READY == PIR1bits.CCP1IF) {
                *capture_status = CCP_CAPTURE_READY;
            } else {
                *capture_status = CCP_CAPTURE_NOT_READY;
            }
        } else if (CCP2_INST == ccp_obj->ccp_inst) {
            if (CCP_CAPTURE_READY == PIR2bits.CCP2IF) {
                *capture_status = CCP_CAPTURE_READY;
            } else {
                *capture_status = CCP_CAPTURE_NOT_READY;
            }
        } else {
            /*Nothing*/
        }
    }
    return ret;
}

/**
 * 
 * @param capture_value
 * @return 
 */
STD_ReturnType CCP_Capture_Mode_Read_Value(const ccp_t *ccp_obj, uint16 *capture_value) {
    STD_ReturnType ret = E_OK;
    ccp_reg_t capture_temp_value = {.ccpr_low = 0, .ccpr_high = 0};
    if (NULL == capture_value) {
        ret = E_NOT_OK;
    } else {
        if (CCP1_INST == ccp_obj->ccp_inst) {
            capture_temp_value.ccpr_low = CCPR1L;
            capture_temp_value.ccpr_high = CCPR1H;
            *capture_value = capture_temp_value.ccpr_16bit;
        } else if (CCP2_INST == ccp_obj->ccp_inst) {
            capture_temp_value.ccpr_low = CCPR2L;
            capture_temp_value.ccpr_high = CCPR2H;
            *capture_value = capture_temp_value.ccpr_16bit;
        } else {
            /*Nothing*/
        }
    }
    return ret;
}

static void CCP_Capture_Mode_Config(const ccp_t *ccp_obj) {
    if (CCP1_INST == ccp_obj->ccp_inst) {
        switch (ccp_obj->ccp_mode_variant) {
            case CCP_CAPTURE_MODE_1_FALLING_EDGE:
                CCP1_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE);
                break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE:
                CCP1_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);
                break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE:
                CCP1_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);
                break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE:
                CCP1_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE);
                break;
            default:break;
        }
    } else if (CCP2_INST == ccp_obj->ccp_inst) {
        switch (ccp_obj->ccp_mode_variant) {
            case CCP_CAPTURE_MODE_1_FALLING_EDGE:
                CCP2_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE);
                break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE:
                CCP2_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);
                break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE:
                CCP2_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);
                break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE:
                CCP2_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE);
                break;
            default:break;
        }
    } else {
        /*Nothing*/
    }
}


#endif

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED)

/**
 * 
 * @param compare_status
 * @return 
 */
STD_ReturnType CCP_IsCompareComplete(const ccp_t *ccp_obj, uint8 *compare_status) {
    STD_ReturnType ret = E_OK;
    if (NULL == ccp_obj || NULL == compare_status) {
        ret = E_NOT_OK;
    } else {
        if (CCP1_INST == ccp_obj->ccp_inst) {
            if (CCP_COMPARE_READY == PIR1bits.CCP1IF) {
                *compare_status = CCP_COMPARE_READY;
            } else {
                *compare_status = CCP_COMPARE_NOT_READY;
            }
        } else if (CCP2_INST == ccp_obj->ccp_inst) {
            if (CCP_COMPARE_READY == PIR2bits.CCP2IF) {
                *compare_status = CCP_COMPARE_READY;
            } else {
                *compare_status = CCP_COMPARE_NOT_READY;
            }
        } else {
            /*Nothing*/
        }
    }
    return ret;
}

/**
 * 
 * @param compare_value
 * @return 
 */
STD_ReturnType CCP_Compare_Mode_Set_Value(const ccp_t *ccp_obj, uint16 compare_value) {
    STD_ReturnType ret = E_OK;
    if (NULL == ccp_obj) {
        ret = E_NOT_OK;
    } else {
        ccp_reg_t capture_temp_val = {.ccpr_16bit = compare_value};
        if (CCP1_INST == ccp_obj->ccp_inst) {
            CCPR1L = capture_temp_val.ccpr_low;
            CCPR1H = capture_temp_val.ccpr_high;
        } else if (CCP2_INST == ccp_obj->ccp_inst) {
            CCPR2L = capture_temp_val.ccpr_low;
            CCPR2H = capture_temp_val.ccpr_high;
        } else {
            /*Nothing*/
        }
    }
    return ret;
}

static void CCP_Compare_Mode_Config(const ccp_t *ccp_obj) {
    if (CCP1_INST == ccp_obj->ccp_inst) {
        switch (ccp_obj->ccp_mode_variant) {
            case CCP_COMPARE_MODE_SET_PIN_LOW:
                CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);
                break;
            case CCP_COMPARE_MODE_SET_PIN_HIGH:
                CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);
                break;
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH:
                CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);
                break;
            case CCP_COMPARE_MODE_GEN_SW_INTERRUPT:
                CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);
                break;
            case CCP_COMPARE_MODE_GEN_EVENT:
                CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);
                break;
            default:break;
        }
    } else if (CCP2_INST == ccp_obj->ccp_inst) {
        switch (ccp_obj->ccp_mode_variant) {
            case CCP_COMPARE_MODE_SET_PIN_LOW:
                CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);
                break;
            case CCP_COMPARE_MODE_SET_PIN_HIGH:
                CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);
                break;
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH:
                CCP2_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);
                break;
            case CCP_COMPARE_MODE_GEN_SW_INTERRUPT:
                CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);
                break;
            case CCP_COMPARE_MODE_GEN_EVENT:
                CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);
                break;
            default:break;
        }
    } else {
        /*Nothing*/
    }
}
#endif

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)

/**
 * 
 * @param duty
 * @return 
 */
STD_ReturnType CCP_PWM_Set_Duty(const ccp_t *ccp_obj, const uint8 duty) {
    STD_ReturnType ret = E_OK;
    if (NULL == ccp_obj) {
        ret = E_NOT_OK;
    } else {
        uint16 l_duty = (uint16) (4 * (PR2 + 1)*(duty / 100.0));
        if (CCP1_INST == ccp_obj->ccp_inst) {
            CCP1CONbits.DC1B = (uint8) (l_duty & (0x0003));
            CCPR1L = (uint8) (l_duty >> 2);
        } else if (CCP2_INST == ccp_obj->ccp_inst) {
            CCP2CONbits.DC2B = (uint8) (l_duty & (0x0003));
            CCPR2L = (uint8) (l_duty >> 2);
        } else {
            /*Nothing*/
        }
    }
    return ret;
}

/**
 * 
 * @param 
 * @return 
 */
STD_ReturnType CCP_PWM_Start(const ccp_t *ccp_obj) {
    STD_ReturnType ret = E_OK;
    if (NULL == ccp_obj) {
        ret = E_NOT_OK;
    } else {
        if (CCP1_INST == ccp_obj->ccp_inst) {
            CCP1_SET_MODE(CCP_PWM_MODE);
        } else if (CCP2_INST == ccp_obj->ccp_inst) {
            CCP2_SET_MODE(CCP_PWM_MODE);
        } else {
            /*Nothing*/
        }
    }
    return ret;
}

/**
 * 
 * @param 
 * @return 
 */
STD_ReturnType CCP_PWM_Stop(const ccp_t *ccp_obj) {
    STD_ReturnType ret = E_OK;
    if (NULL == ccp_obj) {
        ret = E_NOT_OK;
    } else {
        if (CCP1_INST == ccp_obj->ccp_inst) {
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
        } else if (CCP2_INST == ccp_obj->ccp_inst) {
            CCP2_SET_MODE(CCP_MODULE_DISABLE);
        } else {
            /*Nothing*/
        }
    }
    return ret;
}

static void CCP_PWM_Mode_Config(const ccp_t *ccp_obj) {
    if (CCP1_INST == ccp_obj->ccp_inst) {
        if (CCP_PWM_MODE == ccp_obj->ccp_mode_variant) {
            CCP1_SET_MODE(CCP_PWM_MODE);
        } else {
            /*Nothing*/
        }
    } else if (CCP2_INST == ccp_obj->ccp_inst) {
        if (CCP_PWM_MODE == ccp_obj->ccp_mode_variant) {
            CCP2_SET_MODE(CCP_PWM_MODE);
        } else {
            /*Nothing*/
        }
    } else {
        /*Nothing*/
    }
    PR2 = (uint8) ((_XTAL_FREQ / (ccp_obj->PWM_Frequency * 4.0 * ccp_obj->ccp_postscaler_value * ccp_obj->ccp_prescaler_value)) - 1);
}

#endif

void CCP1_ISR(void) {
    CCP1_InterruptClearFlag();
    if (CCP1_InterruptHandler) {
        CCP1_InterruptHandler();
    }
}

void CCP2_ISR(void) {
    CCP2_InterruptClearFlag();
    if (CCP2_InterruptHandler) {
        CCP2_InterruptHandler();
    }
}

static void CCP_Interrupt_Config(const ccp_t *ccp_obj) {
    if (CCP1_INST == ccp_obj->ccp_inst) {
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        CCP1_InterruptEnable();
        CCP1_InterruptClearFlag();
        CCP1_InterruptHandler = ccp_obj->CCP1_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if (INTERRUPT_HIGH_PRIORITY == ccp_obj->CCP1_priority) {
            INTERRUPT_GlobalInterruptHighEnable();
            CCP1_HighPrioritySet();
        } else if (INTERRUPT_LOW_PRIORITY == ccp_obj->CCP1_priority) {
            INTERRUPT_GlobalInterruptLowEnable();
            CCP1_LowPrioritySet();
        } else {
            /*Nothing*/
        }
#else
        INTERRUPT_PeripheralInterruptEnable();
        INTERRUPT_GlobalInterruptEnable();
#endif
#endif
    } else if (CCP2_INST == ccp_obj->ccp_inst) {
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        CCP2_InterruptEnable();
        CCP2_InterruptClearFlag();
        CCP2_InterruptHandler = ccp_obj->CCP2_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if (INTERRUPT_HIGH_PRIORITY == ccp_obj->CCP2_priority) {
            INTERRUPT_GlobalInterruptHighEnable();
            CCP2_HighPrioritySet();
        } else if (INTERRUPT_LOW_PRIORITY == ccp_obj->CCP2_priority) {
            INTERRUPT_GlobalInterruptLowEnable();
            CCP2_LowPrioritySet();
        } else {
            /*Nothing*/
        }
#else
        INTERRUPT_PeripheralInterruptEnable();
        INTERRUPT_GlobalInterruptEnable();
#endif
#endif
    } else {
        /*Nothing*/
    }
}

static void CCP_Capture_Compare_Mode_Timer_Select(const ccp_t *ccp_obj) {
    if (CCP1_CCP2_TIMER3 == ccp_obj->ccp_capture_compare_timer) {
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 1;
    } else if (CCP1_TIMER1_CCP2_TIMER3 == ccp_obj->ccp_capture_compare_timer) {
        T3CONbits.T3CCP1 = 1;
        T3CONbits.T3CCP2 = 0;
    } else if (CCP1_CCP2_TIMER1 == ccp_obj->ccp_capture_compare_timer) {
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 0;
    } else {
        /*Nothing*/
    }
}