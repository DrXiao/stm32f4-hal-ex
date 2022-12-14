#include "stm32f4xx_hal.h"

void HAL_MspInit(void) {
	__HAL_RCC_SYSCFG_CLK_ENABLE();
	__HAL_RCC_PWR_CLK_ENABLE();
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *hal_tim) {
	if(hal_tim->Instance == TIM3)
		__HAL_RCC_TIM3_CLK_ENABLE();
}

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *hal_tim) {
	if (hal_tim->Instance == TIM3) {
		__HAL_RCC_GPIOA_CLK_ENABLE();
	
		GPIO_InitTypeDef GPIO_InitStruct = {
			.Pin = GPIO_PIN_6 | GPIO_PIN_7,
			.Mode = GPIO_MODE_AF_PP,
			.Speed = GPIO_SPEED_FREQ_HIGH,
			.Pull = GPIO_NOPULL,
			.Alternate = GPIO_AF2_TIM3
		};

		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	}
}
