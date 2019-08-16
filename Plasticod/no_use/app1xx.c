//

 //   #include "app1.h"

#include <includes.h>

#include "stm32f10x.h"
#include "stdio.h"
#include "config.h"
#include "HD_PLASTIC1.h"


////////////////////////////////////////////////////////////////////



//电机控制量转化为移相值
unsigned short int PowerToShiftTimr( unsigned short int val)
{

    #define Mod  1000
    
    #define min  100
    
    //最大1000
    #define max  950
    
    unsigned short int  shift;            //电机移相值
    
    if( val > Mod ) shift = Mod;
    	
    shift = Mod - val ;                   //  1000 -val
    
    if( shift < min ) shift = 0 ;         //最开始的相位放弃
    
    if( shift > max ) shift = max ;       //最后面的相位放弃
    
    return   shift ;                      //电机移相值

}

                  
/////////////////////////////////////////////////////////////                  

#define   Delay_1ms    OSTimeDly(OS_TICKS_PER_SEC/1000)


unsigned char LedKeyProcess( unsigned char FlagLed  ) 
{
      unsigned char keybuf;
      
      keybuf = 0 ;
      
     //第一组
     if( FlagLed & 0x01 )
     	{
     		LEDCOM1_0();
     	}
     if( FlagLed & 0x02 )
     	{
     		LEDCOM2_0();
     	}	

     
     KIO1_1();//第一组
     
     Delay_1ms;   //亮一会
     Delay_1ms;
     Delay_1ms;
     
     
     //准备读
     KIO1_0();//第一组
     
     LEDCOM1_1();  //oc
     LEDCOM2_1();
     
     Delay_1ms;
     
     if(  LEDCOM1_IS_0() )
     	{
     		keybuf  |=  0x01;
     	}
     
     if(  LEDCOM2_IS_0() )
     	{
     		keybuf  |=  0x02;
     	}
     

     
     //第二组
     if( FlagLed & 0x04 )
     	{
     		LEDCOM1_0();
     	}
     if( FlagLed & 0x08 )
     	{
     		LEDCOM2_0();
     	}	

     
     KIO2_1();//第一组
     
     Delay_1ms;   //亮一会
     Delay_1ms;
     Delay_1ms;
     
     
     //准备读
     KIO2_0();//第一组
     
     LEDCOM1_1();  //oc
     LEDCOM2_1();
     
     Delay_1ms;
     
     if(  LEDCOM1_IS_0() )
     	{
     		keybuf  |=  0x04;
     	}
     
     if(  LEDCOM2_IS_0() )
     	{
     		keybuf  |=  0x08;
     	}

     //第三组
     if( FlagLed & 0x10 )
     	{
     		LEDCOM1_0();
     	}
     if( FlagLed & 0x20 )
     	{
     		LEDCOM2_0();
     	}	

     
     KIO3_1();//第一组
     
     Delay_1ms;   //亮一会
     Delay_1ms;
     Delay_1ms;
     
     
     //准备读
     KIO3_0();//第一组
     
     LEDCOM1_1();  //oc
     LEDCOM2_1();
     
     Delay_1ms;
     
     if(  LEDCOM1_IS_0() )
     	{
     		keybuf  |=  0x10;
     	}
     
     if(  LEDCOM2_IS_0() )
     	{
     		keybuf  |=  0x20;
     	}     
     return   keybuf	;
     
}



