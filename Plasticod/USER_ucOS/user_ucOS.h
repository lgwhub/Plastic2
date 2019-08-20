

#ifndef _USER_H
#define _USER_H


//#include "includes.h"

//产品唯一身份标识寄存器（96位）
//基地址0X1FFF F7E8
//位15:0
//地址偏移0x02
//位31:16
//地址偏移0x04
//位63:32
//地址偏移0x06
//位95:64




///////////////////////////////

extern unsigned char TimeForSaveParam;

//extern OS_EVENT *OSSemOutSwOn;

void  App_BlinkTaskCreate   (void);

void TaskMeasure(void * pdata);
void TaskStatu(void * pdata);
void TaskAverage(void * pdata);
void TaskTimeout(void * pdata);
void TaskRuning(void * pdata);
void TaskModbus(void * pdata);



void TaskEvent(void * pdata);
void TaskVirPwm(void * pdata);
void TaskRpm(void * pdata);
void TaskSave(void * pdata);
void TaskKey(void * pdata);





///////////////////////////////////////////////////

extern unsigned char    LedEventTime1;
//extern unsigned char  InputBuf;




/* 数据类型 */
typedef unsigned char        BOOLEN;
typedef unsigned char        INT8U;
typedef signed char          INT8S;
typedef unsigned short       INT16U;
typedef signed short         INT16S;
typedef unsigned int         INT32U;
typedef signed int           INT32S;
typedef float                FP32;
typedef double               FP64;


#define BYTE                 INT8S
#define UBYTE                INT8U    
#define WORD                 INT16S
#define UWORD                INT16U
#define LONG                 INT32S
#define ULONG                INT32U





/**************************************************************************************************/

////LedRunStatu1
//#define LED_RUN1_ON			SetLed1
//#define LED_RUN1_OFF			ClrLed1
//
////LedEventTime1
//#define LED_EVENT_ON			SetLed2
//#define LED_EVENT_OFF		  ClrLed2
//
//#define LED_TEST_GET_ON			;//SetLed2
//#define LED_TEST_GET_OFF		;//ClrLed2







//
//extern struct	struct_save *gpParam;
////#define Max_Param_Len		8
//#define Max_Param_Len		8
////参数已经初始化标记
//#define FlagParamInitnized	0xA9
//extern uint32 gbParamBuf[Max_Param_Len+2];
//
////参数的EEPROM区首地址
//#define EEPROM_BASE_ADR	0X4010




void AutoSend(void);


void Run_Init(void);



#endif


