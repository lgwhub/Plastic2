#include "includes.h"


//#define Max_MemBuf  400
unsigned char cMemBufA[Max_MemBuf+2];
unsigned char cMemBufB[Max_MemBuf+2];
unsigned char FlagSetAllDefault;




_paramter_for_modbus_struct    gCommParam;


//ϵͳ����

//unsigned char InitMemoFlag;		//�����Ѿ���ʼ�����
//unsigned short int  MemoChecksum;    //У����
//�洢������
unsigned short int Stm32IdSum6;   


//modbusͨѶ������

//float ModBusParaBuf[32];   //modbus ���� ����������
unsigned char  ModBusParaByte[Max_ModbusBuf_Len+3];   //modbus ���� ����������

//float ModByte
////////////////////////////////////////////////////////////////////////
//void SwapFourByte(unsigned char *in,unsigned char *out)  //����4�ֽڴ���
//{
//  #if MODBUS_FLOAT_HIGHBYTE_FORWORD
//  //�����ͺ���������С��ģʽ����λ��ǰ����modbus�Ǹ�λ��ǰ
//  //unsigned char temp;	
//  //temp     =    *out;
//  *out     =    *(in+3);
//  //*(in+3)  =    temp;
//			         
//  //temp     =   *(out+1)
//  *(out+1) =   *(in+2);   
//  //*(in+2)  =   temp;
//			       
// // temp     =   *(out+2);
//  *(out+2) =   *(in+1); 
//  //*(in+1)  =   temp;
//  
// // temp     =   *(out+3)			    
//  *(out+3) =   *in;   
//  //*in      =    temp;   
//
//   #else
//			        
//   *out=*in; 
//   *(out+1)=*(in+1);   
//   *(out+2)=*(in+2); 
//   *(out+3)=*(in+3); 
//   #endif
//
//}
////////////////////////////////////////////////////////////////////////
//void MovBlock_4byte(unsigned char *sou,unsigned char *dest,unsigned short int block_len)
//{
//	//len/=4;
//	
//	while(block_len>0)
//     {
//     SwapFourByte(sou,dest);
//     dest+=4;
//     sou+=4;
//     block_len--;
//     }
//	
//}

//void ParamBlockCopyToModbusBuf(unsigned short int start_position , unsigned short int len)   // 
//{
////unsigned short int i;
//
//
//      MovBlock_4byte( start_position+ (unsigned char *)&gCommParam , &ModBusParaByte[0] , len/4);     //
//}
//
//
//void ParamBlockCopyFromModbusBuf(unsigned short int start_position , unsigned short int len)
//{//���������ȷ
////unsigned short int i;
//
//        MovBlock_4byte( &ModBusParaByte[0]   , start_position + (unsigned char *)&gCommParam , len/4);		//��ǰ����
//        
//        
//  
//}



////////////////////////////////////////////////////
void Default_ParamInit0(void)//����Ҫ����Ĳ���
{
	unsigned char i;
	
   gCommParam.lCMD              = 0;
   gCommParam.lWATCHING         = 0;
   gCommParam.lBOARD_STATE      = 1;
   gCommParam.ldevice_type      = 2;
   //gCommParam.lBaudrate_reserve = 57600;     //����һͨ��������Ϊ׼	              //4�ֽ�           =0x2444

   gCommParam.lSubAdr_reserve   = 123 +124 ;           //=��ַ����                  //1�ֽ�      =0X2448	
   //gCommParam.lSubAdr_reserve = SUB_ADR_ABIS_80  + ( lAddressKey & 0x0f ) ;           //��ַ����
   
   #if CONFIG_CURRENT_CH10
   
   gCommParam.lSoftVer          =  330000 + 12*100 + SOFT_VER;  
   
   #else
   
   gCommParam.lSoftVer          =  330000 + 1*100 + SOFT_VER;  
   
   #endif
   
   
   
   gCommParam.lBackupRestore    = 0;

	
	//����Ҫ����Ĳ���������Ҫ����

    for(i=0;i<12;i++)
       {
	
	      gCommParam.l_unit_ONOFF_flag[i]          = 0 ;  //������ʶ
				gCommParam.l_limit_recode[i]	           = 0xF0;		 //������ʶ lAnyError
			//����0xF0  TC����0xE1    VD������0xE2  VD������0xF2    
			                          //����������0xE3������������0xF3 �洢������0xE8
        gCommParam.lStats1[i]	                   = 0;	
   
        gCommParam.fIS[i]                        = i+0.001 ;		//����������Чֵ
        gCommParam.fPW[i]                        = i+0.002 ;		//���ʼ���ֵ
        gCommParam.fVS[i]                        = i+0.003 ;		//��ѹ������Чֵ		  
       }
				

   gCommParam.fIF_SET          = 0 ;        //�����趨ֵ,��Чֵ
   gCommParam.fIF_sx           = 0 ;        //
   gCommParam.fIF_xx           = 0 ;        //   
   

   gCommParam.fSetR = 19.5;		//�����趨ֵ	
			

			//PidBufStruct;  //��ʱ����
	    PID_BufInit(pPidBufA);
      PID_BufInit(pPidBufB);  //�߾������ٶȵ���PID���Ʋ���




Stm32IdSum6=0;                                                   //2�ֽ�
     

TimeAutoLock1=0;
TimeAutoLock2=0;
TimeAutoLock3=0;

FlagSetAllDefault = 0;
 
	#if CONFIG_UART1
	ClearLoopBuf(&Uart1RecvStruct,UART1_RECV_BUF_SIZE);	//������ͻ�����
	#endif
	#if CONFIG_UART2
	ClearLoopBuf(&Uart2RecvStruct,UART2_RECV_BUF_SIZE);	//������ͻ�����
	#endif
	#if CONFIG_UART3
	ClearLoopBuf(&Uart3RecvStruct,UART3_RECV_BUF_SIZE);	//������ͻ�����
	#endif		
}

void Default_ParamInit1(void)//��Ҫ����Ĳ���
{

	//unsigned char i;
	
//��Ҫ����Ĳ���

   //PID_ParaInit(&gPublic.PidRate[0], 5.0  , 0.01  ,0.002);  	//һ����ٵ���PID���Ʋ���
   //PID_ParaInit(&gPublic.PidRate[0],2.0  , 0.05  ,0.1);  	//һ����ٵ���PID���Ʋ���

   gCommParam.fMaxI = 125 ;		//maxI�����������
   gCommParam.fMaxV = 50  ;		//maxV��ѹ�������
   gCommParam.fMaxP = 600 ;		//maxP�����������


}

//////////////////////////



void Default_ParamInit2(void)//����ֵ
{
	 //unsigned char i;
	 gCommParam.fVS_AMP    =  1           ;		 //��ѹ�Ŵ���
	 gCommParam.fVS_BIS    =  0.0002           ;		 //��ѹƫ��

	 gCommParam.fIS_AMP1   =  1.0001           ;		 //�����Ŵ���
	 gCommParam.fIS_BIS1   =  0.001           ;		 //����ƫ��	bias
	 gCommParam.fIS_AMP2   =  1.0002           ;		 //�����Ŵ���
	 gCommParam.fIS_BIS2   =  0.002           ;		 //����ƫ��	bias   
	 gCommParam.fIS_AMP3   =  1.0003           ;		 //�����Ŵ���
	 gCommParam.fIS_BIS3   =  0.003           ;		 //����ƫ��	bias
	 gCommParam.fIS_AMP4   =  1.0004           ;		 //�����Ŵ���
	 gCommParam.fIS_BIS4   =  0.004           ;		 //����ƫ��	bias    
	 gCommParam.fIS_AMP5   =  1.0005           ;		 //�����Ŵ���
	 gCommParam.fIS_BIS5   =  0.005           ;		 //����ƫ��	bias
	 gCommParam.fIS_AMP6   =  1.0006           ;		 //�����Ŵ���
	 gCommParam.fIS_BIS6   =  0.006           ;		 //����ƫ��	bias   
	 gCommParam.fIS_AMP7   =  1.0007           ;		 //�����Ŵ���
	 gCommParam.fIS_BIS7   =  0.007           ;		 //����ƫ��	bias
	 gCommParam.fIS_AMP8   =  1.0008           ;		 //�����Ŵ���
	 gCommParam.fIS_BIS8   =  0.008           ;		 //����ƫ��	bias       
	 gCommParam.fIS_AMP9   =  1.0009           ;		 //�����Ŵ���
	 gCommParam.fIS_BIS9   =  0.009           ;		 //����ƫ��	bias 
	 gCommParam.fIS_AMP10  =  1.0011           ;		 //�����Ŵ���
	 gCommParam.fIS_BIS10  =  0.011           ;		 //����ƫ��	bias  	 
	 gCommParam.fIS_AMP11  =  1.0011           ;		 //�����Ŵ���
	 gCommParam.fIS_BIS11  =  0.011           ;		 //����ƫ��	bias 	 
	 gCommParam.fIS_AMP12  =  1.0011           ;		 //�����Ŵ���
	 gCommParam.fIS_BIS12  =  0.011           ;		 //����ƫ��	bias 	 
	 
	 //�߾������ٶȵ���PID���Ʋ���
//	 gCommParam.PidParamCtrl[0] = 0.1;//12   ;    
//	 gCommParam.PidParamCtrl[1] = 0.05;//3 ;  	 
//	 gCommParam.PidParamCtrl[2] = 0.001 ;  	 
	 
	 
	 #if CONFIG_CURRENT_CH10
	    	 //�߾������ٶȵ���PID���Ʋ���
	 gCommParam.PidParamCtrl[0] = 0.5;//2   ;    
	 gCommParam.PidParamCtrl[1] = 2;//8;//0.2;  	
	 gCommParam.PidParamCtrl[2] = 0.001 ;  	 
	 #else
	 	 //�߾������ٶȵ���PID���Ʋ���
	 gCommParam.PidParamCtrl[0] = 0.1;//12   ;    
	 gCommParam.PidParamCtrl[1] = 0.1; //0.3;//0.05;//3 ;  	 
	 gCommParam.PidParamCtrl[2] = 0.015 ;  	 
	 #endif
	 
	 //ͬ��PID���Ʋ���
	 gCommParam.PidParamSync[0] = 0.5;//2   ;    //.Proportion=2;           //�������� ͬ�� 1-5      
	 gCommParam.PidParamSync[1] = 0.2;//0.2 ;    //.Integral=0.2;           //         ͬ�� 0.1-0.5  
	 gCommParam.PidParamSync[2] = 0   ;    //.Derivative=0;           //                       		

}
//////////////////////////
unsigned char _GetParamCheck(unsigned char *p,unsigned short int len)
{
unsigned short int i;
unsigned char Sum;	
	//if(p->flag==FlagParamInitnized)
			//�����Ѿ���ʼ�������ȷ
			//ViewTestStatu("SAVE INIT OK\r\n");
			
			Sum=0;
			for(i=0;i<len;i++)
				{
				Sum+=*(p+i);//У����
				}

return Sum;
}
//////////////////////////
void _copy_4byte(unsigned char type,unsigned char *a,unsigned char *b,unsigned char len)
{
	unsigned char i;
	
	if(type == 0)  //  type = 0    a--> b
		{
			for(i=0;i<len;i++)
			  {
			  *(b+i)=*(a+i);
			
			  }
		}
		
else{  //  type = 1    a--> b
	
			for(i=0;i<len;i++)
			  {
			  *(a+i)=*(b+i);
			
			  }	
    }		
	
}

unsigned short int _Param_SwapMemery(unsigned char type,unsigned char *p)  //type = 0   Param --> memery_buf
{ 

       //	unsigned char  i;
       unsigned short int len;	
       
       len=0;
       	

               
               _copy_4byte(type,(unsigned char *)&gCommParam.fVS_AMP       , p , 4);		//��ѹ�Ŵ��� 
               p+=4;len+=4;
               _copy_4byte(type,(unsigned char *)&gCommParam.fVS_BIS       , p , 4);		//��ѹƫ��
               p+=4;len+=4;
               
               
               
               _copy_4byte(type,(unsigned char *)&gCommParam.fIS_AMP1       , p , 4);   	//�����Ŵ���
               p+=4;len+=4;                                                    
               _copy_4byte(type,(unsigned char *)&gCommParam.fIS_BIS1       , p , 4);   	//����ƫ��	
               p+=4;len+=4;                
               
               _copy_4byte(type,(unsigned char *)&gCommParam.fIS_AMP2       , p , 4);   	//�����Ŵ���
               p+=4;len+=4;                                                    
               _copy_4byte(type,(unsigned char *)&gCommParam.fIS_BIS2       , p , 4);   	//����ƫ��	
               p+=4;len+=4;                              
               
               _copy_4byte(type,(unsigned char *)&gCommParam.fIS_AMP3       , p , 4);   	//�����Ŵ���
               p+=4;len+=4;                                                    
               _copy_4byte(type,(unsigned char *)&gCommParam.fIS_BIS3       , p , 4);   	//����ƫ��	
               p+=4;len+=4;               
               
               _copy_4byte(type,(unsigned char *)&gCommParam.fIS_AMP4       , p , 4);   	//�����Ŵ���
               p+=4;len+=4;                                                    
               _copy_4byte(type,(unsigned char *)&gCommParam.fIS_BIS4       , p , 4);   	//����ƫ��	
               p+=4;len+=4;  
               
               _copy_4byte(type,(unsigned char *)&gCommParam.fIS_AMP5       , p , 4);   	//�����Ŵ���
               p+=4;len+=4;                                                    
               _copy_4byte(type,(unsigned char *)&gCommParam.fIS_BIS5       , p , 4);   	//����ƫ��	
               p+=4;len+=4;               
               
               _copy_4byte(type,(unsigned char *)&gCommParam.fIS_AMP6       , p , 4);   	//�����Ŵ���
               p+=4;len+=4;                                                    
               _copy_4byte(type,(unsigned char *)&gCommParam.fIS_BIS6       , p , 4);   	//����ƫ��	
               p+=4;len+=4;                 
               
               _copy_4byte(type,(unsigned char *)&gCommParam.fIS_AMP7       , p , 4);   	//�����Ŵ���
               p+=4;len+=4;                                                    
               _copy_4byte(type,(unsigned char *)&gCommParam.fIS_BIS7       , p , 4);   	//����ƫ��	
               p+=4;len+=4;               
               
               _copy_4byte(type,(unsigned char *)&gCommParam.fIS_AMP8       , p , 4);   	//�����Ŵ���
               p+=4;len+=4;                                                    
               _copy_4byte(type,(unsigned char *)&gCommParam.fIS_BIS8       , p , 4);   	//����ƫ��	
               p+=4;len+=4;                                
               
               _copy_4byte(type,(unsigned char *)&gCommParam.fIS_AMP9       , p , 4);   	//�����Ŵ���
               p+=4;len+=4;                                                    
               _copy_4byte(type,(unsigned char *)&gCommParam.fIS_BIS9       , p , 4);   	//����ƫ��	
               p+=4;len+=4;               
               
               _copy_4byte(type,(unsigned char *)&gCommParam.fIS_AMP10       , p , 4);   	//�����Ŵ���
               p+=4;len+=4;                                                    
               _copy_4byte(type,(unsigned char *)&gCommParam.fIS_BIS10       , p , 4);   	//����ƫ��	
               p+=4;len+=4;                 
               
               _copy_4byte(type,(unsigned char *)&gCommParam.fIS_AMP11       , p , 4);   	//�����Ŵ���
               p+=4;len+=4;                                                    
               _copy_4byte(type,(unsigned char *)&gCommParam.fIS_BIS11       , p , 4);   	//����ƫ��	
               p+=4;len+=4;                 

               _copy_4byte(type,(unsigned char *)&gCommParam.fIS_AMP12       , p , 4);   	//�����Ŵ���
               p+=4;len+=4;                                                    
               _copy_4byte(type,(unsigned char *)&gCommParam.fIS_BIS12       , p , 4);   	//����ƫ��	
               p+=4;len+=4;                 



               
               
               _copy_4byte(type,(unsigned char *)&gCommParam.fMaxI          , p , 4);		//�����������
               p+=4;len+=4;
               _copy_4byte(type,(unsigned char *)&gCommParam.fMaxV          , p , 4);		//��ѹ�������
               p+=4;len+=4;
               _copy_4byte(type,(unsigned char *)&gCommParam.fMaxP          , p , 4);		//�����������
               p+=4;len+=4;

      // _copy_4byte(type,(unsigned char *)&gCommParam.lBaudrate_reserve            , p , 4);        //����������	                                    //4�ֽ�
    //   p+=4;len+=4;
       //  _copy_4byte(type,(unsigned char *)&gCommParam.yy_reserve                  , p , 4);
       //  p+=4;len+=4;
       //  _copy_4byte(type,(unsigned char *)&gCommParam.SubAdr_reserve              , p , 4);        

       //  _copy_4byte(type,(unsigned char *)&gCommParam.SoftVer             , p , 4);  
       //  p+=4;len+=4;
         _copy_4byte(type,(unsigned char *)&Stm32IdSum6                   , p , 2);                                                   //2�ֽ�
         p+=2;len+=2;  
       
       return len;	
	
}




//////////////////////////



//////////////////////////
unsigned char Write_Param(void) // cMemBufA --> cMemBufB --> eeprom
{
	
  unsigned short int i;
  unsigned char numb,flag,sucess;	
  unsigned char 	checksum;
  
	sucess = 1;
	
	//_Param_SwapMemery(0,cMemBufA);   //parameter ---> cMemBufA
	//cMemBufB[Max_MemBuf-2] =  FlagParamInitnized;
	
	//check
	if( cMemBufA[Max_MemBuf-2] ==  FlagParamInitnized)
          {

           checksum = _GetParamCheck( cMemBufA , Max_MemBuf-1);  //����У����
           cMemBufA[ Max_MemBuf-1] = (~checksum)+1;
          }
  else {
  	    sucess = 0;  //��ʼ����ǲ���
  	    return 0;
  	   } 
  	   
  	   
  	         
  for(i=0;i<Max_MemBuf;i++)
    {
    
    flag = 0 ;
    for(numb=0;numb<3;numb++)
    			{	
    				 
    				
           //if(ReadByteEE(AT24C16_ADR+i) != cMemBufB[i])
            if(cMemBufA[i] != cMemBufB[i])	
    	         {
    	         	cMemBufB[i] = cMemBufA[i];
                
                SaveEE(AT24C16_ADR+i, cMemBufB[i]);
                gCommParam.lStats1[0] ++;
                if(ReadByteEE(AT24C16_ADR+i) == cMemBufB[i])
                	{
                		
                		flag = 1; //sucess
            	      break;
                	}
               }
            else{ 
            	   flag = 1; //sucess
            	   break;
            	  }
    			}
    
    if(flag == 0)
    			{
    				sucess = 0; //д�����
    			}	
    }

return sucess;
}
//////////////////////////

unsigned char Load_Param(void)  //eeprom --> cMemBufB --> cMemBufA
{
  unsigned short int i;
  unsigned char numb,flag;


  flag = 1;

  for(numb=0;numb<3;numb++)
      {		
      for(i=0;i<Max_MemBuf;i++)
           {
           cMemBufB[i]=ReadByteEE(AT24C16_ADR+i);  //��ʼ��ַ    // eeprom --> cMemBufB
           cMemBufA[i]=cMemBufB[i];                              // cMemBufB --> cMemBufA
           }	
      //check
      if( cMemBufA[Max_MemBuf-2] ==  FlagParamInitnized)
          {
	
           flag = _GetParamCheck( cMemBufA , Max_MemBuf);
          }
      
      if(  flag != 0)
          {//
           return 0;  //error
          }
          
      //ok
      //copy

      _Param_SwapMemery(1,cMemBufA);   //cMemBufA ---> parameter
      
          
      }
  return 1;
}




