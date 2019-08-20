//

 //   #include "app1.h"

#include <includes.h>

#include "stm32f10x.h"
#include "stdio.h"
#include "config.h"
#include "HD_PLASTIC1.h"
#include "adc.h"
//#include  "LedKeys.h"
#include "app1.h"
#include "lcd.h"
//#include "HT1621.h"
extern GPIO_InitTypeDef GPIO_InitStructure2;


unsigned char FlagDebug_SWCLK_Off;
unsigned char FlagEnable_TestMod;   //ENABLE_TEST_MOD

////////////////////////////////////////////////////////////////////

//#define   Delay_1ms    OSTimeDly(OS_TICKS_PER_SEC/1000)

#define   DelayTimeMs(x)    OSTimeDly( x * OS_TICKS_PER_SEC / 1000 )

//type enum 
//{
//	ModNomal,
//  ModHeatMatheSet,
//  ModTemprature,
//  ModRpm,
//  Test1,
//  Test2,
//  Test3	
//}_SetMod;  

_SetMod  SetMods   =  ModNomal  ;

//
//struct str_adc_resoult
//{
//unsigned short int 	temprature0;       //оƬ�ڲ��¶�
//unsigned short int 	rpm;               //ת��
//unsigned short int 	temptemprature1;   //�¶�1
//unsigned short int 	temptemprature2;   //�¶�2
//unsigned short int 	current;           //����ȵ���
//unsigned short int 	volt;              //��Դ��ѹ
//	
//}AdcRes;

 _str_adc_resoult     AdcRes;
 _str_key_get         KeyScan;


unsigned char LedsBuf;


//���������ת��Ϊ����ֵ
unsigned short int PowerToShiftTimr( unsigned short int val)
{
    //����������ֵ
    #define Mod  1000
    
    //���������Сֵ
    #define min  100
    
    //����������1000
    #define max  1000
    
    unsigned short int  shift;            //�������ֵ
    
    if( val > Mod ) val = Mod;
    	
    shift = Mod - val ;                   //  1000 -val
    
    if( shift < min ) shift = 0 ;         //�ʼ����λ����
    
    if( shift > max ) shift = max ;       //��������λ����
    
    return   shift ;                      //�������ֵ

}

/////////////////////////////////////////////////////////////
void Get_ChipAdc_Measure(void)
{
//unsigned short int temp16;


	
	#if CONFIG_ADC
	
					AdcFilter();

          //оƬ�ڲ��¶ȴ������� 25��ʱΪ0x6e2�� �൱��1.43v  ,б��4.3mv
           AdcRes.temprature0  =  25 * 10 + 10 * ( 0x6E2 - After_filter[0] ) * 3300/17612;   //AdcRes.temp0  =  25 + ( 0x6E2 - After_filter[0] ) * 3300/4096/4.3 

//           //�������ٷ����
//           AdcRes.RpmCur            = After_filter[1]  *990 /4095 ;             //ת�٣� ���99
//               
//           AdcRes.temptemprature1   = After_filter[2] /8 ;              //�¶�1
//           AdcRes.temptemprature2   = After_filter[3] /8 ;              //�¶�2
//           
//           AdcRes.current           = After_filter[4] /8;              //����ȵ���
//           
//	         AdcRes.volt              = After_filter[5] /20;              //��Դ��ѹ
#endif



}                  
/////////////////////////////////////////////////////////////                  



//#define DelayTimeUs ;


unsigned char KeyLedScan( unsigned char ledsbuf  ) 
{
      unsigned char keybuf;
      
      keybuf = 0 ;
      
     //��һ��
     LedKeyPortReSet(1);   //����Ϊ�����
     if( ledsbuf & 0x01 )
     	{
     		LEDCOM1_0();
     	}
     if( ledsbuf & 0x02 )
     	{
     		LEDCOM2_0();
     	}	

     
     KIO1_1();//��һ��
     KIO2_0();
     KIO3_0();
     
     DelayTimeMs(1);   //��һ��
     DelayTimeMs(1);
     DelayTimeMs(1);
     
     
     //׼����
     //LEDCOM1_1();
     //LEDCOM2_1();
     KIO2_In();//��һ��
     KIO3_In();
     KIO1_0(); 
        
     LedKeyPortReSet(0);  //����Ϊ�����
     
     
     //DelayTimeUs;
     
     if(  LEDCOM1_IS_0() )
     	{
     		keybuf  |=  0x01;
     	}
     
     if(  LEDCOM2_IS_0() )
     	{
     		keybuf  |=  0x02;
     	}
     


 
 
     //�ڶ���
     LedKeyPortReSet(1);   //����Ϊ�����
     
     if( ledsbuf & 0x04 )
     	{
     		LEDCOM1_0();
     	}
     if( ledsbuf & 0x08 )
     	{
     		LEDCOM2_0();
     	}	

     
     KIO2_1();//�ڶ���
     KIO1_0();
     KIO3_0();
     
     DelayTimeMs(1);   //��һ��
     DelayTimeMs(1);
     DelayTimeMs(1);
     
     
     //׼����
     //LEDCOM1_1();
     //LEDCOM2_1();     
     KIO3_In();//�ڶ���
     KIO1_In();
     KIO2_0();
     
     LedKeyPortReSet(0);  //����Ϊ�����
     
     
     //DelayTimeUs;
     
     if(  LEDCOM1_IS_0() )
     	{
     		keybuf  |=  0x04;
     	}
     
     if(  LEDCOM2_IS_0() )
     	{
     		keybuf  |=  0x08;
     	}

     //������
     
     LedKeyPortReSet(1);   //����Ϊ�����
     if( ledsbuf & 0x10 )
     	{
     		LEDCOM1_0();
     	}
     if( ledsbuf & 0x20 )
     	{
     		LEDCOM2_0();
     	}	

     
     KIO3_1();//������
     KIO2_0();
     KIO1_0();
     
     DelayTimeMs(1);   //��һ��
     DelayTimeMs(1);
     DelayTimeMs(1);
     
     
     //׼����
     //LEDCOM1_1();
     //LEDCOM2_1();     
     KIO2_In();//��3��
     KIO1_In();
     KIO3_0();
     
     LedKeyPortReSet(0);  //����Ϊ�����
     
     
     //DelayTimeUs;
     
     if(  LEDCOM1_IS_0() )
     	{
     		keybuf  |=  0x10;
     	}
     
     if(  LEDCOM2_IS_0() )
     	{
     		keybuf  |=  0x20;
     	}  
     	KIO3_In();
     	KIO2_In();
      KIO1_In();   
     return   keybuf	;
     
}

////////////////////////////////////////
#define   KEY_SELECT   0x01
#define   KEY_ADD      0X04
#define   KEY_DEC      0X08
#define   KEY_OK       0X02
#define   KEY_ON       0X10
#define   KEY_OFF      0X20



////////////////////////////////////////////
void _KeySelect_Process	( void  )     //ѡ����Ĳ���
{
   if (  KeyScan.resoult != KeyScan.last  )
  	    {//���ǳ���
 	        switch ( SetMods )
 	            {
 	            	
 	            case ModNomal:  //ƽʱģʽ
 	            	
                  SetMods  =  ModHeatMatheSet ;
                  
              break;
              
              case ModHeatMatheSet:  //���ȷ�ʽѡ��
              	
                  SetMods  =  ModTemprature ;
                  
              break;
              
              case ModTemprature:  //�����¶�ģʽ
              	
                  SetMods  =  ModRpm ;
                  
              break;
              
              case ModRpm:  //�����ٶ�
              	SetMods  =  ModNomal ;
              	
              	#if ENABLE_TEST_MOD
              	
                   if ( FlagEnable_TestMod != 0 )   //ENABLE_TEST_MOD
                        {
                        	SetMods  =  Test1  ;
                        }
                        
                #endif
                   
              break;
              
              case Test1:
              
                SetMods  =  ModNomal ;
              	
              	#if ENABLE_TEST_MOD
              	
                   if ( FlagEnable_TestMod != 0 )   //ENABLE_TEST_MOD
                        {
                        	SetMods  =  Test2  ;
                        }
                        
                #endif
                
              break;
              
              case Test2:
              
                SetMods  =  ModNomal ;
              	
              	#if ENABLE_TEST_MOD
              	
                   if ( FlagEnable_TestMod != 0 )   //ENABLE_TEST_MOD
                        {
                        	SetMods  =  Test3_rmp_pid  ;
                        }
                        
                #endif
                              
              break;
              
              case Test3_rmp_pid:
                   SetMods  =  ModNomal ; 
              break;
              
              default:
              	   SetMods  =  ModNomal ;
              break;	
             }	
        }
	
}
////////////////////////////////////////////
void _KeyAdd_Process	( void )       //���Ӽ��Ĳ���
{
   //if (  KeyScan.resoult != KeyScan.last  )//���ǳ���

 	        switch ( SetMods )
 	            {
 	            case ModNomal:  //ƽʱģʽ
 	            case ModRpm:  //�����ٶ�
 	            	if ( KeyScan.AdjTim == 1 )
 	            		  {
 	            	    if (  LcdPort.RpmSet < 99 )
                 	        LcdPort.RpmSet ++ ;
                 	  }
                 	      
 	            	
               	if ( KeyScan.age < 250 )
              		  {
                   if ( KeyScan.AdjTim > 30 )
                   	     { 
                   		    KeyScan.AdjTim = 0 ;
                         } 
                 	    }
                 else  {//����
                 	   	if ( KeyScan.AdjTim > 15 )
                   	     { 
                   	     	KeyScan.AdjTim = 0 ;
                 	        }
                    }             
              break;
              
              case ModHeatMatheSet:  //���ȷ�ʽѡ��
                
              break;
              
              case ModTemprature:  //�����¶�ģʽ
              if ( KeyScan.AdjTim == 1 )
                   	     { 
                          if (  LcdPort.TempratureSet < 999 )
                 	                LcdPort.TempratureSet ++ ;
                 	       }
                 
              if ( KeyScan.age < 250 )
              		 {
                   if ( KeyScan.AdjTim > 30 )
                   	     { 
                   		   KeyScan.AdjTim = 0 ;
                 	       }
                 	    }
                 else {//����
                 	   	if ( KeyScan.AdjTim > 10 )
                   	     { 
                   	     	KeyScan.AdjTim = 0 ;
                 	        }
                    }  
              break;
              
              


                 	  
                 	  
             
              
              case Test1:
              
              break;
              
              case Test2:
              
              break;
              
              case Test3_rmp_pid:
              
              break;
              
              default:
              	
              break;	
             }	
}
////////////////////////////////////////////

void _KeyDec_Process	( void  )        //���ټ��Ĳ���
{
   //if (  KeyScan.resoult != KeyScan.last  )//���ǳ���
   
 	        switch ( SetMods )
 	            {
 	            case ModNomal:  //ƽʱģʽ
 	            case ModRpm:  //�����ٶ�

 	            	if ( KeyScan.AdjTim == 1 )
 	            		  {
 	            	    if (  LcdPort.RpmSet > 0 )
                 	        LcdPort.RpmSet -- ;
                 	  }
                 	      
 	            	
               	if ( KeyScan.age < 250 )
              		  {
                   if ( KeyScan.AdjTim > 30 )
                   	     { 
                   		    KeyScan.AdjTim = 0 ;
                         } 
                 	    }
                 else  {//����
                 	   	if ( KeyScan.AdjTim > 15 )
                   	     { 
                   	     	KeyScan.AdjTim = 0 ;
                 	        }
                    }                  
              break;
              case ModHeatMatheSet:  //���ȷ�ʽѡ��
                
              break;
              
              case ModTemprature:  //�����¶�ģʽ

               if ( KeyScan.AdjTim == 1 )
                   	     { 
                          if (  LcdPort.TempratureSet > 0 )
                 	                LcdPort.TempratureSet -- ;
                 	       }
                 
              if ( KeyScan.age < 250 )
              		 {
                   if ( KeyScan.AdjTim > 30 )
                   	     { 
                   		   KeyScan.AdjTim = 0 ;
                 	       }
                 	    }
                 else {//����
                 	   	if ( KeyScan.AdjTim > 10 )
                   	     { 
                   	     	KeyScan.AdjTim = 0 ;
                 	        }
                    }                   
                    
                    
              break;
   


              case Test1:
              
              break;
              case Test2:
              
              break;
              case Test3_rmp_pid:
              
              break;
              
              default:
              break;	
             }	
}
////////////////////////////////////////////
void SwitchDirect( unsigned char x )  //����̵����л�����  0��ת 1��ת
{

if ( x == 0 )JSP1_1();
	
	else  JSP1_0();//����̵����л�����  0��ת 1��ת
	
}
////////////////////////////////////////////
void KeyProcess( _str_key_get   k   )
{
		switch ( k.resoult )  //KeyScan.resoult
	   {
	   	case KEY_SELECT:  //ѡ���
	   	
	   	   _KeySelect_Process	(  ) ;     //ѡ����Ĳ���

	   	break;
	   	case KEY_ADD:
	   		
          _KeyAdd_Process	(  ) ;       //���Ӽ��Ĳ���
          
	   	break;	
	   	case KEY_DEC:  //  --
	   		
          _KeyDec_Process	(  ) ;       //���ټ��Ĳ���
          
	   	break;
	   	
	   	case KEY_OK:  //ȷ�ϼ�
	   		
	   		  SetMods  =  ModNomal ;
	   		  
	   	break;
	   	
	   	case KEY_ON:  //ON��
	   		
	   		if (  KeyScan.resoult != KeyScan.last  )
	   			   {	   		     //�����л�
	   		     //���PID,���������ı䷽��	
	   		     LcdPort.RpmBackSet = 0;   //�����ٶ�   		     
	   		     if( LcdPort.MovingF  == 0 )
	   		     	{
	   		     
	   		       DelayTimeMs(50);
	   		       SwitchDirect(0);  //����̵����л�����  0��ת 1��ת
	   		       DelayTimeMs(50);  
	   		        
	   		      }
	   		     LcdPort.StopF = 1 ;
	   		     LcdPort.MovingF  =  1 ;
	   		     
	   		     }
	   		
	   		
	   	break;	  
	   	
	   	case KEY_OFF:  //OFF��
	   		
	   		   
	   		   if ( KeyScan.age == 3 )
	   		   	{
	   		   		SwitchDirect(1);  //����̵����л�����  0��ת 1��ת
	   		   			//LcdPort.MovingF  =  1 ;
	   		   	}
	   		   else if ( KeyScan.age >= 50 )
	   		   	{
	   		   		LcdPort.MovingF  =  1 ;
	   		   		LcdPort.RpmBackSet = 45;   //�����ٶ�  �̶���
	   		   		
	   		   		if ( KeyScan.age > 150 )
	   		   	     {
	   		   		LcdPort.RpmBackSet += 1;   //�����ٶ�
	   		        	}
	   		   	}	
	   		  else{   		     
	   		       LcdPort.MovingF  =  0 ;
	   		       LcdPort.RpmBackSet = 0;   //�����ٶ�
	   		  	  LcdPort.StopF = 0 ;
	   		      } 	
	   		   	
	   	break; 
		}	
	   	
}
////////////////////////////////////////

void KeyGet(unsigned char key_in)
{

if( KeyScan.buf1 != key_in )
	{//���Ż��߱仯��
		KeyScan.buf1 = key_in ;  //����
		return;
  }
  
if( KeyScan.buf2 != KeyScan.buf1 )
	{//���Ż��߱仯��
		KeyScan.buf2 = KeyScan.buf1 ;   //����
		return;
  }	
	
if( KeyScan.buf3 != KeyScan.buf2 )
	{//���Ż��߱仯��
		KeyScan.buf3 = KeyScan.buf2 ;   //����
		return;
  }		
  

  
KeyScan.resoult = KeyScan.buf1;
	
KeyProcess( KeyScan ); //KeyScan.resoult , KeyScan.buf1 ,KeyScan.age);	

if( KeyScan.last != KeyScan.resoult )
	{
		KeyScan.last = KeyScan.resoult; //����
		KeyScan.age = 0;
		KeyScan.AdjTim = 0;
		KeyScan.NoKeyTim = 0;
	}
else{
	   if( KeyScan.NoKeyTim < 254 )KeyScan.NoKeyTim  ++ ; //
	   
	   if(KeyScan.resoult !=  0 )
	   	   {
	       if( KeyScan.age <254 )KeyScan.age++;
	       	if( KeyScan.AdjTim <254 )KeyScan.AdjTim++;
	       }
	   else{//   KeyScan.resoult ==  0
	   	   //if( KeyScan.NoKeyTim < 254 )KeyScan.NoKeyTim  ++ ; //
	   	  }
    }

}




//��ֵ��
#define  InterPoint_Tab_Long  42
unsigned short int InterPointTab[InterPoint_Tab_Long + 3]
={ //��ֵ��
29         ,     //0           704      
38         ,     //5           539      
49         ,     //10          415.9    
62         ,     //15          323.48   
79         ,     //20          253.46   
100        ,     //25          200      
125        ,     //30          158.878  
155        ,     //35          127.021  
191        ,     //40          102.17   
234        ,     //45          82.668   
283        ,     //50          67.26    
341        ,     //55          55       
408        ,     //60          45.234   
483        ,     //65          37.37    
569        ,     //70          31       
663        ,     //75          25.87    
768        ,     //80          21.665   
882        ,     //85          18.22    
1005       ,     //90          15.3845  
1135       ,     //95          13.04    
1272       ,     //100         11.0948  
1415       ,     //105         9.4733   
1561       ,     //110         8.1168   
1710       ,     //115         6.9778   
1859       ,     //120         6.018    
2007       ,     //125         5.2064   
2152       ,     //130         4.5178   
2293       ,     //135         3.93     
2429       ,     //140         3.4314   
2560       ,     //145         3        
2660       ,     //150         2.7     ���150�� 
2831       ,     //155         2.235    
2926       ,     //160         2        
3012       ,     //165         1.8      
3103       ,     //170         1.6      
3200       ,     //175         1.4      
3303       ,     //180         1.2      
3413       ,     //185         1        
3531       ,     //190         0.8      
3657       ,     //195         0.6      
3793       ,     //200         0.4      
3938       ,     //205         0.2      
4092       ,     //210          0        
4094       ,     //210         0 
4096             //210         0 
	
  };

//unsigned short int InterPointCala( unsigned short int  x )
//{
//	//ʵ�����뷶Χ Xmax - Xmin
//	//���Χ  Nmax - Nmin
//	// Nx1  =  Nmin + ( x - Xmin ) * ( Nmax - Nmin ) / ( Xmax - Xmin )   //��ǰ���λ��1
//	
//	// x1 =    Xmin + ( Nx1  -  Nmin )  *  ( Xmax - Xmin ) /  ( Nmax - Nmin )    //��ǰ���λ��ʵ������ֵ
//	
//	// y1 +  ( y2-y1 ) / ( Nx2 -Nx1 ) * ( x - x1 )    ....    Nx2 = Nx1 + 1
//	unsigned char Nx1 ;
//	unsigned short int  x1 ;
//  
//	
//	
//	
//return 	InterPointTab[ Nx1 ] + ( InterPointTab[ Nx1 + 1 ] - InterPointTab[Nx1] ) * ( x - x1 );
//	
//}





unsigned short int _InterPointPosition( unsigned short int  y  , unsigned short int *AAA )
{

	unsigned short int pointLow,pointHalf,pointHigh, i;
	
	pointHigh =  InterPoint_Tab_Long ;   //��λ��
	pointLow = 0;                       //��λ��
	
	
	for( i =0 ; i< InterPoint_Tab_Long ;i++ )
	{
	if ( pointHigh <= pointLow  )
		{//ok			
			return pointHalf=0;
		}
		
	pointHalf = ( pointHigh - pointLow )/ 2  + pointLow ;	 //����λ��
		
	if ( pointHigh <= pointHalf  )
		{//ok			
			return pointHalf;
		}	
	if ( pointLow >= pointHalf  )
		{//ok			
			return pointHalf;
		}	
				
	if( y == AAA [ pointHalf ] )
		  {//ok
			return pointHalf;
		  }
		else	if( y >  AAA [ pointHalf ] )
		{ 
			if( y < AAA [ pointHalf + 1 ] )
				  {// ok
					return pointHalf;
				  }
			
			
			
		  pointLow = pointHalf + 1  ;   //

	  }
	else{
		  pointHigh =  pointHalf   ;   
		  
		  }
		}
	
	
return pointHalf;
		
}
//////////////////////////

// InterPointTab
unsigned short int InterPointCala( unsigned short int  y )
{
	//ʵ�����뷶Χ Xmax - Xmin
	//���Χ  Nmax - Nmin
	// Nx1  =  Nmin + ( x - Xmin ) * ( Nmax - Nmin ) / ( Xmax - Xmin )   //��ǰ���λ��1
	
	// x1 =    Xmin + ( Nx1  -  Nmin )  *  ( Xmax - Xmin ) /  ( Nmax - Nmin )    //��ǰ���λ��ʵ������ֵ
	
	// y1 +  ( y2-y1 ) / ( Nx2 -Nx1 ) * ( x - x1 )    ....    Nx2 = Nx1 + 1

	unsigned short int  x , x1 , y1 , y2 ;
  
  unsigned short int  *tabx;
  
  tabx = InterPointTab;
  
  x1 = _InterPointPosition( y , tabx );
  
	//x = x1 +  ( x2 - x1 ) * ( y - y1 ) / ( y2 -y1 ); 
	y1 = *( tabx + x1);
	y2 = *( tabx + x1 +1 );
	x = 5 * x1 +  5*( y - y1 ) / ( y2 -y1 );    //���5��
	
return 	x;
	
}


//void InterPoint_Test(void)
//{
//unsigned short int	ff[30];
//unsigned short int i;	
//	for(i=0;i<22;i++)
//	{
//		
//		ff[i]=InterPointCala(i , InterPointTab );
//	}
//	
//	
//}
//







