
#include "includes.h"
#include "PID.h"

unsigned char flag_point_init = 0 ;  //pid����ָ���Ѿ���ʼ�����

   float PidMt[3];     //������PID���Ʋ���
   float PidHt1[3];    //�����PID���Ʋ���
   float PidHt2[3];    //�����PID���Ʋ���  
   float PidBuf_A[8];
   float PidBuf_B[8];
   float PidBuf_C[8];


PidParamStruct          *pPidMt;   //������PID���Ʋ���
PidParamStruct          *pPidHt1;  //�����PID���Ʋ���
PidParamStruct          *pPidHt2;  //�����PID���Ʋ���

PidBufStruct            *pPidBufMt;   //������PID��ʱ����������
PidBufStruct            *pPidBufHt1;  //�����PID��ʱ����������
PidBufStruct            *pPidBufHt2;  //�����PID��ʱ����������

/////////////////////





void _ParamPointTab_Init_pid(void)//����ָ���ʼ��
{

//   float PidMt[3];     //������PID���Ʋ���
//   float PidHt1[3];    //�����PID���Ʋ���
//   float PidHt2[3];    //�����PID���Ʋ���  
//   float PidBuf_A[8];
//   float PidBuf_B[8];
//   float PidBuf_C[8];
   
   
//	pPidMt = (PidParamStruct *)&gCommParam.PidMt[0];//������PID���Ʋ���
//  pPidHt1 = (PidParamStruct *)&gCommParam.PidHt1[0];//�����PID���Ʋ���
//  pPidHt2 = (PidParamStruct *)&gCommParam.PidHt2[0];//�����PID���Ʋ���
//
//
//	pPidBufMt = (PidBufStruct *)&gCommParam.PidBuf_A[0];
//	pPidBufHt1 = (PidBufStruct *)&gCommParam.PidBuf_B[0];
//	pPidBufHt2 = (PidBufStruct *)&gCommParam.PidBuf_C[0];	
//	
	
	pPidMt     = (PidParamStruct *)&PidMt[0];//������PID���Ʋ���
  pPidHt1    = (PidParamStruct *)&PidHt1[0];//�����PID���Ʋ���
  pPidHt2    = (PidParamStruct *)&PidHt2[0];//�����PID���Ʋ���


	pPidBufMt  =   (PidBufStruct *)&PidBuf_A[0];
	pPidBufHt1 =   (PidBufStruct *)&PidBuf_B[0];
	pPidBufHt2 =   (PidBufStruct *)&PidBuf_C[0];		
	
	flag_point_init = 1 ;  //pid����ָ���Ѿ���ʼ�����
}

//////////////////////////


void PID_BufInit(PidBufStruct *pidch)
{
	  if ( flag_point_init == 0 )  //pid����ָ���Ѿ���ʼ�����
	  	{
	  		return;
	  	}
	  //pidch->SetPoint=0;       //�趨Ŀ��
   
    pidch->LastError	= 0;     //�ϴ�ƫ��
    pidch->PreError   = 0;      //���ϴ�ƫ��
    pidch->SumError   = 0;     //�ۻ�ƫ��
    pidch->Qx=0;									//���   ��� Px+Ix+Dx
    pidch->Px=0;		//P����
    pidch->Ix=0;    //I����  
    pidch->Dx=0;			//D����	

}
/////////////////////////////////////////////////////////////////
void PID_Init(void)
{	
_ParamPointTab_Init_pid();//����ָ���ʼ�� 

	
//PID_ParaInit
	
//xxxxxxxxxxxxxxx	
//pPidMt  -> Proportion = 1; //1 ;          //��������
//pPidMt  -> Integral   = 0.05;//(0.1) ;     //���ֳ���
//pPidMt  -> Derivative = 0.1 ;          //΢�ֳ���

	//xxxxxxxxxxxxxxxx
//pPidMt  -> Proportion = 0.2;    //1 ;          //��������
//pPidMt  -> Integral   = 0.015;   //(0.1) ;     //���ֳ���
//pPidMt  -> Derivative =  0.0;          //΢�ֳ���

//60	
//pPidMt  -> Proportion = 0.4;    //1 ;          //��������
//pPidMt  -> Integral   = 0.1;   //(0.1) ;     //���ֳ���
//pPidMt  -> Derivative =  0.9;          //΢�ֳ���	


//65
//pPidMt  -> Proportion = 0.7;    //1 ;          //��������
//pPidMt  -> Integral   = 0.02;   //(0.1) ;     //���ֳ���
//pPidMt  -> Derivative =  0.2;          //΢�ֳ���		
	
//67	
//pPidMt  -> Proportion = 0.9;    //1 ;          //��������
//pPidMt  -> Integral   = 0.03;   //(0.1) ;     //���ֳ���
//pPidMt  -> Derivative =  3;          //΢�ֳ���		

//70
//pPidMt  -> Proportion = 1.3;    //1 ;          //��������
//pPidMt  -> Integral   = 0.03;   //(0.1) ;     //���ֳ���
//pPidMt  -> Derivative =  3;          //΢�ֳ���		

pPidMt  -> Proportion = 1.5;    //1 ;          //��������
pPidMt  -> Integral   = 0.05;   //(0.1) ;     //���ֳ���
pPidMt  -> Derivative =  2;          //΢�ֳ���		


	
//////////////////////////////////////////////////////////////

pPidHt1  -> Proportion = 5 ;          //��������
pPidHt1  -> Integral   = (0.01) ;     //���ֳ���
pPidHt1  -> Derivative = 0 ;          //΢�ֳ���

pPidHt2  -> Proportion = 5 ;          //��������
pPidHt2  -> Integral   = (0.01) ;     //���ֳ���
pPidHt2  -> Derivative = 0 ;          //΢�ֳ���

PID_BufInit( pPidBufMt  );
PID_BufInit( pPidBufHt1 );
PID_BufInit( pPidBufHt2 );

}




/********************************************************
* Function:    PID_Calc
* Description: PID����
* Input:       PIDstruct *  ��Ҫ�����PID���ƽṹ��ָ��
*              NowPoint         ʵ�ʷ���ֵ
* Output:      float           PID������
* Calls:       ��
* Called by:   CtrlTemp
* Others:
*********************************************************/
void PID_Calc(PidParamStruct *types, PidBufStruct *pidch, float NowPoint)
{
    float dError,Error;
    
    float total;
    
    Error            =    pidch->SetPoint   -   NowPoint   ;              //����ƫ��  e0
    pidch->SumError  +=   Error;                      							//�����ۼ�  e0++
    dError           =    pidch->LastError  -  pidch->PreError;     		//��ǰ΢��  e1-e2
    
    //����
    pidch->PreError  =    pidch->LastError;              							//�ϴ�ƫ������ϴ�ƫ��  e2=e1
    pidch->LastError =    Error;                 										//��ǰƫ����ϴ�ƫ��    e1=e0
    
    
    
    //////////������////////////////////////////////////////////////////MAX_PID_INTEGRAL

		    
		 if(types->Integral != 0)
		 	 {   
		    
        if( pidch->SumError   >  ( MAX_PID_INTEGRAL/(types->Integral) ) )
		        {
		         pidch->SumError  =  ( MAX_PID_INTEGRAL/(types->Integral) );
		        }
       else if(  pidch->SumError  <  ((MIN_PID_INTEGRAL) /(types->Integral))  )
		       {
		        pidch->SumError      =  (MIN_PID_INTEGRAL) /(types->Integral);  //PWM_PERIOD_PULSE
		       } 		    
		    
		  }
		//////////////////////    

		////////////////////    
    #if ENABLE_PID_DEBUG
    
    pidch->Px =   types->Proportion *  Error;	          //P����
    pidch->Ix =   types->Integral   *  pidch->SumError;	//I����  
    pidch->Dx =   types->Derivative *  dError;	        //D����
   
   
    total     =   pidch->Px + pidch->Ix + pidch->Dx;

    
    #else
    //��� Px+Ix+Dx
      total     =      types->Proportion * Error    +    types->Integral  *  pidch->SumError   +    types->Derivative * dError  ;              //���������
    #endif
    
    if( total < MIN_PID_RESOULT )
    	{   pidch->Qx  =  MIN_PID_RESOULT;
    	}
    else if( total > MAX_PID_RESOULT )
    	{
    		pidch->Qx   = MAX_PID_RESOULT;
    	}
    else {
    	    pidch->Qx   = total;
         }
         
        
}

