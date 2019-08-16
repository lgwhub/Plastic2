#ifndef   _LCD_H
#define   _LCD_H
//#include "lcd1.h"




//SEG1 SEG2 SEG3   ��ʾ999  ��Ӧ  Ht1621DigtTab1
void LcdDigetDecode123( unsigned short val  ,  unsigned char *buf );   //lcd Datbuf 5
//SEG4 SEG5   ��ʾ99  ��Ӧ  Ht1621DigtTab2
void LcdDigetDecode45( unsigned char val  ,  unsigned char *buf );    //lcd Datbuf 0


//SEG1 SEG2 SEG3   ��ʾ������  ��Ӧ  Ht1621FlagTab1
void LcdFlagDecode123( unsigned char *s ,  unsigned char *buf );    //lcd Datbuf 5
//SEG4 SEG5   ��ʾ������  ��Ӧ  Ht1621FlagTab2
void LcdFlagDecode45(unsigned char *s   ,  unsigned char *buf);    //lcd Datbuf 0


void LCD_Display	( unsigned char flashing   )  ;


typedef struct
{
unsigned short int   val1;            //��ʱ�����999
unsigned short int   val2;            //��ʱ�����99	
unsigned short int 	 RpmOut;              //�ٶȿ���ֵ
unsigned char 	     RpmBackSet;          //�����ٶ��趨ֵ

unsigned short int 	 TempratureSet;   //�¶��趨ֵ        p1
unsigned char 	     RpmSet;          //�����趨ֵ        p4

unsigned char 	     MathedSet	;      //����ѡ��        p11
                     
unsigned char 	     TopCir;          //��Ȧ        p6   
unsigned char 	     BottomCir;       //��Ȧ        p9
unsigned char 	     MidLine;         //����        p8
unsigned char 	     SelectTop;       //�Ϲ�ѡ      p7
unsigned char 	     SelectBottnm;    //�¹�ѡ      p10
                     
unsigned char 	     Heating;                      //p12
unsigned char 	     HeatB;                        //p13	
                     
unsigned char 	     MovingF;                       //p14
unsigned char 	     MovingB;                         //p15
                     
unsigned char 	     StopF;                         //p16
                     
                     
unsigned char 	     Dot11;            //��ֵ1��С����1
unsigned char 	     Dot12;            //��ֵ1��С����2	
unsigned char 	     Dot2;             //��ֵ2��С����


unsigned char 	     flashing ;        //lcd��˸

} _struct_lcd_buf_val ;

extern _struct_lcd_buf_val   LcdPort;












//����flag,�� Dchar ��ĳһλ��1��������
void CopyBit (unsigned char flag , unsigned char *DChar , unsigned char BitN );

#define  xxBIT0   0x01
#define  xxBIT1   0x02
#define  xxBIT2   0x04
#define  xxBIT3   0x08


//��ʾ������ 4bit LCD ��������ͼ��   //com1 ��λ    com4 ��λ

//�¶��趨ģʽ        p1
#define  LcdFlag_TempratureSetMod(x)          CopyBit( x , Ht1621buf + 5 ,  xxBIT0 )
 //����ѡ��ģʽ        p11                                                  xx
#define  LcdFlag_MathedSetMod(x)              CopyBit( x , Ht1621buf + 4 ,  xxBIT2 )
 //�����趨ģʽ        p4                                                   xx
#define  LcdFlag_RpmSetMod(x)                 CopyBit( x , Ht1621buf + 3 ,  xxBIT3 )
//��Ȧ        p6                                                            xx
#define  LcdFlag_TopCir(x)                    CopyBit( x , Ht1621buf + 11 , xxBIT0 )
//��Ȧ        p9                                                            xx
#define  LcdFlag_BottomCir(x)                 CopyBit( x , Ht1621buf + 11 , xxBIT1 )
  //����        p8                                                          xx
#define  LcdFlag_MidLine(x)                   CopyBit( x , Ht1621buf + 4 ,  xxBIT3 )
//�Ϲ�ѡ      p7                                                            xx
#define  LcdFlag_SelectTop(x)                 CopyBit( x , Ht1621buf + 11 , xxBIT3 )
//�¹�ѡ      p10                                                           xx
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
//p2 ��ֵ1��С����1                                                         xx
#define  LcdFlag_Dot11(x)                     CopyBit( x , Ht1621buf + 7 ,  xxBIT0 )
//p3 ��ֵ1��С����2                                                         xx
#define  LcdFlag_Dot12(x)                     CopyBit( x , Ht1621buf + 9 ,  xxBIT0 )
//p5 ��ֵ2��С����                                                          xx
#define  LcdFlag_Dot2(x)                      CopyBit( x , Ht1621buf + 1 ,  xxBIT3 )
                     
                     
      


#endif
