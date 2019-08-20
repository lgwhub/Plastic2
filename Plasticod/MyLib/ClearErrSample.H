//  ClearErrSample.h
//#include "ClearErrSample.h"
#ifndef _CLEAR_ERRSAMPLE_
#define _CLEAR_ERRSAMPLE_

#define SampleDataType    unsigned short int

//#define MaxNumbAvergeGb  8

//#define MaxNumbAvergeGa  25  //多路数据的样本数

#define MaxSampleBufLen   25

//extern SampleDataType  SmpBuf[MaxSampleBufLen +1];
//extern unsigned short int CurrenLen;

unsigned short int ClearSample( SampleDataType *p ,unsigned long int  length );

//void Test_Clear_err(void);

#endif

