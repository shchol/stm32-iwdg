/**
  ******************************************************************************
  * @file    stm32f10x_iwdg.c
  * @author  Shcherbinin  Oleg
  * @version V1.0.0
  * @date    01-July-2022
  * @brief   This file provides several functions to manage the IWDG peripheral
  * 		 using RAM and without using RAM (e.g. in case of running memory test).

  *    	 	IWDG boundary addresses 0x40003000 - 400033ff.
  *    	 	IWDG address offset:
  *			 	IWDG_KR - 0x00
  *  	  	 		IWDG_PR - 0x04
  *  	  	 		IWDG_RLR - 0x08
  *	  	  	 	IWDG_SR - 0x0C
  */


/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stm32f10x_iwdg.h>
#include "stm32f1xx_hal_conf.h"

/** Macros for writing IWDG registers */
#define IWDG_LOAD_REG(val,addr)								\
	__asm__ __volatile__ (	"mov.w r1,%1\n\t"					\
							"ldr r0,[r1]\n\t"		\
							"mov.w r3,%0\n\t"		\
							"orr.w r0, r3\n\t"		\
							"str r0, [r1]\n\t"		\
							:/*output*/			\
							:/*input*/			\
							 "r" (val), "r" (addr));


/** Check Reload flag register */
#define IWDG_RELOAD_REG_CHECK_LOOP							\
		__asm__ __volatile__ (	".LOOP:\n\t"					\
							"ldr r1, =0x4000300c\n\t"	\
							"ldr r0, [r1]\n\t"		\
							"and r2, r0, #0x02\n\t"		\
							"cmp r2, #2\n\t"		\
							"beq .ENDLOOP\n\t"		\
							"b .LOOP\n\t"			\
							".ENDLOOP:\n\t"			\
							"bx lr\n\t"			\
							:/*no output*/			\
							:/*no input*/			\
							:/*no clobbers*/);


/**
*
*    @brief The following function init the internal watchdog timer.
*    @note: Once enabled,and it can only be disabled by a reset
*/
void iwdt_init(void)
{


	IWDG_LOAD_REG(KR_KEY_ENABLE, IWDG_KR_REG_ADDR);
	IWDG_LOAD_REG(IWDG_WriteAccess_Enable, IWDG_KR_REG_ADDR);
	IWDG_LOAD_REG(IWDG_Prescaler_64, IWDG_PR_REG_ADDR);
	IWDG_LOAD_REG(0xFFF, IWDG_RLR_REG_ADDR);
	IWDG_LOAD_REG(IWDG_WriteAccess_Disable, IWDG_KR_REG_ADDR);


	/**
	* \warning
	*  \code IWDG_RELOAD_REG_CHECK_LOOP \endcode
	* This macro just check watchdog reload update flag in a loop.
	* The flag is set by hardware to indicate that an update of the reload value
	* is ongoing.
	 */

	IWDG_RELOAD_REG_CHECK_LOOP;
}

/**
*     The following function reloads the
*     internal watchdog timer.
*/
void iwdt_reset(void)
{
	IWDG_LOAD_REG(KR_KEY_RELOAD, IWDG_KR_REG_ADDR);
}

/**
*
*    The following function checks if the watchdog reset was happened
*/
unsigned char wdt_check(void)
{
	return (unsigned char)(READ_BIT(RCC->CSR, RCC_CSR_IWDGRSTF) == (RCC_CSR_IWDGRSTF));
}


/**
 * Clear IWDGRSTF flag in RCC->CSR
 */
void clear_IWDGRSTF(void)
{
	SET_BIT(RCC->CSR, RCC_CSR_RMVF);
}

/**
*   The following function resets the MCU by causing the watchdog reset.
*/
void iwdt_do_reset(void)
{
	 IWDG->KR = KR_KEY_ENABLE;
	 IWDG->KR = IWDG_WriteAccess_Enable;
	 IWDG->PR = IWDG_Prescaler_4;
	 IWDG->RLR = 0x00;
	 IWDG->KR = IWDG_WriteAccess_Disable;

    /* wait for a watchdog reset */
	 while (1) {}
}

/************************************END OF FILE*****************************************/
