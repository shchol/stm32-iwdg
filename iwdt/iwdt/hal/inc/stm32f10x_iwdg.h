/**
  ******************************************************************************
  * @file    stm32f10x_iwdg.h
  * @author  Shcherbinin Oleg
  * @version  * @date    28-July-2022
  * @brief   This file contains all the functions prototypes for the IWDG
  *          firmware library.
  ******************************************************************************
  * [..] The IWDG can be started by either software or hardware (configurable
         through option byte).
    [..] The IWDG is clocked by its own dedicated low-speed clock (LSI) and
         thus stays active even if the main clock fails.
         Once the IWDG is started, the LSI is forced ON and cannot be disabled
         (LSI cannot be disabled too), and the counter starts counting down from
         the reset value of 0xFFF. When it reaches the end of count value (0x000)
         a system reset is generated.
         The IWDG counter should be reloaded at regular intervals to prevent
         an MCU reset.
    [..] The IWDG is implemented in the VDD voltage domain that is still functional
         in STOP and STANDBY mode (IWDG reset can wake-up from STANDBY).
    [..] IWDGRST flag in RCC_CSR register can be used to inform when a IWDG
         reset occurs.
    [..] Min-max timeout value @40KHz (LSI): ~0.4ms / ~26.5s
    	Timeout = (4 * RLR * pow(2, PR))/(LSI clock frequency)
  *
  ******************************************************************************
  */


#ifndef IWDT_HAL_INC_STM32F10X_IWDG_H_
#define IWDT_HAL_INC_STM32F10X_IWDG_H_


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f103xb.h"
#include "stm32f1xx.h"
#include "defs.h"

 /* ---------------------- IWDG registers addresses ----------------------------*/
#define IWDG_KR_REG_ADDR		(IWDG_BASE + 0x00)
#define IWDG_PR_REG_ADDR		(IWDG_BASE + 0x04)
#define IWDG_RLR_REG_ADDR		(IWDG_BASE + 0x08)
#define IWDG_SR_REG_ADDR		(IWDG_BASE + 0x0C)

 /* ---------------------- IWDG registers bit mask ----------------------------*/
 /* KR register bit mask */
#define KR_KEY_RELOAD    ((uint16_t)0xAAAA)
#define KR_KEY_ENABLE    ((uint16_t)0xCCCC)

 /* ---------------------- Prescaler divider at 40 kHz LSI --------------------*/
 #define IWDG_Prescaler_4            ((uint8_t)0x00)							// 409 ms
 #define IWDG_Prescaler_8            ((uint8_t)0x01)							// 819 ms
 #define IWDG_Prescaler_16           ((uint8_t)0x02)							// 1638 ms
 #define IWDG_Prescaler_32           ((uint8_t)0x03)							// 3276 ms
 #define IWDG_Prescaler_64           ((uint8_t)0x04)							// 6553 ms
 #define IWDG_Prescaler_128          ((uint8_t)0x05)							// 13107 ms
 #define IWDG_Prescaler_256          ((uint8_t)0x06)							// 26214 ms


 //Prescaler Value Update flag
 #define IWDG_FLAG_PVU               ((uint16_t)0x0001)
 //Reload Value Update flag
 #define IWDG_FLAG_RVU               ((uint16_t)0x0002)
 //Counter Window Value Update flag
 #define IWDG_FLAG_WVU               ((uint16_t)0x0002)

#define IWDG_WriteAccess_Enable     ((uint16_t)0x5555)
#define IWDG_WriteAccess_Disable    ((uint16_t)0x0000)


 /*
     Watchdog driver API
 */
extern void iwdt_init(void);
extern unsigned char wdt_check(void);
void clear_IWDGRSTF(void);
extern void iwdt_do_reset(void) NORETURN;
extern void iwdt_reset(void);

#define IWDT_INIT iwdt_init()
#define IWDT_RESET iwdt_reset()

/*
     The following macro reloads the
     internal watchdog timer.
*/
#ifdef RAM_MODE
#define IWDG_RESET 				\
do {							\
	IWDG->KR = KR_KEY_RELOAD;	\
} while(0)
#endif

#ifdef __cplusplus
}
#endif


#endif /* IWDT_HAL_INC_STM32F10X_IWDG_H_ */

