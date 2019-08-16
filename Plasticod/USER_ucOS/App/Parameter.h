#ifndef _PARAMETER_H
#define _PARAMETER_H


/////struct	struct_save

//�����Ѿ���ʼ�����
#define FlagParamInitnized	0x33

#define Max_MemBuf  (120+100)

extern unsigned char cMemBufA[Max_MemBuf+2];
extern unsigned char cMemBufB[Max_MemBuf+2];


////////////////////////////////////////////////////////////////////////////

//typedef struct 
//{
//    float Proportion;          //��������
//    float Integral;            //���ֳ���
//    float Derivative;          //΢�ֳ���
//}PID_FineAdjustStruct;
//PidAdj




////////////////////////////////////////////////////////////////////////////

typedef struct
{   

   unsigned long  int  lCMD;
   unsigned long  int  lWATCHING;
   unsigned long  int  lBOARD_STATE;
   unsigned long  int  ldevice_type;

   unsigned long  int  lBaudrate_reserve;     //���� ������Ϊ׼
   unsigned long  int  lyy_reserve;
    unsigned long  int  lSubAdr_reserve;           //���� ��ַ����
   unsigned long  int  lSoftVer;   
   unsigned long  int  lBackupRestore;
   unsigned long  int  lSysSwitch_reserve;          //����  Ĭ�Ͽ��� ϵͳ����	

	 float fVS_AMP;		   //��ѹ�Ŵ���
   float fVS_BIS;		   //��ѹƫ��
   
   float fIS_AMP1;		 //�����Ŵ���
   float fIS_BIS1;		 //����ƫ��	bias
   float fIS_AMP2;		 //�����Ŵ���
   float fIS_BIS2;		 //����ƫ��	bias   
   float fIS_AMP3;		 //�����Ŵ���
   float fIS_BIS3;		 //����ƫ��	bias

   
   float fIF_SET;        //�����趨ֵ,��Чֵ
  
   unsigned long int   l_unit_ONOFF_flag[12];  //������ʶ   //12ch

   
      //63  x 32bit   =  126 x16bit   //55  x 32bit   =  110 x16bit
   
	 float fIS[12];		//����������Чֵ    //12ch
	 float fPW;		//���ʼ���ֵ        //12ch
	 float fVS;		//��ѹ������Чֵ	  //12ch	   

		 	 
	 float fMaxI;		//maxI�����������
	 float fMaxV;		//maxV��ѹ�������
	 float fMaxP;		//maxP�����������
	 float fSetR;		    //setR�����趨ֵ	     
  
   unsigned long  int 	lStats1[4];  //ͳ����Ϣ  //12ch

  


   
   //(115+8) x 32bit   = 246 x16bit      //(99+8) x 32bit   = 214 x16bit
   
   float PidParamCtrl[3];    //�߾������ٶȵ���PID���Ʋ���  PID_FineAdjustStruct
   float PidParamSync[3];    //ͬ��PID���Ʋ���
  
   float PidBuf_A[8];
   float PidBuf_B[8];

}   _paramter_for_modbus_struct;    // �ֽ�
extern  _paramter_for_modbus_struct    gCommParam;


//extern unsigned char InitMemoFlag;		//�����Ѿ���ʼ�����
//extern unsigned short int  MemoChecksum;    //У����
//�洢������
extern unsigned short int Stm32IdSum6;   


extern unsigned char ModBusParaByte[];   //modbus ���� ����������

extern unsigned char FlagSetAllDefault;


void ParamPointInit(void);//����ָ���ʼ��

void Default_ParamInit0(void);//����Ҫ����Ĳ���
void Default_ParamInit1(void); //��ͨ����  //��Ҫ����Ĳ���
void Default_ParamInit2(void); //����ֵ

unsigned char Write_Param(void);
unsigned char Load_Param(void);
unsigned short int _Param_SwapMemery(unsigned char type,unsigned char *p);  //type = 0   Param --> memery_buf

//void ParamBlockCopyToModbusBuf(unsigned short int start_position , unsigned short int len);
//void ParamBlockCopyFromModbusBuf(unsigned short int start_position , unsigned short int len);

#endif




