

//#include <includes.h>

#include "config.h"
#include	"GetAverage.h"

//unsigned short int AvergeOffsetGb;
//unsigned short int AvergeOffsetGa[ ChannelsAvergeGa ];
//unsigned short int  AvergeBufGa[ ChannelsAvergeGa ][ MaxNumbAvergeGb ];
//unsigned short int  AvergeBufGb[ MaxNumbAvergeGb ];
								
//								 #define  MaxNumbAvergeGa  25
						//		#define  		  MaxNumbAvergeGb		20

unsigned short int AvergeOffsetGa[ ChannelsAvergeGa ];
unsigned short int AvergeBufGa[ ChannelsAvergeGa ][ MaxNumbAvergeGa ];

unsigned short int AvergeOffsetGb;
unsigned short int AvergeBufGb[ MaxNumbAvergeGb ];
///////////////////////////////
//buf 平均缓冲区
//offset 位置偏移
//add 新增加的
//MaxSize 缓冲区尺寸
//////////////////////////////
void AddAverage(unsigned short int *buf,unsigned short int *offset,unsigned short int add, unsigned short int MaxSize)
{
	
		if(*offset<MaxSize)
			{
				(*offset)++;
			}
		else{
			 *offset=0;
			 //gFlagGetAverage=1;		//平均电流数据就绪标记
				}
				
*(buf+(*offset))=add;	
	
}
///////////////////////////////

unsigned short int GetAverage(unsigned short int *buf , unsigned short int MaxSize)
{//把测量值放入个缓冲区，滤波取数据，数据的时间范围
 //数据的更新时间为
unsigned short int average;
unsigned long int  temp32;
unsigned short int  i;

	temp32=0;
	for(i=0;i<MaxSize;i++)
		{
		temp32+=(unsigned long int)*(buf+i);
		}

	average=(unsigned short int)(temp32/MaxSize);
	
return average;
}

////////////
void InitAverage(unsigned short int *buf , unsigned short int MaxSize)
{
	unsigned short int i;
	for(i=0;i<MaxSize;i++)
		{
			*(buf+i)=0;
		}
	//gFlagGetAverage=0;		//平均电流数据就绪标记
}


