#include "stm32f4xx_hal.h"

void HAL_MspInit(void) {
	__HAL_RCC_SYSCFG_CLK_ENABLE();
	__HAL_RCC_PWR_CLK_ENABLE();
}

void HAL_I2C_MspInit(I2C_HandleTypeDef *hal_i2c) {
	if (hal_i2c->Instance == I2C1) {
		__HAL_RCC_I2C1_CLK_ENABLE();

		__HAL_RCC_GPIOB_CLK_ENABLE();

		GPIO_InitTypeDef GPIO_InitStruct = {
			.Pin = GPIO_PIN_6 | GPIO_PIN_7,
			.Mode = GPIO_MODE_AF_OD,
			.Pull = GPIO_NOPULL,
			.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
			.Alternate = GPIO_AF4_I2C1
		};

		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	}
}
