/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.blkeji.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               app_cfg.h
** Descriptions:            ucosii configuration
**
**--------------------------------------------------------------------------------------------------------

** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__
					  
// app_cfg.h
/*
*********************************************************************************************************
*                                       MODULE ENABLE / DISABLE
*********************************************************************************************************
*/
#define  OS_VIEW_MODULE                 0*DEF_ENABLED

#define  OS_VIEW_USART_NUMBER			1


#if   OS_VIEW_USART_NUMBER == 1
#define  OS_VIEW_USART				     USART1	    
#elif  OS_VIEW_USART_NUMBER == 2
#define  OS_VIEW_USART				     USART2    
#elif  OS_VIEW_USART_NUMBER == 3
#define  OS_VIEW_USART				     USART3    
#endif

#define CONFIG_TEST_LED_BLINK		0






/*
*********************************************************************************************************
*                                              TASKS NAMES
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define  APP_TASK_START_PRIO                               3
#define  TaskVirPwm_PRIO          	 		(OS_LOWEST_PRIO - 31)
#define  TaskRpm_PRIO          	 		(OS_LOWEST_PRIO - 30)

#define  TaskRuning_PRIO          	(OS_LOWEST_PRIO - 25)
#define  TaskModbus_PRIO          	 		(OS_LOWEST_PRIO - 24)

#define  TaskEvent_PRIO          	 		(OS_LOWEST_PRIO - 23)

#define  TaskMeasure_PRIO          	 		(OS_LOWEST_PRIO - 21)


#define  TaskSave_PRIO          	 		(OS_LOWEST_PRIO - 18)

#define  TaskAverage_PRIO          	 		(OS_LOWEST_PRIO - 17)


#define  TaskKey_PRIO          	 		(OS_LOWEST_PRIO - 13)



#define  TaskTimeout_PRIO         (OS_LOWEST_PRIO - 11)
#define  TaskStatu_PRIO          	 		(OS_LOWEST_PRIO - 10)


#define  MyTASK_PRIO          	 		(OS_LOWEST_PRIO - 7)
#define  APP_TASK_BLINK_PRIO          	 (OS_LOWEST_PRIO - 6)

#define  APP_TASK_OSVIEW_TERMINAL_PRIO	 (OS_LOWEST_PRIO - 4)
#define  OS_VIEW_TASK_PRIO               (OS_LOWEST_PRIO - 3)
#define  OS_TASK_TMR_PRIO                (OS_LOWEST_PRIO - 2)




/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/

#define  APP_TASK_START_STK_SIZE                          (92+2)
#define  APP_TASK_BLINK_STK_SIZE                         (56+2)
#define  APP_TASK_OSVIEW_TERMINAL_STK_SIZE   			 128u
#define  OS_VIEW_TASK_STK_SIZE                           128u

#define  MyTASKStk_SIZE                          (56+2u)

#define  TaskEventStk_SIZE                          (84+2u)
#define  TaskVirPwmStk_SIZE                          (194+2u)
#define  TaskRpmStk_SIZE                          (194+2u)
#define  TaskMeasureStk_SIZE                          (194+2u)
#define  TaskSaveStk_SIZE                          (118+2u)

#define  TaskAverageStk_SIZE                          (188+2u)
#define  TaskModbusStk_SIZE                          (138+2u)

#define  TaskKeyStk_SIZE                          (180+50+2u)
#define  TaskStatuStk_SIZE                          (98+2u)
#define  TaskTimeoutStk_SIZE                    (80+2u)
#define  TaskRuningStk_SIZE                       (120+2u)


/*
*********************************************************************************************************
*                                                  LIB
*********************************************************************************************************
*/

#define  uC_CFG_OPTIMIZE_ASM_EN                 DEF_ENABLED
#define  LIB_STR_CFG_FP_EN                      DEF_DISABLED

/*
*********************************************************************************************************
*                                             io def     
*********************************************************************************************************
*/







#endif
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

