/**
  ******************************************************************************
  * @file    main.c
  * @author  Trembach D.N.
  * @version V1.0.0
  * @date    07-10-2019
  * @brief   Файл стартовой функции проекта.
  *
  *
  ******************************************************************************
  * @attention
  *
  *
  * <h2><center>&copy; COPYRIGHT 2019 ONE TO ONE</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "board.h"
#include "printf_dbg.h"
#include "cmd_process.h"
    
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
  
volatile const char __date__[]    =  __DATE__;
volatile const char __time__[]    =  __TIME__;

/**
 * @brief  Функция тестирования.
 * @param  None
 * @retval None
 */
void test_crc(void);

/**
 * @brief  Функция пауза. 
 * @param  uint32_t time_val
 * @retval None
  ******************************************************************************
  * @attention
  * результаты измерения ( SystemCoreClock = 72000000 Hz )
  *  time_val=1000000   - 100004.3 мкс 
  *  time_val=100       -    100.5 мкс
  *   Если запрашиваем из другого файла через хеадер - теряется точность !!! 
  *    
  ******************************************************************************
 */
#pragma optimize=none 
void delay_us(uint32_t time_val)
{
  for(uint32_t cnt_time = 0;cnt_time < (time_val<<1);cnt_time++)
  {
    asm("nop");  asm("nop");   asm("nop");  asm("nop");       
    asm("nop");  asm("nop");   asm("nop");  asm("nop"); 
    asm("nop");  asm("nop");   asm("nop");  asm("nop");       
    asm("nop");  asm("nop");   asm("nop");  asm("nop"); 
    asm("nop");  asm("nop");   asm("nop");  asm("nop");       
    asm("nop");  asm("nop");   asm("nop");       
  }
}

uint32_t cnt = 0;

/**
 * @brief  Функция с которой стартует программа системы.
 * @param  None
 * @retval None
 */
int main(void)
{
  /* Обновление переменных тактирование по состоянию регистров тактирования    */
  SystemCoreClockUpdate();
  /* Настройка групп приоритеов все 4 бита для управления приоритетом, 0 бит для подприоритета */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  /* Configures GPIO */
  Board_Init();
  /* Инициализация аппаратной части отладки */
  DBG_Hardware_Setup();  
  /* Информационная шапка программы */
  printf("  \r\n");  
  printf("__________________________________\r\n");
  printf("\r\n");
  printf("   STM32F103_MODULE   \r\n");  
  printf("   DATA: %s \r\n",__date__);
  printf("   TIME: %s \r\n",__time__);
  printf("   CPU FREQ = %d Hz \r\n",SystemCoreClock);
  printf("__________________________________\r\n");  
  
  /* Зацикливание программы */
  while (1)
  {
    /* функция полинга терминала команд  */
    terminal_cntrl();
    
    delay_us(1);    
  };
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *   where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif
/************************ (C) COPYRIGHT ONE TO ONE *****END OF FILE****/
