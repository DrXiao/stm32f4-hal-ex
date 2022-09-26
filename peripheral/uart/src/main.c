#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"

UART_HandleTypeDef hal_uart1;
char recv;

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

int main(void) {

	HAL_Init();

	UART1_Init();

	while(1) {
		while(HAL_UART_Receive(&hal_uart1, &recv, sizeof(recv), HAL_MAX_DELAY) != HAL_OK);
		while(HAL_UART_Transmit(&hal_uart1, &recv, sizeof(recv), HAL_MAX_DELAY) != HAL_OK);
	}

        return 0;
}
