
#include "includes.h"


//调整高位在前



unsigned char ResponeBuf[Max_ModbusBuf_Len+1];  //modbus返回信息缓冲区


////////////////////////////////////////////////////////////////////////	
void _SendStringUartx( unsigned char *p, unsigned short int len) 
{
		uint16 i;
	for(i=0;i<len;i++)
	  {
	  Uart1CharSend(*(p+i));    // Uart1
	  }
}

///////////////////////////////
void _SendModbusPark(unsigned char *p , unsigned short int len)  //加校验码，发送
{
	unsigned short int checksum;
	
	checksum = GetCRC_Checksum4(p,len);
	
	
	#if MODBUS_CHECKSUM_HIGHBYTE_FORWORD
	*(p+len)=checksum>>8;		 //high byte 
	*(p+len+1)=	checksum&0xff;	//low byte
	#else
	*(p+len)=checksum&0xff;		 //low byte
	*(p+len+1)=	checksum>>8;	 //high byte
	#endif	
	
	
	len+=2;
	
	_SendStringUartx(p,len);
}

//////////////////////////////	            
void _MakeReadRegRespone(unsigned char *p,unsigned short int byteLen,unsigned char *respone)//读寄存器 回复
{
	unsigned char i;
	//adr;                     //地址  gMemory[Channl].adr;
	//MODBUS_READ_REGISTER;   //写寄存器 回复
	
	*respone  =  byteLen;                  //字节数
	
	respone++;
	
//////////////////
#if MODBUS_FLOAT_HIGHBYTE_FORWORD
	while (byteLen>=4)//实际数据字节 高位
	   {
	   	byteLen-=4;
	    *respone = *(p+3);//参数地址  (3-i)为了把参数高位放在前面
       respone++;
	    *respone = *(p+2);//参数地址  (3-i)为了把参数高位放在前面
       respone++;       
	    *respone = *(p+1);//参数地址  (3-i)为了把参数高位放在前面
       respone++;       
      *respone = *p;
       respone++;
	     p+=4;
	    }
 #elif MODBUS_HIGHBYTE_FORWORD_2X2
  	while (byteLen>=2)//实际数据字节 高位
	   {
	   	byteLen-=2;
	    *respone = *(p+1);//参数地址  (3-i)为了把参数高位放在前面
       respone++;
      *respone = *p;
       respone++;
	     p+=2;
	    }
 #else
 	while (byteLen>=2)//实际数据字节 高位
	   {
	      byteLen--;
	      *respone = *p;//参数地址  把参数低位放在前面
        respone++;
	      p++;
	    }
	#endif    
	
}
///////////////////////////////
void _MakeWriteRegRespone(unsigned short int RegAdr,unsigned short int RegNmb,unsigned char *p)//写寄存器 回复
{

	*p  =  RegAdr>>8;                //寄存器地址 高位
	p++;
	*p  =  RegAdr&0xff;              //寄存器地址 低位 
	p++;
	*p  =  RegNmb>>8;	                    //寄存器数量 高位
	p++;
	*p  =  RegNmb&0xff;	                  //寄存器数量 低位 
	
}

///////////



//////////////////////////////////////////////
//void _ModbusReadBitRespone()//读线圈 回复
//{
//	
//}
/////////////////////////////////
//void _ModbusWriteBitRespone()//写线圈 回复
//{
//	
//}


//
//输入：  Channl分机号，p整个modbus包指针，modbus包len不含校验码的长度,pr应答的内容
//void _ModbusReadBit(unsigned char Channl,unsigned char *p,unsigned short int len)//读线圈
//{
//
//	unsigned short int ParaAdrress;  //参数地址
//	unsigned short int ParaNumb;	   //参数字数  整型
//	
//	//*p;  //分机地址
//	
//	ParaAdrress=*(p+1)*0x100+*(p+2);
//  ParaNumb=*(p+3)*0x100+*(p+4);		
//  
//
//  
//}
///////////////////////

//
////输入：  Channl分机号，p整个modbus包指针，modbus包len不含校验码的长度,pr应答的内容
//void _ModbusWriteBit(unsigned char Channl,unsigned char *p,unsigned short int len)//写线圈
//{
//
//	unsigned short int ParaAdrress;  //参数地址
//	unsigned short int ParaNumb;	   //参数字数  整型
//	
//	// *p;  //分机地址
//	
//	ParaAdrress=*(p+1)*0x100+*(p+2);
//  ParaNumb=*(p+3)*0x100+*(p+4);		
//  
//  
//
//}
///////////////////////


//
//输入：  Channl分机号，p整个modbus包指针，modbus包len不含校验码的长度,pr应答的内容
void ModbusReadWord(unsigned char Channl, unsigned char *p, unsigned short int len, unsigned char *pr)//读寄存器
{
	
  unsigned short int ParaAdrress;  //参数地址  双字节
  unsigned short int byte_position_ref;     //字节地址偏移
	unsigned short int ParaNumb;	   //参数字数  整型
	unsigned char *ffp;
	// *p;  //分机地址
	
	ParaAdrress=*(p+2)*0x100+*(p+3);
  ParaNumb=*(p+4)*0x100+*(p+5);		//2n	 单位为字，  最小至少4字节

  byte_position_ref = 2*(ParaAdrress);

			if( ParaNumb > (MaxModbusWordNumb) ){return;};
			if( ParaNumb  ==  0 ){return;};
      if( (ParaNumb &0x0001) !=  0 ){ return; };  //单数
      
      //ParamBlockCopyToModbusBuf(byte_position_ref , ParaNumb*2);   // ModBusParaByte
      ffp = byte_position_ref + (unsigned char *)& gCommParam;  //数据地址开始值

		  *pr= *p;  //分机地址
			*(pr+1)= *(p+1); //功能

		  //_MakeReadRegRespone(ModBusParaByte,ParaNumb*2,pr+2);//读寄存器 回复
		  _MakeReadRegRespone(ffp,ParaNumb*2,pr+2);//读寄存器 回复
		  
		  _SendModbusPark(pr,2+1+ParaNumb*2);      
		  
}
//////////////////////





//////////////////////
void _PlaceModbusFloat( unsigned char *p,unsigned char *ffp,unsigned char numb)
{
	unsigned char i;
			//i=0;  //字节数
#if MODBUS_FLOAT_HIGHBYTE_FORWORD
	unsigned char 	j;
			for(i=0;(i*2)<numb;i++)
			    {
			    for(j=0;j<4;j++)  //一个float的4个字节
			       {

		            *(ffp+4*i+(3-j))=*(p+4*i+j);   // (3-j)浮点型数据小端模式，低位在前

			       
			       }
			    }	
 #elif MODBUS_HIGHBYTE_FORWORD_2X2
			
			for(i=0;i<numb;i++)
			    {

		            *(ffp+2*i)=*(p+2*i+1);   // (3-j)浮点型数据小端模式，低位在前

			            *(ffp+2*i+1)=*(p+2*i);
		
			       
			       
			    }	
	/////////////////	
	   #else    
			for(i=0;i<(2*numb);i++)
			    {
			            *(ffp+i)=*(p+i);
			    }	

	#endif	
}
//
//输入：  Channl分机号，p整个modbus包指针，modbus包len不含校验码的长度,pr应答的内容
void ModbusWriteWord(unsigned char Channl,unsigned char *p,unsigned short int len, unsigned char *pr)//写寄存器
{
	
  unsigned short int ParaAdrress;  //参数地址
  unsigned short int byte_position_ref;     //字节地址偏移
	unsigned short int ParaNumb;	   //参数字数  整型
	
	unsigned short int ByteNmb;      //字节数
	unsigned char i,j; 	
	unsigned char *ffp;
	
	// *p;  //分机地址
	ParaAdrress=*(p+2)*0x100+*(p+3);//参数地址
  ParaNumb=*(p+4)*0x100+*(p+5);	//	 单位为字，  最小至少4字节
  ByteNmb=*(p+6);              //字节数
	
	byte_position_ref = 2*(ParaAdrress);
	  
	if( ParaNumb > (MaxModbusWordNumb) ){ return; };
	if( ParaNumb  ==  0 ){ return; };
	if(2*ParaNumb!=ByteNmb){  return;	};  
	  
  if( (ParaNumb &0x0001) !=  0 ){ return; };  //单数


      ffp = byte_position_ref + (unsigned char *)& gCommParam;  //数据地址开始值
			_PlaceModbusFloat(p+7,ffp,ParaNumb);
      //ParamBlockCopyFromModbusBuf(byte_position_ref , 2*ParaNumb);//ModBusParaByte


		  *pr= *p;  //分机地址
			*(pr+1)= *(p+1); //功能

		  _MakeWriteRegRespone(ParaAdrress,ParaNumb,pr+2);//写寄存器 回复    
		  _SendModbusPark(pr,2+4);      

}

///////////////////////
//根据功能码分别处理数据
//输入：  Channl分机号，p整个modbus包指针，modbus包len不含校验码的长度
void _ModbusParameterProcess(unsigned char Channl,unsigned char *p,unsigned short int len)
{

	switch (*(p+1))                   //功能码
	   {
//		  case MODBUS_READ_BIT:			   //读线圈0x01
//		  
//		  _ModbusReadBit(Channl,p,len);
//		  
//		  break;
//		  
//		  case MODBUS_WRITE_BIT:       //写线圈0x05
//		  
//		  _ModbusWriteBit(Channl,p,len);
//		  
//		  break;	
		  	  
		  case MODBUS_READ_REGISTER:   //读寄存器0x03
		  
		  ModbusReadWord(Channl,p,len,ResponeBuf);
		  
		  break;	
		  
		  case MODBUS_WRITE_REGISTER:  //写寄存器0x10
		  
		  ModbusWriteWord(Channl,p,len,ResponeBuf);
		  
      ModbusCommand();  //收到参数时执行一下

		  TimeForSaveParam = 5;//秒
		  break;	
		  		  	
		  default:
		  			  	
		  break;		  	
	   }
	
	
}

////////////////////////////////////////////

//接收到MODBUS包处理，判断地址，校验包，应答
//输入：  p整个modbus包指针，len整个modbus包长度
void ModbusRecvProcess(unsigned char *p,unsigned short int len)
{
  unsigned char  Channl;
  unsigned short Checksum;
  

//      if( (gPublic.SubAdr_reserve & 0xfffc) != (*p & 0xfffc ) )  //忽略地址最后2位，分配给4个通道了
//	       {                                
//		      return;
//	       }
       if( (gCommParam.lSubAdr_reserve & 0x000000ff) != (*p & 0x000000ff ) )  //忽略地址最后2位，分配给4个通道了
	       {                                
		      return;
	       }
if(len<2)
	{
		_SendStringUartx(p,1);
		_SendStringUartx("\x80",1);
		
		return;  //包长度不够
   }
   
   Channl=*p & 0x0003;  //找到分机的通道号Channl
  
  Checksum=GetCRC_Checksum4(p,len-2);
  #if MODBUS_CHECKSUM_HIGHBYTE_FORWORD
  if( Checksum != (*(p+len-2)*0x100+ *(p+len-1)) ) return;  //校验错误   高位在前
  #else
  if( Checksum != (*(p+len-2)+ *(p+len-1)*0x100) ) return;  //校验错误   低位在前
  #endif
  	
  LedEventTime1 = 15;	
  _ModbusParameterProcess(Channl,p,len-2)	;  //长度忽略校验码

}


//////////////////////////////////////////////////////////////////////////////
/*高位字节表 Table of CRC values for high–order byte */

static unsigned char auchCRCHi[] = {
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40
};

/* 低位字节表Table of CRC values for low–order byte */

static char auchCRCLo[] = {
0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
0x40
};
/*
CRC生成
 例： 功能取2个自变量： unsigned char *puchMsg ; 	为生成CRC值，把指针指向含有二进制
	的数据的缓冲器 unsigned short usDataLen ;	缓冲器中的字节数。 该功能返回CRC作为一种类型“unsigned short”。
 CRC产生的功能
 */
 unsigned short GetCRC_Checksum4(unsigned char *puchMsg,unsigned short usDataLen)
{
unsigned char uchCRCHi = 0xFF ; /* 初始化高字节*/
unsigned char uchCRCLo = 0xFF ; /* 初始化低字节*/
unsigned uIndex ; /*把CRC表*/
while (usDataLen--) /*通过数据缓冲器*/
  {
   uIndex = uchCRCHi ^ *puchMsg++; /*计算CRC */
   uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex] ;
   uchCRCLo = auchCRCLo[uIndex] ;
  }
   return (uchCRCHi << 8 | uchCRCLo) ;
}




