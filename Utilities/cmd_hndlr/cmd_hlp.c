 /**
  ******************************************************************************
  * @file    cmd_hlp.c
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
#include "cmd_hlp.h"
#include "cmd_tabl.h"

/* Описание функции поиска мнемомики в массиве команд */
uint8_t scan_cmd( char* cmd_name );

/**
  * @brief  функция вывода в терминал краткого описания команды 
  * @param  uint8_t cmd_index - индекс команды
  * @retval none 
  */
void print_descrip_cmd( uint8_t cmd_index )
{
  printf("%10s - %s \r\n",array_cmd[cmd_index].cmd_name,array_cmd[cmd_index].cmd_descrip);
}

/**
  * @brief  функция вывода в терминал краткого описания всех команд
  * @param  none
  * @retval none
  */
void print_descrip_cmd_all( void )
{
  /* Цикл по всем командам */
  for ( uint8_t i = 0; i < max_num_cmd;i++ )
  {  
    printf("%10s - %s \r\n",array_cmd[i].cmd_name,array_cmd[i].cmd_descrip);
  }
}

/**
  * @brief  функция вывода в терминал расширенного описания команды 
  * @param  chat* cmd_name - указатель мнемокод команды
  * @retval none 
  */
void print_inform_cmd( char* cmd_name )
{
  uint8_t temp_index_cmd = scan_cmd(cmd_name);
  
  if ( temp_index_cmd == 255 )
  {
    /*нет совпадений по команде*/
    printf("Неверный параметр\r\n");   
  }
  else
  {  
    printf("\r\n");
    printf(" справочная информация по команде %s\r\n\r\n",array_cmd[temp_index_cmd].cmd_name); 
    printf("  %s\r\n\r\n",array_cmd[temp_index_cmd].cmd_inform); 
  }
}

/**
  * @brief  обработчик команды формирование справки
  * @param  cmd_parametr_t *parametr - указатель на параметр команды
  * @retval uint16_t - возвращаемое значение
  */
uint16_t help_cmd_handler( cmd_parametr_t *parametr )
{
  if (parametr != NULL)
  {
    if ( strcmp( parametr->var_ch,"all") == 0)
    {
      /* краткая справка по всем командам */
      print_descrip_cmd_all();      
      return 0;	
    }
    
    /* Расширенная справка по заданной команде */
    print_inform_cmd( parametr->var_ch );
    return 0;    
  }    
  
  /* краткая справка по всем командам */
  print_descrip_cmd_all();      
  return 0;	  
}

/************************ (C) COPYRIGHT ONE TO ONE *****END OF FILE****/