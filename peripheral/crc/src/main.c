#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"

#include <stdio.h>
#include <string.h>

UART_HandleTypeDef hal_uart1;
void UART1_Init(void);

CRC_HandleTypeDef hal_crc;

void CRC_Init(void) {
	hal_crc.Instance = CRC;
	HAL_CRC_Init(&hal_crc);
}

int main(void) {

	HAL_Init();
	CRC_Init();
	UART1_Init();

	uint8_t tmp[256];
	char buf[256];

	for (int i = 0; i < 256; i++)
		tmp[i] = i;

	uint32_t ret = HAL_CRC_Calculate(&hal_crc, (uint32_t *)tmp, 256 / 4);

	sprintf(buf, "CRC: %X\r\n", ret);
	HAL_UART_Transmit(&hal_uart1, buf, strlen(buf), HAL_MAX_DELAY);

	while (1) {

	}

        return 0;
}

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
