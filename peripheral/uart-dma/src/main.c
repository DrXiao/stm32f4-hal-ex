#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"

UART_HandleTypeDef hal_uart1;
char recv[16] = "Hello\r\n";

void UART1_Init(void) {
	UART_InitTypeDef UART_InitStruct = {
		.BaudRate = 9600,
		.WordLength = UART_WORDLENGTH_8B,
		.StopBits = UART_STOPBITS_1,
		.Parity = UART_PARITY_NONE,
		.Mode = UART_MODE_TX_RX,
	};

	hal_uart1 = (UART_HandleTypeDef) {
		.Instance = USART1,
		.Init = UART_InitStruct
	};

	HAL_UART_Init(&hal_uart1);
}

void DMA2_Init(void) {
	__HAL_RCC_DMA2_CLK_ENABLE();
}


int main(void) {

	HAL_Init();
	DMA2_Init();
	UART1_Init();
	HAL_UART_Transmit_DMA(&hal_uart1, recv, 7);
	while(1) {

	}

        return 0;
}
