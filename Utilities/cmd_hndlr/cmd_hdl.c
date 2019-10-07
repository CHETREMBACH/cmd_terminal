 /**
  ******************************************************************************
  * @file    cmd_hdl.c
  * @author  Trembach D.N.
  * @version V1.2.0
  * @date    07-10-2019
  * @brief   файл  функций обработчиков команд  
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "cmd_hdl.h"
#include "cmd_hlp.h"

extern void delay_us(uint32_t time_val);

/**
  * @brief  обработчик команды програмного перезапуска контроллера
  * @param  cmd_parametr_t *parametr - указатель на параметр команды
  * @retval uint16_t - возвращаемое значение
  */
uint16_t reset_cmd_handler( cmd_parametr_t *parametr )
{
  /* Вывод информации о том что сейчас будет програмный перезапуск */
  printf("Микроконтроллер будет перезапущен через 1 сек.\r\n");
  /* Пауза на время выдачи информации в терминад */
  delay_us(1000000);  
  /* Сброс микроконтроллера */
  NVIC_SystemReset();
  return  0;					
}

/**
  * @brief  обработчик команды установки режима светодиода
  * @param  cmd_parametr_t *parametr - указатель на параметр команды
  * @retval uint16_t - возвращаемое значение
  */
uint16_t led_cmd_handler( cmd_parametr_t *parametr )
{
  if (parametr != NULL)
  {
    if ( strcmp( parametr->var_ch,"on") == 0)
    {
      LED_LO;
      printf("Включен светодиод\r\n"); 
      return 0;	
    }

    if ( strcmp( parametr->var_ch,"off") == 0)    
    {  
      LED_HI;
      printf("Выключен светодиод\r\n");
      return 0;	
    }
  }    
  
  printf("Неверный параметр\r\n");    
  return  0;					
}


/************************ (C) COPYRIGHT ONE TO ONE *****END OF FILE****/