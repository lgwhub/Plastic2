//jump.h

#ifndef _JUMP3_APP_ADR_H
#define _JUMP3_APP_ADR_H



//#define    CMND_RESET_21      21
#define    CMND_ISP_22        22



void IspMarkLoad(void);
void IspMarkWrite(uint16_t ix);	
void SoftReset(void);  
  
////////////////////////////////////////
void JumpAppAdr(unsigned long int adr);

//void MakeIspReset(unsigned char commandxx);//收到参数时执行一下

#endif



