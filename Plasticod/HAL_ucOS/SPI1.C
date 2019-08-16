
#include "includes.h"

#if CONFIG_SPI1

#include "SPI1.h"



void GPIO_Configuration_SPI1(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;


  /* SPI1 Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  /* Configure SPI1 pins: SCK, MISO and MOSI ---------------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;    //sck  mosi
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;     //cs
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //GPIO_Mode_IN_FLOATING;
  //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}




void SPI1_Configuration(void)
{
	SPI_InitTypeDef   SPI_InitStructure;
	
  /* System clocks configuration ---------------------------------------------*/
  //RCC_Configuration();

  /* GPIO configuration ------------------------------------------------------*/
  GPIO_Configuration_SPI1();

  /* SPI1 configuration ------------------------------------------------------*/
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;  //SPI_Mode_Slave;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;  //SPI_DataSize_16b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;//SPI_CPOL_Low;//
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;//SPI_CPHA_1Edge;//
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;//SPI_NSS_Hard;//
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitStructure);

  /* SPI2 configuration ------------------------------------------------------*/
//  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;  //SPI_Mode_Slave;
//  SPI_Init(SPI2, &SPI_InitStructure);

  /* Enable SPI1 CRC calculation */
//  SPI_CalculateCRC(SPI1, ENABLE);
  /* Enable SPI2 CRC calculation */
//  SPI_CalculateCRC(SPI2, ENABLE);

  /* Enable SPI1 */
  SPI_Cmd(SPI1, ENABLE);
  /* Enable SPI2 */
 // SPI_Cmd(SPI2, ENABLE);

  /* Transfer procedure */
//  while (TxIdx < BufferSize - 1)
//  {
//    /* Wait for SPI1 Tx buffer empty */
//    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
//    /* Send SPI2 data */
//    SPI_I2S_SendData(SPI2, SPI2_Buffer_Tx[TxIdx]);
//    /* Send SPI1 data */
//    SPI_I2S_SendData(SPI1, SPI1_Buffer_Tx[TxIdx++]);
//    /* Wait for SPI2 data reception */
//    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
//    /* Read SPI2 received data */
//    SPI2_Buffer_Rx[RxIdx] = SPI_I2S_ReceiveData(SPI2);
//    /* Wait for SPI1 data reception */
//    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
//    /* Read SPI1 received data */
//    SPI1_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData(SPI1);
//  }

}
void SPI1_WRITE_13bit(unsigned short int dat)
{

    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
       {
    	
        }     
    /* Send SPI2 data */
    //SPI_I2S_SendData(SPI2, SPI2_Buffer_Tx[TxIdx]);
    /* Send SPI1 data */
    SPI_I2S_SendData(SPI1, dat);
    
 
    
   
}

unsigned short int SPI1_WRITE_READ_16bit(unsigned short int dat)
{
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
       {
    	
        }
    
    /* Send SPI2 data */
    //SPI_I2S_SendData(SPI2, SPI2_Buffer_Tx[TxIdx]);
    /* Send SPI1 data */
    SPI_I2S_SendData(SPI1, dat);
    return SPI_I2S_ReceiveData(SPI1);
}




#endif
////////////////
#if CONFIG_SPI2
void GPIO_Configuration_SPI2(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  
  /* SPI2 Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  /* Configure SPI2 pins: SCK, MISO and MOSI ---------------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
  
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  
}

////////////////

void SPI2_Configuration(void)
{
	SPI_InitTypeDef   SPI_InitStructure;
  /* System clocks configuration ---------------------------------------------*/
 // RCC_Configuration();

  /* GPIO configuration ------------------------------------------------------*/
  GPIO_Configuration_SPI2();

  /* SPI1 configuration ------------------------------------------------------*/
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;  //SPI_Mode_Slave;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;//SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; //SPI_NSS_Hard;//
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  //SPI_Init(SPI1, &SPI_InitStructure);

  /* SPI2 configuration ------------------------------------------------------*/
  //SPI_InitStructure.SPI_Mode = SPI_Mode_Master;  //SPI_Mode_Slave;
  SPI_Init(SPI2, &SPI_InitStructure);

  /* Enable SPI2 CRC calculation */
 // SPI_CalculateCRC(SPI2, ENABLE);

  /* Enable SPI2 */
  SPI_Cmd(SPI2, ENABLE);

  /* Transfer procedure */
//  while (TxIdx < BufferSize - 1)
//  {
//    /* Wait for SPI1 Tx buffer empty */
//    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
//    /* Send SPI2 data */
//    SPI_I2S_SendData(SPI2, SPI2_Buffer_Tx[TxIdx]);
//    /* Send SPI1 data */
//    SPI_I2S_SendData(SPI1, SPI1_Buffer_Tx[TxIdx++]);
//    /* Wait for SPI2 data reception */
//    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
//    /* Read SPI2 received data */
//    SPI2_Buffer_Rx[RxIdx] = SPI_I2S_ReceiveData(SPI2);
//    /* Wait for SPI1 data reception */
//    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
//    /* Read SPI1 received data */
//    SPI1_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData(SPI1);
//  }

}


//{
//  /* Wait for SPI1 Tx buffer empty */
//  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
//  /* Wait for SPI2 Tx buffer empty */
//  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
//
//  /* Send last SPI2_Buffer_Tx data */
//  SPI_I2S_SendData(SPI2, SPI2_Buffer_Tx[TxIdx]);
//  /* Enable SPI2 CRC transmission */
//  SPI_TransmitCRC(SPI2);
//  /* Send last SPI1_Buffer_Tx data */
//  SPI_I2S_SendData(SPI1, SPI1_Buffer_Tx[TxIdx]);
//  /* Enable SPI1 CRC transmission */
//  SPI_TransmitCRC(SPI1);
//
//  /* Wait for SPI1 last data reception */
//  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
//  /* Read SPI1 last received data */
//  SPI1_Buffer_Rx[RxIdx] = SPI_I2S_ReceiveData(SPI1);
//
//  /* Wait for SPI2 last data reception */
//  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
//  /* Read SPI2 last received data */
//  SPI2_Buffer_Rx[RxIdx] = SPI_I2S_ReceiveData(SPI2);
//
//  /* Wait for SPI1 data reception: CRC transmitted by SPI2 */
//  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
//  /* Wait for SPI2 data reception: CRC transmitted by SPI1 */
//  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
//
//  /* Check the received data with the send ones */
//  TransferStatus1 = Buffercmp(SPI2_Buffer_Rx, SPI1_Buffer_Tx, BufferSize);
//  TransferStatus2 = Buffercmp(SPI1_Buffer_Rx, SPI2_Buffer_Tx, BufferSize);
//  /* TransferStatus1, TransferStatus2 = PASSED, if the data transmitted and received
//     are correct */
//  /* TransferStatus1, TransferStatus2 = FAILED, if the data transmitted and received
//     are different */
//
//  /* Test on the SPI1 CRC Error flag */
//  if ((SPI_I2S_GetFlagStatus(SPI1, SPI_FLAG_CRCERR)) == SET)
//  {
//    TransferStatus2 = FAILED;
//  }
//
//  /* Test on the SPI2 CRC Error flag */
//  if ((SPI_I2S_GetFlagStatus(SPI2, SPI_FLAG_CRCERR)) == SET)
//  {
//    TransferStatus1 = FAILED;
//  }
//
//  /* Read SPI1 received CRC value */
//  CRC1Value = SPI_I2S_ReceiveData(SPI1);
//  /* Read SPI2 received CRC value */
//  CRC2Value = SPI_I2S_ReceiveData(SPI2);
//
//  while (1)
//  {}
//}


unsigned short int SPI2_WRITE_READ_16bit(unsigned short int dat)
{
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
        {
    	
        };
    
    /* Send SPI2 data */
    //SPI_I2S_SendData(SPI2, SPI2_Buffer_Tx[TxIdx]);
    /* Send SPI1 data */
    SPI_I2S_SendData(SPI2, dat);
    return SPI_I2S_ReceiveData(SPI2);
}


#endif



