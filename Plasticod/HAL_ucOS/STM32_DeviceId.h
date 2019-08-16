
//#include "STM32_DeviceId.h"

#ifndef _STM32_DEVICE_ID_H
#define _DEVICE_ID_H
//STM32 CPU唯一身份标识寄存器（96位）


//STM32的ID 16位检验和
#define CONFIG_CHECK_DEVICE_ID  0
//////////////////////////////////////////////////////														
												
struct	struct_stm32_id{
													
												unsigned char Checked;//		
												unsigned char Aeg;
												unsigned char KeyCount;//
											};
								
								
extern struct	struct_stm32_id		STM32DeviceId;						
										
										
												
				
						
														
//STM32 CPU唯一身份标识寄存器 在CPU中的地址														
//#define DEVICE_ID_ADR 	0x1FFFF7E8

unsigned short int GetStm32F103_DeviceId_Sum6(void);

void InitSTM32DeciceID(void);
#endif


