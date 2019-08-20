
//#include "app1.h"

#ifndef   _APP1_H

#define   _APP1_H

//ad����ֵ
typedef struct 	
{

	
unsigned short int 	temprature0;       //оƬ�ڲ��¶�
unsigned short int 	RpmCur;               //ת�٣� ���99  �ڲ�����10����990  
unsigned short int 	RpmDisplay;               //��ʾת�٣� ���99
unsigned short int 	temptemprature1;   //��ǰ�¶�1�� ���999
unsigned short int 	temptemprature2;   //��ǰ�¶�2�� ���999
unsigned short int 	current;           //����ȵ���
unsigned short int 	volt;              //��Դ��ѹ
	
} _str_adc_resoult;
extern  _str_adc_resoult  AdcRes;
///////////////////////

//����ʱ���ֵ
typedef struct 
{
unsigned char 	NoKeyTim;
unsigned char 	age;
unsigned char 	AdjTim;
unsigned char 	last;
unsigned char 	resoult;
unsigned char 	buf1;
unsigned char 	buf2;
unsigned char 	buf3;
}_str_key_get;
extern _str_key_get  KeyScan;  //KeyScan.

extern unsigned char LedsBuf;

#define LedSwitchOn1    ( LedsBuf |= 0x01 )
#define LedSwitchOff1   ( LedsBuf &= (~0x01) )
#define LedSwitchOn2    ( LedsBuf |= 0x02 )
#define LedSwitchOff2   ( LedsBuf &= (~0x02) )
#define LedSwitchOn3    ( LedsBuf |= 0x04 )
#define LedSwitchOff3   ( LedsBuf &= (~0x04) )
#define LedSwitchOn4    ( LedsBuf |= 0x08 )
#define LedSwitchOff4   ( LedsBuf &= (~0x08) )
#define LedSwitchOn5    ( LedsBuf |= 0x10 )
#define LedSwitchOff5   ( LedsBuf &= (~0x10) )
#define LedSwitchOn6    ( LedsBuf |= 0x20 )
#define LedSwitchOff6   ( LedsBuf &= (~0x20) )

#define LedOnAll        ( LedsBuf |= 0x3f )
#define LedOffAll       ( LedsBuf &= 0xc0 )


//LedRunStatu1
#define LED_RUN1_ON			  LedSwitchOn6
#define LED_RUN1_OFF			LedSwitchOff6

//LedEventTime1
#define LED_EVENT_ON			LedSwitchOn5
#define LED_EVENT_OFF		  LedSwitchOff5

#define LED_TEST_GET_ON		;//JSP2_1()	;//SetLed2
#define LED_TEST_GET_OFF	;//JSP2_0()	;//ClrLed2



//enum _SetMod
//{
//	ModNomal,
//  ModHeatMatheSet,
//  ModTemprature,
//  ModRpm	
//}SetMods;

typedef enum{
	ModNomal         =  0  ,
  ModHeatMatheSet          =  1  ,
  ModTemprature    =  2  ,
  ModRpm           =  3  ,
  Test1            =  4  ,
  Test2            =  5  ,
  Test3_rmp_pid    =  6	
}_SetMod;  
extern  _SetMod   SetMods;




void SwitchDirect( unsigned char x );  //����̵����л�����  0��ת 1��ת

unsigned char KeyLedScan( unsigned char ledsbuf  ) ;
void KeyGet(unsigned char key_in);

//���������ת��Ϊ����ֵ
unsigned short int PowerToShiftTimr( unsigned short int val);

void Get_ChipAdc_Measure(void);



extern unsigned char FlagDebug_SWCLK_Off;
extern unsigned char FlagEnable_TestMod;

//void InterPoint_Test(void);
unsigned short int InterPointCala( unsigned short int  y );





#endif

