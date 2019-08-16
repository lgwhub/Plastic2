
#include "includes.h"



//STM32 CPU唯一身份标识寄存器 在CPU中的地址														
#define DEVICE_ID_ADR 	0x1FFFF7E8

/////////////////////////////////////////////////////////
struct	struct_stm32_id		STM32DeviceId;

unsigned short int GetStm32F103_DeviceId_Sum6(void)
{
//产品唯一身份标识寄存器（96位）
//基地址0X1FFF F7E8

unsigned short int temp16;
unsigned short int  *p;
unsigned char i;
///////////////当前STM32 的ID//////////////////////////////////
p=(unsigned short int *)DEVICE_ID_ADR;

/////////////////////////////////////////////
//求当前这块STM32的ID的 和校验码
temp16=0;
for(i=0;i<6;i++)
		{
			temp16+=*(p+i);
		}

return 	(temp16&0xffff);

}



void InitSTM32DeciceID(void)
{
	STM32DeviceId.Checked=0;//
	STM32DeviceId.Aeg=0;//
	STM32DeviceId.KeyCount=0;//
}						
		




