#ifndef    _PID_H   
#define    _PID_H

#define ENABLE_PID_DEBUG   1




#define MAX_PID_RESOULT              1000
#define MIN_PID_RESOULT              (-0)

#define MAX_PID_INTEGRAL             MAX_PID_RESOULT
#define MIN_PID_INTEGRAL             MIN_PID_RESOULT


/********************************************************
* PID���ƽṹ������
*********************************************************/
//typedef struct 
//{
//    float Proportion;          //��������
//    float Integral;            //���ֳ���
//    float Derivative;          //΢�ֳ���
//    float MaxSumError;    
//    float MinSumError;    
//
//}PID_ParaStruct;

typedef struct 
{
    float Proportion;          //��������
    float Integral;            //���ֳ���
    float Derivative;          //΢�ֳ���
}PidParamStruct;


typedef struct 
{
    float SetPoint;            //�趨Ŀ��
    
    float LastError;           //�ϴ�ƫ��
    float PreError;            //���ϴ�ƫ��
    float SumError;            //�ۻ�ƫ��


#if ENABLE_PID_DEBUG
    float Px;									//P����
    float Ix;        					//I����  ��� Px+Ix+Dx
    float Dx;        					//D����
#endif
   
    float Qx;                 //���������
    
}PidBufStruct;  //��ʱ����




extern   PidParamStruct          *pPidMt;   //������PID���Ʋ���
extern   PidParamStruct          *pPidHt1;  //�����PID���Ʋ���
extern   PidParamStruct          *pPidHt2;  //�����PID���Ʋ���

extern   PidBufStruct            *pPidBufMt;   //������PID��ʱ����������
extern   PidBufStruct            *pPidBufHt1;  //�����PID��ʱ����������
extern   PidBufStruct            *pPidBufHt2;  //�����PID��ʱ����������
/********************************************************
* Function:    PID_Calc
* Description: PID����
* Input:       pPIDxxx  ��Ҫ�����PID���ƽṹ��ָ��
*              NowPoint         ʵ�ʷ���ֵ
* Output:      float           PID������
* Calls:       ��
* Called by:   CtrlTemp
* Others:
*********************************************************/
//float

void PID_Init(void);
void PID_Calc(PidParamStruct *types, PidBufStruct *pidch, float NowPoint);
void PID_BufInit(PidBufStruct *pidch);
//void PID_ParaInit(void);

//void _ParamPointTab_Init_pid(void);//����ָ���ʼ��

#endif

