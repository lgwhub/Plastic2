
#include "includes.h"

#include "HT1621.h"
  #if CONFIG_SPI1
      #include "SPI1.h"
  #endif

#define uchar unsigned char
#define uint unsigned int

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

//com1 高位    com4 低位
unsigned char Ht1621buf[13+2]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};   //低4 bit 有效

#define   DelayTimeMs(x)    OSTimeDly( x * OS_TICKS_PER_SEC / 1000 )

/*


//seg7 difine  2   for p4 p5
#define seg_4a   0x010
#define seg_4b   0x020
#define seg_4c   0x040
#define seg_4d   0x080

#define seg_4f   0x01
#define seg_4g   0x02
#define seg_4e   0x04

//seg7 difine  1   for p1 p2 p3
#define seg_1a   0x08
#define seg_1b   0x04
#define seg_1c   0x02
#define seg_1d   0x01

#define seg_1f   0x080
#define seg_1g   0x040
#define seg_1e   0x020


unsigned char Ht1621DigtTab1[]=
{
	seg_5a + seg_5b + seg_5c + seg_5d + seg_5e  + seg_5f ,   //0
	seg_5b + seg_5c ,                            //1
	seg_5a + seg_5b + seg_5d + seg_5e  + seg_5g ,         //2	
	seg_5a + seg_5b + seg_5c + seg_5e +  seg_5g ,         //3
	seg_5b + seg_5c + seg_5f + seg_5g  ,               //4
	seg_5a + seg_5c + seg_5d + seg_5f + seg_5g ,          //5
	seg_5a + seg_5c + seg_5d + seg_5e + seg_5f + seg_5g ,   //6
	seg_5a + seg_5b + seg_5c ,                      //7	
	seg_5a + seg_5b + seg_5c + seg_5d + seg_5e + seg_5f + seg_5g ,   //8	
	seg_5a + seg_5b + seg_5c + seg_5d + seg_5f + seg_5g    //9		
	
}

unsigned char Ht1621DigtTab2[]=
{
	seg_4a + seg_4b + seg_4c + seg_4d + seg_4e  + seg_4f ,   //0
	seg_4b + seg_4c ,                            //1
	seg_4a + seg_4b + seg_4d + seg_4e  + seg_4g ,         //2	
	seg_4a + seg_4b + seg_4c + seg_4e +  seg_4g ,         //3
	seg_4b + seg_4c + seg_4f + seg_4g  ,               //4
	seg_4a + seg_4c + seg_4d + seg_4f + seg_4g ,          //5
	seg_4a + seg_4c + seg_4d + seg_4e + seg_4f + seg_4g ,   //6
	seg_4a + seg_4b + seg_4c ,                      //7	
	seg_4a + seg_4b + seg_4c + seg_4d + seg_4e + seg_4f + seg_4g ,   //8	
	seg_4a + seg_4b + seg_4c + seg_4d + seg_4f + seg_4g    //9		
	
}
*/
/*
//delay us
void Delay(unsigned char us) //5,7,9
{
 while(--us);
}


//delay ms
void DelayMS(unsigned  int iMs)
{
 uint i,j;
 for(i=0;i<iMs;i++)
 {  for(j=0;j<65;j++) Delay(1);
 }
}
*/

/********************************************************
函数名称：void Ht1621WrCmd(uchar Cmd)
功能描述: HT1621命令写入函数
全局变量：无
参数说明：Cmd为写入命令数据
返回说明：无

说 明：写入命令标识位100
********************************************************/
void Ht1621WrCmd(unsigned short int Cmd)
{
  CS_SPI1_CLR; 
  SPI1_WRITE_13bit(Cmd);
	DelayTimeMs(1);
	//OSTimeDly(OS_TICKS_PER_SEC/100);	    //延时1ms秒
  CS_SPI1_SET;
 

}
/********************************************************
函数名称：void Ht1621WrOneData(uchar Addr,uchar Data)
功能描述: HT1621在指定地址写入数据函数
全局变量：无
参数说明：Addr为写入初始地址，Data为写入数据
返回说明：无
说 明：因为HT1621的数据位4位，所以实际写入数据为参数的后4位
********************************************************/
void Ht1621WrOneData(unsigned char Addr,unsigned char Data)
{
	unsigned short int xx;
CS_SPI1_CLR;
 xx = 0xa000; //写入数据标志101
 xx |= (( Addr & 0x1f ) << 7 ); //写入地址数据
 xx |= (( Data & 0x0f ) << 3 ); //写入数据
SPI1_WRITE_13bit(xx);
	DelayTimeMs(1);
	//OSTimeDly(OS_TICKS_PER_SEC/100);	    //延时1ms秒
 CS_SPI1_SET ;
 
}


/********************************************************
函数名称：void Ht1621_Init(void)
功能描述: HT1621初始化
全局变量：无
参数说明：无
返回说明：无
版 本：1.0
说 明：初始化后，液晶屏所有字段均显示
********************************************************/
void Ht1621_Init(void)
{
CS_SPI1_SET;
  //延时使LCD工作电压稳定
 Ht1621WrCmd(BIAS);
 Ht1621WrCmd(RC256); //使用内部振荡器
 Ht1621WrCmd(SYSDIS);
 Ht1621WrCmd(WDTDIS);
 Ht1621WrCmd(SYSEN);
 Ht1621WrCmd(LCDON);
}

/**********************************/


void LcdRefuse(void)
{
unsigned char i;
  for(i=0;i<13;i++)
       {
         Ht1621WrOneData(i,Ht1621buf[i]&0xf);
      }

}










