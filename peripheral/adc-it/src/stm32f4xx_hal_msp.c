#include "stm32f4xx_hal.h"

void HAL_MspInit(void) {
	__HAL_RCC_SYSCFG_CLK_ENABLE();
	__HAL_RCC_PWR_CLK_ENABLE();
}

void HAL_ADC_MspInit(ADC_HandleTypeDef *hal_adc) {
	if(hal_adc->Instance == ADC3) {
		__HAL_RCC_ADC3_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GPIO_InitTypeDef GPIO_InitStruct = {
			.Pin = GPIO_PIN_3,
			.Mode = GPIO_MODE_ANALOG,	
			.Pull = GPIO_NOPULL
		};
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		HAL_NVIC_SetPriority(ADC_IRQn, 2, 0);
		HAL_NVIC_EnableIRQ(ADC_IRQn);
	}
}

void HAL_UART_MspInit(UART_HandleTypeDef *hal_uart) {
	if (hal_uart->Instance == USART1) {
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_USART1_CLK_ENABLE();

		GPIO_InitTypeDef GPIO_InitStruct = {
			.Pin = GPIO_PIN_9 | GPIO_PIN_10,
			.Mode = GPIO_MODE_AF_PP,
			.Pull = GPIO_PULLUP,
			.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
			.Alternate = GPIO_AF7_USART1
		};

		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	}
}
