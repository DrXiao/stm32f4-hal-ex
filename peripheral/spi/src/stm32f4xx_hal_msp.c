#include "stm32f4xx_hal.h"

void HAL_MspInit(void) {
	__HAL_RCC_SYSCFG_CLK_ENABLE();
	__HAL_RCC_PWR_CLK_ENABLE();
}

void HAL_SPI_MspInit(SPI_HandleTypeDef *hal_spi) {
	if (hal_spi->Instance == SPI1) {
		__HAL_RCC_SPI1_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();

		GPIO_InitTypeDef GPIO_InitStruct = {
			.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,
			.Mode = GPIO_MODE_AF_PP,
			.Pull = GPIO_NOPULL,
			.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
			.Alternate = GPIO_AF5_SPI1
		};

		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		
		GPIO_InitStruct = (GPIO_InitTypeDef) {
			.Pin = GPIO_PIN_4,
			.Mode = GPIO_MODE_AF_PP,
			.Pull = GPIO_NOPULL,
			.Speed = GPIO_SPEED_FREQ_VERY_HIGH
		};

		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	}
}
