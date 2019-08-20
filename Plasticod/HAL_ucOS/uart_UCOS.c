
#include <includes.h>

#include "uart_ucos.h"
#include "HD_PLASTIC1.h"
#include "stm32f10x.h"
#include "stdio.h"
#include "LoopBuf.h"
#include "uart_UCOS.h"


//extern OS_EVENT *OSSemUart3;
//extern OS_EVENT *OSSemUart2;
//extern OS_EVENT *OSSemUart1;
#if CONFIG_UART1
unsigned char Uart1Sending;
unsigned char Uart1RecvBuf[UART1_RECV_BUF_SIZE+4];	//串口1接收缓冲区
_loopbuf Uart1RecvStruct;
unsigned char Uart1SendBuf[UART1_SEND_BUF_SIZE+4];	//串口1发缓冲区
_loopbuf Uart1SendStruct;
#endif

#if CONFIG_UART2
unsigned char Uart2Sending;
unsigned char Uart2RecvBuf[UART2_RECV_BUF_SIZE+4];	//串口2接收缓冲区
_loopbuf Uart2RecvStruct;
unsigned char Uart2SendBuf[UART2_SEND_BUF_SIZE+4];	//串口2发缓冲区
_loopbuf Uart2SendStruct;
#endif

#if CONFIG_UART3
unsigned char Uart3Sending;
unsigned char Uart3RecvBuf[UART3_RECV_BUF_SIZE+4];	//串口1接收缓冲区
_loopbuf Uart3RecvStruct;
unsigned char Uart3SendBuf[UART3_SEND_BUF_SIZE+4];	//串口1发缓冲区
_loopbuf Uart3SendStruct;
#endif

#if CONFIG_UART4
unsigned char Uart4Sending;
unsigned char Uart4RecvBuf[UART4_RECV_BUF_SIZE+4];	//串口2接收缓冲区
_loopbuf Uart4RecvStruct;
unsigned char Uart4SendBuf[UART4_SEND_BUF_SIZE+4];	//串口2发缓冲区
_loopbuf Uart4SendStruct;
#endif

////////////////////////////////////////////////////////////////////
//#if CONFIG_UART5
//unsigned char Uart5Sending;
//unsigned char Uart5RecvBuf[UART5_RECV_BUF_SIZE+4];	//串口2接收缓冲区
//_loopbuf Uart5RecvStruct;
//unsigned char Uart5SendBuf[UART5_SEND_BUF_SIZE+4];	//串口2发缓冲区
//_loopbuf Uart5SendStruct;
//#endif
/*****************************************************************************/

///////////////////
//*************************************
void _DelayMs(unsigned short int ms)
{
	unsigned short int i,j;
	
	for(i=0;i<ms;i++)
	   {
		
		for(j=0;j<600;j++)
		  {
		  }
		
	
     }

}


#if CONFIG_UART1
/****************************************************************************
* 名称：void  Uart1Init(ulong baud, unsigned char parity)
* 功能：初始化串口1。设置其工作模式及波特率。
* 入口参数：baud                波特率
*   parity          0:无校验  1：奇校验  2：偶校验
****************************************************************************/
void  Uart1BufInit(void)
{  
//CPU_SR         cpu_sr;
 //  OS_ENTER_CRITICAL();	//ucos2
   Uart1Sending = 0;
   ClearLoopBuf(&Uart1SendStruct,UART1_SEND_BUF_SIZE);				//清除环型缓冲区
	ClearLoopBuf(&Uart1RecvStruct,UART1_RECV_BUF_SIZE);
   
//	OS_EXIT_CRITICAL();          //ucos2  
}


///////////////////


////////////
unsigned char GetOneFromUart1(unsigned char *buf)
{
	unsigned char flag;
//	CPU_SR         cpu_sr;
	
//	OS_ENTER_CRITICAL();	//ucos2   
	
	if(Uart1RecvStruct.len)
		{
		GetLoopbuf(&Uart1RecvStruct,Uart1RecvBuf,UART1_RECV_BUF_SIZE,buf);
		flag= 1;
		}
	else 	flag=  0;
	
//	OS_EXIT_CRITICAL();
	
	return flag;
}


unsigned short int Uart1CharSend(unsigned char x)
{
	
	unsigned char temp;
	unsigned short int fail=0;
	unsigned long int t;
//	CPU_SR         cpu_sr;
	
    if(Uart1SendStruct.len>3)
	    	{//full
	    	t=10;
	    	while((Uart1SendStruct.addTail == Uart1SendStruct.outTail)&&(t>0))
	    		{
	  //  		OSTimeDly(2);	//延时10毫秒		
	  _DelayMs(2);
	    		t--;
	    		}
	    	}
	    if(t==0)
	    	fail=1;
	    	
//	 OS_ENTER_CRITICAL();	//ucos2  
	AddLoopBuf(&Uart1SendStruct,Uart1SendBuf,UART1_SEND_BUF_SIZE,x);	//加入到环型缓冲区
//	OS_EXIT_CRITICAL();          //ucos2  	
	/*
	if(Uart1Sending!=0)	//准备继续发送
		{
		if(U1LSR&BIT5)//发送保持寄存器空
	   		{
	   		Uart1Sending = 0;
	   		}
		}
		//20100915
	*/
	if(Uart1Sending==0)
	             {
	              //Un485Send=FALSE;  //485允许发送
	              //U1MCR=0x03;     //DTR_232=1,RTS_232=1
	             // OS_ENTER_CRITICAL();	//ucos2
	              
	              if(GetLoopbuf(&Uart1SendStruct,Uart1SendBuf,UART1_SEND_BUF_SIZE,&temp))
	              	{
	              		Uart1Sending = 1;
	              		SetEn485_1;	//SetPin_DTR1;	//uart1_485
										USART_SendData(USART1, temp);
	              		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	              	//	USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
	        			}
	      //  OS_EXIT_CRITICAL();          //ucos2  	
	             }
	return (!fail);
}








/************************************************************************/
/************************************************************************/
/*     uart1中断方式发送字符串，调用方法:				*/
/* 1.SendString_UART1("ATZ\r",sizeof("ATZ\r"));				     */
/* 2.SendString_UART1(&XYZ[0],length);					     */
/* 3.如果时间超过而没有发送完成，则返回剩余的未发送字节数，如果成功则返回0 */
/************************************************************************/
void SendString_UART1(unsigned char *StrData,unsigned short int len)
{
unsigned short int i;
	for(i=0;i<len;i++)
	  {
	  Uart1CharSend(*(StrData+i));
	  }
  
}

/*************************************************************/

void SendText_UART1(unsigned char *StrData)
{

	unsigned char i;
	for(i=0;i<255;i++)
	  {
	  if(*(StrData+i)==0x00)break;
	   Uart1CharSend(*(StrData+i));
	  }
}
#endif
///////////////////
#if CONFIG_UART2
void  Uart2BufInit(void)
{  
	CPU_SR         cpu_sr;
	
	OS_ENTER_CRITICAL();	//ucos2
	
  Uart2Sending = 0;
  ClearLoopBuf(&Uart2SendStruct,UART2_SEND_BUF_SIZE);				//清除环型缓冲区
	ClearLoopBuf(&Uart2RecvStruct,UART2_RECV_BUF_SIZE);

OS_EXIT_CRITICAL();          //ucos2  

}
///////////////////



///////////////////
unsigned char GetOneFromUart2(unsigned char *buf)
{
	unsigned char flag;
	CPU_SR         cpu_sr;
	
	OS_ENTER_CRITICAL();	//ucos2   
	
	if(Uart2RecvStruct.len)
		{
		GetLoopbuf(&Uart2RecvStruct,Uart2RecvBuf,UART2_RECV_BUF_SIZE,buf);
		flag= 1;
		}
	else 	flag=  0;
	
	OS_EXIT_CRITICAL();
	
	return flag;
}
///////////////////
unsigned short int Uart2CharSend(unsigned char x)
{
	
	unsigned char temp;
	unsigned short int fail=0;
	unsigned long int t;
	CPU_SR         cpu_sr;	
	
    if(Uart2SendStruct.len>3)
	    	{//full
	    	t=10;
	    	while((Uart2SendStruct.addTail == Uart2SendStruct.outTail)&&(t>0))
	    		{
	    		//OSTimeDly(OS_TICKS_PER_SEC / 100);	//延时10毫秒	
	    		OSTimeDly(2);	//延时10毫秒		
	    		t--;
	    		}
	    	}
	    if(t==0)
	    	fail=1;
		
	
	
	OS_ENTER_CRITICAL();	//ucos2   
	AddLoopBuf(&Uart2SendStruct,Uart2SendBuf,UART2_SEND_BUF_SIZE,x);	//加入到环型缓冲区
	OS_EXIT_CRITICAL();          //ucos2  	
	///
//	if(Uart2Sending)
//		{
//		if(U0LSR&BIT5)//发送保持寄存器空
//	   		{
//	   		 Uart2Sending = 0;
//	   		}
//		}
	///
	if(!Uart2Sending)
	             {

	              OS_ENTER_CRITICAL();	//ucos2
	              if(GetLoopbuf(&Uart2SendStruct,Uart2SendBuf,UART2_SEND_BUF_SIZE,&temp))
	              		{
	              		Uart2Sending = 1;	
	              			SetEn485_2;
										USART_SendData(USART2, temp);
	              	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
	              	//	USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
	        		}
	        	OS_EXIT_CRITICAL();          //ucos2  	
	             }
	 
	return (!fail);
}
///////////////////
void SendText_UART2(unsigned char *StrData)
{
	//	 INT8U err;
	unsigned char i;

		for(i=0;i<255;i++)
		  {
		  if(*(StrData+i)==0x00)break;
		   Uart2CharSend(*(StrData+i));
		  }
 
	  
}
///////////////////
void SendString_UART2(unsigned char *StrData,unsigned short int len)
{
 //  INT8U err;
	unsigned short int i;

	
		for(i=0;i<len;i++)
		  {
		  Uart2CharSend(*(StrData+i));
		  }

}
///////////////////


#endif
///////////////////

#if CONFIG_UART3
/****************************************************************************
* 名称：void  Uart3Init(ulong baud, unsigned char parity)
* 功能：初始化串口1。设置其工作模式及波特率。
* 入口参数：baud                波特率
*   parity          0:无校验  1：奇校验  2：偶校验
****************************************************************************/
void  Uart3BufInit(void)
{  
CPU_SR         cpu_sr;
   OS_ENTER_CRITICAL();	//ucos2
   Uart3Sending = 0;
   ClearLoopBuf(&Uart3SendStruct,UART3_SEND_BUF_SIZE);				//清除环型缓冲区
	ClearLoopBuf(&Uart3RecvStruct,UART3_RECV_BUF_SIZE);
   
	OS_EXIT_CRITICAL();          //ucos2  
}


/////////////////


//////////
unsigned char GetOneFromUart3(unsigned char *buf)
{
	unsigned char flag;
	CPU_SR         cpu_sr;
	
	OS_ENTER_CRITICAL();	//ucos2   
	
	if(Uart3RecvStruct.len)
		{
		GetLoopbuf(&Uart3RecvStruct,Uart3RecvBuf,UART3_RECV_BUF_SIZE,buf);
		flag= 1;
		}
	else 	flag=  0;
	
	OS_EXIT_CRITICAL();
	
	return flag;
}


unsigned short int Uart3CharSend(unsigned char x)
{
	
	unsigned char temp;
	unsigned short int fail=0;
	unsigned long int t;
	CPU_SR         cpu_sr;	
	
    if(Uart3SendStruct.len>3)
	    	{//full
	    	t=10;
	    	while((Uart3SendStruct.addTail == Uart3SendStruct.outTail)&&(t>0))
	    		{
	    		OSTimeDly(2);	//延时10毫秒		
	    		t--;
	    		}
	    	}
	    if(t==0)
	    	fail=1;
	    	
	 OS_ENTER_CRITICAL();	//ucos2  
	AddLoopBuf(&Uart3SendStruct,Uart3SendBuf,UART3_SEND_BUF_SIZE,x);	//加入到环型缓冲区
	OS_EXIT_CRITICAL();          //ucos2  	
	/*
	if(Uart3Sending!=0)	//准备继续发送
		{
		if(U1LSR&BIT5)//发送保持寄存器空
	   		{
	   		Uart3Sending = 0;
	   		}
		}
		//20100915
	*/
	if(Uart3Sending==0)
	             {
	              //Un485Send=FALSE;  //485允许发送
	              //U1MCR=0x03;     //DTR_232=1,RTS_232=1
	              OS_ENTER_CRITICAL();	//ucos2
	              
	              if(GetLoopbuf(&Uart3SendStruct,Uart3SendBuf,UART3_SEND_BUF_SIZE,&temp))
	              	{
	              		Uart3Sending = 1;
	              		SetEn485_3;
										USART_SendData(USART3, temp);
										USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
	              	//	USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
	              		
	        			}
	        OS_EXIT_CRITICAL();          //ucos2  	
	             }
	return (!fail);
}







/************************************************************************/
/************************************************************************/
/*     uart1中断方式发送字符串，调用方法:				*/
/* 1.SendString_UART3("ATZ\r",sizeof("ATZ\r"));				     */
/* 2.SendString_UART3(&XYZ[0],length);					     */
/* 3.如果时间超过而没有发送完成，则返回剩余的未发送字节数，如果成功则返回0 */
/************************************************************************/
void SendString_UART3(unsigned char *StrData,unsigned short int len)
{
unsigned short int i;
	for(i=0;i<len;i++)
	  {
	  Uart3CharSend(*(StrData+i));
	  }
  
}

/*************************************************************/

void SendText_UART3(unsigned char *StrData)
{

	unsigned char i;
	for(i=0;i<255;i++)
	  {
	  if(*(StrData+i)==0x00)break;
	   Uart3CharSend(*(StrData+i));
	  }
}
#endif
//////////////////////////////////////////////////////////////////

#if CONFIG_UART4
//void  Uart4BufInit(void)
//{  
//CPU_SR         cpu_sr;
//   OS_ENTER_CRITICAL();	//ucos2
//   Uart4Sending = 0;
//   ClearLoopBuf(&Uart4SendStruct,UART4_SEND_BUF_SIZE);				//清除环型缓冲区
//	ClearLoopBuf(&Uart4RecvStruct,UART4_RECV_BUF_SIZE);
//   
//	OS_EXIT_CRITICAL();          //ucos2  
//}


///////////////////

////////////
//unsigned char GetOneFromUart4(unsigned char *buf)
//{
//	
//	unsigned char flag;
//	CPU_SR         cpu_sr;
//	
//	OS_ENTER_CRITICAL();	//ucos2   
//	
//	if(Uart4RecvStruct.len)
//		{
//		GetLoopbuf(&Uart4RecvStruct,Uart4RecvBuf,UART4_RECV_BUF_SIZE,buf);
//		flag= 1;
//		}
//	else 	flag=  0;
//	
//	OS_EXIT_CRITICAL();
//	
//	return flag;	
//	
//}
//
//
//unsigned short int Uart4CharSend(unsigned char x)
//{
//	
//	unsigned char temp;
//	unsigned short int fail=0;
//	unsigned long int t;
//	CPU_SR         cpu_sr;
//	
//    if(Uart4SendStruct.len>3)
//	    	{//full
//	    	t=10;
//	    	while((Uart4SendStruct.addTail == Uart4SendStruct.outTail)&&(t>0))
//	    		{
//	    		OSTimeDly(2);	//延时10毫秒		
//	    		t--;
//	    		}
//	    	}
//	    if(t==0)
//	    	fail=1;
//	    	
//	 OS_ENTER_CRITICAL();	//ucos2  
//	AddLoopBuf(&Uart4SendStruct,Uart4SendBuf,UART4_SEND_BUF_SIZE,x);	//加入到环型缓冲区
//	OS_EXIT_CRITICAL();          //ucos2  	
//
//	if(Uart4Sending==0)
//	             {
//	              OS_ENTER_CRITICAL();	//ucos2
//	              
//	              if(GetLoopbuf(&Uart4SendStruct,Uart4SendBuf,UART4_SEND_BUF_SIZE,&temp))
//	              	{
//	              		Uart4Sending = 1;
//	              		SetEn485_4;
//										USART_SendData(UART4, temp);
//	              		USART_ITConfig(UART4, USART_IT_TXE, ENABLE);
//	              	//	USART_ITConfig(UART4, USART_IT_TXE, DISABLE);
//	        			}
//	        OS_EXIT_CRITICAL();          //ucos2  	
//	             }
//	return (!fail);
//}








/************************************************************************/
/************************************************************************/
/*     uart1中断方式发送字符串，调用方法:				*/
/* 1.SendString_UART4("ATZ\r",sizeof("ATZ\r"));				     */
/* 2.SendString_UART4(&XYZ[0],length);					     */
/************************************************************************/
//void SendString_UART4(unsigned char *StrData,unsigned short int len)
//{
//unsigned short int i;
//	for(i=0;i<len;i++)
//	  {
//	  Uart4CharSend(*(StrData+i));
//	  }
//  
//}
//
///*************************************************************/
//
//void SendText_UART4(unsigned char *StrData)
//{
//
//	unsigned char i;
//	for(i=0;i<255;i++)
//	  {
//	  if(*(StrData+i)==0x00)break;
//	   Uart4CharSend(*(StrData+i));
//	  }
//}

#endif

#if CONFIG_UART5
//void  Uart5BufInit(void)
//{  
//CPU_SR         cpu_sr;
//   OS_ENTER_CRITICAL();	//ucos2
//   Uart5Sending = 0;
//   ClearLoopBuf(&Uart5SendStruct,UART5_SEND_BUF_SIZE);				//清除环型缓冲区
//	ClearLoopBuf(&Uart5RecvStruct,UART5_RECV_BUF_SIZE);
//   
//	OS_EXIT_CRITICAL();          //ucos2  
//}


///////////////////


////////////
//unsigned char GetOneFromUart5(unsigned char *buf)
//{
//	
//	unsigned char flag;
//	CPU_SR         cpu_sr;
//	
//	OS_ENTER_CRITICAL();	//ucos2   
//	
//	if(Uart5RecvStruct.len)
//		{
//		GetLoopbuf(&Uart5RecvStruct,Uart5RecvBuf,UART5_RECV_BUF_SIZE,buf);
//		flag= 1;
//		}
//	else 	flag=  0;
//	
//	OS_EXIT_CRITICAL();
//	
//	return flag;	
//	
//}
//
//
//unsigned short int Uart5CharSend(unsigned char x)
//{
//	
//	unsigned char temp;
//	unsigned short int fail=0;
//	unsigned long int t;
//	CPU_SR         cpu_sr;
//	
//    if(Uart5SendStruct.len>3)
//	    	{//full
//	    	t=10;
//	    	while((Uart5SendStruct.addTail == Uart5SendStruct.outTail)&&(t>0))
//	    		{
//	    		OSTimeDly(2);	//延时10毫秒		
//	    		t--;
//	    		}
//	    	}
//	    if(t==0)
//	    	fail=1;
//	    	
//	 OS_ENTER_CRITICAL();	//ucos2  
//	AddLoopBuf(&Uart5SendStruct,Uart5SendBuf,UART5_SEND_BUF_SIZE,x);	//加入到环型缓冲区
//	OS_EXIT_CRITICAL();          //ucos2  	
//
//	if(Uart5Sending==0)
//	             {
//	              OS_ENTER_CRITICAL();	//ucos2
//	              
//	              if(GetLoopbuf(&Uart5SendStruct,Uart5SendBuf,UART5_SEND_BUF_SIZE,&temp))
//	              	{
//	              		Uart5Sending = 1;
//	              		SetEn485_5;
//										USART_SendData(UART5, temp);
//	              		USART_ITConfig(UART5, USART_IT_TXE, ENABLE);
//	              	//	USART_ITConfig(UART5, USART_IT_TXE, DISABLE);
//	        			}
//	        OS_EXIT_CRITICAL();          //ucos2  	
//	             }
//	return (!fail);
//}








/************************************************************************/
/************************************************************************/
/*     uart1中断方式发送字符串，调用方法:				*/
/* 1.SendString_UART5("ATZ\r",sizeof("ATZ\r"));				     */
/* 2.SendString_UART5(&XYZ[0],length);					     */
/************************************************************************/
//void SendString_UART5(unsigned char *StrData,unsigned short int len)
//{
//unsigned short int i;
//	for(i=0;i<len;i++)
//	  {
//	  Uart5CharSend(*(StrData+i));
//	  }
//  
//}
//
///*************************************************************/
//
//void SendText_UART5(unsigned char *StrData)
//{
//
//	unsigned char i;
//	for(i=0;i<255;i++)
//	  {
//	  if(*(StrData+i)==0x00)break;
//	   Uart5CharSend(*(StrData+i));
//	  }
//}

#endif




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
void InitUSART1(unsigned long int baud_rate,unsigned short int parity)
{
    
//    GPIO_InitTypeDef        GPIO_InitStructure;
    USART_InitTypeDef       USART_InitStructure;
    NVIC_InitTypeDef        NVIC_InitStructure;	


    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
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
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
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
 	#if   ( OS_VIEW_MODULE != DEF_ENABLED )|| (OS_VIEW_USART_NUMBER != 1)   
    Uart1BufInit();
    USART1_TxIntEn();
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	#endif    
  #endif 
  
 ClrEn485_1    ;
 ClrRecv485_1   ;
  
  }

/////////////////////////////////////////////////

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
    CPU_SR          cpu_sr;
		unsigned char temp;

    CPU_CRITICAL_ENTER();                                       /* Tell uC/OS-II that we are starting an ISR            */
    OSIntNesting++;
    CPU_CRITICAL_EXIT();


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


    OSIntExit();                                                /* Tell uC/OS-II that we are leaving the ISR            */
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

/******************************************************************************
**                            End Of File
******************************************************************************/


