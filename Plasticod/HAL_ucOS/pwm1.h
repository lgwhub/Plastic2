    
//	#include "pwm1.h"

#ifndef	_PWM_H_
#define	_PWM_H_



//����������ֵ��������
//#define   MAX_PWM_VAL    (PWM_PERIOD_PULSE*90/100)
//#define   MAX_PWM_VAL    (PWM_PERIOD_PULSE)



extern unsigned int PmwVal_TIM1_ch1;
//�����������������������ֵ����ܳ���1000



//TIM_SetCompare1(TIM1, PmwVal_TIM1_ch1);

//#if CONFIG_PWM_TIM1    
void NVIC_Configuration_PWM_T1(void);
void PWM_T1_Configuration(void);  
void GPIO_Configuration_PWM_T1(void);
//#endif



#endif

