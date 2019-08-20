
#include "stm32f0xx.h"
#include "stdio.h"

//�������ú�����Ŀǰֻ���䴮��1
void usart_config(USART_TypeDef* USARTx, uint32_t BaudRate)
{
	USART_InitTypeDef	USART_InitStructure;
	GPIO_InitTypeDef	GPIO_InitStructure;
	
	//��������1��GPIOA��ʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	//PA9(TX),PA10(RX)��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//�����źʹ���1������
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);
	
	//�����������
	USART_DeInit(USARTx);
	
	//���ô���
	USART_InitStructure.USART_BaudRate = BaudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//8������λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;				//����żУ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�������պͷ���
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//��Ӳ��������	
	USART_Init(USARTx, &USART_InitStructure);	//��ʼ������
	
	USART_Cmd(USARTx, ENABLE);	//���ô���
}


//�ض���fputc�������͵�����1
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	/* �ȴ����ͽ��� */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
	{}

	return ch;
}


int fgetc(FILE *f)
{
	/* �ȴ�����1�������� */
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

	return (int)USART_ReceiveData(USART1);
}

