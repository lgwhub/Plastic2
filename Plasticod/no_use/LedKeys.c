
#include <includes.h>

#include "stm32f10x.h"
#include "stdio.h"
#include "config.h"
#include "HD_PLASTIC1.h" 
#include  "LedKeys.h"

 
 
 
void LedKeyPortSet(unsigned char IsOutType)
{
 
 GPIO_InitTypeDef GPIO_InitStructure;
  

	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

if( IsOutType != 0 )
	{

 //部分输出口
 GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_Out_PP;  //GPIO_Mode_IN_FLOATING;//	GPIO_Mode_Out_OD;
 
 GPIO_InitStructure.GPIO_Pin = PIN_LEDCOM1;
 GPIO_Init(PORT_LEDCOM1,&GPIO_InitStructure);
 
 GPIO_InitStructure.GPIO_Pin = PIN_LEDCOM2;
 GPIO_Init(PORT_LEDCOM2,&GPIO_InitStructure); 
 
 GPIO_InitStructure.GPIO_Pin = PIN_KIO1;
 GPIO_Init(PORT_KIO1,&GPIO_InitStructure); 
 
 GPIO_InitStructure.GPIO_Pin = PIN_KIO2;
 GPIO_Init(PORT_KIO2,&GPIO_InitStructure); 
 
 GPIO_InitStructure.GPIO_Pin = PIN_KIO3;
 GPIO_Init(PORT_KIO3,&GPIO_InitStructure); 
  
  }
 else{
  //部分改为输入口
 
   GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_IPU;  //GPIO_Mode_IPD;  // 

//   GPIO_InitStructure.GPIO_Pin = PIN_KIO1;
//   GPIO_Init(PORT_KIO1,&GPIO_InitStructure); 
// 
//   GPIO_InitStructure.GPIO_Pin = PIN_KIO2;
//   GPIO_Init(PORT_KIO2,&GPIO_InitStructure); 
// 
//   GPIO_InitStructure.GPIO_Pin = PIN_KIO3;
//   GPIO_Init(PORT_KIO3,&GPIO_InitStructure); 
 
   GPIO_InitStructure.GPIO_Pin = PIN_LEDCOM1;
   GPIO_Init(PORT_LEDCOM1,&GPIO_InitStructure);
 
   GPIO_InitStructure.GPIO_Pin = PIN_LEDCOM2;
   GPIO_Init(PORT_LEDCOM2,&GPIO_InitStructure); 
 }
}




