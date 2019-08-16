#ifndef _PARAMETER_H
#define _PARAMETER_H


/////struct	struct_save

//参数已经初始化标记
#define FlagParamInitnized	0x33

#define Max_MemBuf  (120+100)

extern unsigned char cMemBufA[Max_MemBuf+2];
extern unsigned char cMemBufB[Max_MemBuf+2];


////////////////////////////////////////////////////////////////////////////

//typedef struct 
//{
//    float Proportion;          //比例常数
//    float Integral;            //积分常数
//    float Derivative;          //微分常数
//}PID_FineAdjustStruct;
//PidAdj




////////////////////////////////////////////////////////////////////////////

typedef struct
{   

   unsigned long  int  lCMD;
   unsigned long  int  lWATCHING;
   unsigned long  int  lBOARD_STATE;
   unsigned long  int  ldevice_type;

   unsigned long  int  lBaudrate_reserve;     //保留 波特率为准
   unsigned long  int  lyy_reserve;
    unsigned long  int  lSubAdr_reserve;           //保留 地址设置
   unsigned long  int  lSoftVer;   
   unsigned long  int  lBackupRestore;
   unsigned long  int  lSysSwitch_reserve;          //保留  默认开机 系统开关	

	 float fVS_AMP;		   //电压放大倍数
   float fVS_BIS;		   //电压偏移
   
   float fIS_AMP1;		 //电流放大倍数
   float fIS_BIS1;		 //电流偏移	bias
   float fIS_AMP2;		 //电流放大倍数
   float fIS_BIS2;		 //电流偏移	bias   
   float fIS_AMP3;		 //电流放大倍数
   float fIS_BIS3;		 //电流偏移	bias

   
   float fIF_SET;        //电流设定值,有效值
  
   unsigned long int   l_unit_ONOFF_flag[12];  //开启标识   //12ch

   
      //63  x 32bit   =  126 x16bit   //55  x 32bit   =  110 x16bit
   
	 float fIS[12];		//电流采样有效值    //12ch
	 float fPW;		//功率计算值        //12ch
	 float fVS;		//电压采样有效值	  //12ch	   

		 	 
	 float fMaxI;		//maxI电流最大限制
	 float fMaxV;		//maxV电压最大限制
	 float fMaxP;		//maxP功率最大限制
	 float fSetR;		    //setR电阻设定值	     
  
   unsigned long  int 	lStats1[4];  //统计信息  //12ch

  


   
   //(115+8) x 32bit   = 246 x16bit      //(99+8) x 32bit   = 214 x16bit
   
   float PidParamCtrl[3];    //高精度慢速度电流PID控制参数  PID_FineAdjustStruct
   float PidParamSync[3];    //同步PID控制参数
  
   float PidBuf_A[8];
   float PidBuf_B[8];

}   _paramter_for_modbus_struct;    // 字节
extern  _paramter_for_modbus_struct    gCommParam;


//extern unsigned char InitMemoFlag;		//参数已经初始化标记
//extern unsigned short int  MemoChecksum;    //校验码
//存储器参数
extern unsigned short int Stm32IdSum6;   


extern unsigned char ModBusParaByte[];   //modbus 参数 拷贝缓冲区

extern unsigned char FlagSetAllDefault;


void ParamPointInit(void);//参数指针初始化

void Default_ParamInit0(void);//不需要保存的参数
void Default_ParamInit1(void); //普通参数  //需要保存的参数
void Default_ParamInit2(void); //整定值

unsigned char Write_Param(void);
unsigned char Load_Param(void);
unsigned short int _Param_SwapMemery(unsigned char type,unsigned char *p);  //type = 0   Param --> memery_buf

//void ParamBlockCopyToModbusBuf(unsigned short int start_position , unsigned short int len);
//void ParamBlockCopyFromModbusBuf(unsigned short int start_position , unsigned short int len);

#endif




