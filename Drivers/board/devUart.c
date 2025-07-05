#include "devUart.h"
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t aTxBuffer[] = "UART Test";
uint8_t aRxBuffer[30];
__IO ITStatus UartReady = RESET;
uint8_t *TxBuff = NULL;
__IO uint16_t TxSize = 0;
__IO uint16_t TxCount = 0;

uint8_t *RxBuff = NULL;
__IO uint16_t RxSize = 0;
__IO uint16_t RxCount = 0;


uart_info_t  uart1;

void uart1_init(void)
{
	uart1.rxTimeout.target = UART1_RX_TICK_TARGET;
}

//PA6 TX PA7 RX
void APP_ConfigUsart(USART_TypeDef *USARTx)
{
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_USART1);
    

  LL_GPIO_InitTypeDef GPIO_InitStructA;

  GPIO_InitStructA.Pin = LL_GPIO_PIN_6;

  GPIO_InitStructA.Mode = LL_GPIO_MODE_ALTERNATE;

  GPIO_InitStructA.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;

  GPIO_InitStructA.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  
  GPIO_InitStructA.Pull = LL_GPIO_PULL_UP;

  GPIO_InitStructA.Alternate = LL_GPIO_AF1_USART1;

  LL_GPIO_Init(GPIOA,&GPIO_InitStructA);

  GPIO_InitStructA.Pin = LL_GPIO_PIN_7;

  GPIO_InitStructA.Alternate = LL_GPIO_AF3_USART1;

  LL_GPIO_Init(GPIOA,&GPIO_InitStructA);
      
  NVIC_SetPriority(USART1_IRQn,0);
  
  NVIC_EnableIRQ(USART1_IRQn);
    
  LL_USART_InitTypeDef USART_InitStruct;

//  USART_InitStruct.BaudRate = 115200;
USART_InitStruct.BaudRate = 512000;

  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;

  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;

  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;

  LL_USART_Init(USARTx, &USART_InitStruct);

  LL_USART_ConfigAsyncMode(USARTx);

  LL_USART_Enable(USARTx);
	
	APP_UsartReceive_IT(USART1, (uint8_t *)aRxBuffer, 1);
      
}

void mt_uart_deinit(USART_TypeDef *USARTx)
{
  LL_USART_DeInit(USART1);
  LL_GPIO_DeInit(GPIOA);
}
void APP_UsartTransmit_IT(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size)
{
    TxBuff = pData;
    TxSize = Size;
    TxCount = Size;
    
    LL_USART_EnableIT_TXE(USARTx); 

}

void APP_UsartReceive_IT(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size)
{
    RxBuff = pData;
    RxSize = Size;
    RxCount = Size;

    LL_USART_EnableIT_PE(USARTx);
  
    LL_USART_EnableIT_ERROR(USARTx);
  
    LL_USART_EnableIT_RXNE(USARTx);
}

void APP_UsartIRQCallback(USART_TypeDef *USARTx)
{
    uint32_t errorflags = (LL_USART_IsActiveFlag_PE(USARTx) | LL_USART_IsActiveFlag_FE(USARTx) |\
                           LL_USART_IsActiveFlag_ORE(USARTx) | LL_USART_IsActiveFlag_NE(USARTx));
    if (errorflags == RESET)
    {
        if ((LL_USART_IsActiveFlag_RXNE(USARTx) != RESET) && (LL_USART_IsEnabledIT_RXNE(USARTx) != RESET))
        {
						uart1_rx_timeout_tick_restart();
					  uart1.rx.pdata[uart1.rx.length] = LL_USART_ReceiveData8(USARTx);
						if(uart1.rx.length < (UART1_RX_LEN_MAX-1))
						{
							uart1.rx.length ++;
						}
            return;
        }
    }

    if (errorflags != RESET)
    {
      LL_USART_ClearFlag_FE(USART1);
			LL_USART_ClearFlag_NE(USART1);
			LL_USART_ClearFlag_ORE(USART1);
			LL_USART_ClearFlag_PE(USART1);
    }
    
    if ((LL_USART_IsActiveFlag_TXE(USARTx) != RESET) && (LL_USART_IsEnabledIT_TXE(USARTx) != RESET))
      {
        LL_USART_TransmitData8(USARTx, *TxBuff);
        TxBuff++;
        if (--TxCount == 0U)
        { 
            LL_USART_DisableIT_TXE(USARTx);
            
            LL_USART_EnableIT_TC(USARTx);
        }
        return;
    }
    
    if ((LL_USART_IsActiveFlag_TC(USARTx) != RESET) && (LL_USART_IsEnabledIT_TC(USARTx) != RESET))
    {
        LL_USART_DisableIT_TC(USARTx);
        return;
    }
    
}

void uart1_rx_timeout_tick_restart(void)
{
	uart1.rxTimeout.tick = 0;
}
void uart1_rx_timeout_update(void)
{
	if(uart1.rxTimeout.tick < uart1.rxTimeout.target)
	{
		uart1.rxTimeout.tick ++;
	}
	else 	if(uart1.rxTimeout.tick == uart1.rxTimeout.target)
	{
		uart1.rxTimeout.tick ++;
    //mcli_nput_timeout_cmd((char *)uart1.rx.pdata,uart1.rx.length);
		//jx_rs465_rx(uart1.rx.pdata,uart1.rx.length);
		uart1.rx.length = 0;
	}
	else 
	{
		
	}
}





int fputc(int ch, FILE *f)
{
  /* Send a byte to USART */
  LL_USART_TransmitData8(USART1, ch);
  while (!LL_USART_IsActiveFlag_TC(USART1));
  LL_USART_ClearFlag_TC(USART1);
  return ch;
}
