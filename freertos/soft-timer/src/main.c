#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include <string.h>

UART_HandleTypeDef hal_uart1;
void UART1_Init(void);

TimerHandle_t timer;

void timer_callback(TimerHandle_t timer) {
	HAL_UART_Transmit(&hal_uart1, "Hello Timer!\r\n", 14, HAL_MAX_DELAY);
}

int main(void) {

	HAL_Init();

	UART1_Init();

	timer = xTimerCreate("timer", pdMS_TO_TICKS(1000), pdTRUE, NULL, timer_callback);

	xTimerStart(timer, 0);

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
