/* 
 * File:   ecu_chr_lcd.c
 * Author: Mahmoud Elgendy
 *
 * Created on August 22, 2023, 8:39 AM
 */
#include "ecu_chr_lcd.h"

static STD_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd, uint8 _data_command);
static STD_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd);
static STD_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column);
static STD_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd);
static STD_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column);

/**
 * 
 * @param lcd
 * @return 
 */
STD_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t *lcd) {
    STD_ReturnType ret = E_OK;
    uint8 l_counter = 0;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&(lcd->lcd_en));
        for (l_counter = 0; l_counter < 4; l_counter++) {
            ret = gpio_pin_intialize(&(lcd->lcd_data[l_counter]));
        }
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);

        ret = lcd_4bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = lcd_4bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(lcd, 0x80);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
STD_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd, uint8 command) {
    STD_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        lcd_send_4bits(lcd, command >> 4);
        lcd_4bit_send_enable_signal(lcd);
        lcd_send_4bits(lcd, command);
        lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
STD_ReturnType lcd_4bit_send_data(const chr_lcd_4bit_t *lcd, uint8 data) {
    STD_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        lcd_send_4bits(lcd, data >> 4);
        lcd_4bit_send_enable_signal(lcd);
        lcd_send_4bits(lcd, data);
        lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}
STD_ReturnType lcd_4bit_send_number(const chr_lcd_4bit_t *lcd, signed long   number) {
    STD_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        uint8 number_data[20];
        sprintf(number_data, "%li", number);
        lcd_4bit_send_string(lcd, number_data);
    }

    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return 
 */
STD_ReturnType lcd_4bit_send_data_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data) {
    STD_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        lcd_4bit_set_cursor(lcd, row, column);
        lcd_4bit_send_data(lcd, data);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
STD_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd, uint8 *str) {
    STD_ReturnType ret = E_OK;
    if ((NULL == lcd) || (NULL == str)) {
        ret = E_NOT_OK;
    } else {
        while (*str) {
            lcd_4bit_send_data(lcd, *str++);
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return 
 */
STD_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str) {
    STD_ReturnType ret = E_OK;
    if ((NULL == lcd) || (NULL == str)) {
        ret = E_NOT_OK;
    } else {
        lcd_4bit_set_cursor(lcd, row, column);
        lcd_4bit_send_string(lcd, str);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param _chr
 * @param mem_pos
 * @return 
 */
STD_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column,
        const uint8 _chr[], uint8 mem_pos) {
    STD_ReturnType ret = E_OK;
    uint8 l_counter = 0;
    if ((NULL == lcd) || (NULL == _chr)) {
        ret = E_NOT_OK;
    } else {
        lcd_4bit_send_command(lcd, _LCD_CGRAM_START + (mem_pos * 8));
        for (l_counter = 0; l_counter < 8; l_counter++) {
            lcd_4bit_send_data(lcd, _chr[l_counter]);
        }
        lcd_4bit_send_data_pos(lcd, row, column, mem_pos);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @return 
 */
STD_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t *lcd) {
    STD_ReturnType ret = E_OK;
    uint8 l_counter = 0;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&(lcd->lcd_en));
        for (l_counter = 0; l_counter < 8; l_counter++) {
            ret = gpio_pin_intialize(&(lcd->lcd_data[l_counter]));
        }
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);

        ret = lcd_8bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_8bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = lcd_8bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(lcd, 0x80);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
STD_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd, uint8 command) {
    STD_ReturnType ret = E_OK;
    uint8 l_counter = 0;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        for (l_counter = 0; l_counter < 8; l_counter++) {
            gpio_pin_write_logic(&(lcd->lcd_data[l_counter]), (command >> l_counter) & (uint8) 0x01);
        }
        lcd_8bit_send_enable_signal(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
STD_ReturnType lcd_8bit_send_data(const chr_lcd_8bit_t *lcd, uint8 data) {
    STD_ReturnType ret = E_OK;
    uint8 l_counter = 0;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        for (l_counter = 0; l_counter < 8; l_counter++) {
            gpio_pin_write_logic(&(lcd->lcd_data[l_counter]), (data >> l_counter) & (uint8) 0x01);
        }
        lcd_8bit_send_enable_signal(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return 
 */
STD_ReturnType lcd_8bit_send_data_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data) {
    STD_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        lcd_8bit_set_cursor(lcd, row, column);
        lcd_8bit_send_data(lcd, data);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
STD_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd, uint8 *str) {
    STD_ReturnType ret = E_OK;
    if ((NULL == lcd) || (NULL == str)) {
        ret = E_NOT_OK;
    } else {
        while (*str) {
            lcd_8bit_send_data(lcd, *str++);
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return 
 */
STD_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str) {
    STD_ReturnType ret = E_OK;
    if ((NULL == lcd) || (NULL == str)) {
        ret = E_NOT_OK;
    } else {
        lcd_8bit_set_cursor(lcd, row, column);
        lcd_8bit_send_string(lcd, str);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param _chr
 * @param mem_pos
 * @return 
 */
STD_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column,
        const uint8 _chr[], uint8 mem_pos) {
    STD_ReturnType ret = E_OK;
    if ((NULL == lcd) || (NULL == _chr)) {
        ret = E_NOT_OK;
    } else {
        STD_ReturnType ret = E_OK;
        uint8 l_counter = 0;
        if ((NULL == lcd) || (NULL == _chr)) {
            ret = E_NOT_OK;
        } else {
            lcd_8bit_send_command(lcd, _LCD_CGRAM_START + (mem_pos * 8));
            for (l_counter = 0; l_counter < 8; l_counter++) {
                lcd_8bit_send_data(lcd, _chr[l_counter]);
            }
            lcd_8bit_send_data_pos(lcd, row, column, mem_pos);
        }
        return ret;
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param _data_command
 * @return 
 */
static STD_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd, uint8 _data_command) {
    STD_ReturnType ret = E_OK;
    uint8 l_counter = 0;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        for (l_counter = 0; l_counter < 4; l_counter++) {
            gpio_pin_write_logic(&(lcd->lcd_data[l_counter]), (_data_command >> l_counter) & (uint8) 0x01);
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @return 
 */
static STD_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd) {
    STD_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param coulmn
 * @return 
 */
static STD_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column) {
    STD_ReturnType ret = E_OK;
    column--;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        switch (row) {
            case ROW1:
                lcd_4bit_send_command(lcd, (0x80 + column));
                break;
            case ROW2:
                lcd_4bit_send_command(lcd, (0xC0 + column));
                break;
            case ROW3:
                lcd_4bit_send_command(lcd, (0x94 + column));
                break;
            case ROW4:
                lcd_4bit_send_command(lcd, (0xD4 + column));
                break;
            default:
                break;
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @return 
 */
static STD_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd) {
    STD_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param coulmn
 * @return 
 */
static STD_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column) {
    STD_ReturnType ret = E_OK;
    column--;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        switch (row) {
            case ROW1:
                lcd_8bit_send_command(lcd, (0x80 + column));
                break;
            case ROW2:
                lcd_8bit_send_command(lcd, (0xC0 + column));
                break;
            case ROW3:
                lcd_8bit_send_command(lcd, (0x94 + column));
                break;
            case ROW4:
                lcd_8bit_send_command(lcd, (0xD4 + column));
                break;
            default:
                break;
        }
    }
    return ret;
}
