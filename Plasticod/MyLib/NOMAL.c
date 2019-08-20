
//#include <includes.h>
#include  "nomal.h"


/////////////////////////////////
/************************************************************************/
/*									*/
/*		       ASC_2码	转换通用子程序				 */
/*									*/
/*	    HexToAsc  半字节二进制转换为1位ASC_2码   子程序		 */
/************************************************************************/
uchar HexToAsc(uchar x)	  /*  1/2hex>>1asc2   */
{ x&=0x0f;
 if(x>9){x-=0x0a;x+='A';}else{x+='0';};
 return	x;
}

/************************************************************************/
/*	    AscToHex  1位ASC_2码转换为半字节二进制   子程序		 */
/*			  1ASC>>1/2HEX					*/
/************************************************************************/

uchar AscToHex(uchar x)	    
{
x&=0xFF;	
if(x>='a')
    {x-=87;//{x-='a';x+=0x0a;}
    }
else if(x>'9')
    {x-=55;//{x-='A';x+=0x0a;
    }
else{x-='0';
    };
x&=0x0f;
return x;
}
//////////////////////////////////////////////



/************************************************************************/
 /* 在数组内加字符串或数组直到0X00 */
uchar PutString(uchar *ps,uchar	*pd,uchar max_ps) 
{uchar len=0; /* 结果长度 */
 uchar temp;
while(len<max_ps)
    {temp=*(ps+len);  /* 原 */
     *(pd+len)=temp;  /* 目的 */
     if(temp==0x00)break;
     else{len++;
	 };
    };
*(pd+len)=0X0;
return len;   /* 指向pd的0X00位	 */
}

/************************************************************************/
void PutCharToChar(uchar *ps,uchar *pd,uchar len) 
{uchar i,temp; /* 长度 */
for(i=0;i<len;i++)
    {
     //*(pd+i)=*(ps+i);

temp=*(ps+i);
*(pd+i)=temp;
    };
}



/************************************************************************/

/************************** 字符串和字符串比较	********************************/
bool CompareCharChar(uchar *chr1,uchar *chr2,uchar len)
{
 uchar i;
 for(i=0;i<len;i++)
    {
    if(*(chr1+i)!=*(chr2+i))
	  {return FALSE;
	  };
    };
return TRUE;
}


/************************** 字符串和字符串比较	********************************/
bool CompareStrStr(uchar *chr,uchar *str,uchar max)
{
 uchar i;
 for(i=0;i<max;i++)
    {if(*(str+i)==0x00)return TRUE;
     else if(*(chr+i)!=*(str+i))
	  {return FALSE;
	  };
    };
return TRUE;
}




/********************************************************************************/
bool IsNumberAsc(uchar x)   /* 判断是否为数字0~9 */
{if(x>'9')
     {return FALSE;
     }
 else if(x<'0')
     {return FALSE;
     }
 else{return TRUE;
     };
}

/***********************************************************************/
bool IsHexAsc(uchar x)	 /* 判断十六进制 是否为数字0~9 或 A~F */
{
if(IsNumberAsc(x)||((x>='A')&&(x<='F')))
  return TRUE;
else return FALSE;
}

/***********************************************************************/
bool IsStringAsc(uchar x)   /* 判断是否为英文字母A~Z 或	a~z*/
{if((x>='A')&&(x<='Z'))
     {return TRUE;
     }
 else if((x>='a')&&(x<='z'))
     {return TRUE;
     }
 else{return FALSE;
     };
}



uchar MakeValAsc16(uchar *StrHead,uint16 Val,uchar *StrEnd,uchar *out)	//16位变量转换为十进制的ASC码，有前后缀
{
 /* 在数组内加字符串或数组直到0X00 */
//uchar PutString(uchar *ps,uchar *pd,uchar max_ps) 
uchar i;

i=PutString(StrHead,out,20);
out[i]=HexToAsc(Val/10000%10);i++;
out[i]=HexToAsc(Val/1000%10);i++;
out[i]=HexToAsc(Val/100%10);i++;
out[i]=HexToAsc(Val/10%10);i++;
out[i]=HexToAsc(Val%10);i++;
i+=PutString(StrEnd,&out[i],20);
return i;
}


///////////////////////////////
uchar MakeValAsc32(uchar *StrHead,uint32 Val,uchar *StrEnd,uchar *out)	//32位变量转换为十进制的ASC码，有前后缀
{
uchar i;

i=PutString(StrHead,out,20);

out[i]=HexToAsc(Val/1000000000%10);i++;

out[i]=HexToAsc(Val/100000000%10);i++;
out[i]=HexToAsc(Val/10000000%10);i++;
out[i]=HexToAsc(Val/1000000%10);i++;

out[i]=HexToAsc(Val/100000%10);i++;
out[i]=HexToAsc(Val/10000%10);i++;
out[i]=HexToAsc(Val/1000%10);i++;

out[i]=HexToAsc(Val/100%10);i++;
out[i]=HexToAsc(Val/10%10);i++;
out[i]=HexToAsc(Val%10);i++;
i+=PutString(StrEnd,&out[i],20);
return i;

}
///////////////////////////////
void HexCharToAscString(uchar *c,uchar *AscBuf,uchar HexLen)	//注意1字节变2字节
{
 uchar i;
 for(i=0;i<HexLen;i++)
        {
         AscBuf[2*i]=(char)HexToAsc(*(c+i)/0X10);
         AscBuf[2*i+1]=(char)HexToAsc(*(c+i)%0X10);
        }
AscBuf[2*i]=0;

}

///////////////////////////////
//CRC软件法?
#define Flag_GetCRC_SoftMethod	FALSE


#if Flag_GetCRC_SoftMethod
/***********************************************************************
Function :        public GetCRC_Checksum2
         软件法，速度较GetCRC_Checksum1慢，但代码小
Parameters :      cp:               A pinter to the PPP Packet
                  len:              Size of PPP Packet

Date :            September 2000

Desc :            Returns the Checksum of the PPP Packet pointed by cp
***********************************************************************/
//uint16 GetCRC_Checksum2(uchar *cp, uint16 len)
uint16 GetCRC_Checksum1(uchar *cp, uint32 len)
{
uint16 fcs=0xffff;
uint16 temp;
uchar i;
while (len--)
     {temp=*cp^fcs;
      temp&=0xff;
      for(i=0;i<8;i++)
          {if(temp&1)
              {temp>>=1;
               temp^=0x8408;
              }
           else temp>>=1;
          };
      cp++;
      fcs=temp^ (fcs >> 8);
      }
return ~fcs;
}

#else
/***********************************************************************
Function :        public GetCRC_Checksum1
         查表法，速度较GetCRC_Checksum2快，但代码大
Parameters :      cp:               A pinter to the PPP Packet
                  len:              Size of PPP Packet

Date :            September 2000

Desc :            Returns the Checksum of the PPP Packet pointed by cp
***********************************************************************/
const uint16   fcstab[256] = {
        0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
        0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
        0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
        0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
        0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
        0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
        0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
        0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
        0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
        0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
        0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
        0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
        0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
        0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
        0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
        0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
        0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
        0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
        0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
        0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
        0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
        0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
        0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
        0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
        0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
        0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
        0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
        0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
        0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
        0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
        0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
        0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};


//uint16 GetCRC_Checksum1(uchar *cp, uint16 len)
uint16 GetCRC_Checksum1(uchar *cp, uint32 len)
{
uint16 fcs=0xffff;
while (len--)
   {fcs = (fcs >> 8)^fcstab[(fcs^*cp++)&0xff];
   }
 return ~fcs;
}
#endif





