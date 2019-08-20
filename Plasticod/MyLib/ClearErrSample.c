//  ClearErrSample.h

//#include  <stdio.h>
//#include  <string.h>
//#include  <ctype.h>
//#include  <stdlib.h>
//#include  <stdarg.h>
//#include  <math.h>
	#include "includes.h"
	
#include "config.h"	
#include "ClearErrSample.h"


//#define SampleDataType    unsigned short int
//#define MaxSampleBufLen   24


/*
void Test_Clear_err(void)
{
   SampleDataType  TestBuf[MaxSampleBufLen +1]
     ={
	     //1112,1112,1113,1114,1115,1116,1111,1112,
		 //1114,1333,1133,1112,1113,1118,1113,1124
		 12,12,12,12,12,12,12,12,
		 12,12,14,12,12,12,12,12
	
       };
unsigned short int TestLen=16;
while(1)
   {
   TestLen =ClearSample(TestBuf,TestLen);
  }

}
*/

unsigned short int ClearSample( SampleDataType *p ,unsigned long int  length )
{

  unsigned short int i,count,lenCopy;
 unsigned char flag	;

 // SampleDataType  avrage;
  //unsigned long int  sum;
 float  sum;      //������
 float  avrage;   //����ƽ��ֵ
 float  StandErr;  //��׼���(���ƽ���͵�ƽ����)
 SampleDataType  TempMax,TempMin;

  if ( length > MaxSampleBufLen )
	     {
		    length = MaxSampleBufLen;
	     }
	   
	
	lenCopy = length ;
	   
	for(count=0;count<lenCopy;count++)
	      {   
          if ( length < 2 )break;
        
        
          sum = 0;
          for(i=0;i<length;i++)
                {
                  sum += (float)  ( * ( p + i ) ) ;
                }
        
          avrage = sum / length ;  //ƽ��ֵ
        
        
        // ��׼���
          sum = 0;
          for(i=0;i<length;i++)
                 {
                   sum += ( (float)  ( * ( p + i ) ) - avrage ) * ( (float)  ( * ( p + i ) ) - avrage )  ;   //���ƽ����
                 }  
          StandErr = sum/( length - 1 );       //���� n-1
          StandErr =  sqrtf ( StandErr );      //������  
          
        //�޳��ִ����
          TempMax  =  ( SampleDataType )( avrage + ( StandErr * 3 ) );
          TempMin  =  ( SampleDataType )( avrage - ( StandErr * 3 ) );
        
        
          flag = 0;
          for(i=0;i<length;   )
             {
              if( ( * ( p + i ) > TempMax ) || ( * ( p + i ) < TempMin ) )
                  	{
                  		* ( p + i ) = * ( p + length -1 ) ;
                  		length -= 1;
                  		flag = 1;
                  	}
              else{
              	    i++;
                    }	
             }
            
          if(flag == 0)break;  
          
          }
return length;
}


