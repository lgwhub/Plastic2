#ifndef _CONFIG_H
#define _CONFIG_H

////////选择看门狗//////
#define EnWdog 				0

#define SOFT_VER   14



#define CONFIG_CLEAR_ERR     0

//为方便调试不要EEPROM
#define SOFT_CONFIG_EEPROM   0

#define  CONFIG_SPI1   1
#define  CONFIG_SPI2   0
#define  CONFIG_ADC		         (1)
#define  CONFIG_DAC		         0
#define  CONFIG_CAPTURE_TIM3   0

#define  CONFIG_PWM_TIM1		1
#define  CONFIG_PWM_TIM3		0
#define  CONFIG_PWM_TIM4		(0)




#define  CONFIG_EXTI		0


#define USART1_REMAP						0
#define SWD_DEBUG_DISABLE				0



#define ENABLE_SWITCH_OFF_DEBUG  1

#define ENABLE_TEST_MOD          1

//数字移相控制
#define CONFIG_RPM_DIGTAL        0


/**************************************************************************************************/



#endif




