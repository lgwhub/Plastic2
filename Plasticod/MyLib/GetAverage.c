

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
//buf ƽ��������
//offset λ��ƫ��
//add �����ӵ�
//MaxSize �������ߴ�
//////////////////////////////
void AddAverage(unsigned short int *buf,unsigned short int *offset,unsigned short int add, unsigned short int MaxSize)
{
	
		if(*offset<MaxSize)
			{
				(*offset)++;
			}
		else{
			 *offset=0;
			 //gFlagGetAverage=1;		//ƽ���������ݾ������
				}
				
*(buf+(*offset))=add;	
	
}
///////////////////////////////

unsigned short int GetAverage(unsigned short int *buf , unsigned short int MaxSize)
{//�Ѳ���ֵ��������������˲�ȡ���ݣ����ݵ�ʱ�䷶Χ
 //���ݵĸ���ʱ��Ϊ
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
	//gFlagGetAverage=0;		//ƽ���������ݾ������
}


