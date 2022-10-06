#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdio.h>
#include <string.h>

#define MILLI_SECOND_TICK (configTICK_RATE_HZ / 1000)

UART_HandleTypeDef hal_uart1;
void UART1_Init(void);

SemaphoreHandle_t bin_semphr;
int share_src = 0;

void task(void *params) {
	char *msg = (char *)params;
	int len = strlen(msg);
	while(1) {
		xSemaphoreTake(bin_semphr, portMAX_DELAY);
		HAL_UART_Transmit(&hal_uart1, msg, len, HAL_MAX_DELAY);
		xSemaphoreGive(bin_semphr);
		vTaskDelay(MILLI_SECOND_TICK * 1000);
	}
}

int main(void) {

	HAL_Init();

	UART1_Init();

	const int task_num = 10, buf_size = 16;
	char task_name[task_num][buf_size];
	char task_msg[task_num][buf_size];
	for (int i = 0; i < 10; i++) {
		sprintf(task_name[i], "task%u", i + 1);
		sprintf(task_msg[i], "TASK %2u\r\n", i + 1);
		
		xTaskCreate(task, task_name[i], configMINIMAL_STACK_SIZE, task_msg[i], tskIDLE_PRIORITY + 1, NULL);
	}
	
	vTaskStartScheduler();

        return 0;
}

void UART1_Init(void) {
	bin_semphr = xSemaphoreCreateBinary();
	xSemaphoreGive(bin_semphr);

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
