/**
  ******************************************************************************
  * @file    uart_dbg.h
  * @version V3.0.0
  * @date    09-03-2018
  * @brief   Инициализация драйвера для запуска UART в режиме отладки
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 ONE TO ONE</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_DBG_H
#define __UART_DBG_H

#if  (DBG_UART_ENABLE == 1)

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "printf_dbg.h"
#include "stdio.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* USART1 описание аппаратных ресурсов отладки */
//========== Определение ресурсов UART =========================================
#define DBG_PORT                         USART1
#define DBG_CLK                          RCC_APB2Periph_USART1
#define DBG_CLK_CMD                      RCC_APB2PeriphClockCmd
  
#define DBG_TX_PIN                       GPIO_Pin_9    //PA.9            
#define DBG_TX_GPIO_PORT                 GPIOA                       
#define DBG_TX_GPIO_CLK                  RCC_APB2Periph_GPIOA
  
#define DBG_RX_PIN                       GPIO_Pin_10   //PA.10                
#define DBG_RX_GPIO_PORT                 GPIOA                    
#define DBG_RX_GPIO_CLK                  RCC_APB2Periph_GPIOA
  
#define DBG_IRQn                         USART1_IRQn
#define DBG_IRQHandler                   USART1_IRQHandler	
/* ===========================================================================*/
/* Битовая скорость UART                   */
#define DBG_BaudRate     	     38400  // 921600 //2625000 // 5250000 // 
/* Размер буфера диагностических сообщений */
#define DBG_UART_MAX_SIZE_BUFF       (2000)
/* Размер буфера приема команд */
#define DBG_UART_MAX_SIZE_CMD_BUFF   (50)

/* Буфер для диагностического сообщения */
extern volatile uint8_t buf_dbg[DBG_UART_MAX_SIZE_BUFF];
/* Индекс записи сообщения */
extern uint16_t index_wr_buf_mes;
/* Индекс чтения сообщения */
extern volatile uint16_t index_rd_buf_mes;


/* Буфер для приема команды */
extern volatile uint8_t buf_cmd[DBG_UART_MAX_SIZE_CMD_BUFF];
/* Индекс записи команды */
extern volatile uint16_t index_wr_buf_cmd;
/* Индекс чтения команды */
extern uint16_t index_rd_buf_cmd;

/**
  * @brief  Инициализация аппаратной части отладки по uart.
  * @param  None
  * @retval None
  */
void DBG_UART_Setup(void);

#endif /*  (DBG_UART_ENABLE == 1) */

#endif /* __UART_DBG_H */
/******************* (C)  COPYRIGHT 2018 ONE TO ONE  *****END OF FILE****/
