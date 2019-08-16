

#ifndef _MODBUS_RECV_H
#define _MODBUS_RECV_H
//#include "includes.h"


#define DEFAULT_MODBUS_TIME  (10/2);

struct _modbus_struct
{

unsigned short int  MaxNothingMs5;   		//MODBUS没有数据收到设定值  此时处理包，并且必须CLR包

unsigned short int  NothingTimer;      //MODBUS没有数据收到定时器
unsigned short int	LenA;
unsigned short int	LenB;
unsigned short int	LenC;
unsigned char BufA[Max_ModbusBuf_Len+3];
unsigned char BufB[Max_ModbusBuf_Len+3];
unsigned char BufC[Max_ModbusBuf_Len+3];
unsigned char Select;	
unsigned char OverA;
unsigned char OverB;
unsigned char OverC;
};

extern struct _modbus_struct  Modbusx;


// modbus数据接收函数
// 此函数在串口中断内调用，
// 输入 recv_char 是接收到的字符
void ModbusRxISRHandler(unsigned char recv_char);

//  modbus包结束时间判断函数
void ModbusTimeHandler(void);
//不断地检查MODBUS接收缓冲区
//在主程序里面调用
void GetModbusPark(void);
void ModbusInit(void);

#endif


