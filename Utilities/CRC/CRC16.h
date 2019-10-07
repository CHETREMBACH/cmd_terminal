/**
  ******************************************************************************
  * @file    CRC16.h
  * @author  Trembach Dmitry
  * @version V1.2.2
  * @date    03-08-2019
  * @brief   GenerationCRC16 содержит несколько реализаций 16-циклической проверки ,CRC-16 и контрольной суммы.
  ******************************************************************************
  * @attention
  *  Представлены параметры для большинства известных алгоритмов CRC-16. 
  *
  * <h2><center>&copy; COPYRIGHT 2019 ONE TO ONE</center></h2>
  ******************************************************************************
  */
#ifndef _CRC16_H
#define _CRC16_H

#include "stm32f10x.h"
#include <stdbool.h>

/* Структура Params содержит параметры алгоритмов CRC-16 */
typedef struct 
{
  uint16_t     Poly;
  uint16_t     Init;
  bool         RefIn;
  bool         RefOut;
  uint16_t     XorOut;
  uint16_t     Check;
  const char  *Name;
}Params;

/* Параметры предназначены для создания таблицы выбранного алгоритма.  */
extern const Params CRC16_ARC;
extern const Params CRC16_AUG_CCITT;
extern const Params CRC16_BUYPASS;
extern const Params CRC16_CCITT_FALSE;
extern const Params CRC16_CDMA2000;
extern const Params CRC16_DDS_110;
extern const Params CRC16_DECT_R;
extern const Params CRC16_DECT_X;
extern const Params CRC16_DNP;
extern const Params CRC16_EN_13757;
extern const Params CRC16_GENIBUS;
extern const Params CRC16_MAXIM;
extern const Params CRC16_MCRF4XX;
extern const Params CRC16_RIELLO;
extern const Params CRC16_T10_DIF;
extern const Params CRC16_TELEDISK;
extern const Params CRC16_TMS37157;
extern const Params CRC16_USB;
extern const Params CRC16_CRC_A;
extern const Params CRC16_KERMIT;
extern const Params CRC16_MODBUS;
extern const Params CRC16_X_25;
extern const Params CRC16_XMODEM;

/* Структура Table содержит структуру с параметрами алгоритма и коэффициенты для эффективного вычисления CRC. */
typedef struct 
{
  Params params;
  uint16_t data[256];
}Table;

/**
  * @brief  Формирует таблицу для заданного алгоритма.
  * @param  Params* params - указатель на структуру параметров алгоритма
  * @param  Table* table - указатель на таблицу коэффициентов и параметров алгоритма
  * @retval none
  */
void MakeTable( const Params* params, Table* table );

/**
  * @brief Функция возвращает контрольную сумму данных CRC, используя указанный алгоритм, представленный в таблице.
  * @param uint8_t* data - указатель на массив данных 
  * @param uint16_t length - размер данных
  * @param Table* table - указатель на таблицу коэффициентов и параметров алгоритма
  * @retval uint16_t - выходное значение котрольной суммы
  */
uint16_t ChecksumCRC( uint8_t* data, uint16_t length, Table* table );

#endif /* _CRC16_H */
/************************ COPYRIGHT 2019 ONE TO ONE *****END OF FILE****/