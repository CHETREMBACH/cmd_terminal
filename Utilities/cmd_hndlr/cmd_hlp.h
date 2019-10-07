 /**
  ******************************************************************************
  * @file    cmd_hlp.h
  * @author  Trembach D.N.
  * @version V1.0.0
  * @date    07-10-2019
  * @brief   файл функций обработки команд помощи терминала  
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CMD_HLP
#define __CMD_HLP

#include "stm32f10x.h"
#include "cmd_process.h"

/**
  * @brief  обработчик команды формирование справки
  * @param  cmd_parametr_t *parametr - указатель на параметр команды
  * @retval uint16_t - возвращаемое значение
  */
uint16_t help_cmd_handler( cmd_parametr_t *parametr );

#endif /* __CMD_HLP */
/************************ (C) COPYRIGHT ONE TO ONE *****END OF FILE****/

