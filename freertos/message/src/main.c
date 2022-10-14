#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"
#include "FreeRTOS.h"
#include "task.h"
#include "message_buffer.h"
#include <string.h>

UART_HandleTypeDef hal_uart1;
void UART1_Init(void);

#define MILLI_SECOND_TICK (configTICK_RATE_HZ / 1000)
#define MESSAGE_BUF_SIZE 32

MessageBufferHandle_t message;

void feed_you_task(void *params) {
	char buf[MESSAGE_BUF_SIZE];
	char *str[4] = {
		"Hello this", "World is", "Start a", "Conti pen"
	};
	uint8_t idx = 0;
	while(1) {
		xMessageBufferSend(message, str[idx & 3], strlen(str[idx & 3]), portMAX_DELAY);
		idx++;
		vTaskDelay(MILLI_SECOND_TICK * 1500);
		if (xMessageBufferIsEmpty(message) == pdFALSE)
			xMessageBufferReceive(message, buf, MESSAGE_BUF_SIZE, portMAX_DELAY);
	}
}

void feed_me_task(void *params) {
	char buf[9];
	int ret;
	while(1) {
		vTaskDelay(MILLI_SECOND_TICK * 500);
		ret = xMessageBufferReceive(message, buf, 9, portMAX_DELAY);
		if (ret == 0)
			HAL_UART_Transmit(&hal_uart1, "(Unable to receive)", strlen("(Unable to receive)"), HAL_MAX_DELAY);
		else
			HAL_UART_Transmit(&hal_uart1, buf, ret, HAL_MAX_DELAY);
		HAL_UART_Transmit(&hal_uart1, "\r\n", 2, HAL_MAX_DELAY);
	}
}

int main(void) {

	HAL_Init();

	UART1_Init();

	message = xMessageBufferCreate(MESSAGE_BUF_SIZE);

	xTaskCreate(feed_you_task, "feed you task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);
	xTaskCreate(feed_me_task, "feed me task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

	vTaskStartScheduler();

        return 0;
}

void UART1_Init(void) {
	UART_InitTypeDef UART_InitStruct = {
		.BaudRate = 9600,
		.WordLength = UART_WORDLENGTH_8B,
		.StopBits = UART_STOPBITS_1,
		.Parity = UART_PARITY_NONE,
		.Mode = UART_MODE_TX_RX
	};

	hal_uart1 = (UART_HandleTypeDef) {
		.Instance = USART1,
		.Init = UART_InitStruct
	};

	HAL_UART_Init(&hal_uart1);
}
