/**
  ******************************************************************************
  * @file    printf_dbg.c
  * @version V1.2.0
  * @date    03-11-2018
  * @brief   Перенаправление библиотечной C-функции printf.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 ONE TO ONE</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "printf_dbg.h"

/**
  * @brief  Инициализация аппаратной части отладки
  * @param  None
  * @retval None
  */
void DBG_Hardware_Setup(void)
{
#if  (DBG_UART_ENABLE == 1)
  /* Инициализация аппаратной части отладки по uart */
  DBG_UART_Setup();
#endif  /* (DBG_UART_ENABLE == 1) */  
}

/**
 * @brief Перенаправление библиотечной C-функции printf на USART.
 */
int putchar(int ch)
{
#if  (DBG_UART_ENABLE == 1)
  
  if ( index_rd_buf_mes == index_wr_buf_mes )
  {/* Данных в буфере нет - включение передачи */
    /* Загружаем символ в буфер */    
    buf_dbg[index_wr_buf_mes] = (char)ch;    
    /* Увеличение индекса */
    index_wr_buf_mes++;
    /* Проверка на переполнение  */
    if ( index_wr_buf_mes >= DBG_UART_MAX_SIZE_BUFF )
    {
      /* Организация циклического буфера */  
      index_wr_buf_mes = 0;    
    }      
    /* включаем прерывание по передаче */
    USART_ITConfig(DBG_PORT, USART_IT_TXE, ENABLE);      
  }
  else
  { /* Есть данные загружаем данные и инкрементируем индекс */
    /* Загружаем символ в буфер */    
    buf_dbg[index_wr_buf_mes] = (char)ch;    
    /* Увеличение индекса */
    index_wr_buf_mes++;
    /* Проверка на переполнение  */
    if ( index_wr_buf_mes >= DBG_UART_MAX_SIZE_BUFF )
    {
      /* Организация циклического буфера */  
      index_wr_buf_mes = 0;    
    }     
  }   
#endif  /* (DBG_UART_ENABLE == 1) */  
 
  return ch;
}
/******************* (C) COPYRIGHT 2017 ONE TO ONE *****END OF FILE****/
