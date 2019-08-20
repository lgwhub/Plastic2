
#include "stm32f0xx.h"
#include "stdio.h"

#include "FreeRTOS.h"
#include "task.h"

extern void usart_config(USART_TypeDef* USARTx, uint32_t BaudRate);

void led_config(void);



void led_task(void *para);


//#define sbi(ADDRESS,BIT) 	((ADDRESS->BSRR = BIT))	// Set bit
//#define cbi(ADDRESS,BIT) 	((ADDRESS->BRR = BIT))	// Clear bit
//#define	bis(ADDRESS,BIT)	(GPIO_ReadInputDataBit(ADDRESS,BIT))	// Is bit set?
//#define	bic(ADDRESS,BIT)	(!GPIO_ReadInputDataBit(ADDRESS,BIT))	// Is bit clear
//#define	toggle(ADDRESS,BIT)	(GPIO_WriteBit(ADDRESS,BIT,(BitAction)((1-GPIO_ReadOutputDataBit(ADDRESS,BIT)))))	// Toggle bit




int main(void)
{
	RCC_ClocksTypeDef RCC_Clocks;

	//��ȡϵͳʱ��Ƶ��
	RCC_GetClocksFreq(&RCC_Clocks);
	//��SysTick��ʱ�����ж�Ƶ������1ms����FreeRTOS��ʱ��ƬΪ1ms
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);

	//����LED����
	xTaskCreate(led_task, ( signed char * )"led", 128, NULL, 1, NULL);
	
	vTaskStartScheduler();
	
	while (1)
	{
		
	}
}


void led_port_config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOC, GPIO_Pin_8 | GPIO_Pin_9);
}



void led_task(void *para)
{
	const uint8_t *COMPILED_DATE=__DATE__;//��ñ�������
	const uint8_t *COMPILED_TIME=__TIME__;//��ñ���ʱ��

	
	uint32_t runtime = 0;
	
	led_port_config();
		
	usart_config(USART1, 115200);
	
	printf("		FreeRTOS 7.6.0 for STM32F030\r\n");
	printf("		Build date: ");
	printf((char *)COMPILED_DATE);
	printf(" ");
	printf((char *)COMPILED_TIME);
	printf("\r\n");
	
	
	while (1)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_8);
		GPIO_ResetBits(GPIOC, GPIO_Pin_9);
		
		vTaskDelay(500);
		
		GPIO_SetBits(GPIOC, GPIO_Pin_9);
		GPIO_ResetBits(GPIOC, GPIO_Pin_8);
		
		vTaskDelay(500);
		
		printf("led_task has run %ds.\r\n",++runtime);
	}
	
}


//�ڴ����ʧ�ܵĹ��Ӻ�����configUSE_MALLOC_FAILED_HOOK����Ϊ1ʱ�����
//void vApplicationMallocFailedHook( void )
//{
//	/* vApplicationMallocFailedHook() will only be called if
//	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
//	function that will get called if a call to pvPortMalloc() fails.
//	pvPortMalloc() is called internally by the kernel whenever a task, queue,
//	timer or semaphore is created.  It is also called by various parts of the
//	demo application.  If heap_1.c or heap_2.c are used, then the size of the
//	heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
//	FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
//	to query the size of free heap space that remains (although it does not
//	provide information on how the remaining heap might be fragmented). */
//	taskDISABLE_INTERRUPTS();
//	for( ;; );
//}
///*-----------------------------------------------------------*/

//���������Ӻ�����configUSE_IDLE_HOOK����Ϊ1ʱ��Ҫ�����������
//void vApplicationIdleHook( void )
//{
//	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
//	to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
//	task.  It is essential that code added to this hook function never attempts
//	to block in any way (for example, call xQueueReceive() with a block time
//	specified, or call vTaskDelay()).  If the application makes use of the
//	vTaskDelete() API function (as this demo application does) then it is also
//	important that vApplicationIdleHook() is permitted to return to its calling
//	function, because it is the responsibility of the idle task to clean up
//	memory allocated by the kernel to any task that has since been deleted. */
//}
///*-----------------------------------------------------------*/

//��ջ������Ӻ�����configCHECK_FOR_STACK_OVERFLOW����Ϊ1��2ʱ�����
//void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
//{
//	( void ) pcTaskName;
//	( void ) pxTask;

//	/* Run time stack overflow checking is performed if
//	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
//	function is called if a stack overflow is detected. */
//	taskDISABLE_INTERRUPTS();
//	for( ;; );
//}
///*-----------------------------------------------------------*/

//ʱ����હ��Ӻ�������SysTick��ʱ���жϴ������л����������������Դ˺����ڵ���FreeRTOS APIʱ��Ҫע�ⰲȫ
//configUSE_TICK_HOOK������Ϊ1ʱ�����
//void vApplicationTickHook( void )
//{
//	/* This function will be called by each tick interrupt if
//	configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
//	added here, but the tick hook is called from an interrupt context, so
//	code must not attempt to block, and only the interrupt safe FreeRTOS API
//	functions can be used (those that end in FromISR()). */
//}
///*-----------------------------------------------------------*/


