
// #include "uart.h"
// #include "uart_UCOS.h"
#ifndef __UART_UCOS_H 
#define __UART_UCOS_H

#define CONFIG_UART1		1
#define CONFIG_UART2		0
#define CONFIG_UART3		0
#define CONFIG_UART4		0
#define CONFIG_UART5		0

#define UART1_RECV_BUF_SIZE	16
#define UART1_SEND_BUF_SIZE	24
#define UART2_RECV_BUF_SIZE	64
#define UART2_SEND_BUF_SIZE	64
#define UART3_RECV_BUF_SIZE	32
#define UART3_SEND_BUF_SIZE	32
//#define UART4_RECV_BUF_SIZE	128
//#define UART4_SEND_BUF_SIZE	128
//#define UART5_RECV_BUF_SIZE	128
//#define UART5_SEND_BUF_SIZE	128


#include "LoopBuf.h"

///////////////////////////////////////
#if CONFIG_UART1
extern unsigned char Uart1RecvBuf[UART1_RECV_BUF_SIZE+4];	//串口1接收缓冲区
extern _loopbuf Uart1RecvStruct;
extern unsigned char Uart1SendBuf[UART1_SEND_BUF_SIZE+4];	//串口1发缓冲区
extern _loopbuf Uart1SendStruct;


extern unsigned char Uart1Sending;
void  Uart1BufInit(void);
unsigned char GetOneFromUart1(unsigned char *buf);
unsigned short int Uart1CharSend(unsigned char x);
void SendString_UART1(unsigned char *StrData,unsigned short int len);
void SendText_UART1(unsigned char *StrData);

#endif

///////////////////////////////////////
#if CONFIG_UART2

extern unsigned char Uart2RecvBuf[UART2_RECV_BUF_SIZE+4];	//串口2接收缓冲区
extern _loopbuf Uart2RecvStruct;
extern unsigned char Uart2SendBuf[UART2_SEND_BUF_SIZE+4];	//串口2发缓冲区
extern _loopbuf Uart2SendStruct;




extern unsigned char Uart2Sending;
void  Uart2BufInit(void);
unsigned char GetOneFromUart2(unsigned char *buf);
unsigned short int Uart2CharSend(unsigned char x);
void SendString_UART2(unsigned char *StrData,unsigned short int len);
void SendText_UART2(unsigned char *StrData);

#endif

/////////////////////////////////////////
#if CONFIG_UART3
extern unsigned char Uart3RecvBuf[UART3_RECV_BUF_SIZE+4];	//串口1接收缓冲区
extern _loopbuf Uart3RecvStruct;
extern unsigned char Uart3SendBuf[UART3_SEND_BUF_SIZE+4];	//串口1发缓冲区
extern _loopbuf Uart3SendStruct;

extern unsigned char Uart3Sending;
void  Uart3BufInit(void);
unsigned char GetOneFromUart3(unsigned char *buf);
unsigned short int Uart3CharSend(unsigned char x);
void SendString_UART3(unsigned char *StrData,unsigned short int len);
void SendText_UART3(unsigned char *StrData);

#endif
//
//
//#if CONFIG_UART4
//extern unsigned char Uart4RecvBuf[UART4_RECV_BUF_SIZE+4];	//串口2接收缓冲区
//extern _loopbuf Uart4RecvStruct;
//extern unsigned char Uart4SendBuf[UART4_SEND_BUF_SIZE+4];	//串口2发缓冲区
//extern _loopbuf Uart4SendStruct;
//
//extern unsigned char Uart4Sending;
//void  Uart4BufInit(void);
//unsigned char GetOneFromUart4(unsigned char *buf);
//unsigned short int Uart4CharSend(unsigned char x);
//void SendString_UART4(unsigned char *StrData,unsigned short int len);
//void SendText_UART4(unsigned char *StrData);
//
//#endif
//
//#if CONFIG_UART5
//extern unsigned char Uart5RecvBuf[UART5_RECV_BUF_SIZE+4];	//串口2接收缓冲区
//extern _loopbuf Uart5RecvStruct;
//extern unsigned char Uart5SendBuf[UART5_SEND_BUF_SIZE+4];	//串口2发缓冲区
//extern _loopbuf Uart5SendStruct;
//
//extern unsigned char Uart5Sending;
//void  Uart5BufInit(void);
//unsigned char GetOneFromUart5(unsigned char *buf);
//unsigned short int Uart5CharSend(unsigned char x);
//void SendString_UART5(unsigned char *StrData,unsigned short int len);
//void SendText_UART5(unsigned char *StrData);
//
//#endif


///////////////////////////////////////////////////////////////////////////////////////////////


//void InitUSART1(uint32_t baud_rate,uint16_t parity);
void InitUSART1(unsigned long int baud_rate,unsigned short int parity);
//void InitUSART2(uint32_t baud_rate,uint16_t parity);
//void InitUSART3(uint32_t baud_rate,uint16_t parity);
//void InitUART4(INT32U baud_rate,uint16_t parity);
//void InitUART5(INT32U baud_rate,uint16_t parity);

#if CONFIG_UART1
void  USART1_RxTxISRHandler (void);
#endif

#if CONFIG_UART2
void  USART2_RxTxISRHandler (void);
#endif
//
#if CONFIG_UART3
void  USART3_RxTxISRHandler (void);
#endif
//
//#if CONFIG_UART4
//void  UART4_RxTxISRHandler (void);
//#endif
//
//#if CONFIG_UART5
//void  UART5_RxTxISRHandler (void);
//#endif

#endif /* end __UART_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
