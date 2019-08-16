/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.blkeji.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               includes.h
** Descriptions:            includes.h for ucos
**
**--------------------------------------------------------------------------------------------------------

** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/


#ifndef  __INCLUDES_H__
#define  __INCLUDES_H__

/* Includes ------------------------------------------------------------------*/
#include  <stdio.h>
#include  <string.h>
#include  <ctype.h>
#include  <stdlib.h>
#include  <stdarg.h>
#include  <math.h>

#include "config.h"


#include  <uCOS-II\Source\ucos_ii.h>

#include  <uCOS-II\Ports\ARM-Cortex-M3\RealView\os_cpu.h>
#include  <uC-CPU\ARM-Cortex-M3\RealView\cpu.h>
#include  <lib_def.h>
#include  <lib_mem.h>
#include  <lib_str.h>





//#include "Nomal.h"

#include  <stm32f10x.h>
#include "config.h"

#include "HD_PLASTIC1.h"				
#include "uart_UCOS.h"						//担心 stm32f10x_it.c  不能包含到  CONFIG_UART1
#include "pid.h"
#include "LoopBuf.h"
//#include "uart.h"
/*
//#include "HD_CONST.h"
#include "HD_CONST10.h"

//#include "CC1100.H"
#include "user.h"
//#include "SaveData.h"
#include "Parameter.h"


//#include "ClearErrSample.h"


#include "bsp_tm7705.h"

#include "AT24C1024.H"

#include "ClearErrSample.h"


	//#if CONFIG_ADC
			#include "adc.h"
	//#endif
	
	#include "STM32_DeviceId.h"
	
	#include "pwm.h"
	#include "ModbusProcess.h"
	#include "ModbusRecv.h"
	#include "jump.h"
	#if	CONFIG_EXTI	
		#include "Exti.h"
	#endif
//
//#include "HD_SIN2.h"
//#include "DacD.h"	
#include "Dac1.h"	
#include "CaptureTim.h"
	*/
	
	//#define      test1234   1
#if (OS_VIEW_MODULE == DEF_ENABLED)

#include    <uCOS-VIEW\Ports\ARM-Cortex-M3\Realview\os_viewc.h>

#include    <uCOS-VIEW\Source\os_view.h>
#endif	
	
	
#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/


