
//#include "STM32_DeviceId.h"

#ifndef _STM32_DEVICE_ID_H
#define _DEVICE_ID_H
//STM32 CPUΨһ��ݱ�ʶ�Ĵ�����96λ��


//STM32��ID 16λ�����
#define CONFIG_CHECK_DEVICE_ID  0
//////////////////////////////////////////////////////														
												
struct	struct_stm32_id{
													
												unsigned char Checked;//		
												unsigned char Aeg;
												unsigned char KeyCount;//
											};
								
								
extern struct	struct_stm32_id		STM32DeviceId;						
										
										
												
				
						
														
//STM32 CPUΨһ��ݱ�ʶ�Ĵ��� ��CPU�еĵ�ַ														
//#define DEVICE_ID_ADR 	0x1FFFF7E8

unsigned short int GetStm32F103_DeviceId_Sum6(void);

void InitSTM32DeciceID(void);
#endif


