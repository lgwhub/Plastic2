    
#include "includes.h"


#if CONFIG_PWM_TIM1
#include "stm32f10x.h"   
#include "pwm1.h"

unsigned int PmwVal_TIM1_ch1;  //TIM_SetCompare1(TIM1, PmwVal_TIM1_ch1);

#define SYNC_USE_ETR  1

//TIM_SetCompare3(TIM4, 0);
//TIM_SetCompare4(TIM4, PmwVal_TIM42_Buf);



    /*
    TIM1 TIM8�Ǹ߼���ʱ��
    �߼���ʱ������ʱ��72MHZ,����TIM1����3������������źţ�Ƶ��1HZ,ռ�ձ�25%��50%,75%,�ֱ���1/10000������������ʱ�䡣
    
    Ԥ����Ĵ�����ֵ=72000000/10000  -1 =7199
    �ȽϼĴ���1��ֵ=10000x25%=2500
		�ȽϼĴ���2��ֵ=10000x50%=5000
		�ȽϼĴ���3��ֵ=10000x75%=7500    
    */
    
    

    
//////////////////////////////////    
void GPIO_Configuration_PWM_T1(void)
{
		GPIO_InitTypeDef	GPIO_InitStructure;
		
	//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
		
		
		//GPIOBͨ��1N 2N,3N		PB13 PB14 PB15
//		GPIO_InitStructure.GPIO_Pin		=	GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
//		GPIO_InitStructure.GPIO_Mode	=		GPIO_Mode_AF_PP;
//		
//				GPIO_InitStructure.GPIO_Speed	=		GPIO_Speed_50MHz;
//		GPIO_Init(GPIOB,&GPIO_InitStructure);
		



//GPIOAͨ��1,2,3			PA8  PA9  PA10
			RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);

 			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
 			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	    GPIO_Init(GPIOA, &GPIO_InitStructure);
	    
	    //ETR   P12
 			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
 			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	    GPIO_Init(GPIOA, &GPIO_InitStructure);
}
//////////////////////// 

void NVIC_Configuration_PWM_T1(void)
{
//  NVIC_InitTypeDef NVIC_InitStructure;
//
//  // Enable the TIM1 Interrupt
//  NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;  //TIM1_UP_IRQn;//TIM1_CC_IRQn;  //TIM1_TRG_COM_IRQn; //
//  
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure); 
//
//
//  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;//TIM1_CC_IRQn;  //TIM1_TRG_COM_IRQn; //
//  
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure); 
}    


/* Synchronization management *************************************************
TIM_SelectSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_SlaveMode)
void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource);
void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_TRGOSource);
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_SlaveMode);
void TIM_SelectMasterSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_MasterSlaveMode);
void TIM_ETRConfig(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                   uint16_t ExtTRGFilter);
*************************************************/
////////////////////////  
//10ms����
//#define PERIOD_9990US  10000
#define PERIOD_9990US  9500
//#define PERIOD_9990US  9000
#define PRESCALER_val  ( ( 72 * PERIOD_9990US /  1000  ) - 1 )


void PWM_T1_Configuration(void)
{
    
    //#define PWM_T1_PERIOD_PULSE  (36000/6)
    
    TIM_TimeBaseInitTypeDef  		TIM_TimeBaseStructure;
		TIM_OCInitTypeDef						TIM_OCInitStructure;


   //NVIC_SetPriority(SysTick_IRQn, 0);
    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
		
/////////////////
 
  #if   (  SYNC_USE_ETR )
  //ʹ��ETRͬ������
		TIM_ETRConfig(TIM1 ,TIM_ExtTRGPSC_OFF , TIM_ExtTRGPolarity_Inverted ,0);  // //TIM_ExtTRGPolarity_Inverted  ETR�½���, TIM_ExtTRGPolarity_NonInverted  ETR������		

		//TIM_ETRConfig(TIM1 ,TIM_ExtTRGPSC_OFF , TIM_ExtTRGPolarity_NonInverted ,0);  //TIM_ExtTRGPolarity_Inverted  ETR�½���, TIM_ExtTRGPolarity_NonInverted  ETR������		
		TIM_SelectInputTrigger(TIM1 ,TIM_TS_ETRF);
		TIM_SelectSlaveMode (TIM1 , TIM_SlaveMode_Reset);
		TIM_SelectMasterSlaveMode (TIM1 , TIM_MasterSlaveMode_Enable );
  #endif
//////////////////////		
		

	TIM_TimeBaseStructure.TIM_Prescaler     = PRESCALER_val;//720-1;			//Ԥ����Ĵ���  36mhz 100khz  0.01ms - 10ms  1000����
   //TIM_TimeBaseStructure.TIM_Prescaler     = 720-1;			//Ԥ����Ĵ���  36mhz 100khz  0.01ms - 10ms  1000���� 
	
	TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;//TIM_CounterMode_Down;//
	//TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Down;//TIM_CounterMode_Up;//
	
  TIM_TimeBaseStructure.TIM_Period        = 1000;  //1000  (x0.01ms) = 10ms  //PWM_T1_PERIOD_PULSE;//2000;  //36mhz/2000=18khz   (36000000/f
    
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
    


   PmwVal_TIM1_ch1=50 ;//(PWM_T1_PERIOD_PULSE*8/100);//8%  0;//400
   //TIM_SetCompare1(TIM1,PWM_T1_PERIOD_PULSE*8/100);



		//����ͨ��2,3������PWMģʽ
		TIM_OCInitStructure.TIM_OCMode				=	TIM_OCMode_PWM2;//TIM_OCMode_PWM1;//TIM_OCMode_Active;//TIM_OCMode_Timing;//

    TIM_OCInitStructure.TIM_OutputState		=	TIM_OutputState_Enable;
  //TIM_OCInitStructure.TIM_OutputState		=	TIM_OutputState_Disable;
//		TIM_OCInitStructure.TIM_OutputNState	=	TIM_OutputNState_Enable;		//�򿪻������
    
    
    TIM_OCInitStructure.TIM_Pulse					=	PmwVal_TIM1_ch1;  //100 - 900 (x0.01ms)
    TIM_OCInitStructure.TIM_OCPolarity		=	TIM_OCPolarity_High;//TIM_OCPolarity_Low;//pwm�������
    
    
    TIM_OCInitStructure.TIM_OCNPolarity		=	TIM_OCNPolarity_Low;//TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState		=	TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState	=	TIM_OCNIdleState_Reset;
    
    
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); 			//pwm��ֵͨ���������ڸ����¼���װ��
    
    TIM_OC1Init(TIM1,&TIM_OCInitStructure);
    
    
//    TIM_OCInitStructure.TIM_Pulse					=	0;//PmwVal_TIM1_ch3;
//    
//    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);			//pwm��ֵͨ���������ڸ����¼���װ��
//    TIM_OC2Init(TIM1,&TIM_OCInitStructure);
////    
//    TIM_OCInitStructure.TIM_Pulse					=	PmwVal_TIM1_ch3;
//    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);			//pwm��ֵͨ���������ڸ����¼���װ��
//    TIM_OC3Init(TIM1,&TIM_OCInitStructure);   
//    


/*
#define TIM_IT_Update                      ((uint16_t)0x0001)
#define TIM_IT_CC1                         ((uint16_t)0x0002)
#define TIM_IT_CC2                         ((uint16_t)0x0004)
#define TIM_IT_CC3                         ((uint16_t)0x0008)
#define TIM_IT_CC4                         ((uint16_t)0x0010)
#define TIM_IT_COM                         ((uint16_t)0x0020)
#define TIM_IT_Trigger                     ((uint16_t)0x0040)
#define TIM_IT_Break                       ((uint16_t)0x0080)

*/
    TIM_CCPreloadControl(TIM1, ENABLE);  //TIMx->CR2 |= TIM_CR2_CCPC;

		     //TIM_ITConfig(TIM1, TIM_IT_COM, ENABLE);//
		     //TIM_ITConfig(TIM1, TIM_IT_Trigger, ENABLE);//
//		TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	       //	TIM_ITConfig(TIM1, TIM_IT_CC1, ENABLE);
		     //TIM_ITConfig(TIM1, TIM_IT_CC2, ENABLE);
         //	   TIM_ITConfig(TIM1, TIM_IT_CC3, ENABLE);
		//TIM1�������
    TIM_Cmd(TIM1, ENABLE);
    //�����������
    TIM_CtrlPWMOutputs(TIM1,ENABLE);
    
    
    //void TIM_SetCompare1(TIM_TypeDef* TIMx, uint16_t Compare1);
    //void TIM_SetCompare2(TIM_TypeDef* TIMx, uint16_t Compare2);
    
}
#endif



#if CONFIG_PWM_TIM3


#endif

#if CONFIG_PWM_TIM4
/////////////////////////////////////////////////

#endif

