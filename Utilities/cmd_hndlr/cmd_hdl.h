 /**
  ******************************************************************************
  * @file    cmd_hdl.h
  * @author  Trembach D.N.
  * @version V1.2.0
  * @date    07-10-2019
  * @brief   файл описания функций обработчиков команд  
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CMD_HDL
#define __CMD_HDL

#include "cmd_process.h"

/**
  * @brief  обработчик команды програмного перезапуска контроллера
  * @param  cmd_parametr_t *parametr - указатель на параметр команды
  * @retval uint16_t - возвращаемое значение
  */
uint16_t reset_cmd_handler( cmd_parametr_t *parametr );

/**
  * @brief  обработчик команды установки режима светодиода
  * @param  cmd_parametr_t *parametr - указатель на параметр команды
  * @retval uint16_t - возвращаемое значение
  */
uint16_t led_cmd_handler( cmd_parametr_t *parametr );

#endif /* __CMD_HDL */
/************************ (C) COPYRIGHT ONE TO ONE *****END OF FILE****/

