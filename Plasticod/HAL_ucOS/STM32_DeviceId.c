
#include "includes.h"



//STM32 CPUΨһ��ݱ�ʶ�Ĵ��� ��CPU�еĵ�ַ														
#define DEVICE_ID_ADR 	0x1FFFF7E8

/////////////////////////////////////////////////////////
struct	struct_stm32_id		STM32DeviceId;

unsigned short int GetStm32F103_DeviceId_Sum6(void)
{
//��ƷΨһ��ݱ�ʶ�Ĵ�����96λ��
//����ַ0X1FFF F7E8

unsigned short int temp16;
unsigned short int  *p;
unsigned char i;
///////////////��ǰSTM32 ��ID//////////////////////////////////
p=(unsigned short int *)DEVICE_ID_ADR;

/////////////////////////////////////////////
//��ǰ���STM32��ID�� ��У����
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
		




