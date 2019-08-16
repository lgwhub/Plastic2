
#include "includes.h"

#include "HT1621.h"
  #if CONFIG_SPI1
      #include "SPI1.h"
  #endif

#define uchar unsigned char
#define uint unsigned int

#define _Nop() _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_()
#define BIAS 0x8520 //0b1000 0101 0010  // 0x52 //0b1000 0101 0010 1/3duty 4com

#define SYSDIS 0x8000 //0X00 //0b1000 0000 0000 ����ϵͳ������LCDƫѹ������
#define SYSEN 0X8020 //0b1000 0000 0010 ��ϵͳ����

#define LCDOFF 0X8040 //0b1000 0000 0100 ��LCDƫѹ
#define LCDON 0X8060 //0b1000 0000 0110 ��LCDƫѹ
#define XTAL 0x8280 //0b1000 0010 1000 �ⲿ��ʱ��
#define RC256 0X8300 //0b1000 0011 0000 �ڲ�ʱ��
#define TONEON 0X8120 //0b1000 0001 0010 ���������
#define TONEOFF 0X8100 //0b1000 0001 0000 �ر��������
#define WDTDIS 0X80A0 //0b1000 0000 1010 ��ֹ���Ź�

//com1 ��λ    com4 ��λ
unsigned char Ht1621buf[13+2]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};   //��4 bit ��Ч

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
�������ƣ�void Ht1621WrCmd(uchar Cmd)
��������: HT1621����д�뺯��
ȫ�ֱ�������
����˵����CmdΪд����������
����˵������

˵ ����д�������ʶλ100
********************************************************/
void Ht1621WrCmd(unsigned short int Cmd)
{
  CS_SPI1_CLR; 
  SPI1_WRITE_13bit(Cmd);
	DelayTimeMs(1);
	//OSTimeDly(OS_TICKS_PER_SEC/100);	    //��ʱ1ms��
  CS_SPI1_SET;
 

}
/********************************************************
�������ƣ�void Ht1621WrOneData(uchar Addr,uchar Data)
��������: HT1621��ָ����ַд�����ݺ���
ȫ�ֱ�������
����˵����AddrΪд���ʼ��ַ��DataΪд������
����˵������
˵ ������ΪHT1621������λ4λ������ʵ��д������Ϊ�����ĺ�4λ
********************************************************/
void Ht1621WrOneData(unsigned char Addr,unsigned char Data)
{
	unsigned short int xx;
CS_SPI1_CLR;
 xx = 0xa000; //д�����ݱ�־101
 xx |= (( Addr & 0x1f ) << 7 ); //д���ַ����
 xx |= (( Data & 0x0f ) << 3 ); //д������
SPI1_WRITE_13bit(xx);
	DelayTimeMs(1);
	//OSTimeDly(OS_TICKS_PER_SEC/100);	    //��ʱ1ms��
 CS_SPI1_SET ;
 
}


/********************************************************
�������ƣ�void Ht1621_Init(void)
��������: HT1621��ʼ��
ȫ�ֱ�������
����˵������
����˵������
�� ����1.0
˵ ������ʼ����Һ���������ֶξ���ʾ
********************************************************/
void Ht1621_Init(void)
{
CS_SPI1_SET;
  //��ʱʹLCD������ѹ�ȶ�
 Ht1621WrCmd(BIAS);
 Ht1621WrCmd(RC256); //ʹ���ڲ�����
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










