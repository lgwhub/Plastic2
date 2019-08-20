/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.4.0
  * @date    10/15/2010
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include <includes.h>
#include "uart_UCOS.h"

#if ( OS_VIEW_MODULE == DEF_ENABLED )
extern	void OSView_RxTxISRHandler(void);
#endif

__IO uint32_t step = 1;
//__IO uint32_t step2 = 1;
//__IO uint32_t step3 = 1;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}



/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	CPU_SR         cpu_sr;
	OS_ENTER_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
    OSIntNesting++;
    OS_EXIT_CRITICAL();

    OSTimeTick();                                /* Call uC/OS-II's OSTimeTick()                       */


	//PeriodPidCtrl(); ////SysTick_Config
	//ModbusTimeHandler();


    OSIntExit();                                 /* Tell uC/OS-II that we are leaving the ISR          */
}



/////////////////////////
void TIM3_IRQHandler(void)
{
//__IO uint32_t step2 = 1;	
//static unsigned char step2=1;//__IO uint32_t step = 1;

	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
      {

        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
        
 #if  CONFIG_PWM_TWO_SYNS  
   	 if (step2 == 1)
			  	{
			  	TIM_SetCompare1(TIM3, PmwVal_TIM31_Buf);
  				TIM_SetCompare2(TIM3, 0);	
			  		
  				TIM_SetCompare3(TIM3, PmwVal_TIM32_Buf);
  				TIM_SetCompare4(TIM3, 0);
  				step2=0;
  				
  				TestSyncPinTIM3_CLR;
  			}
  			
  	else{
  				TIM_SetCompare1(TIM3, 0);
					TIM_SetCompare2(TIM3, PmwVal_TIM31_Buf);
					
  				TIM_SetCompare3(TIM3, 0);
					TIM_SetCompare4(TIM3, PmwVal_TIM32_Buf);		
					
					PmwVal_TIM31_Buf=iPmwVal[0];		//两次切换后刷新缓冲器，保持一个波形的完整性,PA0.6  PA0.7			
					PmwVal_TIM32_Buf=iPmwVal[1];		//两次切换后刷新缓冲器，保持一个波形的完整性,PB0.0  PB0.1
					
					step2=1;
					TestSyncPinTIM3_SET;
				}
				   
 #endif

        }
//////////////////////////////////////////////////////////////////////////////
  if (TIM_GetITStatus(TIM3, TIM_IT_CC4) != RESET)
  	{
  		TIM_ClearITPendingBit(TIM3, TIM_IT_CC4);
  	}
  	
  	
  if (TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET)
  {

			TIM_ClearITPendingBit(TIM3, TIM_IT_CC3);	
  }


}

				
/////////////////////////
void TIM4_IRQHandler(void)
{
	
//static unsigned char step2=1;//__IO uint32_t step = 1;

	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
      {
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);

 #if  CONFIG_PWM_TWO_SYNS
  	 if (step2 == 1)
			  	{
  				TIM_SetCompare1(TIM4, PmwVal_TIM41_Buf);
  				TIM_SetCompare2(TIM4, 0);
  				
  				TIM_SetCompare3(TIM4, PmwVal_TIM42_Buf);
  				TIM_SetCompare4(TIM4, 0);  		
  						
  				step2=0;
  				TestSyncPinTIM4_CLR;
  			}
  			
  	else{
  		
  				TIM_SetCompare1(TIM4, 0);
					TIM_SetCompare2(TIM4, PmwVal_TIM41_Buf);
					
  				TIM_SetCompare3(TIM4, 0);
					TIM_SetCompare4(TIM4, PmwVal_TIM42_Buf);					
					
					PmwVal_TIM41_Buf=iPmwVal[2];		//两次切换后刷新缓冲器，保持一个波形的完整性,控制PB0.6  PB0.7
					PmwVal_TIM42_Buf=iPmwVal[3];		//两次切换后刷新缓冲器，保持一个波形的完整性,控制PB0.8  PB0.9		
								
					step2=1;
					TestSyncPinTIM4_SET;
				}

#endif
        }
//////////////////////////////////////////////////////////////////////////////
  if (TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET)
  	{
  		TIM_ClearITPendingBit(TIM4, TIM_IT_CC4);
  	}
  	
  	
  if (TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)
  {

			TIM_ClearITPendingBit(TIM4, TIM_IT_CC3);	
  }


}
////////////////

void TIM1_UP_IRQHandler(void)
{
//__IO uint32_t step3 = 1;
//static unsigned char step3=1;//__IO uint32_t step = 1;	
//	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
//      {
//        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
//    
//
//#if CONFIG_PWM_TIM1
//  	 if (step3 == 1)
//			  	{
//			  		
//  				TIM_SetCompare2(TIM1, PmwVal_TIM1_ch3);
//  				TIM_SetCompare3(TIM1, 0);
//  				step3=0;
//  				TestSyncPinTIM1_CLR;
//  			}
//  			
//  	else{
//  				TIM_SetCompare2(TIM1, 0);
//					TIM_SetCompare3(TIM1, PmwVal_TIM1_ch3);
//					step3=1;
//					TestSyncPinTIM1_SET;
//				}
//#endif
//
//        }
}
/////////////////////////
void TIM1_CC_IRQHandler(void)
{
	


  if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)
     {
    TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);


  }
//////////////////////////////////////////////////////////////////////////////
  if (TIM_GetITStatus(TIM1, TIM_IT_CC2) != RESET)
  	{
  		TIM_ClearITPendingBit(TIM1, TIM_IT_CC2);
  	}
  	
  	
  if (TIM_GetITStatus(TIM1, TIM_IT_CC3) != RESET)
  {

			TIM_ClearITPendingBit(TIM1, TIM_IT_CC3);	
  }


}
/////////////////////////
void TIM1_BRK_IRQHandler(void)
{
}
/////////////////////////
void TIM1_TRG_COM_IRQHandler(void)
{
   /* Clear TIM1 COM pending bit */
TIM_ClearITPendingBit(TIM1, TIM_IT_COM);
//TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);	
//TIM_ClearITPendingBit(TIM1, TIM_IT_CC2);
//TIM_ClearITPendingBit(TIM1, TIM_IT_CC3);

}


/*******************************************************************************
* Function Name  : USART1_IRQHandler
* Description    : This function handles USART1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void USART1_IRQHandler(void)
{		//担心 stm32f10x_it.c  不能包含到  CONFIG_UART1
	#if   ( OS_VIEW_MODULE != DEF_ENABLED )|| (OS_VIEW_USART_NUMBER != 1)
	#if CONFIG_UART1
	USART1_RxTxISRHandler();
	#endif
	#endif	
	
	#if ( OS_VIEW_MODULE == DEF_ENABLED )
				#if   OS_VIEW_USART_NUMBER == 1
							OSView_RxTxISRHandler();
				#endif	
	#endif
}

/*******************************************************************************
* Function Name  : USART2_IRQHandler
* Description    : This function handles USART1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void USART2_IRQHandler(void)
{
#if   ( OS_VIEW_MODULE != DEF_ENABLED )|| (OS_VIEW_USART_NUMBER != 2)
#if CONFIG_UART2
	USART2_RxTxISRHandler();
	#endif
	#endif
	
	
	#if ( OS_VIEW_MODULE == DEF_ENABLED )
		#if   OS_VIEW_USART_NUMBER == 2			
				OSView_RxTxISRHandler();
		#endif	
#endif
}

void USART3_IRQHandler(void)
{
#if   ( OS_VIEW_MODULE != DEF_ENABLED )|| (OS_VIEW_USART_NUMBER != 3)
		#if CONFIG_UART3
	USART3_RxTxISRHandler();
	#endif
	#endif	
	
	#if ( OS_VIEW_MODULE == DEF_ENABLED )
		#if   OS_VIEW_USART_NUMBER == 3			
				OSView_RxTxISRHandler();
		#endif	
#endif
}

//void UART4_IRQHandler(void)
//{
//	#if   ( OS_VIEW_MODULE != DEF_ENABLED )|| (OS_VIEW_USART_NUMBER != 4)
//	#if CONFIG_UART4
//	UART4_RxTxISRHandler();
//	#endif
//	#endif	
//	
//	#if ( OS_VIEW_MODULE == DEF_ENABLED )
//		#if   OS_VIEW_USART_NUMBER == 4			
//				OSView_RxTxISRHandler();
//		#endif	
//#endif
//}
//
//
//void UART5_IRQHandler(void)
//{
//	#if   ( OS_VIEW_MODULE != DEF_ENABLED )|| (OS_VIEW_USART_NUMBER != 5)
//	#if CONFIG_UART5
//	UART5_RxTxISRHandler();
//	#endif
//	#endif	
//	
//	#if ( OS_VIEW_MODULE == DEF_ENABLED )
//		#if   OS_VIEW_USART_NUMBER == 5			
//				OSView_RxTxISRHandler();
//		#endif	
//#endif
//}
//////////////////

void EXTI0_IRQHandler(void)
{
#if CONFIG_EXTI
  if(EXTI_GetITStatus(EXTI_Line12) != RESET)
  {

    /* Clear the Key Button EXTI line pending bit */

    //强制输出为0   TIM_CH1
    
    //移相定时器提前清0
  //  TIM_SetCounter(TIM1,0);
    

    
    
    EXTI_ClearITPendingBit(EXTI_Line12);
  }
 #endif
}

void EXTI9_5_IRQHandler(void)
{
#if CONFIG_EXTI
  if(EXTI_GetITStatus(EXTI_Line6) != RESET)
  {
    /* Toggle LED1 */
    // STM_EVAL_LEDToggle(LED1);

//Blk.lStats1[1] = DMA_GetCurrDataCounter(DMA2_Channel4); //当前DMA通道X剩余的待传输数据数目

    /* Clear the Key Button EXTI line pending bit */
    EXTI_ClearITPendingBit(EXTI_Line6);
  }
  
  if(EXTI_GetITStatus(EXTI_Line7) != RESET)
  {
    /* Toggle LED1 */
    // STM_EVAL_LEDToggle(LED1);

    EXTI_ClearITPendingBit(EXTI_Line7);
  }  
 #endif
}

void EXTI15_10_IRQHandler(void)
{
#if CONFIG_EXTI
  if(EXTI_GetITStatus(EXTI_Line12) != RESET)
  {

    /* Clear the Key Button EXTI line pending bit */

    //强制输出为0   TIM_CH1
  //  void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction)
    //移相定时器提前清0
    TIM_SetCounter(TIM1,0);
    

    
    
    EXTI_ClearITPendingBit(EXTI_Line12);
  }
 #endif
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
