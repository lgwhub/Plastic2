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


//����PWM  A �� ͨ����Ŀ
#define PwmVirChNumberA   2
//����PWM  A �� ����
#define PwmVirCycleA      1000

//����PWM  B �� ͨ����Ŀ
#define PwmVirChNumberB   2
//����PWM  B �� ����
#define PwmVirCycleB      10
//////////����Ļ����� A��//////////////
unsigned short int  PwmValBufA[PwmVirChNumberA];
unsigned char       FlagOnBufA[PwmVirChNumberA];   //���ƿ�����Ӧ������pwm
///////////////////////

//////////����Ļ����� B��//////////////
unsigned short int  PwmValBufB[PwmVirChNumberB]={10,10};
unsigned char       FlagOnBufB[PwmVirChNumberB]={1,1};  //���ƿ�����Ӧ������pwm


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
 * Description    : ��ȡ����ʱ��[BCD�룺YY-MM-DD HH:MM:SS]
 * EntryParameter : pTim - ת�����BCD�룬mode - ģʽ[0-���ڣ�1-ʱ�䣬2-����+ʱ��]
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
       if (!memcmp(&tmpMth[i][0], &tmpDty[0], 3))         // �����·�
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
		
//	len		+=	MakeValAsc16("I1=",56,",",&buf[len]);	//����100ma
//	len		+=	MakeValAsc16("I2=",57,",",&buf[len]);	//����100ma
	
	len		+=	MakeValAsc16("Px=",pPidBufMt ->Px,",",&buf[len]);	//����100ma
	len		+=	MakeValAsc16("Ix=",pPidBufMt ->Ix,",",&buf[len]);	//����100ma
  len		+=	MakeValAsc16("Dx=",pPidBufMt ->Dx,",",&buf[len]);	//����100ma
  
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


		
							
							
//OUT_ENALL_SET;				//��������ܿ���	

}
////////////////////







/////////////////////////////////////////


void TaskEvent_old(void * pdata)
{
//INT8U err;
 
	pdata = pdata;                          	 	// ������뾯��	   

OSTimeDly(OS_TICKS_PER_SEC/5);	    //��ʱ0.2��


	for(;;)
				{
				//OS_ENTER_CRITICAL();   //CPU_SR         cpu_sr;
				//OS_EXIT_CRITICAL();



		OSTimeDly(OS_TICKS_PER_SEC/100);	    //��ʱ0.01��
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
				   
				//	OSTimeDly(OS_TICKS_PER_SEC/1000);	    //��ʱ0.001��		

					}
}
/////////////////////////////



/////////////////////////////
void TaskRpm(void * pdata)  // synchronous
{
	INT8U err;
 	pdata = pdata;                          	 	// ������뾯��	   

PID_Init();

OSTimeDly(OS_TICKS_PER_SEC/10);	    //��ʱ0.1��


					

//////
	for(;;)
				{
				//OS_ENTER_CRITICAL();   //CPU_SR         cpu_sr;
				//OS_EXIT_CRITICAL();

          //�������ٷ����   // AdcRes.RpmCur CurRpmDisplay
          //pid    LcdPort.RpmSet * 10
          
          
			  	  OSSemPend(OSSemOutCC,0,&err);
         
          if (  (  LcdPort.MovingF  ==  0 ) &&  ( LcdPort.RpmBackSet == 0  )  )
          	        {//������ʱ
                    PID_BufInit( pPidBufMt  );
            
                    #if  0 * ENABLE_TEST_MOD
           
                            LcdPort.RpmOut        =   ( 10 * LcdPort.RpmSet );      //�ٶȿ���ֵ
              
                    #else
           
                            LcdPort.RpmOut        =   0;
             
                    #endif
                    }
          else{
          	#if CONFIG_RPM_DIGTAL
          	//���ַ�������
                 if ( LcdPort.MovingF  ==  1 )
                           {
                            pPidBufMt -> SetPoint = LcdPort.RpmSet * 10 ;       //�趨Ŀ��
                           }
                 else{
          	               pPidBufMt -> SetPoint = LcdPort.RpmBackSet ;   //�����ٶ�
          	              }
          
          
                  PID_Calc( pPidMt , pPidBufMt , AdcRes.RpmCur );
          
                  LcdPort.RpmOut    =  (unsigned short int)pPidBufMt -> Qx ;     //�ٶȿ���ֵ
        #else
              LcdPort.RpmOut  =    LcdPort.RpmSet;
        #endif      
                    }
           
            //���������ת��Ϊ����ֵ
            
            
            
            
           PmwVal_TIM1_ch1 = PowerToShiftTimr( LcdPort.RpmOut  );
           
           ////////////////////////
//           pPidBufMt -> SetPoint = LcdPort.RpmSet * 10 ;       //�趨Ŀ��
//           PID_Calc( pPidMt , pPidBufMt , AdcRes.RpmCur );
//           PmwVal_TIM1_ch1 = PowerToShiftTimr( pPidBufMt -> Qx  );
           //PmwVal_TIM1_ch1 = PowerToShiftTimr( LcdPort.RpmSet * 10   );
           ////////////////////////////////////////////
           
           TIM_SetCompare1(TIM1,PmwVal_TIM1_ch1);
	// #if CONFIG_RPM_DIGTAL
	
          //OSTimeDly(OS_TICKS_PER_SEC/50);	    //��ʱ  20MS      
           //OSTimeDly(OS_TICKS_PER_SEC/100);	    //��ʱ  10MS
           OSTimeDly(OS_TICKS_PER_SEC/500);	    //��ʱ  2MS
            
					}
}
///////////////����ȿ���//////////////
void  _HeatContral( void )  //����ȿ���
{//  ���	1s  ֪ͨ����ȿ���12
	static unsigned char ChSel;
	ChSel ++;
	//if( ChSel & 0x01 )
	//	{
			 //AdcRes.temptemprature1;              //�¶�1
			 //LcdPort.TempratureSet
			 
			 pPidBufHt1 -> SetPoint = LcdPort.TempratureSet ;   //�趨Ŀ��
			 PID_Calc( pPidHt1 , pPidBufHt1 , AdcRes.temptemprature1 )	 ;
			 
			 PwmValBufA[0] =  pPidBufHt1 -> Qx;
			//FlagOnBufA[1];   //���ƿ�����Ӧ������pwm

	//	}
//else{
	    //AdcRes.temptemprature2;              //�¶�2
	    //LcdPort.TempratureSet
	    
	    //pid
	    pPidBufHt2 -> SetPoint = LcdPort.TempratureSet ;   //�趨Ŀ��
			PID_Calc( pPidHt2 , pPidBufHt2 , AdcRes.temptemprature2 )	 ;
			
	   	PwmValBufA[1] =   pPidBufHt2 -> Qx;
	   	//FlagOnBufA[1];   //���ƿ�����Ӧ������pwm
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
			
			
			//��һ·����
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
//���ٷ�������¶Ȳ���x2�������¶ȣ���ѹ������
          
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

OSTimeDly(OS_TICKS_PER_SEC/5);	    //��ʱ0.2��

pdata = pdata;                          	 	// ������뾯��		


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
    
    //After_filter[1]  *990 /4095 ;             //ת�٣� ���99
    //AddAverage(unsigned short int *buf,unsigned short int *offset,unsigned short int add , unsigned short int MaxSize);
    
    AddAverage( &AvergeBufGb[0] , &AvergeOffsetGb , After_filter[1] , MaxNumbAvergeGb );
    
    //AdcRes.temptemprature1   = After_filter[2] /8 ;              //�¶�1
    //AdcRes.temptemprature2   = After_filter[3] /8 ;              //�¶�2
    //AdcRes.current           = After_filter[4] /8;              //����ȵ���
	  //AdcRes.volt              = After_filter[5] /20;              //��Դ��ѹ
    //AddAverage(unsigned short int *buf,unsigned short int *offset,unsigned short int add , unsigned short int MaxSize);
 
    for( i = 0 ; i < 4 ; i ++ )
         {
    	   AddAverage( &AvergeBufGa[ i ][0] , &AvergeOffsetGa[ i ] , After_filter[ 2 + i ] , MaxNumbAvergeGa);
         }
 
 
   
    //�������ٷ����
    AdcRes.RpmCur            =    After_filter[1] * 990 /4095 ;
    //AdcRes.RpmDisplay   =  = GetAverSS( &AvergeBufGb[ 0 ]  , buf_temp , MaxNumbAvergeGb ) * 99 /4095 ;           //ת�٣� ���99 ,����ʱ�ڲ�����10��
    //AdcRes.RpmDisplay   =AdcRes.RpmCur /10; 
    AdcRes.RpmDisplay   =LcdPort.RpmSet/10;
    //temp16                   = GetAverSS( &AvergeBufGa [ 0 ][ 0 ]  , buf_temp , MaxNumbAvergeGa );              //�¶�1
    temp16                   = After_filter[2] ;
    AdcRes.temptemprature1   = InterPointCala( temp16 );
    temp16                   = GetAverSS( &AvergeBufGa [ 1 ][ 0 ]  , buf_temp , MaxNumbAvergeGa ) ;              //�¶�2
    AdcRes.temptemprature2   = InterPointCala( temp16 );
    AdcRes.current           = GetAverSS( &AvergeBufGa [ 2 ][ 0 ]  , buf_temp , MaxNumbAvergeGa ) /8;               //����ȵ���
    AdcRes.volt              = GetAverSS( &AvergeBufGa [ 3 ][ 0 ]  , buf_temp , MaxNumbAvergeGa ) /20;              //��Դ��ѹ
	  

   
    OSSemPost(OSSemOutCC);   //  ���	  ֪ͨ�����

    //OSTimeDly(OS_TICKS_PER_SEC/50);	    //��ʱ0.02��
    //OSTimeDly(OS_TICKS_PER_SEC/100);	    //��ʱ0.01��
    OSTimeDly(OS_TICKS_PER_SEC/500);	    //��ʱ2ms��        
			}		
}


////////////////////////////////////////////////
void TaskSave(void * pdata)
{
//INT8U err;
//CPU_SR         cpu_sr;

 
	pdata = pdata;                          	 	// ������뾯��	   

//InterPoint_Test();

OSTimeDly(OS_TICKS_PER_SEC/5);	    //��ʱ0.2��

	for(;;)
				{
				 AutoSend();
				 /*
          
							
        if(FlagSetAllDefault > 0)//flag
        	   {
        	   	
        	   	if(3 == FlagSetAllDefault)
				 	      {
         
                Default_ParamInit1();    ////��Ҫ����Ĳ���
                Default_ParamInit2();    ////����ֵ
                }
        	   	else if(2 == FlagSetAllDefault)
				 	      {
         
                Default_ParamInit1();    ////��Ҫ����Ĳ���

                }
        	   	
        	   	Default_ParamInit0();//����Ҫ����Ĳ���
        	   	
        	   	FlagSetAllDefault = 0 ;
        	   	
        	#if SOFT_CONFIG_EEPROM
             //�Զ��ָ�Ĭ��ֵ
             cMemBufA[Max_MemBuf-2] =  FlagParamInitnized; 
             
             OS_ENTER_CRITICAL();   //CPU_SR         cpu_sr;
             _Param_SwapMemery(0,cMemBufA);   //parameter ---> cMemBufB
              OS_EXIT_CRITICAL();
              
             Write_Param();
         #endif
             
             
             }
          
          
          
          
          if(TimeForSaveParam==1)  //��ʱ����
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
				OSTimeDly(OS_TICKS_PER_SEC);	    //��ʱ1��		
			}		
}

//////////////////
void TaskAverage(void * pdata)
{
//INT8U err;
pdata = pdata;                          	 	// ������뾯��		
OSTimeDly(OS_TICKS_PER_SEC/5);	    //��ʱ0.2��
for(;;)
		{


		OSTimeDly(OS_TICKS_PER_SEC/10);	    //��ʱ0.1��


         	
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
   LcdPort.RpmOut  = 0;  //800;     //�ٶȿ���ֵ
   

   
	OSTimeDly(OS_TICKS_PER_SEC*2);	    //��ʱ1��
	AutoSend();
 

		for(;;)
						{
						//OS_ENTER_CRITICAL();   //CPU_SR         cpu_sr;
						//OS_EXIT_CRITICAL();
						OSTimeDly(OS_TICKS_PER_SEC/500);	    //��ʱ0.02��		
				

            
            //LedSwitchOn1
            //LedSwitchOn2	
				   //i= KeyLedScan( 0x03f  );
							
							LedSwitchOn1;
           temp = KeyLedScan( LedsBuf  ) ;
           
							KeyGet  ( temp  );
           //LedsBuf = (temp);
           
          
           if( KeyScan.resoult ==  (16 + 32 ) )
           	{ //ͨ������ȡ��SWCLK
           		//KeyScan.age
           		
           	#if ENABLE_SWITCH_OFF_DEBUG //(  SWD_DEBUG_DISABLE  +  0  )
           	if(FlagDebug_SWCLK_Off  == 1)
           		{  //�رյ��ԣ�ʹ��SWCLK     PwmValBufB
           			FlagDebug_SWCLK_Off  = 0;
           			
           			GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);     //SWD�ں�jtag��ȫ����ȡ��  Full SWJ Disabled (JTAG-DP + SW-DP)
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

             
             

//SEG1 SEG2 SEG3   ��ʾ������  ��Ӧ  Ht1621FlagTab1
//void LcdFlagDecode123( unsigned char *s ,  unsigned char *buf );    //lcd Datbuf 5
//SEG4 SEG5   ��ʾ������  ��Ӧ  Ht1621FlagTab2
//void LcdFlagDecode45(unsigned char *s   ,  unsigned char *buf);    //lcd Datbuf 0
             
        
           //SEG1 SEG2 SEG3   ��ʾ999  ��Ӧ  Ht1621DigtTab1
           LcdDigetDecode123( LcdPort.val1 , Ht1621buf );   //lcd Datbuf 5
           //SEG4 SEG5   ��ʾ99  ��Ӧ  Ht1621DigtTab2
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

pdata = pdata;                          	 	// ������뾯��		
LedRunStatu1 =0;

OSTimeDly(OS_TICKS_PER_SEC/2);	    //��ʱ0.2��

for(i=0;i<3;i++)
				{

				  OSTimeDly(OS_TICKS_PER_SEC/2);	    //��ʱ0.2��
					
					LedOnAll;

					OSTimeDly(OS_TICKS_PER_SEC/2);	    //��ʱ0.2��
				
          LedOffAll;
	
				}


		
    for (;;)
    {
	switch(LedRunStatu1)
	{
	case 2:		//2��/2��

			
	LED_RUN1_ON;//SetLED_Statu1;
        OSTimeDly(OS_TICKS_PER_SEC / 8);	//��ʱ0.125��
  LED_RUN1_OFF;//ClrLED_Statu1;
        OSTimeDly(OS_TICKS_PER_SEC / 4);	//��ʱ0.25��
	LED_RUN1_ON;//SetLED_Statu1;
        OSTimeDly(OS_TICKS_PER_SEC / 8);	//��ʱ0.125��
  LED_RUN1_OFF;//ClrLED_Statu1;        
        OSTimeDly(6*OS_TICKS_PER_SEC/4);	  	//��ʱ1.5��
	break;
	
	case 1:		//1��/2��
		
	LED_RUN1_ON;//SetLED_Statu1;
        OSTimeDly(OS_TICKS_PER_SEC / 4);	//��ʱ0.25��
  LED_RUN1_OFF;//ClrLED_Statu1;
        OSTimeDly(7*OS_TICKS_PER_SEC/4);	  	//��ʱ1.75��
	break;
	
	default:	
	case 0:	//1��/2��
	LED_RUN1_ON;//SetLED_Statu1;
        OSTimeDly(OS_TICKS_PER_SEC);	//��ʱ0.5��
  LED_RUN1_OFF;//ClrLED_Statu1;
        OSTimeDly(OS_TICKS_PER_SEC);	  	//��ʱ5��
	
	break;	
	}
    }		
		
		
		
		
}
////////////////////



////////////////////////////
void  TaskEvent(void *pdata)   //TaskLED_Event1(void *pdata)	//�¼�ָʾ��1��LedEventTime1��λ1S
{
	
	unsigned char Timexx;
    pdata = pdata;                          	 	// ������뾯��

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
        	OSTimeDly( Timexx*OS_TICKS_PER_SEC/10 );	 	  //��ʱLedEventTime/10��
        	Timexx = 0 ;
        	LedEventTime1=0;
        	LED_EVENT_OFF;//ClrLED_Event1;
        	}
        	
        LcdPort.flashing ++ ;	   //lcd��˸
	OSTimeDly(OS_TICKS_PER_SEC/5);	     //Led��ʱ0.2��
    }
}
////////////////////////////




void TaskModbus(void * pdata)
{
//INT8U err;
//CPU_SR          cpu_sr;

pdata = pdata;                          	 	// ������뾯��		



OSTimeDly(OS_TICKS_PER_SEC/5);	    //��ʱ0.2��



#if CONFIG_MODBUS
ModbusInit();
#endif


#if TEST_MODBUS_78
 TestModbus();
#endif

OSTimeDly(OS_TICKS_PER_SEC/5);	    //��ʱ0.2��

for(;;)
		{




       OSTimeDly(OS_TICKS_PER_SEC/500);	    //��ʱ2����

     #if CONFIG_MODBUS
	
	
			CPU_CRITICAL_ENTER();                                       /* Tell uC/OS-II that we are starting an ISR            */

   
     //����ԭ����BUG�ĵط�
		   ModbusTimeHandler();
  
       CPU_CRITICAL_EXIT();
		
		
		
		   GetModbusPark();  //����Ҳ����
		
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


//SEG1 SEG2 SEG3   ��ʾ������  ��Ӧ  Ht1621FlagTab1
//void LcdFlagDecode123( unsigned char *s ,  unsigned char *buf );    //lcd Datbuf 5
//SEG4 SEG5   ��ʾ������  ��Ӧ  Ht1621FlagTab2
//void LcdFlagDecode45(unsigned char *s   ,  unsigned char *buf);    //lcd Datbuf 0
               //SEG1 SEG2 SEG3   ��ʾ999  ��Ӧ  Ht1621DigtTab1
           LcdDigetDecode123( j%999  , Ht1621buf  );   //lcd Datbuf 5
           //SEG4 SEG5   ��ʾ99  ��Ӧ  Ht1621DigtTab2
           LcdDigetDecode45( k%99  , Ht1621buf );    //lcd Datbuf 0
    
     LcdFlag_TempratureSetMod(0);
     
     LcdRefuse();   
     OSTimeDly(OS_TICKS_PER_SEC);	    //��ʱ1��
     
     j++;
     
               //SEG1 SEG2 SEG3   ��ʾ999  ��Ӧ  Ht1621DigtTab1
           LcdDigetDecode123( j%999  , Ht1621buf );   //lcd Datbuf 5
           //SEG4 SEG5   ��ʾ99  ��Ӧ  Ht1621DigtTab2
           LcdDigetDecode45( k%99  , Ht1621buf );    //lcd Datbuf 0
    
     LcdFlag_TempratureSetMod(1);
     LcdRefuse();
    OSTimeDly(OS_TICKS_PER_SEC);	    //��ʱ1��
}
#endif
////////////////////
void TaskRuning(void * pdata)
{
	
//INT8U err;

//unsigned short int   i,j,k,temp16;
unsigned long int   temp32;

pdata = pdata;                          	 	// ������뾯��		

//FlagSetAllDefault = 0 ;
TimeForSaveParam = 0;

  //_ParamPointTab_Init_pid();

 //Default_ParamInit0();//����Ҫ����Ĳ���

 
 temp32    = GetDate();
 
LcdPort.RpmSet = 8;
LcdPort.TempratureSet =  100;

   LcdPort.RpmOut  = 0;  //800;     //�ٶȿ���ֵ
LcdPort.StopF = 1 ;
LcdPort.MovingF  =  1;

//p2 ��ֵ1��С����1                                                         xx
LcdFlag_Dot11(0);
//p3 ��ֵ1��С����2                                                         xx
LcdFlag_Dot12(0);
//p5 ��ֵ2��С����                                                          xx
LcdFlag_Dot2(0);


#if SOFT_CONFIG_EEPROM
  //if(Load_Param()==0)		//ȡ�趨ֵ
   {
 
    //�洢������
 

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




//OSTimeDly(OS_TICKS_PER_SEC/100);	    //��ʱ0.01��



#if	CONFIG_EXTI
	Exti_Init();  //#if CONFIG_CAPTURE_TIM3
#endif



Run_Init();

JSP2_0();  //�ص�Դ

Ht1621_Init();


LedSwitchOn1;

OSTimeDly(OS_TICKS_PER_SEC/2);	    //��ʱ0.1��
JSP2_1();  //����Դ

SwitchDirect( 0 );  //����̵����л�����  0��ת 1��ת

for(;;)
		{
			
    //TestSyncPinPwm_SET ;
    //���ඨʱ����ǰ��0
   // TIM_SetCounter(TIM1,0);
	//	OSTimeDly(OS_TICKS_PER_SEC/1000);	    //��ʱ1ms��
 //   TestSyncPinPwm_CLR ;
  //  OSTimeDly(OS_TICKS_PER_SEC*9/1000);	    //��ʱ8ms��
    
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
pdata = pdata;                          	 	// ������뾯��		
OSTimeDly(OS_TICKS_PER_SEC/5);	    //��ʱ0.2��
for(;;)
		{
//			OS_ENTER_CRITICAL();   //CPU_SR         cpu_sr;
//			//if(SetIdTime>0)SetIdTime--;			//����IDʱ��
//			OS_EXIT_CRITICAL();

			
		OSTimeDly(OS_TICKS_PER_SEC/200);	    //��ʱ5ms��
		
		OSTimeDly(OS_TICKS_PER_SEC/200);	    //��ʱ5ms��
		
		OSSemPost(OSSemGetAA);

		}
}
////////////////////



void _VirtualPwmOutFuncA(unsigned char ch , unsigned char High)  //A��
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
			  {//�����Ч��ƽ
			  	SetVirtualPwmOutPinA1;
			  }
			else{//�ر���Ч��ƽ
				  ClrVirtualPwmOutPinA1;
			  }
	  break;
	  
		case 1:
			if(High != 0)
			  {//�����Ч��ƽ
			  	SetVirtualPwmOutPinA2;
			  }
			else{//�ر���Ч��ƽ
				   ClrVirtualPwmOutPinA2;
			  }
	  break;	
	  
		case 2:
			if(High != 0)
			  {//�����Ч��ƽ
			  	SetVirtualPwmOutPinA3;
			  }
			else{//�ر���Ч��ƽ
				  ClrVirtualPwmOutPinA3;
			  }
	  break;
	  
		case 3:
			if(High != 0)
			  {//�����Ч��ƽ
			  	SetVirtualPwmOutPinA4;
			  }
			else{//�ر���Ч��ƽ
				   ClrVirtualPwmOutPinA4;
			  }
	  break;	    

		case 4:
			if(High != 0)
			  {//�����Ч��ƽ
			  	SetVirtualPwmOutPinA5;
			  }
			else{//�ر���Ч��ƽ
				  ClrVirtualPwmOutPinA5;
			  }
	  break;
	  
		case 5:
			if(High != 0)
			  {//�����Ч��ƽ
			  	SetVirtualPwmOutPinA6;
			  }
			else{//�ر���Ч��ƽ
				   ClrVirtualPwmOutPinA6;
			  }
	  break;
	  
		case 6:
			if(High != 0)
			  {//�����Ч��ƽ
			  	SetVirtualPwmOutPinA7;
			  }
			else{//�ر���Ч��ƽ
				  ClrVirtualPwmOutPinA7;
			  }
	  break;
	  
		case 7:
			if(High != 0)
			  {//�����Ч��ƽ
			  	SetVirtualPwmOutPinA8;
			  }
			else{//�ر���Ч��ƽ
				   ClrVirtualPwmOutPinA8;
			  }
	  break;	  		
	}
	
}

/////////////////////////////
void _VirtualPwmOutFuncB(unsigned char ch , unsigned char High)  //B��
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
			  {//�����Ч��ƽ
			  	SetVirtualPwmOutPinB1;
			  }
			else{//�ر���Ч��ƽ
				  ClrVirtualPwmOutPinB1;
			  }
	  break;
	  
		case 1:
			if(High != 0)
			  {//�����Ч��ƽ
			  	SetVirtualPwmOutPinB2;
			  }
			else{//�ر���Ч��ƽ
				   ClrVirtualPwmOutPinB2;
			  }
	  break;	
	  
		case 2:
			if(High != 0)
			  {//�����Ч��ƽ
			  	SetVirtualPwmOutPinB3;
			  }
			else{//�ر���Ч��ƽ
				  ClrVirtualPwmOutPinB3;
			  }
	  break;
	  
		case 3:
			if(High != 0)
			  {//�����Ч��ƽ
			  	SetVirtualPwmOutPinB4;
			  }
			else{//�ر���Ч��ƽ
				   ClrVirtualPwmOutPinB4;
			  }
	  break;	    

		case 4:
			if(High != 0)
			  {//�����Ч��ƽ
			  	SetVirtualPwmOutPinB5;
			  }
			else{//�ر���Ч��ƽ
				  ClrVirtualPwmOutPinB5;
			  }
	  break;
	  
		case 5:
			if(High != 0)
			  {//�����Ч��ƽ
			  	SetVirtualPwmOutPinB6;
			  }
			else{//�ر���Ч��ƽ
				   ClrVirtualPwmOutPinB6;
			  }
	  break;
	  
		case 6:
			if(High != 0)
			  {//�����Ч��ƽ
			  	SetVirtualPwmOutPinB7;
			  }
			else{//�ر���Ч��ƽ
				  ClrVirtualPwmOutPinB7;
			  }
	  break;
	  
		case 7:
			if(High != 0)
			  {//�����Ч��ƽ
			  	SetVirtualPwmOutPinB8;
			  }
			else{//�ر���Ч��ƽ
				   ClrVirtualPwmOutPinB8;
			  }
	  break;	  		
	}
	
}




//����PWM  A �� ͨ����Ŀ
//#define PwmVirChNumberA   2
//����PWM  A �� ����
//#define PwmVirCycleA      1000

//����PWM  B �� ͨ����Ŀ
//#define PwmVirChNumberB   2
//����PWM  B �� ����
//#define PwmVirCycleB      10

void TaskVirPwm(void * pdata)  //Virtual
{
//INT8U err;
unsigned char i;

////////// A��//////////////
unsigned short int curDutyA[PwmVirChNumberA];//A���·ռ�ձȼ�����
unsigned short int curCycleA;//A�����ڼ�����
unsigned short int  *pPwmValA  ;
unsigned char       *pFlagOnA  ;

//////////����Ļ����� A��//////////////
//unsigned short int  PwmValBufA[PwmVirChNumberA];
//unsigned char       FlagOnBufA[PwmVirChNumberA];   //���ƿ�����Ӧ������pwm
///////////////////////

////////// B��//////////////
unsigned short int curDutyB[PwmVirChNumberB];//A���·ռ�ձȼ�����
unsigned short int curCycleB;//A�����ڼ�����
unsigned short int  *pPwmValB  ;
unsigned char       *pFlagOnB  ;


//////////����Ļ����� B��//////////////
//unsigned short int  PwmValBufB[PwmVirChNumberB];
//unsigned char       FlagOnBufB[PwmVirChNumberB];   //���ƿ�����Ӧ������pwm
///////////////////////

pdata = pdata;	// ������뾯��		

//PID_Init();

//ȡ��ַ A��
pPwmValA   =  & PwmValBufA[0];  
pFlagOnA   =  & FlagOnBufA[0];
//ȡ��ַ B��
pPwmValB   =  & PwmValBufB[0];  
pFlagOnB   =  & FlagOnBufB[0];
                          	 


curCycleA = PwmVirCycleA;//A������
curCycleB = PwmVirCycleB;//A������

OSTimeDly(OS_TICKS_PER_SEC/10);	    //��ʱ0.1��
for(;;)
		{
			//A����� PWM
			for( i = 0 ; i < PwmVirChNumberA ; i++ )  //A��·��
			    {
			     if(curDutyA[i] > 0)
			     	  {
			     		
			     		 curDutyA[i] --;
			     	  }
			     else{//�����
			     	
			     	   _VirtualPwmOutFuncA(i,0);
			         }
			     }
			
			  if(curCycleA > 0)
			     	{
			     		curCycleA --;
			     	}
			  else{
			     	 curCycleA = PwmVirCycleA ;//���ڵ�
             for( i = 0 ; i < PwmVirChNumberA ; i++ )   //A��·��
			            {
                   curDutyA[i] = *( pPwmValA + i )    ;//ˢ��PWMֵ
			     	       //�����
			     	       if( *( pFlagOnA + i ) > 0 )
			     	       	   {
			     	       		  _VirtualPwmOutFuncA(i,1);
			     	       	   }
			     	       
			     	       }			     	    
			       }



			//B����� PWM
			for( i = 0 ; i < PwmVirChNumberB ; i++ )  //B��·��
			    {
			     if(curDutyB[i] > 0)
			     	  {
			     		
			     		 curDutyB[i] --;
			     	  }
			     else{//�����
			     	
			     	   _VirtualPwmOutFuncB(i,0);
			         }
			     }
			
			  if(curCycleB > 0)
			     	{
			     		curCycleB --;
			     	}
			  else{
			  	    
			  	    _HeatContral( ) ; //����ȿ���	  //  ���	1s  ֪ͨ����ȿ���12		  
			     	 curCycleB = PwmVirCycleB ;//���ڵ�
             for( i = 0 ; i < PwmVirChNumberB ; i++ )   //B��·��
			            {
                   curDutyB[i] = *( pPwmValB + i )    ;//ˢ��PWMֵ
			     	       //�����
			     	       if( *( pFlagOnB + i ) > 0 )
			     	       	   {
			     	       		  _VirtualPwmOutFuncB(i,1);
			     	       	   }
			     	       
			     	       }
   	    
			       }			        
			
		  OSTimeDly(OS_TICKS_PER_SEC/1000);	    //��ʱ0.001��

		}		
}












/////////////////



//////////////





