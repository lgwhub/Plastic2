//

 //   #include "app1.h"

#include <includes.h>

#include "stm32f10x.h"
#include "stdio.h"
#include "config.h"
#include "HD_PLASTIC1.h"


////////////////////////////////////////////////////////////////////



//���������ת��Ϊ����ֵ
unsigned short int PowerToShiftTimr( unsigned short int val)
{

    #define Mod  1000
    
    #define min  100
    
    //���1000
    #define max  950
    
    unsigned short int  shift;            //�������ֵ
    
    if( val > Mod ) shift = Mod;
    	
    shift = Mod - val ;                   //  1000 -val
    
    if( shift < min ) shift = 0 ;         //�ʼ����λ����
    
    if( shift > max ) shift = max ;       //��������λ����
    
    return   shift ;                      //�������ֵ

}

                  
/////////////////////////////////////////////////////////////                  

#define   Delay_1ms    OSTimeDly(OS_TICKS_PER_SEC/1000)


unsigned char LedKeyProcess( unsigned char FlagLed  ) 
{
      unsigned char keybuf;
      
      keybuf = 0 ;
      
     //��һ��
     if( FlagLed & 0x01 )
     	{
     		LEDCOM1_0();
     	}
     if( FlagLed & 0x02 )
     	{
     		LEDCOM2_0();
     	}	

     
     KIO1_1();//��һ��
     
     Delay_1ms;   //��һ��
     Delay_1ms;
     Delay_1ms;
     
     
     //׼����
     KIO1_0();//��һ��
     
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
     

     
     //�ڶ���
     if( FlagLed & 0x04 )
     	{
     		LEDCOM1_0();
     	}
     if( FlagLed & 0x08 )
     	{
     		LEDCOM2_0();
     	}	

     
     KIO2_1();//��һ��
     
     Delay_1ms;   //��һ��
     Delay_1ms;
     Delay_1ms;
     
     
     //׼����
     KIO2_0();//��һ��
     
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

     //������
     if( FlagLed & 0x10 )
     	{
     		LEDCOM1_0();
     	}
     if( FlagLed & 0x20 )
     	{
     		LEDCOM2_0();
     	}	

     
     KIO3_1();//��һ��
     
     Delay_1ms;   //��һ��
     Delay_1ms;
     Delay_1ms;
     
     
     //׼����
     KIO3_0();//��һ��
     
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



