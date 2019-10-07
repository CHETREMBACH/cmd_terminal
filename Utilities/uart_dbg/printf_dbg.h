/**
  ******************************************************************************
  * @file    printf_dbg.h
  * @version V1.0.0
  * @date    03-11-2018
  * @brief   Перенаправление библиотечной C-функции printf.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 ONE TO ONE</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PRINTF_DBG_H
#define __PRINTF_DBG_H

#if  (DBG_UART_ENABLE == 1)
#include "uart_dbg.h"
#endif  /* (DBG_UART_ENABLE == 1) */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"

/* Хранение принятого байта */
extern volatile uint16_t ReceiveCode;

/**
  * @brief  Инициализация аппаратной части отладки
  * @param  None
  * @retval None
  */
void DBG_Hardware_Setup(void);

#endif /* __PRINTF_DBG_H */
/******************* (C)  COPYRIGHT 2018 ONE TO ONE  *****END OF FILE****/
