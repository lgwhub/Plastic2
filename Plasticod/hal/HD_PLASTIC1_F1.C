     
//    #include <includes.h>
#include "stm32f10x.h"
#include "stdio.h"
#include "config.h"
#include "HD_PLASTIC1.h"
#include "LoopBuf.h"
//#include "uart.h"
//#include "FreeRTOS.h"
//#include "task.h" 
//#include "stm32f10x_misc.h"


//#define SWD_DEBUG_DISABLE  0
#define USART1_REMAP       0
//#define CONFIG_UART1       1

#define DBGMCU_CR    (*((volatile unsigned long *)0xE0042004))    //�ڶ������Ϻ궨��	     

GPIO_InitTypeDef GPIO_InitStructure2;



//IOͳ��
//����̵���             2
//����                   1
//��������               1+1
//�¶Ȳ���AD             1+1
//���������AD           1+1
//ͬ������               1
//����                   6
//lcd                    3
//����                   1
//����                   2


////����1
//#define    RCC_HEAT1    RCC_AHB2Periph_GPIOA
//#define    PORT_HEAT1   GPIOA
//#define    PIN_HEAT1    GPIO_Pin_11
//
////����2
//#define    RCC_HEAT2    RCC_AHB2Periph_GPIOA
//#define    PORT_HEAT2   GPIOA
//#define    PIN_HEAT2    GPIO_Pin_15
//
//
////����̵��� 1
//#define    RCC_JSP1    RCC_APB2Periph_GPIOB
//#define    PORT_JSP1   GPIOB
//#define    PIN_JSP1    GPIO_Pin_0
//
////��Դ�̵��� 2
//#define    RCC_JSP2    RCC_APB2Periph_GPIOB
//#define    PORT_JSP2   GPIOB
//#define    PIN_JSP2    GPIO_Pin_1
//
////����ܺͼ��̿���
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






//���̷���ܽӿ��������ת������   LedKeyProces()��Ҫ����
void LedKeyPortReSet(unsigned char IsOutType)
{
 
 GPIO_InitTypeDef GPIO_InitStructure;
  

	//RCC_AHBPeriphClockCmd(RCC_AHB2Periph_GPIOA, ENABLE);

if( IsOutType != 0 )
	{

 //���������
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
  //���ָ�Ϊ�����
 
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
  
  //���������
 GPIO_SetBits(GPIOA,GPIO_Pin_All);
//	GPIO_SetBits(GPIOB,GPIO_Pin_All); 
//	GPIO_SetBits(GPIOC,GPIO_Pin_All);	 
 // GPIO_SetBits(GPIOD,GPIO_Pin_All);
//	GPIO_SetBits(GPIOE,GPIO_Pin_All);

 ////////  GPIO  PA  //////////////////

	//��������1��GPIOA��ʱ��

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA,ENABLE); 
	
	RCC_APB2PeriphClockCmd(RCC_JSP1 | RCC_JSP2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);


  #if SWD_DEBUG_DISABLE
 				GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);     //SWD�ں�jtag��ȫ����ȡ��  Full SWJ Disabled (JTAG-DP + SW-DP)
  #else


     GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);     //ֻȡ��JTAG�ڣ�����SWD�ڣ�SWDIO = PA13  SWCLK = PA14
     
     DBGMCU_CR &= 0xFFFFFFDF;		//��ֹ�첽���٣��ͷ�PB3   //#define DBGMCU_CR    (*((volatile unsigned long *)0xE0042004))    //�ڶ������Ϻ궨��	     

  #endif  	
   
 
 
 // PA2->TXD2,PA9->TXD1
 			//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_9;
 			GPIO_InitStructure.GPIO_Pin   =  GPIO_Pin_9;
 			GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
 			GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_AF_PP;
	    GPIO_Init(GPIOA, &GPIO_InitStructure);
	  
  
 //����,PA3->RXD2,PA10->RXD1

 //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_10; 
 GPIO_InitStructure.GPIO_Pin   =  GPIO_Pin_10; 
 GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_IPU;  //GPIO_Mode_IN_FLOATING;	
 
 GPIO_Init(GPIOA,&GPIO_InitStructure);
 
 
 //���������
 GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_Out_PP;  //GPIO_Mode_IN_FLOATING;	
 
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
 GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_Out_OD;  //GPIO_Mode_IN_FLOATING;	
 
 GPIO_InitStructure.GPIO_Pin = PIN_LEDCOM1;
 GPIO_Init(PORT_LEDCOM1,&GPIO_InitStructure);
 
 GPIO_InitStructure.GPIO_Pin = PIN_LEDCOM2;
 GPIO_Init(PORT_LEDCOM2,&GPIO_InitStructure); 

 #if   0 * (  SWD_DEBUG_DISABLE  +  0  )
 //SWCLK  PA14
 GPIO_InitStructure.GPIO_Pin = PIN_BackLight;
 GPIO_Init(PORT_BackLight,&GPIO_InitStructure);
 #endif
 
 //PA4      DAC
//  GPIO_InitStructure.GPIO_Pin   =  GPIO_Pin_4;
//  GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_AIN;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
 
 ////////  GPIO  PB  ////////////////// 
/*
 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB,ENABLE); 
  //PB7 PB8 PB9 ��ͨ�����,		LED1 ->PB6  LED2 ->PB5  ��ָʾ��PB10->TXD3
  

  #if USART1_REMAP

 // GPIO_Pin_6 , GPIO_Pin_7 ӳ��UART1
  #else
  //GPIO_Pin_6 , GPIO_Pin_7 ��ͨ��
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
 
//PB11 RXD3 ����;
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//GPIO_Mode_IPU;
GPIO_Init(GPIOB,&GPIO_InitStructure);  

//    PB1��������;
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

// PC6 PC7 PC8 PC9���,PC12���
// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 |  GPIO_Pin_12;
// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
// GPIO_Init(GPIOC,&GPIO_InitStructure);
 
 // PC ���
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10  |  GPIO_Pin_13;
 
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//GPIO_Mode_AF_PP;
 GPIO_Init(GPIOC,&GPIO_InitStructure);
 
// pc2 �¶ȱ���  PC11 RXD4����  pc6 pc7 PC8 PC9 ���뿪������   AD7705_DRDY = PC14
  GPIO_InitStructure.GPIO_Pin =    GPIO_Pin_2 |  GPIO_Pin_6 |  GPIO_Pin_7 |  GPIO_Pin_8 |  GPIO_Pin_9 |  GPIO_Pin_11 |  GPIO_Pin_14;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 GPIO_Init(GPIOC,&GPIO_InitStructure);
 
 
 
 
  ////////  GPIO  PD  //////////////////
  
   RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD,ENABLE); 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
 GPIO_Init(GPIOD,&GPIO_InitStructure);	
 // PD0 PD1 PD2 RXD5����
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







