/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.blkeji.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               uctsk_Blink.c
** Descriptions:            The uctsk_Blink application function
**
**--------------------------------------------------------------------------------------------------------

** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <includes.h>            

#include  "user_ucOS.h"


#if (OS_VIEW_MODULE == DEF_ENABLED)

#include    <uCOS-VIEW\Ports\ARM-Cortex-M3\Realview\os_viewc.h>

#include    <uCOS-VIEW\Source\os_view.h>

extern void  App_OSViewTaskCreate (void);

#endif	

extern OS_EVENT *OSSemGetAA;
extern OS_EVENT *OSSemOutCC;
extern OS_EVENT *OSSemRfcc1100;
extern OS_EVENT *OSSemUart1;
/* Private variables ---------------------------------------------------------*/
static  OS_STK         App_TaskBlinkStk[APP_TASK_BLINK_STK_SIZE];

static  OS_STK         MyTASKStk[MyTASKStk_SIZE];
static  OS_STK         TaskVirPwmStk[TaskVirPwmStk_SIZE];
static  OS_STK         TaskRpmStk[TaskRpmStk_SIZE];
static  OS_STK         TaskEventStk[TaskEventStk_SIZE];
static  OS_STK         TaskSaveStk[TaskSaveStk_SIZE];
static  OS_STK         TaskKeyStk[TaskKeyStk_SIZE];

static  OS_STK         TaskMeasureStk[TaskMeasureStk_SIZE];
static  OS_STK         TaskStatuStk[TaskStatuStk_SIZE];
static  OS_STK         TaskAverageStk[TaskAverageStk_SIZE];
static  OS_STK         TaskTimeoutStk[TaskTimeoutStk_SIZE];
static  OS_STK         TaskRuningStk[TaskRuningStk_SIZE];
static  OS_STK         TaskModbusStk[TaskModbusStk_SIZE];


/* Private function prototypes -----------------------------------------------*/
static void uctsk_Blink (void);
static void MyTASK (void);
//extern void TaskVirPwm(void);
//extern void TaskRpm(void);
//extern void TaskEvent(void);
//extern void TaskSave(void * pdata);
 
void  App_BlinkTaskCreate (void)
{
    CPU_INT08U  os_err;

	os_err = os_err; /* prevent warning... */
	
#if CONFIG_TEST_LED_BLINK
	os_err = OSTaskCreate((void (*)(void *)) uctsk_Blink,				
                          (void          * ) 0,							
                          (OS_STK        * )&App_TaskBlinkStk[APP_TASK_BLINK_STK_SIZE - 1],		
                          (INT8U           ) APP_TASK_BLINK_PRIO  );							

	#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(APP_TASK_BLINK_PRIO, "Task LED Blink", &os_err);
	#endif
#endif



OSSemGetAA = OSSemCreate(0);
OSSemOutCC = OSSemCreate(0);
OSSemRfcc1100 = OSSemCreate(1);
OSSemUart1 = OSSemCreate(1);
//MyStk
//	os_err = OSTaskCreate((void (*)(void *)) MyTASK,				
//                          (void          * ) 0,							
//                          (OS_STK        * )&MyTASKStk[MyTASKStk_SIZE - 1],		
//                          (INT8U           ) MyTASK_PRIO  );	

/*
    os_err = OSTaskCreateExt((void (*)(void *)) MyTASK,
                             (void          * ) 0,
                             (OS_STK        * )&MyTASKStk[MyTASKStk_SIZE - 1],
                             (INT8U           ) MyTASK_PRIO,
                             (INT16U          ) MyTASK_PRIO,
                             (OS_STK        * )&MyTASKStk[0],
                             (INT32U          ) MyTASKStk_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));

*/

    os_err = OSTaskCreateExt((void (*)(void *)) TaskKey,
                             (void          * ) 0,
                             (OS_STK        * )&TaskKeyStk[TaskKeyStk_SIZE - 1],
                             (INT8U           ) TaskKey_PRIO,
                             (INT16U          ) TaskKey_PRIO,
                             (OS_STK        * )&TaskKeyStk[0],
                             (INT32U          ) TaskKeyStk_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));


    os_err = OSTaskCreateExt((void (*)(void *)) TaskEvent,
                             (void          * ) 0,
                             (OS_STK        * )&TaskEventStk[TaskEventStk_SIZE - 1],
                             (INT8U           ) TaskEvent_PRIO,
                             (INT16U          ) TaskEvent_PRIO,
                             (OS_STK        * )&TaskEventStk[0],
                             (INT32U          ) TaskEventStk_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));


    os_err = OSTaskCreateExt((void (*)(void *)) TaskRpm,
                             (void          * ) 0,
                             (OS_STK        * )&TaskRpmStk[TaskRpmStk_SIZE - 1],
                             (INT8U           ) TaskRpm_PRIO,
                             (INT16U          ) TaskRpm_PRIO,
                             (OS_STK        * )&TaskRpmStk[0],
                             (INT32U          ) TaskRpmStk_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));

    os_err = OSTaskCreateExt((void (*)(void *)) TaskVirPwm,
                             (void          * ) 0,
                             (OS_STK        * )&TaskVirPwmStk[TaskVirPwmStk_SIZE - 1],
                             (INT8U           ) TaskVirPwm_PRIO,
                             (INT16U          ) TaskVirPwm_PRIO,
                             (OS_STK        * )&TaskVirPwmStk[0],
                             (INT32U          ) TaskVirPwmStk_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));

    os_err = OSTaskCreateExt((void (*)(void *)) TaskMeasure,
                             (void          * ) 0,
                             (OS_STK        * )&TaskMeasureStk[TaskMeasureStk_SIZE - 1],
                             (INT8U           ) TaskMeasure_PRIO,
                             (INT16U          ) TaskMeasure_PRIO,
                             (OS_STK        * )&TaskMeasureStk[0],
                             (INT32U          ) TaskMeasureStk_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
    


    os_err = OSTaskCreateExt((void (*)(void *)) TaskSave,
                             (void          * ) 0,
                             (OS_STK        * )&TaskSaveStk[TaskSaveStk_SIZE - 1],
                             (INT8U           ) TaskSave_PRIO,
                             (INT16U          ) TaskSave_PRIO,
                             (OS_STK        * )&TaskSaveStk[0],
                             (INT32U          ) TaskSaveStk_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));


    os_err = OSTaskCreateExt((void (*)(void *)) TaskAverage,
                             (void          * ) 0,
                             (OS_STK        * )&TaskAverageStk[TaskAverageStk_SIZE - 1],
                             (INT8U           ) TaskAverage_PRIO,
                             (INT16U          ) TaskAverage_PRIO,
                             (OS_STK        * )&TaskAverageStk[0],
                             (INT32U          ) TaskAverageStk_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));



    os_err = OSTaskCreateExt((void (*)(void *)) TaskStatu,
                             (void          * ) 0,
                             (OS_STK        * )&TaskStatuStk[TaskStatuStk_SIZE - 1],
                             (INT8U           ) TaskStatu_PRIO,
                             (INT16U          ) TaskStatu_PRIO,
                             (OS_STK        * )&TaskStatuStk[0],
                             (INT32U          ) TaskStatuStk_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));


                             
    os_err = OSTaskCreateExt((void (*)(void *)) TaskTimeout,
                             (void          * ) 0,
                             (OS_STK        * )&TaskTimeoutStk[TaskTimeoutStk_SIZE - 1],
                             (INT8U           ) TaskTimeout_PRIO,
                             (INT16U          ) TaskTimeout_PRIO,
                             (OS_STK        * )&TaskTimeoutStk[0],
                             (INT32U          ) TaskTimeoutStk_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));                         
                    
     os_err = OSTaskCreateExt((void (*)(void *)) TaskRuning,
                             (void          * ) 0,
                             (OS_STK        * )&TaskRuningStk[TaskRuningStk_SIZE - 1],
                             (INT8U           ) TaskRuning_PRIO,
                             (INT16U          ) TaskRuning_PRIO,
                             (OS_STK        * )&TaskRuningStk[0],
                             (INT32U          ) TaskRuningStk_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));                                
                           
      os_err = OSTaskCreateExt((void (*)(void *)) TaskModbus,
                             (void          * ) 0,
                             (OS_STK        * )&TaskModbusStk[TaskModbusStk_SIZE - 1],
                             (INT8U           ) TaskModbus_PRIO,
                             (INT16U          ) TaskModbus_PRIO,
                             (OS_STK        * )&TaskModbusStk[0],
                             (INT32U          ) TaskModbusStk_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));                               
                             
                             
	#if OS_TASK_NAME_EN > 0
    	OSTaskNameSet(MyTASK_PRIO, "MyTASK", &os_err);

    	OSTaskNameSet(TaskEvent_PRIO, "TaskEvent", &os_err);
			OSTaskNameSet(TaskVirPwm_PRIO, "TaskVirPwm", &os_err);    	
			OSTaskNameSet(TaskRpm_PRIO, "TaskRpm", &os_err);
    	OSTaskNameSet(TaskKey_PRIO, "TaskKey", &os_err);			
    	OSTaskNameSet(TaskSave_PRIO, "TaskSave", &os_err);
    	
    	OSTaskNameSet(TaskMeasure_PRIO, "TaskMeasure", &os_err);
    	
    	OSTaskNameSet(TaskStatu_PRIO, "TaskStatu", &os_err);
    	OSTaskNameSet(TaskAverage_PRIO, "TaskAverage", &os_err);
     	OSTaskNameSet(TaskTimeout_PRIO, "TaskTimeout", &os_err);
    	
    	OSTaskNameSet(TaskRuning_PRIO, "TaskRuning", &os_err);
    	OSTaskNameSet(TaskModbus_PRIO, "TaskModbus", &os_err);   	
    	
    	
	#endif
	
	#if (OS_VIEW_MODULE == DEF_ENABLED)
	App_OSViewTaskCreate();
  #endif	
	
	
	
}
/*******************************************************************************
* Function Name  : Delay
* Description    : Delay Time
* Input          : - nCount: Delay Time
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void  Delay (uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}
//////////////
static void MyTASK (void)
{
	
	for(;;)
	{
		
		
		OSTimeDlyHMSM(0, 0,1, 100);	 /* 1 seconds  */
		//ClrPowJspOut1;
		//ClrResumMegnet;
		//GPIO_ResetBits(GPIOE , GPIO_Pin_1);
		//LED1_ON;
		//LED2_OFF;
		//GPIO_ResetBits(GPIOE,GPIO_Pin_1);
		//Delay(60000);
		OSTimeDlyHMSM(0, 0, 1, 100);
		//SetPowJspOut1;
		//SetResumMegnet;
		//LED2_ON;
		//LED1_OFF;
//GPIO_SetBits(GPIOE , GPIO_Pin_1);
	
	
	
		}
}


#if CONFIG_TEST_LED_BLINK
static void uctsk_Blink (void) {                 
  
   
   	for(;;)
   	{   
	    //Delay( rand()%0xfffff ); 	
	    #if CONFIG_TEST_LED_BLINK
//LED1_ON;	    
//LED2_ON;
//GPIO_SetBits(GPIOE , GPIO_Pin_0);
#endif
//OSTimeDly(OS_TICKS_PER_SEC);
OSTimeDlyHMSM(0, 0, 0,50);	//50ms
		//OSTimeDlyHMSM(0, 0, 1, 0);	 /* 1 seconds  */
	 	/* LED1-ON LED2-OFF */
	//	GPIO_SetBits(GPIOE , GPIO_Pin_0);
		//GPIO_ResetBits(GPIOE , GPIO_Pin_1);

	    //Delay( rand()%0xfffff ); 
	    #if CONFIG_TEST_LED_BLINK
//LED1_OFF;
//LED2_OFF;
//GPIO_ResetBits(GPIOE , GPIO_Pin_0);
#endif
//OSTimeDly(OS_TICKS_PER_SEC);
OSTimeDlyHMSM(0, 0, 0,50);	//50ms
      	
	    /* LED1-OFF LED2-ON */
		//GPIO_ResetBits(GPIOE , GPIO_Pin_0);
		//GPIO_SetBits(GPIOE , GPIO_Pin_1);
   }
}
#endif
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
