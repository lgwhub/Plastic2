    
//	#include "pwm.h"

#ifndef	_PWM_H_
#define	_PWM_H_



//#define PWM_FREQ_x_KHZ    180
//#define PWM_PERIOD_PULSE   ( 72000/2/(PWM_FREQ_x_KHZ ) )


//����������ֵ��������
//#define   MAX_PWM_VAL    (PWM_PERIOD_PULSE*90/100)
//#define   MAX_PWM_VAL    (PWM_PERIOD_PULSE)



//PmwVal_TIM1_ch1
//#define DEFAULT_PWM_VAL5 (500*PWM_PERIOD_PULSE/1000);
//�����������������������ֵ����ܳ�����ֵ��Ҳ��Ӱ������ķֱ��ʣ����Ƶ��=72M/2000/2  =18KHZ

extern unsigned int PmwVal_TIM1_ch1;



//TIM1��ʱ��Ƶ��6KHZ,����UP1...��С��ѹ������4V����ȫ����ѹ��·
//#define PWM_T1_PERIOD_PULSE  (36000/6)



#if CONFIG_PWM_TIM1    
void NVIC_Configuration_PWM_T1(void);
void PWM_T1_Configuration(void);  
void GPIO_Configuration_PWM_T1(void);
#endif



// #if  CONFIG_PWM_TWO_SYNS == 0
//void SetPwmVar(void);	 
//#endif

#endif

