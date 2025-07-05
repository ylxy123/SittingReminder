#ifndef __DEVUART_H
#define __DEVUART_H
#include "stddef.h"
#include "py32f002b_ll_gpio.h"
#include "py32f002b_ll_bus.h"
#include "py32f002b_ll_exti.h"
#include "py32f002b_ll_usart.h"
#include "py32f002b_ll_utils.h"
#include "py32f002bxx_ll_Start_Kit.h"

#include "bsp.h"

#ifdef __cplusplus
extern "C" {
#endif

#define UART1_TX_LEN_MAX      (30)
#define UART1_RX_LEN_MAX      (30)

#define UART1_RX_TICK_TARGET  (3)


typedef struct
{
	uint8_t  pdata[UART1_RX_LEN_MAX];
	uint16_t length;
}uart_rx_info_t;


typedef struct
{
	uint8_t  pdata[UART1_TX_LEN_MAX];
	uint16_t length;
}uart_tx_info_t;


typedef struct
{
	uint8_t tick;
	uint8_t target;
}uart_Timout_info_t;


typedef struct
{
	uart_rx_info_t  rx;
	uart_tx_info_t  tx;
	uart_Timout_info_t rxTimeout;
	uart_Timout_info_t txTimeout;
}uart_info_t;



extern uint8_t aTxBuffer[];
extern uart_info_t  uart1;

extern void APP_UsartReceive_IT(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size);
	

extern void uart1_init(void);
extern void APP_ConfigUsart(USART_TypeDef *USARTx);
extern void APP_UsartTransmit_IT(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size);
extern void uart1_rx_timeout_update(void);
extern void uart1_rx_timeout_tick_restart(void);
extern void uart1_tx_tick_target_set(uint8_t tick);
extern void uart1_tx_timeout(void);

extern void mt_uart_deinit(USART_TypeDef *USARTx);
#ifdef __cplusplus
}
#endif

#endif 




