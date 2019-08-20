
#ifndef _MODBUS_PROCESS_H
#define _MODBUS_PROCESS_H
//#include "ModbusProcess.h"

//调整高位在前
#define MODBUS_FLOAT_HIGHBYTE_FORWORD  0
#define MODBUS_HIGHBYTE_FORWORD_2X2    1


#define MODBUS_CHECKSUM_HIGHBYTE_FORWORD    1


#define MaxModbusWordNumb   (120)
#define Max_ModbusBuf_Len  ( MaxModbusWordNumb*2 + 9 +1 ) 

//读线圈
#define MODBUS_READ_BIT        0x01
//写线圈
#define MODBUS_WRITE_BIT       0x05
//读寄存器
#define MODBUS_READ_REGISTER   0x03
//写寄存器
#define MODBUS_WRITE_REGISTER  0x10


///////////////////////////////////////////////
  
  
  
  
void _ModbusReadBit(unsigned char Channl,unsigned char *p,unsigned short int len);//读线圈
  
///////////////////////
void _ModbusWriteBit(unsigned char Channl,unsigned char *p,unsigned short int len);//写线圈
  
  
void _ModbusReadWord(unsigned char Channl, unsigned char *p, unsigned short int len, unsigned char *pr);//读寄存器
  
///////////////////////
void _ModbusWriteWord(unsigned char Channl,unsigned char *p,unsigned short int len, unsigned char *pr);//写寄存器
  
///////////////////////
//void _ModbusParameterProcess(unsigned char Channl,unsigned char *p,unsigned short int len);
  
  
//接收到MODBUS包处理，判断地址，校验包，应答
//输入：  p整个modbus包指针，len整个modbus包长度
void ModbusRecvProcess(unsigned char *p,unsigned short int len);
  
unsigned short GetCRC_Checksum4(unsigned char *puchMsg,unsigned short usDataLen);
//unsigned  short int GetModbusCheckSumCrc(unsigned char *p, short int len);
  
#endif

