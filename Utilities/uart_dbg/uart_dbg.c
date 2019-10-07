/**
  ******************************************************************************
  * @file    uart_dbg.c
  * @version V3.0.0
  * @date    09-03-2018
  * @brief   Инициализация драйвера для запуска UART в режиме отладки
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2019 ONE TO ONE</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "uart_dbg.h"

#if  (DBG_UART_ENABLE == 1)

/* Буфер для диагностического сообщения */
volatile uint8_t buf_dbg[DBG_UART_MAX_SIZE_BUFF];
/* Индекс записи сообщения */
uint16_t index_wr_buf_mes = 0;
/* Индекс чтения сообщения */
volatile uint16_t index_rd_buf_mes = 0;

/* Буфер для приема команды */
volatile uint8_t buf_cmd[DBG_UART_MAX_SIZE_CMD_BUFF];
/* Индекс записи команды */
volatile uint16_t index_wr_buf_cmd = 0;
/* Индекс чтения команды */
uint16_t index_rd_buf_cmd = 0;


/**
  * @brief  Инициализация аппаратной части отладки по uart.
  * @param  None
  * @retval None
  */
void DBG_UART_Setup(void)
{
  USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;  
  
  /* Enable GPIO clock */
  RCC_APB2PeriphClockCmd( DBG_TX_GPIO_CLK | DBG_RX_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);  
  /* Enable USART Clock */
  DBG_CLK_CMD( DBG_CLK, ENABLE );   
  
  /* Configure USART Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = DBG_RX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(DBG_RX_GPIO_PORT, &GPIO_InitStructure);
  
  /* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = DBG_TX_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(DBG_TX_GPIO_PORT, &GPIO_InitStructure);
  
  /* Enable the USART Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = DBG_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);  
  
  USART_InitStructure.USART_BaudRate = DBG_BaudRate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* Configure USART */
  USART_Init(DBG_PORT, &USART_InitStructure);
  
  USART_ITConfig(DBG_PORT, USART_IT_RXNE, ENABLE);
  USART_ITConfig(DBG_PORT, USART_IT_TXE, ENABLE);

  /* Enable the USART */
  USART_Cmd(DBG_PORT, ENABLE);  
}

/**
  * @brief  Прерывание DBG_UART.
  * @param  None
  * @retval None
  */
void DBG_IRQHandler( void )
{
  /* прерывание приемника - принят байт */  
  if(USART_GetITStatus(DBG_PORT, USART_IT_RXNE) != RESET)
  {
    /* принимаем данные        */
    buf_cmd[index_wr_buf_cmd] = (uint8_t)USART_ReceiveData(DBG_PORT);
    /* нкремент индекса */ 
    index_wr_buf_cmd++;
    /* Проверка на переполнение  */
    if ( index_wr_buf_cmd >= DBG_UART_MAX_SIZE_CMD_BUFF )
    {
    /* Организация циклического буфера */  
    index_wr_buf_cmd = 0;    
    }
  }
  
  /* прерывание передатчика - пустой буфер передачи */
  if(USART_GetITStatus(DBG_PORT, USART_IT_TXE) != RESET)
  {   
    /* TXE flag автоматически очищается когда записываются новые данные в TDR register */
    if ( index_rd_buf_mes == index_wr_buf_mes )
    {/* Данных в буфере нет - отключение передачи */
      /* отключаем прерывание по передаче */
      USART_ITConfig(DBG_PORT, USART_IT_TXE, DISABLE);      
    }
    else
    {/* Есть данные передаем и инкрементируем индекс */
      /* Передача байта сообщения */
      USART_SendData(DBG_PORT,(uint16_t)(buf_dbg[index_rd_buf_mes]));      
      /* Увеличение индекса */
      index_rd_buf_mes++;
      /* Проверка на переполнение  */
      if ( index_rd_buf_mes >= DBG_UART_MAX_SIZE_BUFF )
      {
        /* Организация циклического буфера */  
        index_rd_buf_mes = 0;    
      }  
    }  
  } 
}
#endif  /* (DBG_UART_ENABLE == 1) */
/******************* (C) COPYRIGHT 2019 ONE TO ONE *****END OF FILE****/
