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
#include "CRC16.h"
#include "printf_dbg.h"

/* Список  CRC-16 алгоритмов с их параметрами                          */
/* Параметры предназначены для создания таблицы выбранного алгоритма.  */
const Params	CRC16_ARC         = {0x8005, 0x0000, true,  true,  0x0000, 0xBB3D, "CRC-16/ARC"};
const Params	CRC16_AUG_CCITT   = {0x1021, 0x1D0F, false, false, 0x0000, 0xE5CC, "CRC-16/AUG-CCITT"};
const Params	CRC16_BUYPASS     = {0x8005, 0x0000, false, false, 0x0000, 0xFEE8, "CRC-16/BUYPASS"};
const Params	CRC16_CCITT_FALSE = {0x1021, 0xFFFF, false, false, 0x0000, 0x29B1, "CRC-16/CCITT-FALSE"};
const Params	CRC16_CDMA2000    = {0xC867, 0xFFFF, false, false, 0x0000, 0x4C06, "CRC-16/CDMA2000"};
const Params	CRC16_DDS_110     = {0x8005, 0x800D, false, false, 0x0000, 0x9ECF, "CRC-16/DDS-110"};
const Params	CRC16_DECT_R      = {0x0589, 0x0000, false, false, 0x0001, 0x007E, "CRC-16/DECT-R"};
const Params	CRC16_DECT_X      = {0x0589, 0x0000, false, false, 0x0000, 0x007F, "CRC-16/DECT-X"};
const Params	CRC16_DNP         = {0x3D65, 0x0000, true,  true,  0xFFFF, 0xEA82, "CRC-16/DNP"};
const Params	CRC16_EN_13757    = {0x3D65, 0x0000, false, false, 0xFFFF, 0xC2B7, "CRC-16/EN-13757"};
const Params	CRC16_GENIBUS     = {0x1021, 0xFFFF, false, false, 0xFFFF, 0xD64E, "CRC-16/GENIBUS"};
const Params	CRC16_MAXIM       = {0x8005, 0x0000, true,  true,  0xFFFF, 0x44C2, "CRC-16/MAXIM"};
const Params	CRC16_MCRF4XX     = {0x1021, 0xFFFF, true,  true,  0x0000, 0x6F91, "CRC-16/MCRF4XX"};
const Params	CRC16_RIELLO      = {0x1021, 0xB2AA, true,  true,  0x0000, 0x63D0, "CRC-16/RIELLO"};
const Params	CRC16_T10_DIF     = {0x8BB7, 0x0000, false, false, 0x0000, 0xD0DB, "CRC-16/T10-DIF"};
const Params	CRC16_TELEDISK    = {0xA097, 0x0000, false, false, 0x0000, 0x0FB3, "CRC-16/TELEDISK"};
const Params	CRC16_TMS37157    = {0x1021, 0x89EC, true,  true,  0x0000, 0x26B1, "CRC-16/TMS37157"};
const Params	CRC16_USB         = {0x8005, 0xFFFF, true,  true,  0xFFFF, 0xB4C8, "CRC-16/USB"};
const Params	CRC16_CRC_A       = {0x1021, 0xC6C6, true,  true,  0x0000, 0xBF05, "CRC-16/CRC-A"};
const Params	CRC16_KERMIT      = {0x1021, 0x0000, true,  true,  0x0000, 0x2189, "CRC-16/KERMIT"};
const Params	CRC16_MODBUS      = {0x8005, 0xFFFF, true,  true,  0x0000, 0x4B37, "CRC-16/MODBUS"};
const Params	CRC16_X_25        = {0x1021, 0xFFFF, true,  true,  0xFFFF, 0x906E, "CRC-16/X-25"};
const Params	CRC16_XMODEM      = {0x1021, 0x0000, false, false, 0x0000, 0x31C3, "CRC-16/XMODEM"};

/**
  * @brief  Формирует таблицу для заданного алгоритма.
  * @param  const Params* params - указатель на структуру параметров алгоритма
  * @param  Table* table - указатель на таблицу коэффициентов и параметров алгоритма
  * @retval none
  */
void MakeTable( const Params* params, Table* table )
{
  uint16_t crc; 
  bool flag_bit;
  /* загрузка параметров в таблицу */
  table->params = *params;
  /* Формирование таблицы */
  for( uint16_t n = 0; n < 256; n++)
  {
    crc = n << 8;
    for( uint16_t i = 0; i < 8; i++)
    {
      flag_bit = ( (crc & 0x8000) != 0 ); 
      crc <<= 1;
      if (flag_bit)
      {
        crc ^= params->Poly;
      }
    }
    table->data[n] = crc;
  }
}

/**
  * @brief  Возвращает код инициализации CRC для заданного алгоритма.
  * @param  Table* table - указатель на таблицу коэффициентов и параметров алгоритма
  * @retval none
  */
uint16_t InitCodeCRC( Table* table )
{
  return table->params.Init;
}

/**
  * @brief  Функция переворачивает биты в байте в обратном порядке .
  * @param  uint8_t ReverseByte - переворачиваемый байт
  * @retval uint8_t - перевернутый байт
  */
uint8_t ReverseByte( uint8_t val ) 
{
  uint8_t rval = 0;
  for( uint8_t i = 0; i < 8; i++ )
  {
    if ( ( val&(1<<i) ) != 0 ) rval |= 0x80 >> i;
  }
  return rval;
}

/**
  * @brief  Функция переворачивает биты в байте в обратном порядке .
  * @param  uint16_t uint16_t val - переворачиваемый байт
  * @retval uint16_t - перевернутый байт
  */
uint16_t ReverseWord( uint16_t val ) 
{
  uint16_t rval = 0;
  for( uint8_t i = 0; i < 16; i++ )
  {
    if ( ( val&(1<<i) ) != 0 ) rval |= 0x8000 >> i;
  }
  return rval;
}

/**
  * @brief  Функция возвращает результат добавления данных к CRC.
  * @param uint16_t crc - входное значение котрольной суммы
  * @param uint8_t* data - указатель на массив данных 
  * @param uint16_t length - размер данных
  * @param Table* table - указатель на таблицу коэффициентов и параметров алгоритма
  * @retval uint16_t - выходное значение котрольной суммы
  */
uint16_t UpdateCRC( uint16_t crc, uint8_t* data, uint16_t length, Table* table ) 
{
  uint8_t t_data;
  
  for( uint16_t i = 0; i < length; i++ )
  {
    t_data = data[i];
    
    if ( table->params.RefIn )
    {
      t_data = ReverseByte(t_data);
    }
    crc = crc<<8 ^ table->data[(uint8_t)(crc>>8)^t_data];
  }
  return crc;
}

/**
  * @brief Функция возвращает результат вычисления CRC и последующей обработки CRC.
  * @param uint16_t crc - входное значение котрольной суммы
  * @param Table* table - указатель на таблицу коэффициентов и параметров алгоритма
  * @retval uint16_t - выходное значение котрольной суммы
  */
uint16_t CompleteCRC( uint16_t crc, Table* table)
{
  if ( table->params.RefOut ) 
  {
    return ReverseWord(crc) ^ table->params.XorOut;
  }
  return crc ^ table->params.XorOut;
}

/**
  * @brief Функция возвращает контрольную сумму данных CRC, используя указанный алгоритм, представленный в таблице.
  * @param uint8_t* data - указатель на массив данных 
  * @param uint16_t length - размер данных
  * @param Table* table - указатель на таблицу коэффициентов и параметров алгоритма
  * @retval uint16_t - выходное значение котрольной суммы
  */
uint16_t ChecksumCRC( uint8_t* data, uint16_t length, Table* table )
{
  /* Инициализации CRC для заданного алгоритма */
  uint16_t crc = InitCodeCRC(table);
  /* Посчет CRC данных  */
  crc = UpdateCRC(crc, data, length, table);
  /* Формирование CRC */
  return CompleteCRC(crc, table);
}


/* Задаем массив для тестирования CRC */
uint8_t mas[] = { 0x7F, 0x0B, 0x55, 0x12, 0x01,   0x00, 0x00, 0xBF, 0x26, 0x04,   0x68, 0x03, 0xE8 };

/* Структура подсчета CRC */
Table crc16_table;


/**
 * @brief  Функция тестирования.
 * @param  None
 * @retval None
 */
void test_crc(void)
{
  /* Формируем таблицу для заданного алгоритма. */
  MakeTable( &CRC16_ARC, &crc16_table );
  /* Подсчет контрольной сумму данных, используя указанный алгоритм, представленный в таблице.*/
  printf(" %X\r\n", ChecksumCRC( mas, sizeof(mas), &crc16_table ) );
  /* Получаем ответ" BC60"*/
}
/************************ COPYRIGHT 2019 ONE TO ONE *****END OF FILE****/