//  #include "HD_PLASTIC1.h"


#ifndef _HD_PLASTIC_H
#define _HD_PLASTIC_H

////////////////////////////////////////////////////////////////////
//extern GPIO_InitTypeDef GPIO_InitStructure2;

////////////////////////////////////////////////////////////////////
//ADC 脚选择 PC3 PC4 PC5  

//  TIM1 可能配置的脚是  PA8  
//  TIM3 配置的脚是 PA6,PA7,PB0,PB1  分别映射TIM3的 CH1,CH2,CH3,CH4
//  TIM4 配置的脚是 PB6 PB7 PB8 PB9  分别映射TIM4的 CH1,CH2,CH3,CH4

//  测试用的DAC脚是 PA4 

//  LED  PE0 PB5

//ADC 脚选择 PC3 PC4 PC5  ==   ADC13 ADC14 ADC15


//示波器同步信号SYNC
#define TestSyncPinTIM1_CLR  ;//TestSyncPin1_CLR
#define TestSyncPinTIM1_SET  ;//TestSyncPin1_SET;


#define TestSyncPinPwm_CLR  //LEDCOM1_0()//;//TestSyncPin1_CLR
#define TestSyncPinPwm_SET  //LEDCOM1_1()//;//TestSyncPin1_SET;    
//#define LEDCOM1_0()		GPIO_ResetBits(PORT_LEDCOM1, PIN_LEDCOM1)
//#define LEDCOM1_1()		GPIO_SetBits(PORT_LEDCOM1, PIN_LEDCOM1)    
    
    
    
#define TestSyncPinTIM3_CLR  ;//TestSyncPin1_CLR
#define TestSyncPinTIM3_SET  ;//TestSyncPin1_SET

#define TestSyncPinTIM4_CLR  ;//TestSyncPin1_CLR
#define TestSyncPinTIM4_SET  ;//TestSyncPin1_SET    





//加热1
#define    RCC_HEAT1    RCC_AHBPeriph_GPIOA
#define    PORT_HEAT1   GPIOA
#define    PIN_HEAT1    GPIO_Pin_11

//加热2
#define    RCC_HEAT2    RCC_AHBPeriph_GPIOA
#define    PORT_HEAT2   GPIOA
#define    PIN_HEAT2    GPIO_Pin_15


//方向继电器 1
#define    RCC_JSP1    RCC_APB2Periph_GPIOB
#define    PORT_JSP1   GPIOB
#define    PIN_JSP1    GPIO_Pin_0

//电源继电器 2
#define    RCC_JSP2    RCC_APB2Periph_GPIOB
#define    PORT_JSP2   GPIOB
#define    PIN_JSP2    GPIO_Pin_1

//发光管和键盘控制

#define    RCC_LEDCOM1    RCC_AHBPeriph_GPIOB
#define    PORT_LEDCOM1   GPIOB
#define    PIN_LEDCOM1    GPIO_Pin_3

#define    RCC_LEDCOM2    RCC_AHBPeriph_GPIOB
#define    PORT_LEDCOM2   GPIOB
#define    PIN_LEDCOM2    GPIO_Pin_4

#define    RCC_KIO1    RCC_AHBPeriph_GPIOB
#define    PORT_KIO1   GPIOB
#define    PIN_KIO1    GPIO_Pin_5
#define    RCC_KIO2    RCC_AHBPeriph_GPIOB
#define    PORT_KIO2   GPIOB
#define    PIN_KIO2    GPIO_Pin_6
#define    RCC_KIO3    RCC_AHBPeriph_GPIOB
#define    PORT_KIO3   GPIOB
#define    PIN_KIO3    GPIO_Pin_7

//SWCLK  PA14
#define    RCC_BackLight    RCC_AHBPeriph_GPIOA
#define    PORT_BackLight   GPIOA
#define    PIN_BackLight    GPIO_Pin_14


#define    BackLight_0()    GPIO_ResetBits(PORT_BackLight, PIN_BackLight)
#define    BackLight_1()		GPIO_SetBits(PORT_BackLight, PIN_BackLight)

#define HEAT1_0()   GPIO_ResetBits(PORT_HEAT1, PIN_HEAT1)
#define HEAT1_1()		GPIO_SetBits(PORT_HEAT1, PIN_HEAT1)
#define HEAT2_0()   GPIO_ResetBits(PORT_HEAT2, PIN_HEAT2)
#define HEAT2_1()		GPIO_SetBits(PORT_HEAT2, PIN_HEAT2)


#define JSP1_0()		GPIO_ResetBits(PORT_JSP1, PIN_JSP1)
#define JSP1_1()		GPIO_SetBits(PORT_JSP1, PIN_JSP1)
#define JSP2_0()		GPIO_ResetBits(PORT_JSP2, PIN_JSP2)
#define JSP2_1()		GPIO_SetBits(PORT_JSP2, PIN_JSP2)

#define LEDCOM1_0()		GPIO_ResetBits(PORT_LEDCOM1, PIN_LEDCOM1)
#define LEDCOM1_1()		GPIO_SetBits(PORT_LEDCOM1, PIN_LEDCOM1)
#define LEDCOM2_0()		GPIO_ResetBits(PORT_LEDCOM2, PIN_LEDCOM2)
#define LEDCOM2_1()		GPIO_SetBits(PORT_LEDCOM2, PIN_LEDCOM2)

//设置成输出，然后置值
#define KIO1_0()		GPIO_InitStructure2.GPIO_Speed =  GPIO_Speed_50MHz;   \
                    GPIO_InitStructure2.GPIO_Mode  =  GPIO_Mode_Out_PP;   \
                    GPIO_InitStructure2.GPIO_Pin = PIN_KIO1;              \
                    GPIO_Init(PORT_KIO1,&GPIO_InitStructure2);           \
                    GPIO_ResetBits(PORT_KIO1, PIN_KIO1)
                    
                    
#define KIO1_1()		GPIO_InitStructure2.GPIO_Speed =  GPIO_Speed_50MHz;   \
                    GPIO_InitStructure2.GPIO_Mode  =  GPIO_Mode_Out_PP;   \
                    GPIO_InitStructure2.GPIO_Pin = PIN_KIO1;              \
                    GPIO_Init(PORT_KIO1,&GPIO_InitStructure2);           \
                    GPIO_SetBits(PORT_KIO1, PIN_KIO1)
                    
#define KIO2_0()		GPIO_InitStructure2.GPIO_Speed =  GPIO_Speed_50MHz;   \
                    GPIO_InitStructure2.GPIO_Mode  =  GPIO_Mode_Out_PP;   \
                    GPIO_InitStructure2.GPIO_Pin = PIN_KIO2;              \
                    GPIO_Init(PORT_KIO2,&GPIO_InitStructure2);           \
                    GPIO_ResetBits(PORT_KIO2, PIN_KIO2)
                    
#define KIO2_1()		GPIO_InitStructure2.GPIO_Speed =  GPIO_Speed_50MHz;   \
                    GPIO_InitStructure2.GPIO_Mode  =  GPIO_Mode_Out_PP;   \
                    GPIO_InitStructure2.GPIO_Pin = PIN_KIO2;              \
                    GPIO_Init(PORT_KIO2,&GPIO_InitStructure2);           \
                    GPIO_SetBits(PORT_KIO2, PIN_KIO2)
                    
#define KIO3_0()		GPIO_InitStructure2.GPIO_Speed =  GPIO_Speed_50MHz;   \
                    GPIO_InitStructure2.GPIO_Mode  =  GPIO_Mode_Out_PP;   \
                    GPIO_InitStructure2.GPIO_Pin = PIN_KIO3;              \
                    GPIO_Init(PORT_KIO3,&GPIO_InitStructure2);           \
                    GPIO_ResetBits(PORT_KIO2, PIN_KIO3)
                    
#define KIO3_1()		GPIO_InitStructure2.GPIO_Speed =  GPIO_Speed_50MHz;   \
                    GPIO_InitStructure2.GPIO_Mode  =  GPIO_Mode_Out_PP;   \
                    GPIO_InitStructure2.GPIO_Pin = PIN_KIO3;              \
                    GPIO_Init(PORT_KIO3,&GPIO_InitStructure2);           \
                    GPIO_SetBits(PORT_KIO2, PIN_KIO3)

//设置为输入 
#define KIO1_In()		GPIO_InitStructure2.GPIO_Mode  =  GPIO_Mode_IN_FLOATING;     \
                    GPIO_InitStructure2.GPIO_Pin = PIN_KIO1;             \
                    GPIO_Init(PORT_KIO1,&GPIO_InitStructure2)       

#define KIO2_In()		GPIO_InitStructure2.GPIO_Mode  =  GPIO_Mode_IN_FLOATING;     \
                    GPIO_InitStructure2.GPIO_Pin = PIN_KIO2;             \
                    GPIO_Init(PORT_KIO2,&GPIO_InitStructure2)

#define KIO3_In()		GPIO_InitStructure2.GPIO_Mode  =  GPIO_Mode_IN_FLOATING;     \
                    GPIO_InitStructure2.GPIO_Pin = PIN_KIO3;            \
                    GPIO_Init(PORT_KIO3,&GPIO_InitStructure2)
                    
                  


#define LEDCOM1_IS_1()		  (GPIO_ReadInputDataBit(PORT_LEDCOM1, PIN_LEDCOM1) == Bit_SET)
#define LEDCOM1_IS_0()		  (GPIO_ReadInputDataBit(PORT_LEDCOM1, PIN_LEDCOM1) == Bit_RESET)
#define LEDCOM2_IS_1()		  (GPIO_ReadInputDataBit(PORT_LEDCOM2, PIN_LEDCOM2) == Bit_SET)
#define LEDCOM2_IS_0()		  (GPIO_ReadInputDataBit(PORT_LEDCOM2, PIN_LEDCOM2) == Bit_RESET)





////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

////I2C
//#define bSDA					(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9))
//#define SetbSDDA			GPIO_SetBits(GPIOE,GPIO_Pin_9)
//#define Clr_SDDA			GPIO_ResetBits(GPIOE,GPIO_Pin_9)
//#define SetbSCCL			GPIO_SetBits(GPIOE,GPIO_Pin_10)
//#define Clr_SCCL			GPIO_ResetBits(GPIOE,GPIO_Pin_10)


//I2C
//#define bSDA					(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7))
//#define SetbSDDA			GPIO_SetBits(GPIOB,GPIO_Pin_7)
//#define Clr_SDDA			GPIO_ResetBits(GPIOB,GPIO_Pin_7)
//#define SetbSCCL			GPIO_SetBits(GPIOB,GPIO_Pin_6)
//#define Clr_SCCL			GPIO_ResetBits(GPIOB,GPIO_Pin_6)

//#define ResetADC10			GPIO_ResetBits(GPIOC,GPIO_Pin_0)

//out
//PA2  TXD2      PWM通讯输出
//#define OUT_COMMUNICATION_VAL_CLR			GPIO_ResetBits(GPIOA,GPIO_Pin_A)
//#define OUT_COMMUNICATION_VAL_SET			GPIO_SetBits(GPIOA,GPIO_Pin_A)



//保护执行脉冲输出总开关
//#define OUT_PROTECT_CLR			GPIO_ResetBits(GPIOC,GPIO_Pin_9)
//#define OUT_PROTECT_SET			GPIO_SetBits(GPIOC,GPIO_Pin_9)

/*
#define OUT1_CLR			GPIO_ResetBits(GPIOC,GPIO_Pin_12)
#define OUT1_SET			GPIO_SetBits(GPIOC,GPIO_Pin_12)
#define OUT2_CLR			;//GPIO_ResetBits(GPIOD,GPIO_Pin_0)
#define OUT2_SET			;//GPIO_SetBits(GPIOD,GPIO_Pin_0)
#define OUT3_CLR			;//GPIO_ResetBits(GPIOD,GPIO_Pin_1)
#define OUT3_SET			;//GPIO_SetBits(GPIOD,GPIO_Pin_1)

#define OUT4_CLR			GPIO_ResetBits(GPIOE,GPIO_Pin_1)
#define OUT4_SET			GPIO_SetBits(GPIOE,GPIO_Pin_1)
#define OUT5_CLR			GPIO_ResetBits(GPIOE,GPIO_Pin_2)
#define OUT5_SET			GPIO_SetBits(GPIOE,GPIO_Pin_2)
#define OUT6_CLR			GPIO_ResetBits(GPIOE,GPIO_Pin_3)
#define OUT6_SET			GPIO_SetBits(GPIOE,GPIO_Pin_3)
#define OUT7_CLR			GPIO_ResetBits(GPIOE,GPIO_Pin_4)
#define OUT7_SET			GPIO_SetBits(GPIOE,GPIO_Pin_4)
#define OUT8_CLR			GPIO_ResetBits(GPIOE,GPIO_Pin_5)
#define OUT8_SET			GPIO_SetBits(GPIOE,GPIO_Pin_5)
*/



//示波器同步信号SYNC PCX
#define TestSyncPin1_CLR			GPIO_ResetBits(GPIOE,GPIO_Pin_X)
#define TestSyncPin1_SET			GPIO_SetBits(GPIOE,GPIO_Pin_X)


////#define JspOut3_OFF			GPIO_ResetBits(GPIOB,GPIO_Pin_11)
///#define JspOut3_ON			GPIO_SetBits(GPIOB,GPIO_Pin_11)



////////////////////////////////////////////////////

#define SetEn485_1    ;//GPIO_SetBits(GPIOA,GPIO_Pin_11)
#define ClrEn485_1    ;//GPIO_ResetBits(GPIOA,GPIO_Pin_11)

#define SetRecv485_1   ;//GPIO_SetBits(GPIOA,GPIO_Pin_12)
#define ClrRecv485_1   ;//GPIO_ResetBits(GPIOA,GPIO_Pin_12)


#define SetEn485_2    ;
#define ClrEn485_2    ;
#define SetEn485_3   ;// GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define ClrEn485_3   ;// GPIO_ResetBits(GPIOA,GPIO_Pin_1)
//#define SetEn485_4    ;
//#define ClrEn485_4    ;
//#define SetEn485_5    ;
//#define ClrEn485_5    ;


// %%%%%%%%%%%%%%%%%%%%%%%%%
//SPI1
#define CS_SPI1_SET 	GPIO_SetBits(GPIOA,GPIO_Pin_6)
#define CS_SPI1_CLR 	GPIO_ResetBits(GPIOA,GPIO_Pin_6)







//SYNC1输入 PC6 PA15  (TIM4_ETR = PE0) (TIM4_CH1 = PB6)
//#define SYNC_PIN6 (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6))
//#define SYNC_PIN15 (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15))
//
//
////SYNC2输入PC7 (TIM4_CH2 = PB7) (PE11 = ADC_ExternalTrigConv_Ext_IT11 ) ( pe15 = ADC_ExternalTrigInjecConv_Ext_IT15 )
//#define SYNC_PIN7 (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7))



//跟boot并联的按钮
#define K1_LVL	(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
#define K2_LVL	(1)



//键盘发光管接口输入输出转换设置   LedKeyProces()需要调用
void LedKeyPortReSet(unsigned char IsOutType);


void InitGpio(void);
//UART
////OS_VIEW_USART				     USART1
//TXD1  PA9





/*
#define CC1100_SCLK_ENABLE		;
#define CC1100_CSN_ENABLE			;
#define CC1100_SI_ENABLE			;
#define SET_CC1100_SO					;
#define SET_CC1100_GDO2				;
#define SET_CC1100_GDO0				;

#define SET_CC1100_CSN   		GPIO_SetBits(GPIOC,GPIO_Pin_1)
#define CLR_CC1100_CSN  		GPIO_ResetBits(GPIOC,GPIO_Pin_1)

#define SET_CC1100_SCLK  		GPIO_SetBits(GPIOC,GPIO_Pin_4)
#define CLR_CC1100_SCLK  		GPIO_ResetBits(GPIOC,GPIO_Pin_4)

#define SET_CC1100_SI    		GPIO_SetBits(GPIOC,GPIO_Pin_5)
#define CLR_CC1100_SI    		GPIO_ResetBits(GPIOC,GPIO_Pin_5)

#define CC1100_SO_LVL    (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3))
//RF_CE
//#define CC1100_GDO0_LVL
//RF_IRQ
#define CC1100_GDO2_LVL  (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))

*/
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)  ;


/**
  * @brief  Reads the specified GPIO output data port.
  * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
  * @retval GPIO output data port value.
  */
//uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);

///////////////////////////////////////////////////////////////////////


////////////////////////////////////
/**
  * @brief  Changes the mapping of the specified pin.
  * @param  GPIO_Remap: selects the pin to remap.
  *   This parameter can be one of the following values:
  *     @arg GPIO_Remap_SPI1             : SPI1 Alternate Function mapping
  *     @arg GPIO_Remap_I2C1             : I2C1 Alternate Function mapping
  *     @arg GPIO_Remap_USART1           : USART1 Alternate Function mapping
  *     @arg GPIO_Remap_USART2           : USART2 Alternate Function mapping
  *     @arg GPIO_PartialRemap_USART3    : USART3 Partial Alternate Function mapping
  *     @arg GPIO_FullRemap_USART3       : USART3 Full Alternate Function mapping
  *     @arg GPIO_PartialRemap_TIM1      : TIM1 Partial Alternate Function mapping
  *     @arg GPIO_FullRemap_TIM1         : TIM1 Full Alternate Function mapping
  *     @arg GPIO_PartialRemap1_TIM2     : TIM2 Partial1 Alternate Function mapping
  *     @arg GPIO_PartialRemap2_TIM2     : TIM2 Partial2 Alternate Function mapping
  *     @arg GPIO_FullRemap_TIM2         : TIM2 Full Alternate Function mapping
  *     @arg GPIO_PartialRemap_TIM3      : TIM3 Partial Alternate Function mapping
  *     @arg GPIO_FullRemap_TIM3         : TIM3 Full Alternate Function mapping
  *     @arg GPIO_Remap_TIM4             : TIM4 Alternate Function mapping
  *     @arg GPIO_Remap1_CAN1            : CAN1 Alternate Function mapping
  *     @arg GPIO_Remap2_CAN1            : CAN1 Alternate Function mapping
  *     @arg GPIO_Remap_PD01             : PD01 Alternate Function mapping
  *     @arg GPIO_Remap_TIM5CH4_LSI      : LSI connected to TIM5 Channel4 input capture for calibration
  *     @arg GPIO_Remap_ADC1_ETRGINJ     : ADC1 External Trigger Injected Conversion remapping
  *     @arg GPIO_Remap_ADC1_ETRGREG     : ADC1 External Trigger Regular Conversion remapping
  *     @arg GPIO_Remap_ADC2_ETRGINJ     : ADC2 External Trigger Injected Conversion remapping
  *     @arg GPIO_Remap_ADC2_ETRGREG     : ADC2 External Trigger Regular Conversion remapping
  *     @arg GPIO_Remap_ETH              : Ethernet remapping (only for Connectivity line devices)
  *     @arg GPIO_Remap_CAN2             : CAN2 remapping (only for Connectivity line devices)
  *     @arg GPIO_Remap_SWJ_NoJTRST      : Full SWJ Enabled (JTAG-DP + SW-DP) but without JTRST
  *     @arg GPIO_Remap_SWJ_JTAGDisable  : JTAG-DP Disabled and SW-DP Enabled
  *     @arg GPIO_Remap_SWJ_Disable      : Full SWJ Disabled (JTAG-DP + SW-DP)
  *     @arg GPIO_Remap_SPI3             : SPI3/I2S3 Alternate Function mapping (only for Connectivity line devices)
  *     @arg GPIO_Remap_TIM2ITR1_PTP_SOF : Ethernet PTP output or USB OTG SOF (Start of Frame) connected
  *                                        to TIM2 Internal Trigger 1 for calibration (only for Connectivity line devices)
  *                                        If the GPIO_Remap_TIM2ITR1_PTP_SOF is enabled the TIM2 ITR1 is connected to 
  *                                        Ethernet PTP output. When Reset TIM2 ITR1 is connected to USB OTG SOF output.    
  *     @arg GPIO_Remap_PTP_PPS          : Ethernet MAC PPS_PTS output on PB05 (only for Connectivity line devices)
  *     @arg GPIO_Remap_TIM15            : TIM15 Alternate Function mapping (only for Value line devices)
  *     @arg GPIO_Remap_TIM16            : TIM16 Alternate Function mapping (only for Value line devices)
  *     @arg GPIO_Remap_TIM17            : TIM17 Alternate Function mapping (only for Value line devices)
  *     @arg GPIO_Remap_CEC              : CEC Alternate Function mapping (only for Value line devices)
  *     @arg GPIO_Remap_TIM1_DMA         : TIM1 DMA requests mapping (only for Value line devices)
  *     @arg GPIO_Remap_TIM9             : TIM9 Alternate Function mapping (only for XL-density devices)
  *     @arg GPIO_Remap_TIM10            : TIM10 Alternate Function mapping (only for XL-density devices)
  *     @arg GPIO_Remap_TIM11            : TIM11 Alternate Function mapping (only for XL-density devices)
  *     @arg GPIO_Remap_TIM13            : TIM13 Alternate Function mapping (only for High density Value line and XL-density devices)
  *     @arg GPIO_Remap_TIM14            : TIM14 Alternate Function mapping (only for High density Value line and XL-density devices)
  *     @arg GPIO_Remap_FSMC_NADV        : FSMC_NADV Alternate Function mapping (only for High density Value line and XL-density devices)
  *     @arg GPIO_Remap_TIM67_DAC_DMA    : TIM6/TIM7 and DAC DMA requests remapping (only for High density Value line devices)
  *     @arg GPIO_Remap_TIM12            : TIM12 Alternate Function mapping (only for High density Value line devices)
  *     @arg GPIO_Remap_MISC             : Miscellaneous Remap (DMA2 Channel5 Position and DAC Trigger remapping, 
  *                                        only for High density Value line devices)     
  * @param  NewState: new state of the port pin remapping.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
//void GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState)  ;





#endif




