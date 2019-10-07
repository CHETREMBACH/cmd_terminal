/**
  ******************************************************************************
  * @file    board.c
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

/* Includes ------------------------------------------------------------------*/
#include "board.h"

/**
  * @brief  Configures GPIO.
  * @param  None 
  * @retval None
  */
void Board_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin = LED_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
}

