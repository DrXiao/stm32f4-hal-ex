#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"
#include "FreeRTOS.h"
#include "task.h"

#define MILLI_SECOND_TICK (configTICK_RATE_HZ / 1000)

void GPIOC_Init(void) {
	__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct = {
		.Pin = GPIO_PIN_10 | GPIO_PIN_11,
		.Mode = GPIO_MODE_OUTPUT_PP,
		.Speed = GPIO_SPEED_FREQ_LOW,
		.Pull = GPIO_NOPULL
	};

	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void PC10_blink(void *params) {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, 0);

	while(1) {
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_10);
		vTaskDelay(MILLI_SECOND_TICK * 1000);
	}
}

void PC11_blink(void *params) {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, 0);

	while(1) {
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_11);
		vTaskDelay(MILLI_SECOND_TICK * 3000);
	}
}

int main(void) {

	HAL_Init();

	GPIOC_Init();

	xTaskCreate(PC10_blink, "PC10_blink", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);
	xTaskCreate(PC11_blink, "PC10_blink", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

	vTaskStartScheduler();

        return 0;
}
