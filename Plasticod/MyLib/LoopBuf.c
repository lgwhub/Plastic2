//#include "nomal.h"
//#include <includes.h>
#include "LoopBuf.h"

//uchar Uart0RecvBuf[UART0_RECV_BUF_SIZE+4];	//串口0接收缓冲区
//_loopbuf Uart0RecvStruct;
//uchar Uart0SendBuf[UART0_SEND_BUF_SIZE+4];	//串口0发缓冲区
//_loopbuf Uart0SendStruct;
//
//
//uchar Uart1RecvBuf[UART1_RECV_BUF_SIZE+4];	//串口1接收缓冲区
//_loopbuf Uart1RecvStruct;
//uchar Uart1SendBuf[UART1_SEND_BUF_SIZE+4];	//串口1发缓冲区
//_loopbuf Uart1SendStruct;



/*****************************************************************************/
void SetLoopBuf_Non(uchar *buf,_loopbuf *st,uint32 BufSize)
{
uint32 i;
ClearLoopBuf(st,BufSize);
	for(i=0;i<BufSize;i++)
				{
					*(buf+i)=0x0;
				}	
	
}

/////////////////////////////////

void ClearLoopBuf(_loopbuf *st,uint32 BufSize)	//清除环型缓冲区
{
st->len		=	0;		//已有长度
st->addTail	=	0;       	//输入数据尾
//st->outHead=0;      			//输出数据头
st->outTail	=	0;	//BufSize;      //输出数据尾
}
/************************************************************************/
bool AddLoopBuf(_loopbuf *st,uchar *buf,uint32 BufSize,uchar chr)	//加入到环型缓冲区
{
if( (st->addTail != st->outTail) || (0 == st->len) )
	{
	*(buf+st->addTail) = chr;	
	if(st->addTail<BufSize)
		{
		st->addTail++;
		}
	else{
		st->addTail=0;	//循环
		}
	st->len++;
	return 1;		
	}	
else{	//缓冲区满
	return 0;
	}	
}


/************************************************************************/
bool GetLoopbuf(_loopbuf *st,uchar *buf,uint32 BufSize,uchar *chr)	//从环型缓冲区提取
{
if( st->len > 0 )
	{
	*chr = *( buf + st->outTail );
	if(st->outTail<BufSize)
		{
		st->outTail ++;	
		}
	else{	//循环
		st->outTail = 0;
		}	
	st->len--;
	if( st->outTail == st->addTail )
		{
		st->len = 0;
		}
	return 1;	//读到数据
	}
else return 0;	//缓冲区没有数据

}

