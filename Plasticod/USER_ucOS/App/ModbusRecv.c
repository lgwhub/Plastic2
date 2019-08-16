

#include "includes.h"

//#define Max_ModbusBuf_Len  254
//#define DEFAULT_MODBUS_TIME  10;

/*
struct _modbus_struct
{

unsigned short int  MaxNothingMs5;   		//MODBUS没有数据收到设定值  此时处理包，并且必须CLR包

unsigned short int  NothingTimer;      //MODBUS没有数据收到定时器
unsigned short int	LenA;
unsigned short int	LenB;
unsigned short int	LenC;
unsigned char BufA[Max_ModbusBuf_Len+8+2];
unsigned char BufB[Max_ModbusBuf_Len+8+2];
unsigned char BufC[Max_ModbusBuf_Len+8+2];
unsigned char Select;	
unsigned char OverA;
unsigned char OverB;
unsigned char OverC;
};
*/
struct _modbus_struct  Modbusx;

// 使用的外部函数 void ModbusRecvProcess(unsigned char *p,unsigned short int len);
//接收到MODBUS包处理，判断地址，校验包，应答
//输入：  p整个modbus包指针，len整个modbus包长度


/////////////////////////////////////////////
// modbus数据接收函数
// 此函数在串口中断内调用，
// recv_char 是接收到的字符
void ModbusRxISRHandler(unsigned char recv_char)
{
 Modbusx.NothingTimer=0;
			
			LedEventTime1 = 1;
			
 switch (Modbusx.Select)
 	 {		
		case 'C':	
			if( Modbusx.OverC == 0)
	  		{
			  if( Modbusx.LenC < Max_ModbusBuf_Len )
				    {
				    	Modbusx.BufC[Modbusx.LenC]=recv_char;
				    	Modbusx.LenC ++ ;
				    }
				}
		break;
		
	  case 'B':
 	 	  if( Modbusx.OverB == 0)
	  		  {
			     if( Modbusx.LenB < Max_ModbusBuf_Len )
				      {
				    	Modbusx.BufB[Modbusx.LenB]=recv_char;
				    	Modbusx.LenB ++ ;
				      }
				  }
		break;		 
		
		case 'A':	
	  default:
	  	if( Modbusx.OverA == 0)
	  		{
			    if( Modbusx.LenA < Max_ModbusBuf_Len )
				      {
				    	Modbusx.BufA[Modbusx.LenA]=recv_char;
				    	Modbusx.LenA ++ ;
				      }
				 }
		break;		   
	 }			
			
						
}
////////////////////////////////////////////////////////////////////
//  modbus包结束时间判断函数
//  在定时器中断里面调用
//  可以切换缓冲区，加缓冲区满标记
void ModbusTimeHandler(void)
{
	
	 if(  Modbusx.NothingTimer > Modbusx.MaxNothingMs5 )     //MODBUS没有数据收到定时器
		     {//没有接收到任何数据时间超时处理
  		   switch(Modbusx.Select)
	   			     {
					     case 'A':
					     if(Modbusx.LenA	> 0 )
					     	     {
					           Modbusx.Select = 'B';
			 		           Modbusx.OverA = 1;
								     //ModbusRecvProcess(Modbusx.Buf,Modbusx.len); 
							       }
				       break;
  		         
  		         case 'B':
	   			     if(Modbusx.LenB	> 0 )   
	   			     			{
	   			     				Modbusx.Select = 'C';	
			 		            Modbusx.OverB = 1;
			 		          }
			 		     
				       break;
  		          
  		         case 'C':
	   			     if(Modbusx.LenC	> 0 )
	   			     	    {
	   			           Modbusx.Select = 'A';	
			 		           Modbusx.OverC = 1;
			 		          }
			 		     break;	
			 		     
			 		     default:
			 		     	  Modbusx.Select = 'A';
			 		     break;
			 		    }				       			       
				  Modbusx.NothingTimer = 0;   
		     }
	else{
		 	
		 	  Modbusx.NothingTimer ++;
		   }
}
/////////////////////////////////////////////

//不断地检查MODBUS接收缓冲区
//在主程序里面调用
void GetModbusPark(void)
{
if(Modbusx.OverA !=0 )
	  {//缓冲区A满
	  	if(Modbusx.LenA>0)
	  		{
			  ModbusRecvProcess(Modbusx.BufA,Modbusx.LenA);
		    }
		 Modbusx.LenA=0;
		 Modbusx.OverA	=0;
		}			
if(Modbusx.OverB !=0 )
	  {//缓冲区B满
	  	if(Modbusx.LenB>0)
	  		 {
			   ModbusRecvProcess(Modbusx.BufB,Modbusx.LenB);
		     }
		 Modbusx.LenB=0;
		 Modbusx.OverB	=0;		     
		}						
if(Modbusx.OverC !=0 )
	  {//缓冲区C满
	  	if(Modbusx.LenC>0)
	  		{
			   ModbusRecvProcess(Modbusx.BufC,Modbusx.LenC);
		    }
		 Modbusx.LenC=0;
		 Modbusx.OverC	=0;	
		 }	
}

////////////////////////////////////
void ModbusInit(void)
{

	Modbusx.LenA=0;
	Modbusx.LenB=0;	
	Modbusx.LenC=0;	
	
	Modbusx.Select='A';
	
	Modbusx.OverA=0;
	Modbusx.OverB=0;	
	Modbusx.OverC=0;
	
 Modbusx.MaxNothingMs5=DEFAULT_MODBUS_TIME ;   		//MODBUS没有数据收到设定值  此时处理包     //根据波特率调整时间
 Modbusx.NothingTimer=0;      //MODBUS没有数据收到定时器	
}






