
//#include "HT1621.H"


#ifndef _HT1621_H
#define _HT1621_H

//#define uchar unsigned char
//#define uint unsigned int
/*
#define _Nop() _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_()
#define BIAS 0x8520 //0b1000 0101 0010  // 0x52 //0b1000 0101 0010 1/3duty 4com

#define SYSDIS 0x8000 //0X00 //0b1000 0000 0000 关振系统荡器和LCD偏压发生器
#define SYSEN 0X8020 //0b1000 0000 0010 打开系统振荡器

#define LCDOFF 0X8040 //0b1000 0000 0100 关LCD偏压
#define LCDON 0X8060 //0b1000 0000 0110 打开LCD偏压
#define XTAL 0x8280 //0b1000 0010 1000 外部接时钟
#define RC256 0X8300 //0b1000 0011 0000 内部时钟
#define TONEON 0X8120 //0b1000 0001 0010 打开声音输出
#define TONEOFF 0X8100 //0b1000 0001 0000 关闭声音输出
#define WDTDIS 0X80A0 //0b1000 0000 1010 禁止看门狗
*/
/*
uchar Ht1621Tab[]={0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

                        0x00,0x00,0x00,0x00,0x00};
*/


/********************************************************
函数名称：void Ht1621WrCmd(uchar Cmd)
功能描述: HT1621命令写入函数
全局变量：无
参数说明：Cmd为写入命令数据
返回说明：无

说 明：写入命令标识位100
********************************************************/
void Ht1621WrCmd(unsigned short int Cmd);
/********************************************************
函数名称：void Ht1621WrOneData(uchar Addr,uchar Data)
功能描述: HT1621在指定地址写入数据函数
全局变量：无
参数说明：Addr为写入初始地址，Data为写入数据
返回说明：无
说 明：因为HT1621的数据位4位，所以实际写入数据为参数的后4位
********************************************************/
void Ht1621WrOneData(unsigned char Addr,unsigned char Data);

/********************************************************
函数名称：void Ht1621_Init(void)
功能描述: HT1621初始化
全局变量：无
参数说明：无
返回说明：无
版 本：1.0
说 明：初始化后，液晶屏所有字段均显示
********************************************************/
void Ht1621_Init(void);
void LcdRefuse(void);

extern unsigned char Ht1621buf[13+2];

#endif


