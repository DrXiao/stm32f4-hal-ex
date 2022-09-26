#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"

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

int main(void) {

	HAL_Init();

	GPIOC_Init();

	int state = 0;

	while(1) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, state);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, !state);
		HAL_Delay(1000);
		state = !state;
	}

        return 0;
}
