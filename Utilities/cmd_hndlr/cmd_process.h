 /**
  ******************************************************************************
  * @file    cmd_process.h
  * @author  Trembach D.N.
  * @version V1.2.0
  * @date    07-10-2019
  * @brief   файл функций обработки запросов команд терминала  
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CMD_PROCESS
#define __CMD_PROCESS

#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>

#define MAX_SIZE_ПАРАМ   (30)
#define MAX_SIZE_CMD     (30)

/* Включение отладочной информации по обработке команд */
//#define  DBG_PRCS_EN         
#define  DBG_ERR_PRCS_EN     

/* перечисление для типа параметра команды */
typedef enum
{ 
  NONE = 0,
  UINT8,
  INT8,
  UINT16,
  INT16,	
  UINT32,
  INT32,
  UINT64,
  INT64,  
  FLOAT,
  DOUBLE,
  CHAR,
  STRING
}type_cmd_prmtr_e;

/* тип переменной/параметра для функции обработчика */
typedef struct
{
  union
  {
    uint8_t   var_u08;
    int8_t    var_i08;
    uint16_t  var_u16;  
    int16_t   var_i16; 
    uint32_t  var_u32;
    int32_t   var_i32;
    double    var_dbl;
    char      var_ch[MAX_SIZE_ПАРАМ];
  };
}cmd_parametr_t;

/* структура команды */
typedef struct
{
  char const*	    cmd_name;                                            /* имя ( мнемомика ) команды        */
  type_cmd_prmtr_e  cmd_type_parametr;                                   /* тип параметра команды            */     
  char const*	    cmd_descrip;                                         /* краткое описание команды         */
  char const*	    cmd_inform;                                          /* расширенное описание команды     */	
  uint16_t          (*cmd_handler_cb)( cmd_parametr_t *parametr );       /* указатель на обработчик команд   */     
}cmd_t;

/**
  * @brief  функция полинга терминала команд  
  * @param  none
  * @retval none 
  */
void terminal_cntrl( void );

#endif /* __CMD_PROCESS */
/************************ (C) COPYRIGHT ONE TO ONE *****END OF FILE****/

