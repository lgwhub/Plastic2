     
//    #include <includes.h>
#include "stm32f0xx.h"
#include "stdio.h"
#include "config.h"
#include "HD_PLASTIC1.h"
#include "LoopBuf.h"
//#include "uart.h"
//#include "FreeRTOS.h"
//#include "task.h" 
//#include "stm32f0xx_misc.h"


//#define SWD_DEBUG_DISABLE  0
#define USART1_REMAP       0
//#define CONFIG_UART1       1

#define DBGMCU_CR    (*((volatile unsigned long *)0xE0042004))    //在顶部加上宏定义	     

GPIO_InitTypeDef GPIO_InitStructure2;


//IO统计
//方向继电器             2
//移相                   1
//不用移相               1+1
//温度测量AD             1+1
//交流电测量AD           1+1
//同步输入               1
//按键                   6
//lcd                    3
//背光                   1
//串口                   2


////加热1
//#define    RCC_HEAT1    RCC_AHBPeriph_GPIOA
//#define    PORT_HEAT1   GPIOA
//#define    PIN_HEAT1    GPIO_Pin_11
//
////加热2
//#define    RCC_HEAT2    RCC_AHBPeriph_GPIOA
//#define    PORT_HEAT2   GPIOA
//#define    PIN_HEAT2    GPIO_Pin_15
//
//
////方向继电器 1
//#define    RCC_JSP1    RCC_AHBPeriph_GPIOB
//#define    PORT_JSP1   GPIOB
//#define    PIN_JSP1    GPIO_Pin_0
//
////电源继电器 2
//#define    RCC_JSP2    RCC_AHBPeriph_GPIOB
//#define    PORT_JSP2   GPIOB
//#define    PIN_JSP2    GPIO_Pin_1
//
////发光管和键盘控制
//
//#define    RCC_LEDCOM1    RCC_AHBPeriph_GPIOB
//#define    PORT_LEDCOM1   GPIOB
//#define    PIN_LEDCOM1    GPIO_Pin_3
//
//#define    RCC_LEDCOM2    RCC_AHBPeriph_GPIOB
//#define    PORT_LEDCOM2   GPIOB
//#define    PIN_LEDCOM2    GPIO_Pin_4
//
//#define    RCC_KIO1    RCC_AHBPeriph_GPIOB
//#define    PORT_KIO1   GPIOB
//#define    PIN_KIO1    GPIO_Pin_5
//#define    RCC_KIO2    RCC_AHBPeriph_GPIOB
//#define    PORT_KIO2   GPIOB
//#define    PIN_KIO2    GPIO_Pin_6
//#define    RCC_KIO3    RCC_AHBPeriph_GPIOB
//#define    PORT_KIO3   GPIOB
//#define    PIN_KIO3    GPIO_Pin_7
//
//
//
//#define HEAT1_0()   GPIO_ResetBits(PORT_HEAT1, PIN_HEAT1)
//#define HEAT1_1()		GPIO_SetBits(PORT_HEAT1, PIN_HEAT1)
//#define HEAT2_0()   GPIO_ResetBits(PORT_HEAT2, PIN_HEAT2)
//#define HEAT2_1()		GPIO_SetBits(PORT_HEAT2, PIN_HEAT2)
//
//
//#define JSP1_0()		GPIO_ResetBits(PORT_JSP1, PIN_JSP1)
//#define JSP1_1()		GPIO_SetBits(PORT_JSP1, PIN_JSP1)

//#define JSP2_0()		GPIO_ResetBits(PORT_JSP2, PIN_JSP2)
//#define JSP2_1()		GPIO_SetBits(PORT_JSP2, PIN_JSP2)

//#define LEDCOM1_0()		GPIO_ResetBits(PORT_LEDCOM1, PIN_LEDCOM1)
//#define LEDCOM1_1()		GPIO_SetBits(PORT_LEDCOM1, PIN_LEDCOM1)
//#define LEDCOM2_0()		GPIO_ResetBits(PORT_LEDCOM2, PIN_LEDCOM2)
//#define LEDCOM2_1()		GPIO_SetBits(PORT_LEDCOM2, PIN_LEDCOM2)
//#define KIO1_0()		GPIO_ResetBits(PORT_KIO1, PIN_KIO1)
//#define KIO1_1()		GPIO_SetBits(PORT_KIO1, PIN_KIO1)
//#define KIO2_0()		GPIO_ResetBits(PORT_KIO2, PIN_KIO2)
//#define KIO2_1()		GPIO_SetBits(PORT_KIO2, PIN_KIO2)
//#define KIO3_0()		GPIO_ResetBits(PORT_KIO2, PIN_KIO3)
//#define KIO3_1()		GPIO_SetBits(PORT_KIO2, PIN_KIO3)


#define DO_IS_HIGH()	(GPIO_ReadInputDataBit(PORT_DOUT, PIN_DOUT) == Bit_SET)

#define DRDY_IS_LOW()	(GPIO_ReadInputDataBit(PORT_DRDY, PIN_DRDY) == Bit_RESET)







//键盘发光管接口输入输出转换设置   LedKeyProces()需要调用
void LedKeyPortReSet(unsigned char IsOutType)
{
 
 GPIO_InitTypeDef GPIO_InitStructure;
  

	//RCC_AHBPeriphClockCmd(RCC_AHB2Periph_GPIOA, ENABLE);

if( IsOutType != 0 )
	{

 //部分输出口
 GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_Out_PP;  //GPIO_Mode_IN_FLOATING;//	GPIO_Mode_Out_OD;
 
 GPIO_InitStructure.GPIO_Pin = PIN_LEDCOM1;
 GPIO_Init(PORT_LEDCOM1,&GPIO_InitStructure);
 
 GPIO_InitStructure.GPIO_Pin = PIN_LEDCOM2;
 GPIO_Init(PORT_LEDCOM2,&GPIO_InitStructure); 
 
 GPIO_InitStructure.GPIO_Pin = PIN_KIO1;
 GPIO_Init(PORT_KIO1,&GPIO_InitStructure); 
 
 GPIO_InitStructure.GPIO_Pin = PIN_KIO2;
 GPIO_Init(PORT_KIO2,&GPIO_InitStructure); 
 
 GPIO_InitStructure.GPIO_Pin = PIN_KIO3;
 GPIO_Init(PORT_KIO3,&GPIO_InitStructure); 
  
  }
 else{
  //部分改为输入口
 
   GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_IPU;  //GPIO_Mode_IPD;  //GPIO_Mode_IN_FLOATING;// 

//   GPIO_InitStructure.GPIO_Pin = PIN_KIO1;
//   GPIO_Init(PORT_KIO1,&GPIO_InitStructure); 
// 
//   GPIO_InitStructure.GPIO_Pin = PIN_KIO2;
//   GPIO_Init(PORT_KIO2,&GPIO_InitStructure); 
// 
//   GPIO_InitStructure.GPIO_Pin = PIN_KIO3;
//   GPIO_Init(PORT_KIO3,&GPIO_InitStructure); 
 
   GPIO_InitStructure.GPIO_Pin = PIN_LEDCOM1;
   GPIO_Init(PORT_LEDCOM1,&GPIO_InitStructure);
 
   GPIO_InitStructure.GPIO_Pin = PIN_LEDCOM2;
   GPIO_Init(PORT_LEDCOM2,&GPIO_InitStructure); 
   }
}
/////////////////////////

void InitGpio(void)
{

  GPIO_InitTypeDef GPIO_InitStructure;
  
  //关所有输出
 GPIO_SetBits(GPIOA,GPIO_Pin_All);
//	GPIO_SetBits(GPIOB,GPIO_Pin_All); 
//	GPIO_SetBits(GPIOC,GPIO_Pin_All);	 
 // GPIO_SetBits(GPIOD,GPIO_Pin_All);
//	GPIO_SetBits(GPIOE,GPIO_Pin_All);

 ////////  GPIO  PA  //////////////////
  //////JTAG_REMAP
    	//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    	//	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA,ENABLE);
	//开启串口1和GPIOA的时钟
	RCC_AHBPeriphClockCmd(RCC_JSP1 | RCC_JSP2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);


  #if SWD_DEBUG_DISABLE
 				GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);     //SWD口和jtag口全部都取消  Full SWJ Disabled (JTAG-DP + SW-DP)
  #else


 //    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);     //只取消JTAG口，保留SWD口，SWDIO = PA13  SWCLK = PA14
	  
	  
     
 //    DBGMCU_CR &= 0xFFFFFFDF;		//禁止异步跟踪，释放PB3   //#define DBGMCU_CR    (*((volatile unsigned long *)0xE0042004))    //在顶部加上宏定义	     

  #endif  	
   
 
 
 // PA2->TXD2,PA9->TXD1
 			//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_9;
 			GPIO_InitStructure.GPIO_Pin   =  GPIO_Pin_9;
 			GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
 			GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_AF;//GPIO_Mode_AF_PP;
 			GPIO_InitStructure.GPIO_OType =  GPIO_OType_PP;
 			GPIO_InitStructure.GPIO_PuPd  =  GPIO_PuPd_NOPULL;
	    GPIO_Init(GPIOA, &GPIO_InitStructure);
	  
  
 //输入,PA3->RXD2,PA10->RXD1

 //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_10; 
 GPIO_InitStructure.GPIO_Pin   =  GPIO_Pin_10;  
 GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_IN;//GPIO_Mode_IPU;  //GPIO_Mode_IN_FLOATING;	
 GPIO_InitStructure.GPIO_PuPd  =  GPIO_PuPd_UP;//GPIO_PuPd_NOPULL;
 
 
 GPIO_Init(GPIOA,&GPIO_InitStructure);
 
 
  //部分输出口
 
 GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_OUT;  //GPIO_Mode_Out_PP;  //GPIO_Mode_IN_FLOATING;	
 GPIO_InitStructure.GPIO_OType =  GPIO_OType_PP;
 
 GPIO_InitStructure.GPIO_Pin = PIN_HEAT1;
 GPIO_Init(PORT_HEAT1,&GPIO_InitStructure);
 
 GPIO_InitStructure.GPIO_Pin = PIN_HEAT2;
 GPIO_Init(PORT_HEAT2,&GPIO_InitStructure);
 
 GPIO_InitStructure.GPIO_Pin = PIN_JSP1;
 GPIO_Init(PORT_JSP1,&GPIO_InitStructure);
 
 GPIO_InitStructure.GPIO_Pin = PIN_JSP2;
 GPIO_Init(PORT_JSP2,&GPIO_InitStructure);


 //////////////////////
 GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_OUT;  //GPIO_Mode_Out_PP;  //GPIO_Mode_IN_FLOATING;	
 GPIO_InitStructure.GPIO_OType =  GPIO_OType_OD;
 
 GPIO_InitStructure.GPIO_Pin = PIN_LEDCOM1;
 GPIO_Init(PORT_LEDCOM1,&GPIO_InitStructure);
 
 GPIO_InitStructure.GPIO_Pin = PIN_LEDCOM2;
 GPIO_Init(PORT_LEDCOM2,&GPIO_InitStructure); 
 
 
 
 //PA4      DAC
//  GPIO_InitStructure.GPIO_Pin   =  GPIO_Pin_4;
//  GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_AN;//GPIO_Mode_AIN;
//  GPIO_InitStructure.GPIO_PuPd  =  GPIO_PuPd_NOPULL;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
 
 ////////  GPIO  PB  ////////////////// 
/*
 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB,ENABLE); 
  //PB7 PB8 PB9 普通输出口,		LED1 ->PB6  LED2 ->PB5  是指示灯PB10->TXD3
  

  #if USART1_REMAP

 // GPIO_Pin_6 , GPIO_Pin_7 映射UART1
  #else
  //GPIO_Pin_6 , GPIO_Pin_7 普通口
 //GPIO_InitStructure.GPIO_Pin =GPIO_Pin_6 | GPIO_Pin_7;
 #endif
 
 //I2C  PB6 -> SCL , PB7 -> SDA

// GPIO_InitStructure.GPIO_Pin =GPIO_Pin_6;
// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;//GPIO_Mode_Out_PP;
// GPIO_Init(GPIOB,&GPIO_InitStructure);
//  
// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;//GPIO_Mode_Out_PP;
//GPIO_Init(GPIOB,&GPIO_InitStructure);

 //PB0-PB1->ADIN,PB2->BOOT1
//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//GPIO_Init(GPIOB,&GPIO_InitStructure);

//PB10 TXD3
 GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 ;//
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
 GPIO_Init(GPIOB,&GPIO_InitStructure);
 
//PB11 RXD3 输入;
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//GPIO_Mode_IPU;
GPIO_Init(GPIOB,&GPIO_InitStructure);  

//    PB1开关输入;
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
GPIO_Init(GPIOB,&GPIO_InitStructure);
  
  
//LED2 = NPB5      AD7705_CS = PB12
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_12;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 GPIO_Init(GPIOB,&GPIO_InitStructure);  
  
  
  // AD7705_SCK = PB13  AD7705_MOSI = PB15 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  
   // AD7705_MISO = PB14 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;;//GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  
  
  
//I2C
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	//GPIO_Mode_IPU;	//GPIO_Mode_IN_FLOATING;GPIO_Mode_Out_PP;
 GPIO_Init(GPIOB,&GPIO_InitStructure);	  
  

 ////////  GPIO  PC  //////////////////

 
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
//  //PC0-PC5->ADIN, 
// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
// GPIO_Init(GPIOC,&GPIO_InitStructure);

// PC6 PC7 PC8 PC9输出,PC12输出
// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 |  GPIO_Pin_12;
// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
// GPIO_Init(GPIOC,&GPIO_InitStructure);
 
 // PC 输出
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10  |  GPIO_Pin_13;
 
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//GPIO_Mode_AF_PP;
 GPIO_Init(GPIOC,&GPIO_InitStructure);
 
// pc2 温度报警  PC11 RXD4输入  pc6 pc7 PC8 PC9 拨码开关输入   AD7705_DRDY = PC14
  GPIO_InitStructure.GPIO_Pin =    GPIO_Pin_2 |  GPIO_Pin_6 |  GPIO_Pin_7 |  GPIO_Pin_8 |  GPIO_Pin_9 |  GPIO_Pin_11 |  GPIO_Pin_14;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 GPIO_Init(GPIOC,&GPIO_InitStructure);
 
 
 
 
  ////////  GPIO  PD  //////////////////
  
   RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD,ENABLE); 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
 GPIO_Init(GPIOD,&GPIO_InitStructure);	
 // PD0 PD1 PD2 RXD5输入
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//GPIO_Mode_IPU;
 GPIO_Init(GPIOD,&GPIO_InitStructure);	
 
  ////////  GPIO  PE  //////////////////	
  
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE,ENABLE); 
//  //LED4
// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_14;
// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//GPIO_Mode_Out_OD;	//GPIO_Mode_IPU;	//GPIO_Mode_IN_FLOATING;GPIO_Mode_Out_PP;
// GPIO_Init(GPIOE,&GPIO_InitStructure);	
////
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_11 | GPIO_Pin_15 ;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//GPIO_Mode_IN_FLOATING;GPIO_Mode_Out_PP;
 GPIO_Init(GPIOE,&GPIO_InitStructure);	  
 */
 
 //I2C
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_9;
// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	//GPIO_Mode_IPU;	//GPIO_Mode_IN_FLOATING;GPIO_Mode_Out_PP;
// GPIO_Init(GPIOE,&GPIO_InitStructure);	

//  
//  
//  #if CONFIG_TEST_LED_BLINK	
//	//////////////////// PE0 ///////////////////////////////
////	   GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0;
//// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//GPIO_Mode_IN_FLOATING;GPIO_Mode_Out_PP;
//// GPIO_Init(GPIOE,&GPIO_InitStructure);
//	////////////////////////////////////////////////////
//	#endif
}


#if CONFIG_UART1
void  USART1_TxIntEn (void)
{
    USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
    USART_ITConfig(USART1, USART_IT_TC, ENABLE);	//485
}
#endif

#if CONFIG_UART2
void  USART2_TxIntEn (void)
{
    USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
    USART_ITConfig(USART2, USART_IT_TC, ENABLE);	//485
}
#endif

#if CONFIG_UART3
void  USART3_TxIntEn (void)
{
    USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
    USART_ITConfig(USART3, USART_IT_TC, ENABLE);	//485
}
#endif

//
//#if CONFIG_UART4
//void  UART4_TxIntEn (void)
//{
//    USART_ITConfig(UART4, USART_IT_TXE, ENABLE);
//   USART_ITConfig(UART4, USART_IT_TC, ENABLE);	//485
//}
//#endif
// 
// 
//
//#if CONFIG_UART5
//void  UART5_TxIntEn (void)
//{
//    USART_ITConfig(UART5, USART_IT_TXE, ENABLE);
//   USART_ITConfig(UART5, USART_IT_TC, ENABLE);	//485
//}
//#endif    
     
/////#if (OS_VIEW_USART == USART1)    

//USART_Parity_No
//USART_Parity_Even
//USART_Parity_Odd
//void InitUSART1(INT32U baud_rate,uint16_t parity)
void InitUSART1(unsigned long int baud_rate,uint16_t parity)
{
    
//    GPIO_InitTypeDef        GPIO_InitStructure;
    USART_InitTypeDef       USART_InitStructure;
    NVIC_InitTypeDef        NVIC_InitStructure;	

	//开启串口1和GPIOA的时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  //  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//
//    /* Configure USARTx_Tx as alternate function push-pull */
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//    /* Configure USARTx_Rx as input floating */
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  
//    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate            = baud_rate;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;
    USART_InitStructure.USART_Parity              = parity;		//USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);

    /* Configure the NVIC Preemption Priority Bits */  
    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
    /* Enable the USARTy Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  //???    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    /////////////////////////////////////
    #if USART1_REMAP
    	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
//
    /* Configure USARTx_Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;			
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* Configure USARTx_Rx as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    
    
    GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);
    #endif
    
  #if CONFIG_UART1  
// 	#if   ( OS_VIEW_MODULE != DEF_ENABLED )|| (OS_VIEW_USART_NUMBER != 1)   
   // Uart1BufInit();
    USART1_TxIntEn();
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//#endif    
  #endif 
  
 ClrEn485_1    ;
 ClrRecv485_1   ;
  
  }

/////////////////////////////////////////////////
/*
void InitUSART2(INT32U baud_rate,uint16_t parity)
{
	USART_InitTypeDef		USART_InitStructure;
	NVIC_InitTypeDef		NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	USART_InitStructure.USART_BaudRate 									=	baud_rate;
	USART_InitStructure.USART_WordLength 					=	USART_WordLength_8b;
	USART_InitStructure.USART_StopBits 						=	USART_StopBits_1;
	USART_InitStructure.USART_Parity 							=	parity;
	USART_InitStructure.USART_HardwareFlowControl	=	USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode								=	USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2,&USART_InitStructure);
	USART_Cmd(USART2,ENABLE);
	
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel						=	USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority	=	3;
	NVIC_InitStructure.NVIC_IRQChannelCmd	=	ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	#if CONFIG_UART2
	#if   ( OS_VIEW_MODULE != DEF_ENABLED )|| (OS_VIEW_USART_NUMBER != 2)   
		  Uart2BufInit();
    USART2_TxIntEn();
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
		#endif 
	#endif
}


/////////////////////////////////////////////////

void InitUSART3(INT32U baud_rate,uint16_t parity)
{
	USART_InitTypeDef		USART_InitStructure;
	NVIC_InitTypeDef		NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	
	USART_InitStructure.USART_BaudRate 									=	baud_rate;
	USART_InitStructure.USART_WordLength 					=	USART_WordLength_8b;
	USART_InitStructure.USART_StopBits 						=	USART_StopBits_1;
	USART_InitStructure.USART_Parity 							=	parity;
	USART_InitStructure.USART_HardwareFlowControl	=	USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode								=	USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3,&USART_InitStructure);
	USART_Cmd(USART3,ENABLE);
	
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel						=	USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority	=	3;
	NVIC_InitStructure.NVIC_IRQChannelCmd	=	ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	#if CONFIG_UART3
	#if   ( OS_VIEW_MODULE != DEF_ENABLED )|| (OS_VIEW_USART_NUMBER != 3)	
		Uart3BufInit();
    USART3_TxIntEn();
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	#endif
	#endif
}
*/
///////////////////////////////////////////////////
//
//void InitUART4(INT32U baud_rate,uint16_t parity)
//{
//	USART_InitTypeDef		USART_InitStructure;
//	NVIC_InitTypeDef		NVIC_InitStructure;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
//	
//	USART_InitStructure.USART_BaudRate 									=	baud_rate;
//	USART_InitStructure.USART_WordLength 					=	USART_WordLength_8b;
//	USART_InitStructure.USART_StopBits 						=	USART_StopBits_1;
//	USART_InitStructure.USART_Parity 							=	parity;
//	USART_InitStructure.USART_HardwareFlowControl	=	USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode								=	USART_Mode_Rx | USART_Mode_Tx;
//	USART_Init(UART4,&USART_InitStructure);
//	USART_Cmd(UART4,ENABLE);
//	
////	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//	NVIC_InitStructure.NVIC_IRQChannel						=	UART4_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority	=	3;
//	NVIC_InitStructure.NVIC_IRQChannelCmd	=	ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//	#if CONFIG_UART4
//			#if   ( OS_VIEW_MODULE != DEF_ENABLED )|| (OS_VIEW_USART_NUMBER != 4)	
//					Uart4BufInit();
//		    UART4_TxIntEn();
//		    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
//			#endif
//
//	#endif	
//}
//
//
///////////////////////////////////////////////////
//void InitUART5(INT32U baud_rate,uint16_t parity)
//{
//	USART_InitTypeDef		USART_InitStructure;
//	NVIC_InitTypeDef		NVIC_InitStructure;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);
//	
//	USART_InitStructure.USART_BaudRate 									=	baud_rate;
//	USART_InitStructure.USART_WordLength 					=	USART_WordLength_8b;
//	USART_InitStructure.USART_StopBits 						=	USART_StopBits_1;
//	USART_InitStructure.USART_Parity 							=	parity;
//	USART_InitStructure.USART_HardwareFlowControl	=	USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode								=	USART_Mode_Rx | USART_Mode_Tx;
//	USART_Init(UART5,&USART_InitStructure);
//	USART_Cmd(UART5,ENABLE);
//	
////	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//	NVIC_InitStructure.NVIC_IRQChannel						=	UART5_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority	=	3;
//	NVIC_InitStructure.NVIC_IRQChannelCmd	=	ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//	
//	#if   ( OS_VIEW_MODULE != DEF_ENABLED )|| (OS_VIEW_USART_NUMBER != 5)	
//			
//			#if CONFIG_UART5
//		Uart5BufInit();
//    UART5_TxIntEn();
//    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
//		#endif
//
//	#endif	
//}

//////////////////////////////
#if CONFIG_UART1
void  USART1_RxTxISRHandler (void)
{
   // CPU_SR          cpu_sr;
		unsigned char temp;

    //CPU_CRITICAL_ENTER();                                       /* Tell uC/OS-II that we are starting an ISR            */
    //OSIntNesting++;
    //CPU_CRITICAL_EXIT();


    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
    	//ModbusRxISRHandler(USART_ReceiveData(USART1)&0xFF);				
				AddLoopBuf(&Uart1RecvStruct,Uart1RecvBuf,UART1_RECV_BUF_SIZE,USART_ReceiveData(USART1)&0xFF);
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);          /* Clear the USART Receive interrupt                   */
    }

    if (USART_GetITStatus(USART1, USART_IT_TXE) != RESET) {
    		if (0 == Uart1SendStruct.len)
				     			{
				     			Uart1Sending = 0;	
				     			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
				     			}
							else{
									SetEn485_1;
									SetRecv485_1;									
									GetLoopbuf(&Uart1SendStruct,Uart1SendBuf,UART1_SEND_BUF_SIZE,&temp);
        					USART_SendData(USART1, temp);
        					}
   //     USART_ClearITPendingBit(USART1, USART_IT_TXE);           /* Clear the USART transmit interrupt                  */
				
    }

			//485
    if (USART_GetITStatus(USART1, USART_IT_TC) != RESET) {
        //OSView_TxHandler();
				ClrEn485_1;
				ClrRecv485_1;
        USART_ClearITPendingBit(USART1, USART_IT_TC);           /* Clear the USART transmit interrupt                  */

    }


    //OSIntExit();                                                /* Tell uC/OS-II that we are leaving the ISR            */
}
#endif
//////////////////////////////
#if CONFIG_UART2
void  USART2_RxTxISRHandler (void)
{
    CPU_SR          cpu_sr;
		unsigned char temp;
    CPU_CRITICAL_ENTER();                                       /* Tell uC/OS-II that we are starting an ISR            */
    OSIntNesting++;
    CPU_CRITICAL_EXIT();


    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
                      /* Read one byte from the receive data register         */
        AddLoopBuf(&Uart2RecvStruct,Uart2RecvBuf,UART2_RECV_BUF_SIZE,USART_ReceiveData(USART2)&0xFF);
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);          /* Clear the USART Receive interrupt                   */

    }

    if (USART_GetITStatus(USART2, USART_IT_TXE) != RESET) {
    		if (0 == Uart2SendStruct.len)
				     			{
				     			Uart2Sending = 0;	
				     			USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
				     			}
							else{
											SetEn485_2;
											GetLoopbuf(&Uart2SendStruct,Uart2SendBuf,UART2_SEND_BUF_SIZE,&temp);
        							USART_SendData(USART2, temp);
      						}
        //USART_ClearITPendingBit(USART2, USART_IT_TXE);           /* Clear the USART transmit interrupt                  */

    }

			//485
    if (USART_GetITStatus(USART2, USART_IT_TC) != RESET) {
			ClrEn485_2;
        USART_ClearITPendingBit(USART2, USART_IT_TC);           /* Clear the USART transmit interrupt                  */

    }


    OSIntExit();                                                /* Tell uC/OS-II that we are leaving the ISR            */
}
#endif
//////////////////////////////
#if CONFIG_UART3
void  USART3_RxTxISRHandler (void)
{
    CPU_SR          cpu_sr;
		unsigned char temp;
    CPU_CRITICAL_ENTER();                                       /* Tell uC/OS-II that we are starting an ISR            */
    OSIntNesting++;
    CPU_CRITICAL_EXIT();


    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) {
                      /* Read one byte from the receive data register         */
				AddLoopBuf(&Uart3RecvStruct,Uart3RecvBuf,UART3_RECV_BUF_SIZE,USART_ReceiveData(USART3)&0xFF);
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);          /* Clear the USART Receive interrupt                   */

    }

    if (USART_GetITStatus(USART3, USART_IT_TXE) != RESET) {
    	    		if (0 == Uart3SendStruct.len)
				     			{
				     			Uart3Sending = 0;	
				     			USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
				     			}
							else{
										SetEn485_3;
						        GetLoopbuf(&Uart3SendStruct,Uart3SendBuf,UART3_SEND_BUF_SIZE,&temp);
						        USART_SendData(USART3, temp);
						      }
        //USART_ClearITPendingBit(USART3, USART_IT_TXE);           /* Clear the USART transmit interrupt                  */

    }

			//485
    if (USART_GetITStatus(USART3, USART_IT_TC) != RESET) {
        //OSView_TxHandler();
        if (0 == Uart3SendStruct.len)
								{
									ClrEn485_3;
								}
        USART_ClearITPendingBit(USART3, USART_IT_TC);           /* Clear the USART transmit interrupt                  */

    }


    OSIntExit();                                                /* Tell uC/OS-II that we are leaving the ISR            */
}
#endif
//////////////////////////////
//#if CONFIG_UART4
//void  UART4_RxTxISRHandler (void)
//{
//    CPU_SR          cpu_sr;
//		unsigned char temp;
//    CPU_CRITICAL_ENTER();                                       /* Tell uC/OS-II that we are starting an ISR            */
//    OSIntNesting++;
//    CPU_CRITICAL_EXIT();
//
//
//    if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET) {
//                      /* Read one byte from the receive data register         */
//				AddLoopBuf(&Uart4RecvStruct,Uart4RecvBuf,UART4_RECV_BUF_SIZE,USART_ReceiveData(UART4)&0xFF);
//        USART_ClearITPendingBit(UART4, USART_IT_RXNE);          /* Clear the USART Receive interrupt                   */
//
//    }
//
//    if (USART_GetITStatus(UART4, USART_IT_TXE) != RESET) {
//    	    		if (0 == Uart4SendStruct.len)
//				     			{
//				     			Uart4Sending = 0;	
//				     			USART_ITConfig(UART4, USART_IT_TXE, DISABLE);
//				     			}
//							else{
//										SetEn485_4;
//										GetLoopbuf(&Uart4SendStruct,Uart4SendBuf,UART4_SEND_BUF_SIZE,&temp);
//						        USART_SendData(UART4, temp);
//						      }
////        USART_ClearITPendingBit(UART4, USART_IT_TXE);           /* Clear the USART transmit interrupt                  */
//
//    }
//
//			//485
//    if (USART_GetITStatus(UART4, USART_IT_TC) != RESET) {
//			ClrEn485_4;
//        USART_ClearITPendingBit(UART4, USART_IT_TC);           /* Clear the USART transmit interrupt                  */
//
//    }
//
//
//    OSIntExit();                                                /* Tell uC/OS-II that we are leaving the ISR            */
//}
//#endif
//
/////////////////////////////////////////////
//#if CONFIG_UART5
//void  UART5_RxTxISRHandler (void)
//{
//    CPU_SR          cpu_sr;
//		unsigned char temp;
//    CPU_CRITICAL_ENTER();                                       /* Tell uC/OS-II that we are starting an ISR            */
//    OSIntNesting++;
//    CPU_CRITICAL_EXIT();
//
//
//    if (USART_GetITStatus(UART5, USART_IT_RXNE) != RESET) {
//                      /* Read one byte from the receive data register         */
//				AddLoopBuf(&Uart5RecvStruct,Uart5RecvBuf,UART5_RECV_BUF_SIZE,USART_ReceiveData(UART5)&0xFF);
//        USART_ClearITPendingBit(UART5, USART_IT_RXNE);          /* Clear the USART Receive interrupt                   */
//
//    }
//
//    if (USART_GetITStatus(UART5, USART_IT_TXE) != RESET) {
//    	    		if (0 == Uart5SendStruct.len)
//				     			{
//				     			Uart5Sending = 0;	
//				     			USART_ITConfig(UART5, USART_IT_TXE, DISABLE);
//				     			}
//							else{
//										SetEn485_5;
//										GetLoopbuf(&Uart5SendStruct,Uart5SendBuf,UART5_SEND_BUF_SIZE,&temp);
//						        USART_SendData(UART5, temp);
//						      }
////        USART_ClearITPendingBit(UART5, USART_IT_TXE);           /* Clear the USART transmit interrupt                  */
//
//    }
//
//			//485
//    if (USART_GetITStatus(UART5, USART_IT_TC) != RESET) {
//			ClrEn485_5;
//        USART_ClearITPendingBit(UART5, USART_IT_TC);           /* Clear the USART transmit interrupt                  */
//
//    }
//
//
//    OSIntExit();                                                /* Tell uC/OS-II that we are leaving the ISR            */
//}
//#endif

////////////////////////////
//void  USARTx_TxIntEn (void)
//{
//    USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);
//    USART_ITConfig(USARTx, USART_IT_TC, ENABLE);	//485
//}
//////////////////////////////
//void  USARTx_RxTxISRHandler (void)
//{
//    CPU_SR          cpu_sr;
//
//    CPU_CRITICAL_ENTER();                                       /* Tell uC/OS-II that we are starting an ISR            */
//    OSIntNesting++;
//    CPU_CRITICAL_EXIT();
//
//
//    if (USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET) {
//                      /* Read one byte from the receive data register         */
//        //OSView_RxHandler( USART_ReceiveData(OS_VIEW_USART) & 0xFF );
//
//        USART_ClearITPendingBit(USARTx, USART_IT_RXNE);          /* Clear the USART Receive interrupt                   */
//
//    }
//
//    if (USART_GetITStatus(USARTx, USART_IT_TXE) != RESET) {
//        //OSView_TxHandler();
//
//        USART_ClearITPendingBit(USARTx, USART_IT_TXE);           /* Clear the USART transmit interrupt                  */
//
//    }
//
//			//485
//    if (USART_GetITStatus(USARTx, USART_IT_TC) != RESET) {
//        //OSView_TxHandler();
//			//485
//        USART_ClearITPendingBit(USARTx, USART_IT_TC);           /* Clear the USART transmit interrupt                  */
//
//    }
//
//
//    OSIntExit();                                                /* Tell uC/OS-II that we are leaving the ISR            */
//}





