/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.blkeji.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The UCOSII application function
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

#include "uart_UCOS.h"
	#include "jump3.h"

/* Private variables ---------------------------------------------------------*/
static  OS_STK         App_TaskStartStk[APP_TASK_START_STK_SIZE];



/* Private function prototypes -----------------------------------------------*/
#if (OS_VIEW_MODULE == DEF_ENABLED)
extern void  App_OSViewTaskCreate (void);
#endif

static  void  App_TaskStart			(void		*p_arg);  
extern  void  App_BlinkTaskCreate   (void);
//static  void  GPIO_Configuration    (void);

 // unsigned char  DataStr[]=__DATE__;

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/
INT32S main (void)
{
// unsigned char  DataStr[]=__DATE__;
 //unsigned char code TimeStr[]=__TIME__;	
	
	
    CPU_INT08U  os_err;
	os_err = os_err; /* prevent warning... */
	
	
	IspMarkLoad();
	
	
	
	//Test_Clear
	

	

	/* Note:  由于使用UCOS, 在OS运行之前运行,注意别使能任何中断. */
	CPU_IntDis();                    /* Disable all ints until we are ready to accept them.  */

    OSInit();                        /* Initialize "uC/OS-II, The Real-Time Kernel".         */
	

	os_err = OSTaskCreateExt((void (*)(void *)) App_TaskStart,  /* Create the start task.                               */
                             (void          * ) 0,
                             (OS_STK        * )&App_TaskStartStk[APP_TASK_START_STK_SIZE - 1],
                             (INT8U           ) APP_TASK_START_PRIO,
                             (INT16U          ) APP_TASK_START_PRIO,
                             (OS_STK        * )&App_TaskStartStk[0],
                             (INT32U          ) APP_TASK_START_STK_SIZE,
                             (void          * )0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
	
#if OS_TASK_NAME_EN > 0
    OSTaskNameSet(APP_TASK_START_PRIO, (CPU_INT08U *)"Start Task", &os_err);
#endif

	OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II).  */

	return (0);
}


/*
*********************************************************************************************************
*                                          App_TaskStart()
*
* Description : The startup task.  The uC/OS-II ticker should only be initialize once multitasking starts.
*
* Argument(s) : p_arg       Argument passed to 'App_TaskStart()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*
* Note(s)     : none.
*********************************************************************************************************
*/	  
static  void  App_TaskStart (void *p_arg)
{   
	(void)p_arg;
	
	/***************  Init hardware ***************/
	/**
  * @brief  Configures the priority grouping: pre-emption priority and subpriority.
  * @param  NVIC_PriorityGroup: specifies the priority grouping bits length. 
  *   This parameter can be one of the following values:
  *     @arg NVIC_PriorityGroup_0: 0 bits for pre-emption priority
  *                                4 bits for subpriority
  *     @arg NVIC_PriorityGroup_1: 1 bits for pre-emption priority
  *                                3 bits for subpriority
  *     @arg NVIC_PriorityGroup_2: 2 bits for pre-emption priority
  *                                2 bits for subpriority
  *     @arg NVIC_PriorityGroup_3: 3 bits for pre-emption priority
  *                                1 bits for subpriority
  *     @arg NVIC_PriorityGroup_4: 4 bits for pre-emption priority
  *                                0 bits for subpriority
  * @retval None
  */
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);		//中断分组方案
//GPIO_Configuration();

//////////////////////////////////////////////////////////////////////////////

	
	
#if CONFIG_CHECK_DEVICE_ID*0
	
	InitSTM32DeciceID();
	
	
		if(GetStm32F103_DeviceId_Sum6() == Stm32IdSum6)
				{
					STM32DeviceId.Checked=1;
				}
		else{
			STM32DeviceId.Checked=0;
				}
#endif	    
    
///////////////////////    
    OS_CPU_SysTickInit();                                    /* Initialize the SysTick.                              */


OSTimeDlyHMSM(0, 0, 0, 50);

InitGpio();



	#if CONFIG_UART1	
	InitUSART1(57600,0);		//;	 InitUSART1(9600,0);	//  //  
	SendText_UART1("UART1 OK\r\n");
	#endif
	
	#if CONFIG_UART2
		InitUSART2(9600,0);//DefaultModemBaud;
		SendText_UART2("UART2 OK\r\n");
	#endif	
	
	#if CONFIG_UART3	
InitUSART3(115200,0);
SendText_UART3("UART3 OK\r\n");
	#endif	

	#if CONFIG_UART4
	InitUART4(9600,0);
	SendText_UART4("UART4 OK\r\n");
	#endif	

	#if CONFIG_UART5
	InitUART5(9600,0);
	SendText_UART5("UART5 OK\r\n");
	#endif	

	//StartLog();

//AutoSend();











#if (OS_TASK_STAT_EN > 0)
    OSStatInit();                                            /* Determine CPU capacity.                              */
#endif

    
    App_BlinkTaskCreate();
    
  OSTimeDlyHMSM(0, 0, 0, 10);                                      /* Create application tasks.                            */
	//AllTaskCreate();
	for(;;)
   	{

      	OSTimeDlyHMSM(0, 0, 5, 0);							 /* Delay One minute */
    }	
}







#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
