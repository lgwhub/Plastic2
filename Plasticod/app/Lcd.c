//

#include "lcd.h"
#include "app1.h"
#include "HT1621.h"
/*
typedef struct
{
unsigned short int 	TempratureSetMod;   //温度        p1
unsigned char 	RpmSetMod;          //调速        p4
unsigned char 	MathedSet	;      //加热模式    p11

unsigned char 	TopCir;          //上圈        p6   
unsigned char 	BottomCir;       //下圈        p9
unsigned char 	MidLine;         //中线        p8
unsigned char 	SelectTop;       //上勾选      p7
unsigned char 	SelectBottnm;    //下勾选      p10

unsigned char 	Heating;                      //p12
unsigned char 	HeatB;                        //p13	

unsigned char 	Moving;                       //p14
unsigned char 	MovB;                         //p15

unsigned char 	Stop;                         //p16


unsigned char 	Dot11;
unsigned char 	Dot12;	
unsigned char 	Dot2;

} _struct_lcd_buf_val ;
*/


_struct_lcd_buf_val   LcdPort;






//com1 高位    com4 低位
//seg7 difine  2   for p4 p5                                                              
#define seg_4a   0x010                                                  
#define seg_4b   0x020                                                  
#define seg_4c   0x040                                                  
#define seg_4d   0x080                                                  
                                                                        
#define seg_4f   0x01                                                   
#define seg_4g   0x02                                                   
#define seg_4e   0x04                                                   
                                                                        
//seg7 difine  1   for p1 p2 p3                                         
#define seg_1a   0x08                                                   
#define seg_1b   0x04                                                   
#define seg_1c   0x02                                                   
#define seg_1d   0x01                                                   
                                                                        
#define seg_1f   0x080                                                  
#define seg_1g   0x040                                                  
#define seg_1e   0x020                                                  
                                                                        
                                                                        
unsigned char Ht1621DigtTab1[]=                                         
{// SEG1 SEG2 SEG3   显示999  对应  Ht1621DigtTab1                                        
	seg_1a + seg_1b + seg_1c + seg_1d + seg_1e  + seg_1f ,            //0          
	seg_1b + seg_1c ,                                                 //1                      
	seg_1a + seg_1b + seg_1d + seg_1e  + seg_1g ,                     //2	            
	seg_1a + seg_1b + seg_1c + seg_1d +  seg_1g ,                     //3             
	seg_1b + seg_1c + seg_1f + seg_1g  ,                              //4                
	seg_1a + seg_1c + seg_1d + seg_1f + seg_1g ,                      //5             
	seg_1a + seg_1c + seg_1d + seg_1e + seg_1f + seg_1g ,             //6           
	seg_1a + seg_1b + seg_1c ,                                        //7	                  
	seg_1a + seg_1b + seg_1c + seg_1d + seg_1e + seg_1f + seg_1g ,    //8	
	seg_1a + seg_1b + seg_1c + seg_1d + seg_1f + seg_1g               //9		        
	                                                                      
}    ;                                                                   
                                                                        
unsigned char Ht1621DigtTab2[]=                                         
{ //SEG4 SEG5   显示99  对应  Ht1621DigtTab2                                                                      
	seg_4a + seg_4b + seg_4c + seg_4d + seg_4e  + seg_4f ,           //0          
	seg_4b + seg_4c ,                                                //1                      
	seg_4a + seg_4b + seg_4d + seg_4e  + seg_4g ,                    //2	            
	seg_4a + seg_4b + seg_4c + seg_4d +  seg_4g ,                    //3             
	seg_4b + seg_4c + seg_4f + seg_4g  ,                             //4                
	seg_4a + seg_4c + seg_4d + seg_4f + seg_4g ,                     //5             
	seg_4a + seg_4c + seg_4d + seg_4e + seg_4f + seg_4g ,            //6           
	seg_4a + seg_4b + seg_4c ,                                       //7	                  
	seg_4a + seg_4b + seg_4c + seg_4d + seg_4e + seg_4f + seg_4g ,   //8	
	seg_4a + seg_4b + seg_4c + seg_4d + seg_4f + seg_4g              //9		        
	                                                                      
};



unsigned char Ht1621FlagTab1[]=                                         
{// SEG1 SEG2 SEG3   显示非数字  对应  Ht1621FlagTab1  
	seg_1a + seg_1b + seg_1c + seg_1e  + seg_1f + seg_1g ,  //A                                        
	seg_1c + seg_1d + seg_1e  + seg_1f  + seg_1g ,          //b                      
	seg_1a + seg_1d + seg_1e  + seg_1f  ,                   //C	            
	seg_1b + seg_1c + seg_1d + seg_1e   + seg_1g  ,         //d             
  seg_1a + seg_1d + seg_1e  + seg_1f  + seg_1g  ,         //E 
  seg_1a + seg_1e  + seg_1f  + seg_1g,                    //F                 
	seg_1a ,                                                // -a   上横         g 
	seg_1b ,                                                // -g	  中横         h       
	seg_1d ,                                                // -d   下横         i
	seg_1a + seg_1b + seg_1f  + seg_1g ,	                  //上口               j
  seg_1c + seg_1d + seg_1e  + seg_1g ,                    //下口               k
	seg_1a + seg_1b + seg_1f  ,	                            //上盖               l
  seg_1c + seg_1d + seg_1e  ,                             //下盖               m
	0                                                       //space		           n
	                                                                      
}    ;                                                                   
                                                                        
unsigned char Ht1621FlagTab2[]=                                         
{ //SEG4 SEG5   显示非数字  对应  Ht1621FlagTab2                                                                      
	seg_4a + seg_4b + seg_4c + seg_4e  + seg_4f + seg_4g ,  //A                                        
	seg_4c + seg_4d + seg_4e  + seg_4f  + seg_4g ,          //b                      
	seg_4a + seg_4d + seg_4e  + seg_4f  ,                   //C	            
	seg_4b + seg_4c + seg_4d + seg_4e   + seg_4g  ,         //d             
  seg_4a + seg_4d + seg_4e  + seg_4f  + seg_4g  ,         //E 
  seg_4a + seg_4e  + seg_4f  + seg_4g,                    //F                 
	seg_4a ,                                                // -a   上横        
	seg_4b ,                                                // -g	  中横                
	seg_4d ,                                                // -d   下横
	seg_4a + seg_4b + seg_4f  + seg_4g ,	                  //上口
  seg_4c + seg_4d + seg_4e  + seg_4g ,                    //下口
	seg_4a + seg_4b + seg_4f  ,	                            //上盖
  seg_4c + seg_4d + seg_4e  ,                             //下盖
	0                                                       //space	     
	                                                                      
};


/////////////////////////////////////////////////////////////////////

//SEG1 SEG2 SEG3   显示非数字  对应  Ht1621FlagTab1
void LcdFlagDecode123( unsigned char *s ,  unsigned char *buf )    //lcd Datbuf 5
{
		unsigned char temp;

	buf  +=  5;   //buf  =  & Ht1621buf[5];
	

  
  temp          = Ht1621FlagTab1[ *s - 'a' ];	  //百位
  
  * buf      &= 0x1 ; //p1保持 ,不改变BIT1
   
  * buf      |= ( temp >> 4 )& 0xfe;

  * ( buf + 1 ) = temp & 0xf ;



  
  temp          = Ht1621FlagTab1[ *(s+1) - 'a' ];	//十位
  
  * ( buf + 2 )  &=  0x1 ; //p2保持,不改变BIT1
  * ( buf + 2 )  |= ( temp >> 4 )& 0xfe;
   	  
	* ( buf + 3 ) = temp & 0xf ;
	
	
	
	
  temp          = Ht1621FlagTab1[ *(s+2) - 'a' ];	//个位
  
  * ( buf + 4 )  &=  0x1 ; //p3保持,不改变BIT1
  * ( buf + 4 )  |= ( temp >> 4 )& 0xfe;
  
	* ( buf + 5 ) = temp & 0xf ;	
	
}



//SEG4 SEG5   显示非数字  对应  Ht1621FlagTab2
void LcdFlagDecode45(unsigned char *s   ,  unsigned char *buf)    //lcd Datbuf 0
{
	unsigned char temp;
	
	
	//buf  =  & Ht1621buf[0];

  
  temp          = Ht1621FlagTab2[ *s - 'a' ];    //十位
  * ( buf + 2 ) = temp >> 4 ;
  
  * ( buf + 3 ) &= 0x08;   //p4保持
  * ( buf + 3 ) |= ( temp  )& 0x07;

  
  
  temp          = Ht1621FlagTab2[ *(s+1) - 'a' ];	      //个位

	  * buf         = temp >> 4 ;
	  
  * ( buf + 1 ) &= 0x08;   //p5保持
  * ( buf + 1 ) |= ( temp  )& 0x07;
}  



//SEG1 SEG2 SEG3   显示999  对应  Ht1621DigtTab1
void LcdDigetDecode123( unsigned short val ,  unsigned char *buf )    //lcd Datbuf 5
{
	unsigned char temp;

	buf  +=  5;   //buf  =  & Ht1621buf[5];
	
	if ( val > 999 ) val = 999 ;
  
  temp          = Ht1621DigtTab1[ val / 100 % 10 ];	  //百位
  
  * buf      &= 0x1 ; //p1保持 ,不改变BIT1
   
  * buf      |= ( temp >> 4 )& 0xfe;

  * ( buf + 1 ) = temp & 0xf ;

  
  temp          = Ht1621DigtTab1[ val / 10 % 10 ];	//十位
  
  * ( buf + 2 )  &=  0x1 ; //p2保持,不改变BIT1
  * ( buf + 2 )  |= ( temp >> 4 )& 0xfe;
   	  
	* ( buf + 3 ) = temp & 0xf ;
	
	
	
	
  temp          = Ht1621DigtTab1[ val  % 10 ];	//个位
  
  * ( buf + 4 )  &=  0x1 ; //p3保持,不改变BIT1
  * ( buf + 4 )  |= ( temp >> 4 )& 0xfe;
  
	* ( buf + 5 ) = temp & 0xf ;	
	
}           

//SEG4 SEG5   显示99  对应  Ht1621DigtTab2
void LcdDigetDecode45(unsigned char val  ,  unsigned char *buf)    //lcd Datbuf 0
{
	unsigned char temp;
	
	
	//buf  =  & Ht1621buf[0];
	
	if ( val > 99 ) val = 99 ;
  
  temp          = Ht1621DigtTab2[ val / 10 % 10 ];    //十位
  * ( buf + 2 ) = temp >> 4 ;
  
  * ( buf + 3 ) &= 0x08;   //p4保持
  * ( buf + 3 ) |= ( temp  )& 0x07;

  
  
  temp          = Ht1621DigtTab2[ val  % 10 ];	      //个位

	  * buf         = temp >> 4 ;
	  
  * ( buf + 1 ) &= 0x08;   //p5保持
  * ( buf + 1 ) |= ( temp  )& 0x07;
}  



//void LcdUpdata( unsigned short val1 , unsigned short val2  ) 
//{
//	LcdDigetDecode45( val2  );
//	LcdDigetDecode123( val1  );
//	
//}




//根据flag,把 Dchar 的某一位置1或者清零
void CopyBit (unsigned char flag , unsigned char *DChar , unsigned char BitN )
{
	if ( flag != 0  )
		{ 
			*DChar |= BitN ; 
		}
	else{
		    *DChar &= ( ~BitN );
		  }
}



////////////////////////////////////////////

void LCD_Display	( unsigned char flashing  )  
{
   //if (  KeyScan.resoult != KeyScan.last  )//不是长按
 	        switch ( SetMods )
 	            {
 	            case ModNomal:  //平时模式
              LcdFlag_MathedSetMod(0);             //加热选择模式        p11
              LcdFlag_TempratureSetMod(0);         //温度设定模式        p1
              LcdFlag_RpmSetMod(0);                //调速设定模式        p4


             
             
           //SEG1 SEG2 SEG3   显示999  对应  Ht1621DigtTab1
           LcdDigetDecode123( AdcRes.temptemprature1 , Ht1621buf );   //lcd Datbuf 5
           //SEG4 SEG5   显示99  对应  Ht1621DigtTab2
           //LcdDigetDecode45( AdcRes.RpmCur /10 , Ht1621buf );    //lcd Datbuf 0       LcdPort.val2       
           LcdDigetDecode45( AdcRes.RpmDisplay  , Ht1621buf );    //lcd Datbuf 0       LcdPort.val2       
              
              
              
              
              
              break;
              case ModHeatMatheSet:  //加热方式选择
              LcdFlag_MathedSetMod(1);             //加热选择模式        p11
              LcdFlag_TempratureSetMod(0);         //温度设定模式        p1
              LcdFlag_RpmSetMod(0);                //调速设定模式        p4          	
//SEG1 SEG2 SEG3   显示非数字  对应  Ht1621FlagTab1
              //LcdFlagDecode123( unsigned char *s ,  unsigned char *buf );    //lcd Datbuf 5
//SEG4 SEG5   显示非数字  对应  Ht1621FlagTab2
//void LcdFlagDecode45(unsigned char *s   ,  unsigned char *buf);    //lcd Datbuf 0              	                        
              break;
              
              case ModTemprature:  //设置温度模式
              LcdFlag_MathedSetMod(0);             //加热选择模式        p11
              LcdFlag_TempratureSetMod(1);         //温度设定模式        p1
              LcdFlag_RpmSetMod(0);                //调速设定模式        p4

                //SEG1 SEG2 SEG3   显示999  对应  Ht1621DigtTab1
              if ( ( flashing & 0x01 ) == 0 )
             	    {//SEG1 SEG2 SEG3   显示非数字  对应  Ht1621FlagTab1
                    LcdFlagDecode123( "nnn"  , Ht1621buf );    //lcd Datbuf 5
                  }
             else{  //SEG1 SEG2 SEG3   显示999  对应  Ht1621DigtTab1
                  LcdDigetDecode123( LcdPort.TempratureSet , Ht1621buf );   //lcd Datbuf 5
                 }
            
            //SEG4 SEG5   显示非数字  对应  Ht1621FlagTab2
            LcdFlagDecode45("nn"   ,   Ht1621buf );    //lcd Datbuf 0     
                
              break;
              
              case ModRpm:  //设置速度
              LcdFlag_MathedSetMod(0);             //加热选择模式        p11
              LcdFlag_TempratureSetMod(0);         //温度设定模式        p1
              LcdFlag_RpmSetMod(1);                //调速设定模式        p4
              
              //SEG1 SEG2 SEG3   显示非数字  对应  Ht1621FlagTab1
              LcdFlagDecode123( "nnn" ,  Ht1621buf );    //lcd Datbuf 5
    
              if ( ( flashing & 0x01 ) == 0 )
             	    {//SEG4 SEG5   显示非数字  对应  Ht1621FlagTab2
                   LcdFlagDecode45("nn"   ,   Ht1621buf );    //lcd Datbuf 0 
                  }
             else{  
                 //SEG4 SEG5   显示99  对应  Ht1621DigtTab2
                 LcdDigetDecode45( LcdPort.RpmSet  , Ht1621buf );    //lcd Datbuf 0      
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
             
      if( LcdPort.StopF == 0 )
      	{//p16
          LcdFlag_StopF( 0 );
      	}
     else{//p16
          LcdFlag_StopF( 1 );
     	   }
     	   
	   	if( LcdPort.MovingF  == 0 )
	   		{//p14                                                                       xx
          LcdFlag_Moving( 0 );
	   		}
	   	else{//p14                                                                       xx
          LcdFlag_Moving( 1 );
	   	   }      
             
             
}


