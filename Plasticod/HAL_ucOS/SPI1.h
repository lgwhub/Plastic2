
//#include "SPI1.h"

#ifndef _SPI1_H
#define _SPI1_H

//#if CONFIG_SPI1

   void GPIO_Configuration_SPI1(void);

   void SPI1_Configuration(void);

   unsigned short int SPI1_WRITE_READ_16bit(unsigned short int dat);


void SPI1_WRITE_13bit(unsigned short int dat);

//#endif
////////////////



//#if CONFIG_SPI2
//   void GPIO_Configuration_SPI2(void);
//
//   void SPI2_Configuration(void);
//
//   unsigned short int SPI2_WRITE_READ_16bit(unsigned short int dat);
//
//#endif
////////////////

#endif

