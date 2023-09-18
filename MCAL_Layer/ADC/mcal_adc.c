
/* 
 * File:   mcal_adc.c
 * Author: Mahmoud Elgendy
 *
 * Created on September 12, 2023, 9:09 AM
 */
#include "mcal_adc.h"
static inline void adc_input_channel_port_configration(adc_channel_select_t channel);
static inline void adc_select_result_format(const adc_conf_t *_adc);
static inline void adc_configure_voltage_reference(const adc_conf_t *_adc);
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void(* ADC_InterruptHandler)(void) = NULL;
#endif 

/**
 * 
 * @param _adc
 * @return 
 */
STD_ReturnType ADC_Init(const adc_conf_t *_adc) {
    STD_ReturnType ret = E_OK;
    if (NULL == _adc) {
        ret = E_NOT_OK;
    } else {
        ADC_CONVERTER_DISABLE();
        ADCON2bits.ACQT = _adc->acquistion_time;
        ADCON2bits.ADCS = _adc->conversion_clock;
        ADCON0bits.CHS = _adc->adc_channel;
        adc_input_channel_port_configration(_adc->adc_channel);
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        ADC_InterruptEnable();
        ADC_InterruptHandler = _adc->ADC_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        if (INTERRUPT_HIGH_PRIORITY == _adc->priority) {
            ADC_HighPrioritySet();
        } else if (INTERRUPT_LOW_PRIORITY == _adc->priority) {
            ADC_LowPrioritySet();
        } else {
            /*Nothing*/
        }
#endif
#endif
        adc_select_result_format(_adc);
        adc_configure_voltage_reference(_adc);
        ADC_ANALOG_DIGITAL_PORT_CONFIGRATION(ADC_AN3_ANALOG_FUNCTIONALITY);
        ADC_CONVERTER_ENABLE();
    }
    return ret;
}

/**
 * 
 * @param _adc
 * @return 
 */
STD_ReturnType ADC_DeInit(const adc_conf_t *_adc) {
    STD_ReturnType ret = E_OK;
    if (NULL == _adc) {
        ret = E_NOT_OK;
    } else {
        ADC_CONVERTER_DISABLE();
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

#endif
    }
    return ret;
}

/**
 * 
 * @param _adc
 * @param channel
 * @return 
 */
STD_ReturnType ADC_SelectChannel(adc_channel_select_t channel) {
    STD_ReturnType ret = E_OK;
    ADCON0bits.CHS = channel;
    adc_input_channel_port_configration(channel);
    return ret;
}

/**
 * 
 * @param _adc
 * @return 
 */
STD_ReturnType ADC_StartConversion(const adc_conf_t *_adc) {
    STD_ReturnType ret = E_OK;
    if (NULL == _adc) {
        ret = E_NOT_OK;
    } else {
        ADC_START_CONVERSION();
    }
    return ret;
}

/**
 * 
 * @param _adc
 * @param conversion_status
 * @return 
 */
STD_ReturnType ADC_IsconversionDone(const adc_conf_t *_adc, uint8 *conversion_status) {
    STD_ReturnType ret = E_OK;
    if ((NULL == _adc) || (NULL == conversion_status)) {
        ret = E_NOT_OK;
    } else {
        *conversion_status = !(ADC_CONVERSION_STATUS());
    }
    return ret;
}

/**
 * 
 * @param _adc
 * @param conversion_result
 * @return 
 */
STD_ReturnType ADC_GetConversionResult(const adc_conf_t *_adc, uint16 *conversion_result) {
    STD_ReturnType ret = E_OK;
    if ((NULL == _adc) || (NULL == conversion_result)) {
        ret = E_NOT_OK;
    } else {
        if (ADC_RESULT_RIGHT == _adc->result_format) {
            *conversion_result = (uint16) ((ADRESH << 8) + ADRESL);
        } else if (ADC_RESULT_LEFT == _adc->result_format) {
            *conversion_result = (uint16) (((ADRESH << 8) + ADRESL) >> 6);
        } else {
            *conversion_result = (uint16) ((ADRESH << 8) + ADRESL);
        }
    }
    return ret;
}

/**
 * 
 * @param _adc
 * @param channel
 * @param conversion_result
 * @return 
 */
STD_ReturnType ADC_GetConversion_Blocking(const adc_conf_t *_adc, adc_channel_select_t channel
        , uint16 *conversion_result) {
    STD_ReturnType ret = E_OK;
    if ((NULL == _adc) || (NULL == conversion_result)) {
        ret = E_NOT_OK;
    } else {
        ADC_SelectChannel(channel);
        ADC_StartConversion(_adc);
        while (ADCON0bits.GO_nDONE);
        ADC_GetConversionResult(_adc, conversion_result);
    }
    return ret;
}

STD_ReturnType ADC_GetConversion_Interrupt(const adc_conf_t *_adc, adc_channel_select_t channel) {
    STD_ReturnType ret = E_OK;
    if ((NULL == _adc)) {
        ret = E_NOT_OK;
    } else {
        ADC_SelectChannel(channel);
        ADC_StartConversion(_adc);
    }
    return ret;
}

static inline void adc_input_channel_port_configration(adc_channel_select_t channel) {
    switch (channel) {
        case ADC_CHANNEL_AN0: SET_BIT(TRISA, _TRISA_TRISA0_POSN);
            break;
        case ADC_CHANNEL_AN1: SET_BIT(TRISA, _TRISA_TRISA1_POSN);
            break;
        case ADC_CHANNEL_AN2: SET_BIT(TRISA, _TRISA_TRISA2_POSN);
            break;
        case ADC_CHANNEL_AN3: SET_BIT(TRISA, _TRISA_TRISA3_POSN);
            break;
        case ADC_CHANNEL_AN4: SET_BIT(TRISA, _TRISA_TRISA5_POSN);
            break;
        case ADC_CHANNEL_AN5: SET_BIT(TRISE, _TRISE_TRISE0_POSN);
            break;
        case ADC_CHANNEL_AN6: SET_BIT(TRISE, _TRISE_TRISE1_POSN);
            break;
        case ADC_CHANNEL_AN7: SET_BIT(TRISE, _TRISE_TRISE2_POSN);
            break;
        case ADC_CHANNEL_AN8: SET_BIT(TRISB, _TRISB_TRISB2_POSN);
            break;
        case ADC_CHANNEL_AN9: SET_BIT(TRISB, _TRISB_TRISB3_POSN);
            break;
        case ADC_CHANNEL_AN10: SET_BIT(TRISB, _TRISB_TRISB1_POSN);
            break;
        case ADC_CHANNEL_AN11: SET_BIT(TRISB, _TRISB_TRISB4_POSN);
            break;
        case ADC_CHANNEL_AN12: SET_BIT(TRISB, _TRISB_TRISB0_POSN);
            break;
    }
}

static inline void adc_select_result_format(const adc_conf_t *_adc) {
    if (ADC_RESULT_RIGHT == _adc->result_format) {
        ADC_RESULT_RIGHT_FORMAT();
    } else if (ADC_RESULT_LEFT == _adc->result_format) {
        ADC_RESULT_LEFT_FORMAT();
    } else {
        ADC_RESULT_RIGHT_FORMAT();
    }
}

static inline void adc_configure_voltage_reference(const adc_conf_t *_adc) {
    if (ADC_VOLTAGE_REFERENCE_ENABLED == _adc->voltage_reference) {
        ADC_ENABLE_VOLTAGE_REFERENCE();
    } else if (ADC_VOLTAGE_REFERENCE_DISABLED == _adc->voltage_reference) {
        ADC_DISABLE_VOLTAGE_REFERENCE();
    } else {
        ADC_DISABLE_VOLTAGE_REFERENCE();
    }
}
void ADC_ISR(void){
    ADC_InterruptClearFlag();
    if(ADC_InterruptHandler){
        ADC_InterruptHandler();
    }
}