


#if CONFIG_PWM_TIM1
#include "stm32f10x.h"   
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
		
		//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
		
		
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
////////////////////////  
void PWM_T1_Configuration(void)
{
    
    TIM_TimeBaseInitTypeDef  		TIM_TimeBaseStructure;
		TIM_OCInitTypeDef						TIM_OCInitStructure;


    //NVIC_SetPriority(SysTick_IRQn, 0);

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	  
	  TIM_TimeBaseStructure.TIM_Prescaler     = 360-1;			//Ԥ����Ĵ���  36mhz 100khz  0.01ms - 10ms  1000����
	  TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;//TIM_CounterMode_Down;//
    TIM_TimeBaseStructure.TIM_Period        = 100;//10ms
    
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
    


    //PmwVal_TIM1_ch1=0;//400




		//����ͨ��
		TIM_OCInitStructure.TIM_OCMode				=	TIM_OCMode_Active;//TIM_OCMode_PWM1;////TIM_OCMode_Timing;//

    TIM_OCInitStructure.TIM_OutputState		=	TIM_OutputState_Enable;

//		TIM_OCInitStructure.TIM_OutputNState	=	TIM_OutputNState_Enable;		//�򿪻������
    
    
    TIM_OCInitStructure.TIM_Pulse					=	500;//PmwVal_TIM1_ch1;
    TIM_OCInitStructure.TIM_OCPolarity		=	TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity		=	TIM_OCNPolarity_Low;//TIM_OCNPolarity_High;//
    TIM_OCInitStructure.TIM_OCIdleState		=	TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState	=	TIM_OCNIdleState_Reset;
    
    
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);			//��ֵͨ���������ڸ����¼�װ��
    
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





