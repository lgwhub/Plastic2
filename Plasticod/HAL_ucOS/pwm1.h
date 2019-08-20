    
//	#include "pwm1.h"

#ifndef	_PWM_H_
#define	_PWM_H_



//脉宽控制最大值，留死区
//#define   MAX_PWM_VAL    (PWM_PERIOD_PULSE*90/100)
//#define   MAX_PWM_VAL    (PWM_PERIOD_PULSE)



extern unsigned int PmwVal_TIM1_ch1;
//脉宽控制周期脉冲数，脉宽值最大不能超过1000



//TIM_SetCompare1(TIM1, PmwVal_TIM1_ch1);

//#if CONFIG_PWM_TIM1    
void NVIC_Configuration_PWM_T1(void);
void PWM_T1_Configuration(void);  
void GPIO_Configuration_PWM_T1(void);
//#endif



#endif

