
/* Includes ------------------------------------------------------------------*/
#include "includes.h"
#include "stm32f10x.h"
#include "adc.h"

#if CONFIG_ADC

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup ADC_ExtLinesTrigger
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//#define ADC1_DR_Address    ((uint32_t)0x4001244C)
//#define ADC3_DR_Address    ((uint32_t)0x40013C4C)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ADC_InitTypeDef   ADC_InitStructure;
DMA_InitTypeDef   DMA_InitStructure;

//#define  GET_ADC_NMB   8               //每通道采50次
//#define  MAX_ADC_CH  5               //为5个通道
__IO uint16_t  AD_Value[GET_ADC_NMB][MAX_ADC_CH];   //用来存放ADC转换结果，也是DMA的目标地址
__IO uint16_t  After_filter[MAX_ADC_CH];    //用来存放求平均值之后的结果

//__IO uint16_t ADC_RegularConvertedValueTab[5*8+8], ADC_InjectedConvertedValueTab[32];

    
/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration_Adc(void);
void GPIO_Configuration_Adc(void);
//void NVIC_Configuration_Adc(void);

  
/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
void ADC_Configuration(void)
{
  /* System clocks configuration ---------------------------------------------*/
  RCC_Configuration_Adc();

  /* NVIC configuration ------------------------------------------------------*/
//  NVIC_Configuration_Adc();

  /* GPIO configuration ------------------------------------------------------*/
  GPIO_Configuration_Adc();

//ResetADC10;		//假ADC10 =0

  /* DMA1 channel1 configuration ----------------------------------------------*/
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = MAX_ADC_CH*GET_ADC_NMB;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//工作在循环缓存模式
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;//DMA通道 x拥有高优先级
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
  /* Enable DMA1 channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);
     
  /* ADC1 configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC工作模式:ADC1和ADC2工作在独立模式
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode =  ENABLE;//DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//ADC_ExternalTrigConv_Ext_IT11_TIM8_TRGO;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = MAX_ADC_CH;//顺序进行规则转换的ADC通道的数目
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channels configuration */ 
//  ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_28Cycles5);
//  ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 2, ADC_SampleTime_28Cycles5);
//  ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 3, ADC_SampleTime_28Cycles5);
//  ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 4, ADC_SampleTime_28Cycles5);//ADC_SampleTime_239Cycles5);
//  ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 5, ADC_SampleTime_28Cycles5);
//  ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 6, ADC_SampleTime_28Cycles5);

  //ADC_RegularChannelConfig(ADC1, ADC_Channel_11,   1, ADC_SampleTime_28Cycles5);		  //ADC11 
   
  ADC_RegularChannelConfig(ADC1, ADC_Channel_16,  1, ADC_SampleTime_239Cycles5);		      //ADC16  内部温度测量
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0,   2, ADC_SampleTime_239Cycles5);		      //ADC0   测速发电机电压
  ADC_RegularChannelConfig(ADC1, ADC_Channel_1,   3, ADC_SampleTime_239Cycles5);		      //ADC1   温度1 //ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_2,   4, ADC_SampleTime_239Cycles5); 	      //ADC2   温度2
  ADC_RegularChannelConfig(ADC1, ADC_Channel_3,   5, ADC_SampleTime_239Cycles5);		      //ADC3   输出电流
  ADC_RegularChannelConfig(ADC1, ADC_Channel_4,   6, ADC_SampleTime_239Cycles5);		      //ADC4   输出电压  

//ADC_SampleTime_13Cycles5  400次大约4-7mS   10us/次
//ADC_SampleTime_28Cycles5  400次大约8-12mS   20us/次
//ADC_SampleTime_239Cycles5  400次大约64-68mS   160us/次


   /*
  //间断模式
  //Regular discontinuous mode channel number configuration
  ADC_DiscModeChannelCountConfig(ADC1, 1);
  //Enable regular discontinuous mode 
  ADC_DiscModeCmd(ADC1, ENABLE);
  */


  /* Enable ADC1 external trigger conversion */ 
//  ADC_ExternalTrigConvCmd(ADC1, ENABLE);


#if 0
  /* Set injected sequencer length */
  ADC_InjectedSequencerLengthConfig(ADC1, 2);
  /* ADC1 injected channel configuration */ 
  ADC_InjectedChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_28Cycles5);
  ADC_InjectedChannelConfig(ADC1, ADC_Channel_12, 2, ADC_SampleTime_28Cycles5);
  /* ADC1 injected external trigger configuration */
  ADC_ExternalTrigInjectedConvConfig(ADC1, ADC_ExternalTrigInjecConv_Ext_IT15_TIM8_CC4);
  /* Enable ADC1 injected external trigger conversion */
  ADC_ExternalTrigInjectedConvCmd(ADC1, ENABLE);

  /* Enable JEOC interupt */
  ADC_ITConfig(ADC1, ADC_IT_JEOC, ENABLE);

#endif

  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);
  
  //内部温度传感器
  ADC_TempSensorVrefintCmd(ENABLE);  
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);  

  /* Enable ADC1 reset calibaration register */   
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));

  /* Start ADC1 calibaration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));
/////////////////////////////////////////////////////
                         
                         
    /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);                       
    
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration_Adc(void)
{
    /* ADCCLK = PCLK2/4 */
    RCC_ADCCLKConfig(RCC_PCLK2_Div8); 

/* Enable peripheral clocks --------------------------------------------------*/   
  /* Enable DMA1 clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  /* Enable GPIOs and ADC1 clock */

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | 
                         RCC_APB2Periph_AFIO |		//功能复用IO时钟
                         RCC_APB2Periph_ADC1, ENABLE); 
}


/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
//选用ADC的通道0  1  2  8  9  10  11  12  13  14  15，
//分别对应的管脚为PA0  PA1  PA2  PB0  PB1  PC0  PC1  PC2  PC3  PC4  PC5
void GPIO_Configuration_Adc(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure PA.00,PA.01,PA.02,PA.03 (ADC Channe0 Channe1 Channe2 Channel3) as analog input -----------------------------------------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  
  /* Configure PC.00 - PC.05 (ADC Channe10-Channe15) as analog input --------------------------*/
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//  GPIO_Init(GPIOC, &GPIO_InitStructure);


}

/**
  * @brief  Configures NVIC and Vector Table base location.
  * @param  None
  * @retval None
  */
//void NVIC_Configuration_Adc(void)
//{
//  NVIC_InitTypeDef NVIC_InitStructure;
//
//  /* Configure and enable ADC interrupt */
//  NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
//}


/////
void AdcFilter(void)
{
//	#define  GET_ADC_NMB   8               //每通道采50次
//#define  MAX_ADC_CH  5               //为5个通道
//__IO uint16_t  AD_Value[GET_ADC_NMB][MAX_ADC_CH];   //用来存放ADC转换结果，也是DMA的目标地址
//__IO uint16_t  After_filter[MAX_ADC_CH];    //用来存放求平均值之后的结果


unsigned long int sum;	//32
unsigned char i,j;


		for(i=0;i<MAX_ADC_CH;i++)
		{
			sum=0;
			
			for(j=0;j<GET_ADC_NMB;j++)
					{
						sum	+= AD_Value[j][i];
						
					}
		After_filter[i]=sum/GET_ADC_NMB;	

		}

	
}

#endif

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/



