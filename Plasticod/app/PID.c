
#include "includes.h"
#include "PID.h"

unsigned char flag_point_init = 0 ;  //pid参数指针已经初始化标记

   float PidMt[3];     //移相电机PID控制参数
   float PidHt1[3];    //电加热PID控制参数
   float PidHt2[3];    //电加热PID控制参数  
   float PidBuf_A[8];
   float PidBuf_B[8];
   float PidBuf_C[8];


PidParamStruct          *pPidMt;   //移相电机PID控制参数
PidParamStruct          *pPidHt1;  //电加热PID控制参数
PidParamStruct          *pPidHt2;  //电加热PID控制参数

PidBufStruct            *pPidBufMt;   //移相电机PID临时变量缓冲器
PidBufStruct            *pPidBufHt1;  //电加热PID临时变量缓冲器
PidBufStruct            *pPidBufHt2;  //电加热PID临时变量缓冲器

/////////////////////





void _ParamPointTab_Init_pid(void)//参数指针初始化
{

//   float PidMt[3];     //移相电机PID控制参数
//   float PidHt1[3];    //电加热PID控制参数
//   float PidHt2[3];    //电加热PID控制参数  
//   float PidBuf_A[8];
//   float PidBuf_B[8];
//   float PidBuf_C[8];
   
   
//	pPidMt = (PidParamStruct *)&gCommParam.PidMt[0];//移相电机PID控制参数
//  pPidHt1 = (PidParamStruct *)&gCommParam.PidHt1[0];//电加热PID控制参数
//  pPidHt2 = (PidParamStruct *)&gCommParam.PidHt2[0];//电加热PID控制参数
//
//
//	pPidBufMt = (PidBufStruct *)&gCommParam.PidBuf_A[0];
//	pPidBufHt1 = (PidBufStruct *)&gCommParam.PidBuf_B[0];
//	pPidBufHt2 = (PidBufStruct *)&gCommParam.PidBuf_C[0];	
//	
	
	pPidMt     = (PidParamStruct *)&PidMt[0];//移相电机PID控制参数
  pPidHt1    = (PidParamStruct *)&PidHt1[0];//电加热PID控制参数
  pPidHt2    = (PidParamStruct *)&PidHt2[0];//电加热PID控制参数


	pPidBufMt  =   (PidBufStruct *)&PidBuf_A[0];
	pPidBufHt1 =   (PidBufStruct *)&PidBuf_B[0];
	pPidBufHt2 =   (PidBufStruct *)&PidBuf_C[0];		
	
	flag_point_init = 1 ;  //pid参数指针已经初始化标记
}

//////////////////////////


void PID_BufInit(PidBufStruct *pidch)
{
	  if ( flag_point_init == 0 )  //pid参数指针已经初始化标记
	  	{
	  		return;
	  	}
	  //pidch->SetPoint=0;       //设定目标
   
    pidch->LastError	= 0;     //上次偏差
    pidch->PreError   = 0;      //上上次偏差
    pidch->SumError   = 0;     //累积偏差
    pidch->Qx=0;									//输出   结果 Px+Ix+Dx
    pidch->Px=0;		//P部分
    pidch->Ix=0;    //I部分  
    pidch->Dx=0;			//D部分	

}
/////////////////////////////////////////////////////////////////
void PID_Init(void)
{	
_ParamPointTab_Init_pid();//参数指针初始化 

	
//PID_ParaInit
	
//xxxxxxxxxxxxxxx	
//pPidMt  -> Proportion = 1; //1 ;          //比例常数
//pPidMt  -> Integral   = 0.05;//(0.1) ;     //积分常数
//pPidMt  -> Derivative = 0.1 ;          //微分常数

	//xxxxxxxxxxxxxxxx
//pPidMt  -> Proportion = 0.2;    //1 ;          //比例常数
//pPidMt  -> Integral   = 0.015;   //(0.1) ;     //积分常数
//pPidMt  -> Derivative =  0.0;          //微分常数

//60	
//pPidMt  -> Proportion = 0.4;    //1 ;          //比例常数
//pPidMt  -> Integral   = 0.1;   //(0.1) ;     //积分常数
//pPidMt  -> Derivative =  0.9;          //微分常数	


//65
//pPidMt  -> Proportion = 0.7;    //1 ;          //比例常数
//pPidMt  -> Integral   = 0.02;   //(0.1) ;     //积分常数
//pPidMt  -> Derivative =  0.2;          //微分常数		
	
//67	
//pPidMt  -> Proportion = 0.9;    //1 ;          //比例常数
//pPidMt  -> Integral   = 0.03;   //(0.1) ;     //积分常数
//pPidMt  -> Derivative =  3;          //微分常数		

//70
//pPidMt  -> Proportion = 1.3;    //1 ;          //比例常数
//pPidMt  -> Integral   = 0.03;   //(0.1) ;     //积分常数
//pPidMt  -> Derivative =  3;          //微分常数		

pPidMt  -> Proportion = 1.5;    //1 ;          //比例常数
pPidMt  -> Integral   = 0.05;   //(0.1) ;     //积分常数
pPidMt  -> Derivative =  2;          //微分常数		


	
//////////////////////////////////////////////////////////////

pPidHt1  -> Proportion = 5 ;          //比例常数
pPidHt1  -> Integral   = (0.01) ;     //积分常数
pPidHt1  -> Derivative = 0 ;          //微分常数

pPidHt2  -> Proportion = 5 ;          //比例常数
pPidHt2  -> Integral   = (0.01) ;     //积分常数
pPidHt2  -> Derivative = 0 ;          //微分常数

PID_BufInit( pPidBufMt  );
PID_BufInit( pPidBufHt1 );
PID_BufInit( pPidBufHt2 );

}




/********************************************************
* Function:    PID_Calc
* Description: PID计算
* Input:       PIDstruct *  需要计算的PID控制结构体指针
*              NowPoint         实际反馈值
* Output:      float           PID运算结果
* Calls:       无
* Called by:   CtrlTemp
* Others:
*********************************************************/
void PID_Calc(PidParamStruct *types, PidBufStruct *pidch, float NowPoint)
{
    float dError,Error;
    
    float total;
    
    Error            =    pidch->SetPoint   -   NowPoint   ;              //计算偏差  e0
    pidch->SumError  +=   Error;                      							//积分累加  e0++
    dError           =    pidch->LastError  -  pidch->PreError;     		//当前微分  e1-e2
    
    //更新
    pidch->PreError  =    pidch->LastError;              							//上次偏差赋给上上次偏差  e2=e1
    pidch->LastError =    Error;                 										//当前偏差赋给上次偏差    e1=e0
    
    
    
    //////////抗饱和////////////////////////////////////////////////////MAX_PID_INTEGRAL

		    
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
    
    pidch->Px =   types->Proportion *  Error;	          //P部分
    pidch->Ix =   types->Integral   *  pidch->SumError;	//I部分  
    pidch->Dx =   types->Derivative *  dError;	        //D部分
   
   
    total     =   pidch->Px + pidch->Ix + pidch->Dx;

    
    #else
    //结果 Px+Ix+Dx
      total     =      types->Proportion * Error    +    types->Integral  *  pidch->SumError   +    types->Derivative * dError  ;              //输出控制量
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

