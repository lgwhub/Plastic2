
//#include "app1.h"

#ifndef   _APP1_H

#define   _APP1_H

//ad测量值
typedef struct 	
{

	
unsigned short int 	temprature0;       //芯片内部温度
unsigned short int 	RpmCur;               //转速， 最大99  内部扩大10倍，990  
unsigned short int 	RpmDisplay;               //显示转速， 最大99
unsigned short int 	temptemprature1;   //当前温度1， 最大999
unsigned short int 	temptemprature2;   //当前温度2， 最大999
unsigned short int 	current;           //电加热电流
unsigned short int 	volt;              //电源电压
	
} _str_adc_resoult;
extern  _str_adc_resoult  AdcRes;
///////////////////////

//键盘时间和值
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




void SwitchDirect( unsigned char x );  //电机继电器切换方向  0正转 1反转

unsigned char KeyLedScan( unsigned char ledsbuf  ) ;
void KeyGet(unsigned char key_in);

//电机控制量转化为移相值
unsigned short int PowerToShiftTimr( unsigned short int val);

void Get_ChipAdc_Measure(void);



extern unsigned char FlagDebug_SWCLK_Off;
extern unsigned char FlagEnable_TestMod;

//void InterPoint_Test(void);
unsigned short int InterPointCala( unsigned short int  y );





#endif

