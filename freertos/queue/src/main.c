#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <string.h>

UART_HandleTypeDef hal_uart1;
void UART1_Init(void);

#define MILLI_SECOND_TICK (configTICK_RATE_HZ / 1000)
#define QUEUE_SIZE 5

typedef struct {
	char string[16];
} queue_item_t;

QueueHandle_t queue_item_handle;

void feed_you_task(void *params) {
	while(1) {
		queue_item_t queue_item;
		strcpy(queue_item.string, "Hello\r\n");
		
		while(xQueueSendToBack(queue_item_handle, &queue_item, portMAX_DELAY) != pdTRUE);

		vTaskDelay(MILLI_SECOND_TICK * 1000);
	}
}

void feed_me_task(void *params) {
	queue_item_t recv_queue_item;
	while(1) {
		if (xQueueReceive(queue_item_handle, &recv_queue_item, portMAX_DELAY) == pdTRUE) {
			HAL_UART_Transmit(&hal_uart1, recv_queue_item.string, strlen(recv_queue_item.string), HAL_MAX_DELAY);		
		}
	}
}

int main(void) {

	HAL_Init();

	UART1_Init();

	queue_item_handle = xQueueCreate(QUEUE_SIZE, sizeof(queue_item_t));

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
