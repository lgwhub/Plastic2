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
//unsigned short int 	temprature0;       //芯片内部温度
//unsigned short int 	rpm;               //转速
//unsigned short int 	temptemprature1;   //温度1
//unsigned short int 	temptemprature2;   //温度2
//unsigned short int 	current;           //电加热电流
//unsigned short int 	volt;              //电源电压
//	
//}AdcRes;

 _str_adc_resoult     AdcRes;
 _str_key_get         KeyScan;


unsigned char LedsBuf;


//电机控制量转化为移相值
unsigned short int PowerToShiftTimr( unsigned short int val)
{
    //输入参数最大值
    #define Mod  1000
    
    //输出参数最小值
    #define min  100
    
    //输出参数最大1000
    #define max  1000
    
    unsigned short int  shift;            //电机移相值
    
    if( val > Mod ) val = Mod;
    	
    shift = Mod - val ;                   //  1000 -val
    
    if( shift < min ) shift = 0 ;         //最开始的相位放弃
    
    if( shift > max ) shift = max ;       //最后面的相位放弃
    
    return   shift ;                      //电机移相值

}

/////////////////////////////////////////////////////////////
void Get_ChipAdc_Measure(void)
{
//unsigned short int temp16;


	
	#if CONFIG_ADC
	
					AdcFilter();

          //芯片内部温度传感器， 25度时为0x6e2， 相当于1.43v  ,斜率4.3mv
           AdcRes.temprature0  =  25 * 10 + 10 * ( 0x6E2 - After_filter[0] ) * 3300/17612;   //AdcRes.temp0  =  25 + ( 0x6E2 - After_filter[0] ) * 3300/4096/4.3 

//           //交流测速发电机
//           AdcRes.RpmCur            = After_filter[1]  *990 /4095 ;             //转速， 最大99
//               
//           AdcRes.temptemprature1   = After_filter[2] /8 ;              //温度1
//           AdcRes.temptemprature2   = After_filter[3] /8 ;              //温度2
//           
//           AdcRes.current           = After_filter[4] /8;              //电加热电流
//           
//	         AdcRes.volt              = After_filter[5] /20;              //电源电压
#endif



}                  
/////////////////////////////////////////////////////////////                  



//#define DelayTimeUs ;


unsigned char KeyLedScan( unsigned char ledsbuf  ) 
{
      unsigned char keybuf;
      
      keybuf = 0 ;
      
     //第一组
     LedKeyPortReSet(1);   //设置为输出口
     if( ledsbuf & 0x01 )
     	{
     		LEDCOM1_0();
     	}
     if( ledsbuf & 0x02 )
     	{
     		LEDCOM2_0();
     	}	

     
     KIO1_1();//第一组
     KIO2_0();
     KIO3_0();
     
     DelayTimeMs(1);   //亮一会
     DelayTimeMs(1);
     DelayTimeMs(1);
     
     
     //准备读
     //LEDCOM1_1();
     //LEDCOM2_1();
     KIO2_In();//第一组
     KIO3_In();
     KIO1_0(); 
        
     LedKeyPortReSet(0);  //设置为输入口
     
     
     //DelayTimeUs;
     
     if(  LEDCOM1_IS_0() )
     	{
     		keybuf  |=  0x01;
     	}
     
     if(  LEDCOM2_IS_0() )
     	{
     		keybuf  |=  0x02;
     	}
     


 
 
     //第二组
     LedKeyPortReSet(1);   //设置为输出口
     
     if( ledsbuf & 0x04 )
     	{
     		LEDCOM1_0();
     	}
     if( ledsbuf & 0x08 )
     	{
     		LEDCOM2_0();
     	}	

     
     KIO2_1();//第二组
     KIO1_0();
     KIO3_0();
     
     DelayTimeMs(1);   //亮一会
     DelayTimeMs(1);
     DelayTimeMs(1);
     
     
     //准备读
     //LEDCOM1_1();
     //LEDCOM2_1();     
     KIO3_In();//第二组
     KIO1_In();
     KIO2_0();
     
     LedKeyPortReSet(0);  //设置为输入口
     
     
     //DelayTimeUs;
     
     if(  LEDCOM1_IS_0() )
     	{
     		keybuf  |=  0x04;
     	}
     
     if(  LEDCOM2_IS_0() )
     	{
     		keybuf  |=  0x08;
     	}

     //第三组
     
     LedKeyPortReSet(1);   //设置为输出口
     if( ledsbuf & 0x10 )
     	{
     		LEDCOM1_0();
     	}
     if( ledsbuf & 0x20 )
     	{
     		LEDCOM2_0();
     	}	

     
     KIO3_1();//第三组
     KIO2_0();
     KIO1_0();
     
     DelayTimeMs(1);   //亮一会
     DelayTimeMs(1);
     DelayTimeMs(1);
     
     
     //准备读
     //LEDCOM1_1();
     //LEDCOM2_1();     
     KIO2_In();//第3组
     KIO1_In();
     KIO3_0();
     
     LedKeyPortReSet(0);  //设置为输入口
     
     
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
void _KeySelect_Process	( void  )     //选择键的操作
{
   if (  KeyScan.resoult != KeyScan.last  )
  	    {//不是长按
 	        switch ( SetMods )
 	            {
 	            	
 	            case ModNomal:  //平时模式
 	            	
                  SetMods  =  ModHeatMatheSet ;
                  
              break;
              
              case ModHeatMatheSet:  //加热方式选择
              	
                  SetMods  =  ModTemprature ;
                  
              break;
              
              case ModTemprature:  //设置温度模式
              	
                  SetMods  =  ModRpm ;
                  
              break;
              
              case ModRpm:  //设置速度
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
void _KeyAdd_Process	( void )       //增加键的操作
{
   //if (  KeyScan.resoult != KeyScan.last  )//不是长按

 	        switch ( SetMods )
 	            {
 	            case ModNomal:  //平时模式
 	            case ModRpm:  //设置速度
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
                 else  {//快速
                 	   	if ( KeyScan.AdjTim > 15 )
                   	     { 
                   	     	KeyScan.AdjTim = 0 ;
                 	        }
                    }             
              break;
              
              case ModHeatMatheSet:  //加热方式选择
                
              break;
              
              case ModTemprature:  //设置温度模式
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
                 else {//快速
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

void _KeyDec_Process	( void  )        //减少键的操作
{
   //if (  KeyScan.resoult != KeyScan.last  )//不是长按
   
 	        switch ( SetMods )
 	            {
 	            case ModNomal:  //平时模式
 	            case ModRpm:  //设置速度

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
                 else  {//快速
                 	   	if ( KeyScan.AdjTim > 15 )
                   	     { 
                   	     	KeyScan.AdjTim = 0 ;
                 	        }
                    }                  
              break;
              case ModHeatMatheSet:  //加热方式选择
                
              break;
              
              case ModTemprature:  //设置温度模式

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
                 else {//快速
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
void SwitchDirect( unsigned char x )  //电机继电器切换方向  0正转 1反转
{

if ( x == 0 )JSP1_1();
	
	else  JSP1_0();//电机继电器切换方向  0正转 1反转
	
}
////////////////////////////////////////////
void KeyProcess( _str_key_get   k   )
{
		switch ( k.resoult )  //KeyScan.resoult
	   {
	   	case KEY_SELECT:  //选择键
	   	
	   	   _KeySelect_Process	(  ) ;     //选择键的操作

	   	break;
	   	case KEY_ADD:
	   		
          _KeyAdd_Process	(  ) ;       //增加键的操作
          
	   	break;	
	   	case KEY_DEC:  //  --
	   		
          _KeyDec_Process	(  ) ;       //减少键的操作
          
	   	break;
	   	
	   	case KEY_OK:  //确认键
	   		
	   		  SetMods  =  ModNomal ;
	   		  
	   	break;
	   	
	   	case KEY_ON:  //ON键
	   		
	   		if (  KeyScan.resoult != KeyScan.last  )
	   			   {	   		     //方向切换
	   		     //清除PID,清除输出，改变方向	
	   		     LcdPort.RpmBackSet = 0;   //倒退速度   		     
	   		     if( LcdPort.MovingF  == 0 )
	   		     	{
	   		     
	   		       DelayTimeMs(50);
	   		       SwitchDirect(0);  //电机继电器切换方向  0正转 1反转
	   		       DelayTimeMs(50);  
	   		        
	   		      }
	   		     LcdPort.StopF = 1 ;
	   		     LcdPort.MovingF  =  1 ;
	   		     
	   		     }
	   		
	   		
	   	break;	  
	   	
	   	case KEY_OFF:  //OFF键
	   		
	   		   
	   		   if ( KeyScan.age == 3 )
	   		   	{
	   		   		SwitchDirect(1);  //电机继电器切换方向  0正转 1反转
	   		   			//LcdPort.MovingF  =  1 ;
	   		   	}
	   		   else if ( KeyScan.age >= 50 )
	   		   	{
	   		   		LcdPort.MovingF  =  1 ;
	   		   		LcdPort.RpmBackSet = 45;   //倒退速度  固定的
	   		   		
	   		   		if ( KeyScan.age > 150 )
	   		   	     {
	   		   		LcdPort.RpmBackSet += 1;   //倒退速度
	   		        	}
	   		   	}	
	   		  else{   		     
	   		       LcdPort.MovingF  =  0 ;
	   		       LcdPort.RpmBackSet = 0;   //倒退速度
	   		  	  LcdPort.StopF = 0 ;
	   		      } 	
	   		   	
	   	break; 
		}	
	   	
}
////////////////////////////////////////

void KeyGet(unsigned char key_in)
{

if( KeyScan.buf1 != key_in )
	{//干扰或者变化中
		KeyScan.buf1 = key_in ;  //更新
		return;
  }
  
if( KeyScan.buf2 != KeyScan.buf1 )
	{//干扰或者变化中
		KeyScan.buf2 = KeyScan.buf1 ;   //更新
		return;
  }	
	
if( KeyScan.buf3 != KeyScan.buf2 )
	{//干扰或者变化中
		KeyScan.buf3 = KeyScan.buf2 ;   //更新
		return;
  }		
  

  
KeyScan.resoult = KeyScan.buf1;
	
KeyProcess( KeyScan ); //KeyScan.resoult , KeyScan.buf1 ,KeyScan.age);	

if( KeyScan.last != KeyScan.resoult )
	{
		KeyScan.last = KeyScan.resoult; //更新
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




//插值法
#define  InterPoint_Tab_Long  42
unsigned short int InterPointTab[InterPoint_Tab_Long + 3]
={ //插值表
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
2660       ,     //150         2.7     最高150度 
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
//	//实际输入范围 Xmax - Xmin
//	//表格范围  Nmax - Nmin
//	// Nx1  =  Nmin + ( x - Xmin ) * ( Nmax - Nmin ) / ( Xmax - Xmin )   //当前表格位置1
//	
//	// x1 =    Xmin + ( Nx1  -  Nmin )  *  ( Xmax - Xmin ) /  ( Nmax - Nmin )    //当前表格位置实际输入值
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
	
	pointHigh =  InterPoint_Tab_Long ;   //高位置
	pointLow = 0;                       //低位置
	
	
	for( i =0 ; i< InterPoint_Tab_Long ;i++ )
	{
	if ( pointHigh <= pointLow  )
		{//ok			
			return pointHalf=0;
		}
		
	pointHalf = ( pointHigh - pointLow )/ 2  + pointLow ;	 //折中位置
		
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
	//实际输入范围 Xmax - Xmin
	//表格范围  Nmax - Nmin
	// Nx1  =  Nmin + ( x - Xmin ) * ( Nmax - Nmin ) / ( Xmax - Xmin )   //当前表格位置1
	
	// x1 =    Xmin + ( Nx1  -  Nmin )  *  ( Xmax - Xmin ) /  ( Nmax - Nmin )    //当前表格位置实际输入值
	
	// y1 +  ( y2-y1 ) / ( Nx2 -Nx1 ) * ( x - x1 )    ....    Nx2 = Nx1 + 1

	unsigned short int  x , x1 , y1 , y2 ;
  
  unsigned short int  *tabx;
  
  tabx = InterPointTab;
  
  x1 = _InterPointPosition( y , tabx );
  
	//x = x1 +  ( x2 - x1 ) * ( y - y1 ) / ( y2 -y1 ); 
	y1 = *( tabx + x1);
	y2 = *( tabx + x1 +1 );
	x = 5 * x1 +  5*( y - y1 ) / ( y2 -y1 );    //间隔5度
	
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







