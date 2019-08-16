#ifndef    _PID_H   
#define    _PID_H

#define ENABLE_PID_DEBUG   1




#define MAX_PID_RESOULT              1000
#define MIN_PID_RESOULT              (-0)

#define MAX_PID_INTEGRAL             MAX_PID_RESOULT
#define MIN_PID_INTEGRAL             MIN_PID_RESOULT


/********************************************************
* PID控制结构体声明
*********************************************************/
//typedef struct 
//{
//    float Proportion;          //比例常数
//    float Integral;            //积分常数
//    float Derivative;          //微分常数
//    float MaxSumError;    
//    float MinSumError;    
//
//}PID_ParaStruct;

typedef struct 
{
    float Proportion;          //比例常数
    float Integral;            //积分常数
    float Derivative;          //微分常数
}PidParamStruct;


typedef struct 
{
    float SetPoint;            //设定目标
    
    float LastError;           //上次偏差
    float PreError;            //上上次偏差
    float SumError;            //累积偏差


#if ENABLE_PID_DEBUG
    float Px;									//P部分
    float Ix;        					//I部分  结果 Px+Ix+Dx
    float Dx;        					//D部分
#endif
   
    float Qx;                 //输出控制量
    
}PidBufStruct;  //临时变量




extern   PidParamStruct          *pPidMt;   //移相电机PID控制参数
extern   PidParamStruct          *pPidHt1;  //电加热PID控制参数
extern   PidParamStruct          *pPidHt2;  //电加热PID控制参数

extern   PidBufStruct            *pPidBufMt;   //移相电机PID临时变量缓冲器
extern   PidBufStruct            *pPidBufHt1;  //电加热PID临时变量缓冲器
extern   PidBufStruct            *pPidBufHt2;  //电加热PID临时变量缓冲器
/********************************************************
* Function:    PID_Calc
* Description: PID计算
* Input:       pPIDxxx  需要计算的PID控制结构体指针
*              NowPoint         实际反馈值
* Output:      float           PID运算结果
* Calls:       无
* Called by:   CtrlTemp
* Others:
*********************************************************/
//float

void PID_Init(void);
void PID_Calc(PidParamStruct *types, PidBufStruct *pidch, float NowPoint);
void PID_BufInit(PidBufStruct *pidch);
//void PID_ParaInit(void);

//void _ParamPointTab_Init_pid(void);//参数指针初始化

#endif

