//	#include "adc.h"
#ifndef _ADC_H
#define _ADC_H

#define ADC1_DR_Address    ((uint32_t)0x4001244C)
#define ADC3_DR_Address    ((uint32_t)0x40013C4C)


#define  GET_ADC_NMB   (16-10)   //50               //ÿͨ����16��  16*6*160us  =  15.8mS
#define  MAX_ADC_CH  (6)               //Ϊ6��ͨ��



		extern __IO uint16_t  AD_Value[GET_ADC_NMB][MAX_ADC_CH];   //�������ADCת�������Ҳ��DMA��Ŀ���ַ
		extern __IO uint16_t  After_filter[MAX_ADC_CH];    //���������ƽ��ֵ֮��Ľ��
#if CONFIG_ADC		
		void ADC_Configuration(void);
		/////
		void AdcFilter(void);

#endif


#endif



