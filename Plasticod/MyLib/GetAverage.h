
//		#include	"GetAverage.h"

#ifndef	_GET_AVERAGE_H
#define	_GET_AVERAGE_H

//��·���ݵ�������
#define MaxNumbAvergeGb  8

extern	unsigned short int AvergeOffsetGb;
extern	unsigned short int AvergeBufGb[ MaxNumbAvergeGb ];



//��·���ݵ�������
#define MaxNumbAvergeGa  25

//��·���ݵ�ͨ����
#define ChannelsAvergeGa  4
extern	unsigned short int AvergeOffsetGa[ ChannelsAvergeGa ];
extern	unsigned short int AvergeBufGa[ChannelsAvergeGa][ MaxNumbAvergeGa ];





//extern	unsigned short int AvergeOffsetI[4];
//extern	unsigned short int AvergeOffsetV[4];
//extern	unsigned short int  AvergeBufI[ ChannelsAverge ][ MaxNumbAvergeGa ];
//extern	unsigned short int  AvergeBufGb[ChannelsAverge][ MaxNumbAvergeGb ];


///////////////////////////////
void AddAverage(unsigned short int *buf,unsigned short int *offset,unsigned short int add , unsigned short int MaxSize);
unsigned short int GetAverage(unsigned short int *buf , unsigned short int MaxSize);
void InitAverage(unsigned short int *buf , unsigned short int MaxSize);


#endif

