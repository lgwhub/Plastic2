//nomal.h
/************************************************************************/
/*                              常用预定义                              */
/************************************************************************/
#ifndef __NOMAL_H
#define __NOMAL_H
#define bool unsigned char
#define uchar unsigned char
#define uint16 unsigned short int
#define uint32 unsigned long int
#define int16 signed short int
#define int32 signed int
#define ulong unsigned long

#define TRUE 1
#define FALSE 0

#define true 1
#define false 0

#define SPACE 0x20
#define CharESC
#define CharSUB

//#define CR 0x0d
//#define LF 0x0a

#define BIT0    0X01
#define BIT1    0X02
#define BIT2    0X04
#define BIT3    0X08
#define BIT4    0X10
#define BIT5    0X20
#define BIT6    0X40
#define BIT7    0X80
#define BIT8    0X100
#define BIT9    0X200
#define BIT10   0X400
#define BIT11   0X800
#define BIT12   0X1000
#define BIT13   0X2000
#define BIT14   0X4000
#define BIT15   0X8000
#define BIT16   0X10000
#define BIT17   0X20000
#define BIT18   0X40000
#define BIT19   0X80000
#define BIT20   0X100000
#define BIT21   0X200000
#define BIT22   0X400000
#define BIT23   0X800000
#define BIT24   0X1000000
#define BIT25   0X2000000
#define BIT26   0X4000000
#define BIT27   0X8000000
#define BIT28   0X10000000
#define BIT29   0X20000000
#define BIT30   0X40000000
#define BIT31   0X80000000


void PutCharToChar(uchar *ps,uchar *pd,uchar len);
uchar PutString(uchar *ps,uchar *pd,uchar max_ps);

bool  CompareCharChar(uchar *chr1,uchar *chr2,uchar len);
/** 字符串和字符串比较  ***/
//bool CompareStrStr(uchar *chr,uchar *str,uchar max)
/*                     ASC_2码  转换通用子程序                           */
uchar HexToAsc(uchar x);   /*  1/2hex>>1asc2   */

/*          AscToHex  1位ASC_2码转换为半字节二进制   子程序              */
uchar AscToHex(uchar x);   


bool  IsNumberAsc(uchar x);   /* 判断是否为数字0~9 */
//bool  IsHexAsc(uchar x);   /* 判断十六进制 是否为数字0~9 或 A~F */
bool  IsStringAsc(uchar x);   /* 判断是否为英文字母A~Z 或 a~z*/
uchar MakeValAsc16(uchar *StrHead,uint16 Val,uchar *StrEnd,uchar *out);	//16位变量转换为十进制的ASC码，有前后缀
//uchar MakeValHex32(uchar *StrHead,uint32 Val,uchar *StrEnd,uchar *out);	//32位变量转换为HEX的ASC码，有前后缀
uchar MakeValAsc32(uchar *StrHead,uint32 Val,uchar *StrEnd,uchar *out);	//32位变量转换为十进制的ASC码，有前后缀

void HexCharToAscString(uchar *c,uchar *AscBuf,uchar HexLen);	//注意1字节变2字节
uint16 GetCRC_Checksum1(uchar *cp, uint32 len);
#endif


