//user.c

#include "includes.h"
//extern 
#include "config.h"	
#include "ClearErrSample.h"

#include  "user_ucOS.h"
#include  "nomal.h"
#include "HT1621.h"
#include "lcd.h"
#include "adc.h"

#include "app1.h"

#include	"GetAverage.h"



  #if CONFIG_SPI1
      #include "SPI1.h"
  #endif

 #if CONFIG_PWM_TIM1
   #include "pwm1.h"
 #endif


OS_EVENT *OSSemGetAA;
OS_EVENT *OSSemOutCC;
OS_EVENT *OSSemRfcc1100;
OS_EVENT *OSSemUart1;
//OS_EVENT *OSSemOutSwOn;

unsigned char    LedEventTime1;
unsigned char    LedRunStatu1;


//uint16 giCodeChecksum;

//uchar FlagCheckStm32DeviceId;

unsigned char TimeForSaveParam;



//struct	struct_save *gpParam;
//uchar gbParamBuf[Max_Param_Len+2];

//unsigned short int  MotorPow;


//虚拟PWM  A 组 通道数目
#define PwmVirChNumberA   2
//虚拟PWM  A 组 周期
#define PwmVirCycleA      1000

//虚拟PWM  B 组 通道数目
#define PwmVirChNumberB   2
//虚拟PWM  B 组 周期
#define PwmVirCycleB      10
//////////假设的缓冲区 A组//////////////
unsigned short int  PwmValBufA[PwmVirChNumberA];
unsigned char       FlagOnBufA[PwmVirChNumberA];   //控制开关相应的虚拟pwm
///////////////////////

//////////假设的缓冲区 B组//////////////
unsigned short int  PwmValBufB[PwmVirChNumberB]={10,10};
unsigned char       FlagOnBufB[PwmVirChNumberB]={1,1};  //控制开关相应的虚拟pwm


#define SetVirtualPwmOutPinA1   HEAT1_1()
#define ClrVirtualPwmOutPinA1   HEAT1_0()
#define SetVirtualPwmOutPinA2   HEAT2_1()
#define ClrVirtualPwmOutPinA2   HEAT2_0()

#define SetVirtualPwmOutPinB1   BackLight_1()
#define ClrVirtualPwmOutPinB1   BackLight_0()

extern GPIO_InitTypeDef GPIO_InitStructure2;

//////////////////////////////////////////////////
/////////////////////////////////////////////////

#define TEST_MODBUS_78   0 
  
  
#if TEST_MODBUS_78
void TestModbus(void)
{
	
uchar MODBUS_TESTBUF1[]=
 {//read
	125,0x03,      //adr func
	0x02,0x00,    //parameter adr 
	0x00,0x32,     //len
	0xCE,0x5B  //checksum	  0XCE5B
 };
uchar MODBUS_TEST_LEN1= 8;
	
uchar MODBUS_TESTBUF2[]=
 {//read
	125,0x03,      //adr func
	0x02,0x04,    //parameter adr 
	0x00,0x04,     //len
	0x0F,0x8C  //checksum	  0X0F8C
 };
uchar MODBUS_TEST_LEN2= 8;

uchar MODBUS_TESTBUF3[]=
 {//write
	124,0x10,      //adr func
	  0x00,0x04,    //parameter adr 
	  0x00,0x06,   //parameter  word number
	  0x0C,     //byte len
	  0x05,0x06,0x07,0x08,
	  0x01,0x02,0x03,0x04,
	  0x0a,0x0b,0x0c,0x0d,
	0x1D,0xCC  //checksum	  0x1DCC
 };
uchar MODBUS_TEST_LEN3= 21;

 uchar MODBUS_TESTBUF4[]=
 {//write
	124,0x10,      //adr func
	0x00,0x00,    //parameter adr 
	0x00,0x04,   //parameter  word number
	0x08,     //byte len
	0x01,0x02,0x03,0x04,
	0x05,0x06,0x07,0x08,
	0xFB,0x9F  //checksum	  0XFB9F
 };
uchar MODBUS_TEST_LEN4= 17;

ModbusRecvProcess(MODBUS_TESTBUF1,MODBUS_TEST_LEN1);
ModbusRecvProcess(MODBUS_TESTBUF2,MODBUS_TEST_LEN2);
ModbusRecvProcess(MODBUS_TESTBUF3,MODBUS_TEST_LEN3);
ModbusRecvProcess(MODBUS_TESTBUF4,MODBUS_TEST_LEN4);


}
#endif  
//////////////////////////D/////////////////////


//struct str_adc_resoult
//{
//unsigned short int 	temprature0;
//unsigned short int 	rpm;
//unsigned short int 	temprature1;
//unsigned short int 	temprature2;
//unsigned short int 	current;
//unsigned short int 	volt;
//	
//}AdcRes;

///////////////////////







/**************************************************************************************
 * FunctionName   : 
 * Description    : 获取编译时间[BCD码：YY-MM-DD HH:MM:SS]
 * EntryParameter : pTim - 转换后的BCD码，mode - 模式[0-日期，1-时间，2-日期+时间]
 * ReturnValue    : None
 **************************************************************************************/
unsigned long int GetDate(void)
 {
 //unsigned char  pTim[10];
  unsigned char  tmpDty[] = {__DATE__}; // mar 1 2016 

 //unsigned char  tmpDty[] = "Jan 28 2018"; // mar 1 2016 

 //unsigned char   tmpTim[] = {__TIME__};
 unsigned char   tmpMth[][3] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

 unsigned long int ldate;

 unsigned char   i = 0;


   
    
   if(tmpDty[5] == ' ')
   	   {
   		//  pTim[k++]=AscToHex(tmpDty[8]);
   		 // pTim[k++]=AscToHex(tmpDty[9]);
		  ldate =  AscToHex(tmpDty[8])*100000;
		  ldate +=  AscToHex(tmpDty[9])*10000;
   	   }                                 
   else{
   	    //pTim[k++]=AscToHex(tmpDty[9]);
   		 // pTim[k++]=AscToHex(tmpDty[10]);

	  	  ldate =  AscToHex(tmpDty[9])*100000;
		  ldate +=  AscToHex(tmpDty[10])*10000;

       }                                 
                                    
                                    
   for (i=0; i<12; i++)
     {
       if (!memcmp(&tmpMth[i][0], &tmpDty[0], 3))         // 查找月份
         {
         // pTim[k++] = i+1;

		  ldate +=  ((i+1)/10)*1000;
		  ldate +=  ((i+1)%10)*100;
          break;
         }
     }

  if(tmpDty[5] == ' ')
	   {
	//	 pTim[k++]=AscToHex(tmpDty[4]);
		 
		 ldate +=  AscToHex(tmpDty[4]);
	   }
  else{
   	     // pTim[k++]=AscToHex(tmpDty[4]);
   		 // pTim[k++]=AscToHex(tmpDty[5]);
		  ldate +=  AscToHex(tmpDty[4])*10;
		  ldate +=  AscToHex(tmpDty[5]);
       }
  	
 return ldate; 	
 }



/////////////////
void ViewTestStatu(uchar *text)
{
	INT8U err;
	

	
#if (OS_VIEW_MODULE == DEF_ENABLED)
			OSView_TxStr(text, 1);
#else
		#if CONFIG_UART1
						OSSemPend(OSSemUart1,0,&err);
			SendText_UART1(text);	
	OSSemPost(OSSemUart1);
		#endif
		#if CONFIG_UART2
					SendText_UART2(text);
		#endif		
					
#endif
}
////////




void AutoSend(void)
{
	uchar len;
//&ET,0,I1=00002,I2=00000,......FMax1=00205,FMax2=00205,....A10=00003,....A1=00005,A2=00000,A3=01946,A4=01965,
	
	uchar buf[60];
	len		=	PutString("&ET,",buf,5);								//head 4
	buf[len]=HexToAsc(0x01);		//

	len++;
	buf[len]=',';
	len++;
	
//	buf[len]=HexToAsc(STM32DeviceId.Checked);		//
//	len++;
//	buf[len]=',';
//	len++;
		
//	len		+=	MakeValAsc16("I1=",56,",",&buf[len]);	//电流100ma
//	len		+=	MakeValAsc16("I2=",57,",",&buf[len]);	//电流100ma
	
	len		+=	MakeValAsc16("Px=",pPidBufMt ->Px,",",&buf[len]);	//电流100ma
	len		+=	MakeValAsc16("Ix=",pPidBufMt ->Ix,",",&buf[len]);	//电流100ma
  len		+=	MakeValAsc16("Dx=",pPidBufMt ->Dx,",",&buf[len]);	//电流100ma
  
len		+=	PutString("\r\n",&buf[len],5);

//SendText_UART2(buf);	
ViewTestStatu(buf);
		
}
///////////////////////////////



/////////////////////////////////
void SendTestMasgToUart(uchar *p)
{
ViewTestStatu(p);
}

/////////////////////////////////



/////////////////////////////////////////








/////////////////////////



/////////////////////////



////////////////////
void Run_Init(void)
{

#if CONFIG_ADC
ADC_Configuration();
#endif


#if CONFIG_PWM_TIM1
NVIC_Configuration_PWM_T1();
GPIO_Configuration_PWM_T1();
PWM_T1_Configuration();  
#else

#endif


#if CONFIG_PWM_TIM3
NVIC_Configuration_PWM_T3();
GPIO_Configuration_PWM_T3();
PWM_T3_Configuration();  
#endif


#if CONFIG_PWM_TIM4
NVIC_Configuration_PWM_T4();
GPIO_Configuration_PWM_T4();
PWM_T4_Configuration();  
#endif

#if CONFIG_SPI1
GPIO_Configuration_SPI1();
SPI1_Configuration();
#endif


#if CONFIG_SPI2
//8bit
GPIO_Configuration_SPI2();
SPI2_Configuration();




#endif


		
							
							
//OUT_ENALL_SET;				//脉冲输出总开关	

}
////////////////////







/////////////////////////////////////////


void TaskEvent_old(void * pdata)
{
//INT8U err;
 
	pdata = pdata;                          	 	// 避免编译警告	   

OSTimeDly(OS_TICKS_PER_SEC/5);	    //延时0.2秒


	for(;;)
				{
				//OS_ENTER_CRITICAL();   //CPU_SR         cpu_sr;
				//OS_EXIT_CRITICAL();



		OSTimeDly(OS_TICKS_PER_SEC/100);	    //延时0.01秒
		  #if CONFIG_ADC
					//AdcFilter();
					  
//					#if CONFIG_UART1
//						 	#if   ( OS_VIEW_MODULE != DEF_ENABLED )|| (OS_VIEW_USART_NUMBER != 1) 
//											SendText_UART1("....");
//											
//											for(i=0;i<MAX_ADC_CH;i++)
//														{
//														MakeValAsc16("",After_filter[i]*330/4096,"V,",buf);
//														SendText_UART1(buf);
//														}
//											SendText_UART1("\r\n");
//							#endif
//					#endif
			#endif
				   
				//	OSTimeDly(OS_TICKS_PER_SEC/1000);	    //延时0.001秒		

					}
}
/////////////////////////////



/////////////////////////////
void TaskRpm(void * pdata)  // synchronous
{
	INT8U err;
 	pdata = pdata;                          	 	// 避免编译警告	   

PID_Init();

OSTimeDly(OS_TICKS_PER_SEC/10);	    //延时0.1秒


					

//////
	for(;;)
				{
				//OS_ENTER_CRITICAL();   //CPU_SR         cpu_sr;
				//OS_EXIT_CRITICAL();

          //交流测速发电机   // AdcRes.RpmCur CurRpmDisplay
          //pid    LcdPort.RpmSet * 10
          
          
			  	  OSSemPend(OSSemOutCC,0,&err);
         
          if (  (  LcdPort.MovingF  ==  0 ) &&  ( LcdPort.RpmBackSet == 0  )  )
          	        {//不工作时
                    PID_BufInit( pPidBufMt  );
            
                    #if  0 * ENABLE_TEST_MOD
           
                            LcdPort.RpmOut        =   ( 10 * LcdPort.RpmSet );      //速度控制值
              
                    #else
           
                            LcdPort.RpmOut        =   0;
             
                    #endif
                    }
          else{
          	#if CONFIG_RPM_DIGTAL
          	//数字反馈控制
                 if ( LcdPort.MovingF  ==  1 )
                           {
                            pPidBufMt -> SetPoint = LcdPort.RpmSet * 10 ;       //设定目标
                           }
                 else{
          	               pPidBufMt -> SetPoint = LcdPort.RpmBackSet ;   //倒退速度
          	              }
          
          
                  PID_Calc( pPidMt , pPidBufMt , AdcRes.RpmCur );
          
                  LcdPort.RpmOut    =  (unsigned short int)pPidBufMt -> Qx ;     //速度控制值
        #else
              LcdPort.RpmOut  =    LcdPort.RpmSet;
        #endif      
                    }
           
            //电机控制量转化为移相值
            
            
            
            
           PmwVal_TIM1_ch1 = PowerToShiftTimr( LcdPort.RpmOut  );
           
           ////////////////////////
//           pPidBufMt -> SetPoint = LcdPort.RpmSet * 10 ;       //设定目标
//           PID_Calc( pPidMt , pPidBufMt , AdcRes.RpmCur );
//           PmwVal_TIM1_ch1 = PowerToShiftTimr( pPidBufMt -> Qx  );
           //PmwVal_TIM1_ch1 = PowerToShiftTimr( LcdPort.RpmSet * 10   );
           ////////////////////////////////////////////
           
           TIM_SetCompare1(TIM1,PmwVal_TIM1_ch1);
	// #if CONFIG_RPM_DIGTAL
	
          //OSTimeDly(OS_TICKS_PER_SEC/50);	    //延时  20MS      
           //OSTimeDly(OS_TICKS_PER_SEC/100);	    //延时  10MS
           OSTimeDly(OS_TICKS_PER_SEC/500);	    //延时  2MS
            
					}
}
///////////////电加热控制//////////////
void  _HeatContral( void )  //电加热控制
{//  间隔	1s  通知电加热控制12
	static unsigned char ChSel;
	ChSel ++;
	//if( ChSel & 0x01 )
	//	{
			 //AdcRes.temptemprature1;              //温度1
			 //LcdPort.TempratureSet
			 
			 pPidBufHt1 -> SetPoint = LcdPort.TempratureSet ;   //设定目标
			 PID_Calc( pPidHt1 , pPidBufHt1 , AdcRes.temptemprature1 )	 ;
			 
			 PwmValBufA[0] =  pPidBufHt1 -> Qx;
			//FlagOnBufA[1];   //控制开关相应的虚拟pwm

	//	}
//else{
	    //AdcRes.temptemprature2;              //温度2
	    //LcdPort.TempratureSet
	    
	    //pid
	    pPidBufHt2 -> SetPoint = LcdPort.TempratureSet ;   //设定目标
			PID_Calc( pPidHt2 , pPidBufHt2 , AdcRes.temptemprature2 )	 ;
			
	   	PwmValBufA[1] =   pPidBufHt2 -> Qx;
	   	//FlagOnBufA[1];   //控制开关相应的虚拟pwm
//	  }
	
	 

        
         
	

	
} 

/////////////////////////////
//unsigned short int GetAverage(unsigned short int *buf , unsigned short int MaxSize)
uint16 GetAverSS(unsigned short int *p , unsigned short int *buf , unsigned short int MaxSize)//(&AvergeBufI[ ChannelsAvergeGa ][ 0 ] , MaxNumbAvergeGa );
{
		

uint16 val;

#if CONFIG_CLEAR_ERR


uint16 j;

uint16 length;
uint32 sum;
	
		
			if( MaxSize > MaxSampleBufLen )
				{
					MaxSize = MaxSampleBufLen ;
				}
			
			
			//第一路电流
			for(j=0;j<MaxSize;j++)
			   {
				 buf[j] = *p;  
			   }
			length = ClearSample( buf ,MaxSize );
			
			//////////////////////////
			//gl_length_for_moni= length;
			

			sum = 0;
			for(j=0;j<length ;j++)
			    {
				  sum += buf[j];
			    }
			if(length >=2 )
				{
				val = (uint16)(sum/length);
				}
      else{
      	   //val = 0;
          }
          
   #else   
   
      val = GetAverage(p , MaxSize)  ;  
          
          
      #endif    
          return val;
}          
          
////          
//////////////////////////////////          
//测速发电机，温度测量x2，环境温度，电压，电流
          
void TaskMeasure(void * pdata)
{
INT8U err;

uchar i;

unsigned short int temp16;

#if MaxNumbAvergeGb > MaxNumbAvergeGa

   unsigned short int buf_temp [ MaxNumbAvergeGb ];
#else 

   unsigned short int buf_temp [ MaxNumbAvergeGa ];
   
#endif

OSTimeDly(OS_TICKS_PER_SEC/5);	    //延时0.2秒

pdata = pdata;                          	 	// 避免编译警告		


for(;;)
		{

    
    

    /*
    if ( AD_Value[0][0] != 0xffff )
    	{
    		AD_Value[0][0] = 0xffff;
    		LED_TEST_GET_OFF;
    
    	}
    else 	{
          LED_TEST_GET_ON;
         }
    */
    
    OSSemPend(OSSemGetAA,0,&err);
    
    Get_ChipAdc_Measure();
    
    //After_filter[1]  *990 /4095 ;             //转速， 最大99
    //AddAverage(unsigned short int *buf,unsigned short int *offset,unsigned short int add , unsigned short int MaxSize);
    
    AddAverage( &AvergeBufGb[0] , &AvergeOffsetGb , After_filter[1] , MaxNumbAvergeGb );
    
    //AdcRes.temptemprature1   = After_filter[2] /8 ;              //温度1
    //AdcRes.temptemprature2   = After_filter[3] /8 ;              //温度2
    //AdcRes.current           = After_filter[4] /8;              //电加热电流
	  //AdcRes.volt              = After_filter[5] /20;              //电源电压
    //AddAverage(unsigned short int *buf,unsigned short int *offset,unsigned short int add , unsigned short int MaxSize);
 
    for( i = 0 ; i < 4 ; i ++ )
         {
    	   AddAverage( &AvergeBufGa[ i ][0] , &AvergeOffsetGa[ i ] , After_filter[ 2 + i ] , MaxNumbAvergeGa);
         }
 
 
   
    //交流测速发电机
    AdcRes.RpmCur            =    After_filter[1] * 990 /4095 ;
    //AdcRes.RpmDisplay   =  = GetAverSS( &AvergeBufGb[ 0 ]  , buf_temp , MaxNumbAvergeGb ) * 99 /4095 ;           //转速， 最大99 ,控制时内部扩大10倍
    //AdcRes.RpmDisplay   =AdcRes.RpmCur /10; 
    AdcRes.RpmDisplay   =LcdPort.RpmSet/10;
    //temp16                   = GetAverSS( &AvergeBufGa [ 0 ][ 0 ]  , buf_temp , MaxNumbAvergeGa );              //温度1
    temp16                   = After_filter[2] ;
    AdcRes.temptemprature1   = InterPointCala( temp16 );
    temp16                   = GetAverSS( &AvergeBufGa [ 1 ][ 0 ]  , buf_temp , MaxNumbAvergeGa ) ;              //温度2
    AdcRes.temptemprature2   = InterPointCala( temp16 );
    AdcRes.current           = GetAverSS( &AvergeBufGa [ 2 ][ 0 ]  , buf_temp , MaxNumbAvergeGa ) /8;               //电加热电流
    AdcRes.volt              = GetAverSS( &AvergeBufGa [ 3 ][ 0 ]  , buf_temp , MaxNumbAvergeGa ) /20;              //电源电压
	  

   
    OSSemPost(OSSemOutCC);   //  间隔	  通知电控制

    //OSTimeDly(OS_TICKS_PER_SEC/50);	    //延时0.02秒
    //OSTimeDly(OS_TICKS_PER_SEC/100);	    //延时0.01秒
    OSTimeDly(OS_TICKS_PER_SEC/500);	    //延时2ms秒        
			}		
}


////////////////////////////////////////////////
void TaskSave(void * pdata)
{
//INT8U err;
//CPU_SR         cpu_sr;

 
	pdata = pdata;                          	 	// 避免编译警告	   

//InterPoint_Test();

OSTimeDly(OS_TICKS_PER_SEC/5);	    //延时0.2秒

	for(;;)
				{
				 AutoSend();
				 /*
          
							
        if(FlagSetAllDefault > 0)//flag
        	   {
        	   	
        	   	if(3 == FlagSetAllDefault)
				 	      {
         
                Default_ParamInit1();    ////需要保存的参数
                Default_ParamInit2();    ////整定值
                }
        	   	else if(2 == FlagSetAllDefault)
				 	      {
         
                Default_ParamInit1();    ////需要保存的参数

                }
        	   	
        	   	Default_ParamInit0();//不需要保存的参数
        	   	
        	   	FlagSetAllDefault = 0 ;
        	   	
        	#if SOFT_CONFIG_EEPROM
             //自动恢复默认值
             cMemBufA[Max_MemBuf-2] =  FlagParamInitnized; 
             
             OS_ENTER_CRITICAL();   //CPU_SR         cpu_sr;
             _Param_SwapMemery(0,cMemBufA);   //parameter ---> cMemBufB
              OS_EXIT_CRITICAL();
              
             Write_Param();
         #endif
             
             
             }
          
          
          
          
          if(TimeForSaveParam==1)  //延时保存
          	{
							//////
					#if SOFT_CONFIG_EEPROM	
						 OS_ENTER_CRITICAL();   //CPU_SR         cpu_sr;
	            _Param_SwapMemery(0,cMemBufA);   //parameter ---> cMemBufB
	            TimeForSaveParam = 0;
             OS_EXIT_CRITICAL();
             Write_Param();
          #endif  
						}
						
					if(TimeForSaveParam>0)
						{
							TimeForSaveParam	-- ;
						}
						
				*/		
				OSTimeDly(OS_TICKS_PER_SEC);	    //延时1秒		
			}		
}

//////////////////
void TaskAverage(void * pdata)
{
//INT8U err;
pdata = pdata;                          	 	// 避免编译警告		
OSTimeDly(OS_TICKS_PER_SEC/5);	    //延时0.2秒
for(;;)
		{


		OSTimeDly(OS_TICKS_PER_SEC/10);	    //延时0.1秒


         	
		}
}
////////////////////


void TaskKey(void * pdata)
{
//INT8U err;

 unsigned char temp;

	pdata = pdata;  
	FlagDebug_SWCLK_Off =  1 ;
	FlagEnable_TestMod  =  0 ;
	
  SetMods = ModNomal ;
   LcdPort.RpmOut  = 0;  //800;     //速度控制值
   

   
	OSTimeDly(OS_TICKS_PER_SEC*2);	    //延时1秒
	AutoSend();
 

		for(;;)
						{
						//OS_ENTER_CRITICAL();   //CPU_SR         cpu_sr;
						//OS_EXIT_CRITICAL();
						OSTimeDly(OS_TICKS_PER_SEC/500);	    //延时0.02秒		
				

            
            //LedSwitchOn1
            //LedSwitchOn2	
				   //i= KeyLedScan( 0x03f  );
							
							LedSwitchOn1;
           temp = KeyLedScan( LedsBuf  ) ;
           
							KeyGet  ( temp  );
           //LedsBuf = (temp);
           
          
           if( KeyScan.resoult ==  (16 + 32 ) )
           	{ //通过键盘取消SWCLK
           		//KeyScan.age
           		
           	#if ENABLE_SWITCH_OFF_DEBUG //(  SWD_DEBUG_DISABLE  +  0  )
           	if(FlagDebug_SWCLK_Off  == 1)
           		{  //关闭调试，使用SWCLK     PwmValBufB
           			FlagDebug_SWCLK_Off  = 0;
           			
           			GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);     //SWD口和jtag口全部都取消  Full SWJ Disabled (JTAG-DP + SW-DP)
                //SWCLK  PA14
                GPIO_InitStructure2.GPIO_Speed =  GPIO_Speed_50MHz;
                GPIO_InitStructure2.GPIO_Mode  =  GPIO_Mode_Out_PP;  //GPIO_Mode_IN_FLOATING;	
                GPIO_InitStructure2.GPIO_Pin = PIN_BackLight;
                GPIO_Init(PORT_BackLight,&GPIO_InitStructure2);
               }
            #endif
            
           	}
           
//           if( KeyScan.resoult ==  0x01 )
//           	{
//           		if(MotorPow <995 ) MotorPow +=5;
//           	}
//           if( KeyScan.resoult ==  0x02)
//           	{
//           		if(MotorPow >= 5 ) MotorPow -=5;
//           	}	
//           LcdPort.val1 = MotorPow;
//           LcdPort.val2 = temp;

          /*
           #if Test_lcd
           _TestLcd();
           #endif

           //  #if Test_lcd

             
             

//SEG1 SEG2 SEG3   显示非数字  对应  Ht1621FlagTab1
//void LcdFlagDecode123( unsigned char *s ,  unsigned char *buf );    //lcd Datbuf 5
//SEG4 SEG5   显示非数字  对应  Ht1621FlagTab2
//void LcdFlagDecode45(unsigned char *s   ,  unsigned char *buf);    //lcd Datbuf 0
             
        
           //SEG1 SEG2 SEG3   显示999  对应  Ht1621DigtTab1
           LcdDigetDecode123( LcdPort.val1 , Ht1621buf );   //lcd Datbuf 5
           //SEG4 SEG5   显示99  对应  Ht1621DigtTab2
           LcdDigetDecode45( LcdPort.val2  , Ht1621buf );    //lcd Datbuf 0
           
//                LcdFlag_TempratureSetMod(0);
     
    */

        			
					}	
}



///////////////////////////
void TaskStatu(void * pdata)
{
//INT8U err;
uchar i;

pdata = pdata;                          	 	// 避免编译警告		
LedRunStatu1 =0;

OSTimeDly(OS_TICKS_PER_SEC/2);	    //延时0.2秒

for(i=0;i<3;i++)
				{

				  OSTimeDly(OS_TICKS_PER_SEC/2);	    //延时0.2秒
					
					LedOnAll;

					OSTimeDly(OS_TICKS_PER_SEC/2);	    //延时0.2秒
				
          LedOffAll;
	
				}


		
    for (;;)
    {
	switch(LedRunStatu1)
	{
	case 2:		//2次/2秒

			
	LED_RUN1_ON;//SetLED_Statu1;
        OSTimeDly(OS_TICKS_PER_SEC / 8);	//延时0.125秒
  LED_RUN1_OFF;//ClrLED_Statu1;
        OSTimeDly(OS_TICKS_PER_SEC / 4);	//延时0.25秒
	LED_RUN1_ON;//SetLED_Statu1;
        OSTimeDly(OS_TICKS_PER_SEC / 8);	//延时0.125秒
  LED_RUN1_OFF;//ClrLED_Statu1;        
        OSTimeDly(6*OS_TICKS_PER_SEC/4);	  	//延时1.5秒
	break;
	
	case 1:		//1次/2秒
		
	LED_RUN1_ON;//SetLED_Statu1;
        OSTimeDly(OS_TICKS_PER_SEC / 4);	//延时0.25秒
  LED_RUN1_OFF;//ClrLED_Statu1;
        OSTimeDly(7*OS_TICKS_PER_SEC/4);	  	//延时1.75秒
	break;
	
	default:	
	case 0:	//1次/2秒
	LED_RUN1_ON;//SetLED_Statu1;
        OSTimeDly(OS_TICKS_PER_SEC);	//延时0.5秒
  LED_RUN1_OFF;//ClrLED_Statu1;
        OSTimeDly(OS_TICKS_PER_SEC);	  	//延时5秒
	
	break;	
	}
    }		
		
		
		
		
}
////////////////////



////////////////////////////
void  TaskEvent(void *pdata)   //TaskLED_Event1(void *pdata)	//事件指示灯1，LedEventTime1单位1S
{
	
	unsigned char Timexx;
    pdata = pdata;                          	 	// 避免编译警告

  LedEventTime1=0;
  Timexx = 0 ;


    for (;;)
    {
        
        if(Timexx < LedEventTime1)
        	{
        		Timexx = LedEventTime1;
        	}
        
        
        
        if(Timexx>0)
        	{
        	LED_EVENT_ON;//SetLED_Event1;
        	OSTimeDly( Timexx*OS_TICKS_PER_SEC/10 );	 	  //延时LedEventTime/10秒
        	Timexx = 0 ;
        	LedEventTime1=0;
        	LED_EVENT_OFF;//ClrLED_Event1;
        	}
        	
        LcdPort.flashing ++ ;	   //lcd闪烁
	OSTimeDly(OS_TICKS_PER_SEC/5);	     //Led延时0.2秒
    }
}
////////////////////////////




void TaskModbus(void * pdata)
{
//INT8U err;
//CPU_SR          cpu_sr;

pdata = pdata;                          	 	// 避免编译警告		



OSTimeDly(OS_TICKS_PER_SEC/5);	    //延时0.2秒



#if CONFIG_MODBUS
ModbusInit();
#endif


#if TEST_MODBUS_78
 TestModbus();
#endif

OSTimeDly(OS_TICKS_PER_SEC/5);	    //延时0.2秒

for(;;)
		{




       OSTimeDly(OS_TICKS_PER_SEC/500);	    //延时2毫秒

     #if CONFIG_MODBUS
	
	
			CPU_CRITICAL_ENTER();                                       /* Tell uC/OS-II that we are starting an ISR            */

   
     //这是原来有BUG的地方
		   ModbusTimeHandler();
  
       CPU_CRITICAL_EXIT();
		
		
		
		   GetModbusPark();  //慢点也可以
		
		 #endif
		}
}

////////////////////

#define Test_lcd   0

#if Test_lcd
void _TestLcd(void)
{
static	unsigned short int   j,k;
	    
	    j++; k++;


//SEG1 SEG2 SEG3   显示非数字  对应  Ht1621FlagTab1
//void LcdFlagDecode123( unsigned char *s ,  unsigned char *buf );    //lcd Datbuf 5
//SEG4 SEG5   显示非数字  对应  Ht1621FlagTab2
//void LcdFlagDecode45(unsigned char *s   ,  unsigned char *buf);    //lcd Datbuf 0
               //SEG1 SEG2 SEG3   显示999  对应  Ht1621DigtTab1
           LcdDigetDecode123( j%999  , Ht1621buf  );   //lcd Datbuf 5
           //SEG4 SEG5   显示99  对应  Ht1621DigtTab2
           LcdDigetDecode45( k%99  , Ht1621buf );    //lcd Datbuf 0
    
     LcdFlag_TempratureSetMod(0);
     
     LcdRefuse();   
     OSTimeDly(OS_TICKS_PER_SEC);	    //延时1秒
     
     j++;
     
               //SEG1 SEG2 SEG3   显示999  对应  Ht1621DigtTab1
           LcdDigetDecode123( j%999  , Ht1621buf );   //lcd Datbuf 5
           //SEG4 SEG5   显示99  对应  Ht1621DigtTab2
           LcdDigetDecode45( k%99  , Ht1621buf );    //lcd Datbuf 0
    
     LcdFlag_TempratureSetMod(1);
     LcdRefuse();
    OSTimeDly(OS_TICKS_PER_SEC);	    //延时1秒
}
#endif
////////////////////
void TaskRuning(void * pdata)
{
	
//INT8U err;

//unsigned short int   i,j,k,temp16;
unsigned long int   temp32;

pdata = pdata;                          	 	// 避免编译警告		

//FlagSetAllDefault = 0 ;
TimeForSaveParam = 0;

  //_ParamPointTab_Init_pid();

 //Default_ParamInit0();//不需要保存的参数

 
 temp32    = GetDate();
 
LcdPort.RpmSet = 8;
LcdPort.TempratureSet =  100;

   LcdPort.RpmOut  = 0;  //800;     //速度控制值
LcdPort.StopF = 1 ;
LcdPort.MovingF  =  1;

//p2 数值1的小数点1                                                         xx
LcdFlag_Dot11(0);
//p3 数值1的小数点2                                                         xx
LcdFlag_Dot12(0);
//p5 数值2的小数点                                                          xx
LcdFlag_Dot2(0);


#if SOFT_CONFIG_EEPROM
  //if(Load_Param()==0)		//取设定值
   {
 
    //存储器错误
 

   }

#endif


#if CONFIG_CHECK_DEVICE_ID
		if(GetStm32F103_DeviceId_Sum6() == gpParam->Stm32IdSum6)
				{
					STM32DeviceId.Checked=1;
				}
		else{
			STM32DeviceId.Checked=0;
				}
#endif




//OSTimeDly(OS_TICKS_PER_SEC/100);	    //延时0.01秒



#if	CONFIG_EXTI
	Exti_Init();  //#if CONFIG_CAPTURE_TIM3
#endif



Run_Init();

JSP2_0();  //关电源

Ht1621_Init();


LedSwitchOn1;

OSTimeDly(OS_TICKS_PER_SEC/2);	    //延时0.1秒
JSP2_1();  //开电源

SwitchDirect( 0 );  //电机继电器切换方向  0正转 1反转

for(;;)
		{
			
    //TestSyncPinPwm_SET ;
    //移相定时器提前清0
   // TIM_SetCounter(TIM1,0);
	//	OSTimeDly(OS_TICKS_PER_SEC/1000);	    //延时1ms秒
 //   TestSyncPinPwm_CLR ;
  //  OSTimeDly(OS_TICKS_PER_SEC*9/1000);	    //延时8ms秒
    
      LCD_Display	( LcdPort.flashing  )  ;
           LcdRefuse();  

    
    OSTimeDly(OS_TICKS_PER_SEC/50);
    
//for(i=0;i<13;i++)
//{
//Ht1621WrOneData(i,0x08);
//}

		}
}
////////////////////
void TaskTimeout(void * pdata)			//sync
{
//INT8U err;
//CPU_SR         cpu_sr;
pdata = pdata;                          	 	// 避免编译警告		
OSTimeDly(OS_TICKS_PER_SEC/5);	    //延时0.2秒
for(;;)
		{
//			OS_ENTER_CRITICAL();   //CPU_SR         cpu_sr;
//			//if(SetIdTime>0)SetIdTime--;			//设置ID时间
//			OS_EXIT_CRITICAL();

			
		OSTimeDly(OS_TICKS_PER_SEC/200);	    //延时5ms秒
		
		OSTimeDly(OS_TICKS_PER_SEC/200);	    //延时5ms秒
		
		OSSemPost(OSSemGetAA);

		}
}
////////////////////



void _VirtualPwmOutFuncA(unsigned char ch , unsigned char High)  //A组
{

#ifndef SetVirtualPwmOutPinA1
#define SetVirtualPwmOutPinA1   ;
#endif
#ifndef ClrVirtualPwmOutPinA1
#define ClrVirtualPwmOutPinA1   ;
#endif
#ifndef SetVirtualPwmOutPinA2
#define SetVirtualPwmOutPinA2   ;
#endif
#ifndef ClrVirtualPwmOutPinA2
#define ClrVirtualPwmOutPinA2   ;
#endif
#ifndef SetVirtualPwmOutPinA3
#define SetVirtualPwmOutPinA3   ;
#endif
#ifndef ClrVirtualPwmOutPinA3
#define ClrVirtualPwmOutPinA3   ;
#endif
#ifndef SetVirtualPwmOutPinA4
#define SetVirtualPwmOutPinA4   ;
#endif
#ifndef ClrVirtualPwmOutPinA4
#define ClrVirtualPwmOutPinA4   ;
#endif
#ifndef SetVirtualPwmOutPinA5
#define SetVirtualPwmOutPinA5   ;
#endif
#ifndef ClrVirtualPwmOutPinA5
#define ClrVirtualPwmOutPinA5   ;
#endif
#ifndef SetVirtualPwmOutPinA6
#define SetVirtualPwmOutPinA6   ;
#endif
#ifndef ClrVirtualPwmOutPinA6
#define ClrVirtualPwmOutPinA6   ;
#endif
#ifndef SetVirtualPwmOutPinA7
#define SetVirtualPwmOutPinA7   ;
#endif
#ifndef ClrVirtualPwmOutPinA7
#define ClrVirtualPwmOutPinA7   ;
#endif	
#ifndef SetVirtualPwmOutPinA8
#define SetVirtualPwmOutPinA8   ;
#endif		
#ifndef ClrVirtualPwmOutPinA8
#define ClrVirtualPwmOutPinA8   ;
#endif
	
	switch(ch)
	{
		case 0:
			if(High != 0)
			  {//输出有效电平
			  	SetVirtualPwmOutPinA1;
			  }
			else{//关闭有效电平
				  ClrVirtualPwmOutPinA1;
			  }
	  break;
	  
		case 1:
			if(High != 0)
			  {//输出有效电平
			  	SetVirtualPwmOutPinA2;
			  }
			else{//关闭有效电平
				   ClrVirtualPwmOutPinA2;
			  }
	  break;	
	  
		case 2:
			if(High != 0)
			  {//输出有效电平
			  	SetVirtualPwmOutPinA3;
			  }
			else{//关闭有效电平
				  ClrVirtualPwmOutPinA3;
			  }
	  break;
	  
		case 3:
			if(High != 0)
			  {//输出有效电平
			  	SetVirtualPwmOutPinA4;
			  }
			else{//关闭有效电平
				   ClrVirtualPwmOutPinA4;
			  }
	  break;	    

		case 4:
			if(High != 0)
			  {//输出有效电平
			  	SetVirtualPwmOutPinA5;
			  }
			else{//关闭有效电平
				  ClrVirtualPwmOutPinA5;
			  }
	  break;
	  
		case 5:
			if(High != 0)
			  {//输出有效电平
			  	SetVirtualPwmOutPinA6;
			  }
			else{//关闭有效电平
				   ClrVirtualPwmOutPinA6;
			  }
	  break;
	  
		case 6:
			if(High != 0)
			  {//输出有效电平
			  	SetVirtualPwmOutPinA7;
			  }
			else{//关闭有效电平
				  ClrVirtualPwmOutPinA7;
			  }
	  break;
	  
		case 7:
			if(High != 0)
			  {//输出有效电平
			  	SetVirtualPwmOutPinA8;
			  }
			else{//关闭有效电平
				   ClrVirtualPwmOutPinA8;
			  }
	  break;	  		
	}
	
}

/////////////////////////////
void _VirtualPwmOutFuncB(unsigned char ch , unsigned char High)  //B组
{

#ifndef SetVirtualPwmOutPinB1
#define SetVirtualPwmOutPinB1   ;
#endif
#ifndef ClrVirtualPwmOutPinB1
#define ClrVirtualPwmOutPinB1   ;
#endif
#ifndef SetVirtualPwmOutPinB2
#define SetVirtualPwmOutPinB2   ;
#endif
#ifndef ClrVirtualPwmOutPinB2
#define ClrVirtualPwmOutPinB2   ;
#endif
#ifndef SetVirtualPwmOutPinB3
#define SetVirtualPwmOutPinB3   ;
#endif
#ifndef ClrVirtualPwmOutPinB3
#define ClrVirtualPwmOutPinB3   ;
#endif
#ifndef SetVirtualPwmOutPinB4
#define SetVirtualPwmOutPinB4   ;
#endif
#ifndef ClrVirtualPwmOutPinB4
#define ClrVirtualPwmOutPinB4   ;
#endif
#ifndef SetVirtualPwmOutPinB5
#define SetVirtualPwmOutPinB5   ;
#endif
#ifndef ClrVirtualPwmOutPinB5
#define ClrVirtualPwmOutPinB5   ;
#endif
#ifndef SetVirtualPwmOutPinB6
#define SetVirtualPwmOutPinB6   ;
#endif
#ifndef ClrVirtualPwmOutPinB6
#define ClrVirtualPwmOutPinB6   ;
#endif
#ifndef SetVirtualPwmOutPinB7
#define SetVirtualPwmOutPinB7   ;
#endif
#ifndef ClrVirtualPwmOutPinB7
#define ClrVirtualPwmOutPinB7   ;
#endif	
#ifndef SetVirtualPwmOutPinB8
#define SetVirtualPwmOutPinB8   ;
#endif		
#ifndef ClrVirtualPwmOutPinB8
#define ClrVirtualPwmOutPinB8   ;
#endif
	
	switch(ch)
	{
		case 0:
			if(High != 0)
			  {//输出有效电平
			  	SetVirtualPwmOutPinB1;
			  }
			else{//关闭有效电平
				  ClrVirtualPwmOutPinB1;
			  }
	  break;
	  
		case 1:
			if(High != 0)
			  {//输出有效电平
			  	SetVirtualPwmOutPinB2;
			  }
			else{//关闭有效电平
				   ClrVirtualPwmOutPinB2;
			  }
	  break;	
	  
		case 2:
			if(High != 0)
			  {//输出有效电平
			  	SetVirtualPwmOutPinB3;
			  }
			else{//关闭有效电平
				  ClrVirtualPwmOutPinB3;
			  }
	  break;
	  
		case 3:
			if(High != 0)
			  {//输出有效电平
			  	SetVirtualPwmOutPinB4;
			  }
			else{//关闭有效电平
				   ClrVirtualPwmOutPinB4;
			  }
	  break;	    

		case 4:
			if(High != 0)
			  {//输出有效电平
			  	SetVirtualPwmOutPinB5;
			  }
			else{//关闭有效电平
				  ClrVirtualPwmOutPinB5;
			  }
	  break;
	  
		case 5:
			if(High != 0)
			  {//输出有效电平
			  	SetVirtualPwmOutPinB6;
			  }
			else{//关闭有效电平
				   ClrVirtualPwmOutPinB6;
			  }
	  break;
	  
		case 6:
			if(High != 0)
			  {//输出有效电平
			  	SetVirtualPwmOutPinB7;
			  }
			else{//关闭有效电平
				  ClrVirtualPwmOutPinB7;
			  }
	  break;
	  
		case 7:
			if(High != 0)
			  {//输出有效电平
			  	SetVirtualPwmOutPinB8;
			  }
			else{//关闭有效电平
				   ClrVirtualPwmOutPinB8;
			  }
	  break;	  		
	}
	
}




//虚拟PWM  A 组 通道数目
//#define PwmVirChNumberA   2
//虚拟PWM  A 组 周期
//#define PwmVirCycleA      1000

//虚拟PWM  B 组 通道数目
//#define PwmVirChNumberB   2
//虚拟PWM  B 组 周期
//#define PwmVirCycleB      10

void TaskVirPwm(void * pdata)  //Virtual
{
//INT8U err;
unsigned char i;

////////// A组//////////////
unsigned short int curDutyA[PwmVirChNumberA];//A组各路占空比计数器
unsigned short int curCycleA;//A组周期计数器
unsigned short int  *pPwmValA  ;
unsigned char       *pFlagOnA  ;

//////////假设的缓冲区 A组//////////////
//unsigned short int  PwmValBufA[PwmVirChNumberA];
//unsigned char       FlagOnBufA[PwmVirChNumberA];   //控制开关相应的虚拟pwm
///////////////////////

////////// B组//////////////
unsigned short int curDutyB[PwmVirChNumberB];//A组各路占空比计数器
unsigned short int curCycleB;//A组周期计数器
unsigned short int  *pPwmValB  ;
unsigned char       *pFlagOnB  ;


//////////假设的缓冲区 B组//////////////
//unsigned short int  PwmValBufB[PwmVirChNumberB];
//unsigned char       FlagOnBufB[PwmVirChNumberB];   //控制开关相应的虚拟pwm
///////////////////////

pdata = pdata;	// 避免编译警告		

//PID_Init();

//取地址 A组
pPwmValA   =  & PwmValBufA[0];  
pFlagOnA   =  & FlagOnBufA[0];
//取地址 B组
pPwmValB   =  & PwmValBufB[0];  
pFlagOnB   =  & FlagOnBufB[0];
                          	 


curCycleA = PwmVirCycleA;//A组周期
curCycleB = PwmVirCycleB;//A组周期

OSTimeDly(OS_TICKS_PER_SEC/10);	    //延时0.1秒
for(;;)
		{
			//A组软件 PWM
			for( i = 0 ; i < PwmVirChNumberA ; i++ )  //A组路数
			    {
			     if(curDutyA[i] > 0)
			     	  {
			     		
			     		 curDutyA[i] --;
			     	  }
			     else{//关输出
			     	
			     	   _VirtualPwmOutFuncA(i,0);
			         }
			     }
			
			  if(curCycleA > 0)
			     	{
			     		curCycleA --;
			     	}
			  else{
			     	 curCycleA = PwmVirCycleA ;//周期到
             for( i = 0 ; i < PwmVirChNumberA ; i++ )   //A组路数
			            {
                   curDutyA[i] = *( pPwmValA + i )    ;//刷新PWM值
			     	       //开输出
			     	       if( *( pFlagOnA + i ) > 0 )
			     	       	   {
			     	       		  _VirtualPwmOutFuncA(i,1);
			     	       	   }
			     	       
			     	       }			     	    
			       }



			//B组软件 PWM
			for( i = 0 ; i < PwmVirChNumberB ; i++ )  //B组路数
			    {
			     if(curDutyB[i] > 0)
			     	  {
			     		
			     		 curDutyB[i] --;
			     	  }
			     else{//关输出
			     	
			     	   _VirtualPwmOutFuncB(i,0);
			         }
			     }
			
			  if(curCycleB > 0)
			     	{
			     		curCycleB --;
			     	}
			  else{
			  	    
			  	    _HeatContral( ) ; //电加热控制	  //  间隔	1s  通知电加热控制12		  
			     	 curCycleB = PwmVirCycleB ;//周期到
             for( i = 0 ; i < PwmVirChNumberB ; i++ )   //B组路数
			            {
                   curDutyB[i] = *( pPwmValB + i )    ;//刷新PWM值
			     	       //开输出
			     	       if( *( pFlagOnB + i ) > 0 )
			     	       	   {
			     	       		  _VirtualPwmOutFuncB(i,1);
			     	       	   }
			     	       
			     	       }
   	    
			       }			        
			
		  OSTimeDly(OS_TICKS_PER_SEC/1000);	    //延时0.001秒

		}		
}












/////////////////



//////////////





