/**
  ******************************************************************************
  * @file    board.h
  * @author  Trembach D.N.
  * @version V1.0.0
  * @date    25-03-2018
  * @brief   Файл содержит функции поддержки аппаратных ресурсов платы 
  ******************************************************************************
  * @attention
  * 
  * 
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BOARD_H
#define __BOARD_H

  /* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "main.h"

#define LED_PIN                         GPIO_Pin_13
#define LED_GPIO_PORT                   GPIOC
#define LED_GPIO_CLK                    RCC_APB2Periph_GPIOC  
#define LED_HI		                GPIO_SetBits(LED_GPIO_PORT,LED_PIN)
#define LED_LO		                GPIO_ResetBits(LED_GPIO_PORT,LED_PIN)
  
/**
  * @brief  Configures GPIO.
  * @param  None 
  * @retval None
  */
  void Board_Init(void);
  

#endif /* __BOARD_H */
/************************ (C) COPYRIGHT ONE TO ONE *****END OF FILE****/

