/*
 * serial.h
 *
 *  Created on: 30 мая 2022 г.
 *      Author: user
 */

#ifndef SRC_INC_SERIAL_H_
#define SRC_INC_SERIAL_H_
//
#include "../../../iwdt/drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal.h"
#include "../../../iwdt/src/inc/cfgint.h"

UART_HandleTypeDef huart1;


//extern void serial_putc(UART_HandleTypeDef *huart, char ch);
//extern void serial_puts(UART_HandleTypeDef *huart, char *str);
extern void serial_putc(char ch);
extern void serial_puts(const char *str);


#endif /* SRC_INC_SERIAL_H_ */
