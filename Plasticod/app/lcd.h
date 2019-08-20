#ifndef   _LCD_H
#define   _LCD_H
//#include "lcd1.h"




//SEG1 SEG2 SEG3   显示999  对应  Ht1621DigtTab1
void LcdDigetDecode123( unsigned short val  ,  unsigned char *buf );   //lcd Datbuf 5
//SEG4 SEG5   显示99  对应  Ht1621DigtTab2
void LcdDigetDecode45( unsigned char val  ,  unsigned char *buf );    //lcd Datbuf 0


//SEG1 SEG2 SEG3   显示非数字  对应  Ht1621FlagTab1
void LcdFlagDecode123( unsigned char *s ,  unsigned char *buf );    //lcd Datbuf 5
//SEG4 SEG5   显示非数字  对应  Ht1621FlagTab2
void LcdFlagDecode45(unsigned char *s   ,  unsigned char *buf);    //lcd Datbuf 0


void LCD_Display	( unsigned char flashing   )  ;


typedef struct
{
unsigned short int   val1;            //临时，最大999
unsigned short int   val2;            //临时，最大99	
unsigned short int 	 RpmOut;              //速度控制值
unsigned char 	     RpmBackSet;          //倒退速度设定值

unsigned short int 	 TempratureSet;   //温度设定值        p1
unsigned char 	     RpmSet;          //调速设定值        p4

unsigned char 	     MathedSet	;      //加热选择        p11
                     
unsigned char 	     TopCir;          //上圈        p6   
unsigned char 	     BottomCir;       //下圈        p9
unsigned char 	     MidLine;         //中线        p8
unsigned char 	     SelectTop;       //上勾选      p7
unsigned char 	     SelectBottnm;    //下勾选      p10
                     
unsigned char 	     Heating;                      //p12
unsigned char 	     HeatB;                        //p13	
                     
unsigned char 	     MovingF;                       //p14
unsigned char 	     MovingB;                         //p15
                     
unsigned char 	     StopF;                         //p16
                     
                     
unsigned char 	     Dot11;            //数值1的小数点1
unsigned char 	     Dot12;            //数值1的小数点2	
unsigned char 	     Dot2;             //数值2的小数点


unsigned char 	     flashing ;        //lcd闪烁

} _struct_lcd_buf_val ;

extern _struct_lcd_buf_val   LcdPort;












//根据flag,把 Dchar 的某一位置1或者清零
void CopyBit (unsigned char flag , unsigned char *DChar , unsigned char BitN );

#define  xxBIT0   0x01
#define  xxBIT1   0x02
#define  xxBIT2   0x04
#define  xxBIT3   0x08


//显示或者灭 4bit LCD 缓冲区的图标   //com1 高位    com4 低位

//温度设定模式        p1
#define  LcdFlag_TempratureSetMod(x)          CopyBit( x , Ht1621buf + 5 ,  xxBIT0 )
 //加热选择模式        p11                                                  xx
#define  LcdFlag_MathedSetMod(x)              CopyBit( x , Ht1621buf + 4 ,  xxBIT2 )
 //调速设定模式        p4                                                   xx
#define  LcdFlag_RpmSetMod(x)                 CopyBit( x , Ht1621buf + 3 ,  xxBIT3 )
//上圈        p6                                                            xx
#define  LcdFlag_TopCir(x)                    CopyBit( x , Ht1621buf + 11 , xxBIT0 )
//下圈        p9                                                            xx
#define  LcdFlag_BottomCir(x)                 CopyBit( x , Ht1621buf + 11 , xxBIT1 )
  //中线        p8                                                          xx
#define  LcdFlag_MidLine(x)                   CopyBit( x , Ht1621buf + 4 ,  xxBIT3 )
//上勾选      p7                                                            xx
#define  LcdFlag_SelectTop(x)                 CopyBit( x , Ht1621buf + 11 , xxBIT3 )
//下勾选      p10                                                           xx
#define  LcdFlag_SelectBottnm(x)              CopyBit( x , Ht1621buf + 11 , xxBIT2 )      
//p12                                                                       xx
#define  LcdFlag_Heating(x)                   CopyBit( x , Ht1621buf + 4 ,  xxBIT1 )        
//p13                                                                       xx
#define  LcdFlag_HeatB(x)                     CopyBit( x , Ht1621buf + 4 ,  xxBIT0 )
//p14                                                                       xx
#define  LcdFlag_Moving(x)                    CopyBit( x , Ht1621buf + 12 , xxBIT2 )
//p15                                                                       xx
#define  LcdFlag_MovingB(x)                      CopyBit( x , Ht1621buf + 12 , xxBIT1 ) 
//p16                                                                       xx
#define  LcdFlag_StopF(x)                      CopyBit( x , Ht1621buf + 12 , xxBIT0 )
//p2 数值1的小数点1                                                         xx
#define  LcdFlag_Dot11(x)                     CopyBit( x , Ht1621buf + 7 ,  xxBIT0 )
//p3 数值1的小数点2                                                         xx
#define  LcdFlag_Dot12(x)                     CopyBit( x , Ht1621buf + 9 ,  xxBIT0 )
//p5 数值2的小数点                                                          xx
#define  LcdFlag_Dot2(x)                      CopyBit( x , Ht1621buf + 1 ,  xxBIT3 )
                     
                     
      


#endif
