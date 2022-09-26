#include "stm32f4xx_hal.h"

void HAL_MspInit(void) {
	__HAL_RCC_SYSCFG_CLK_ENABLE();
	__HAL_RCC_PWR_CLK_ENABLE();
}

DMA_HandleTypeDef hal_dma_uart1_rx;
DMA_HandleTypeDef hal_dma_uart1_tx;

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
		
		DMA_InitTypeDef DMA_InitStruct = {
			.Channel = DMA_CHANNEL_4,
			.Direction = DMA_PERIPH_TO_MEMORY,
			.PeriphInc = DMA_PINC_DISABLE,
			.MemInc = DMA_MINC_ENABLE,
			.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
			.MemDataAlignment = DMA_MDATAALIGN_BYTE,
			.Mode = DMA_NORMAL,
			.Priority = DMA_PRIORITY_LOW,
			.FIFOMode = DMA_FIFOMODE_DISABLE
		};

		hal_dma_uart1_rx = (DMA_HandleTypeDef) {
			.Instance = DMA2_Stream2,
			.Init = DMA_InitStruct
		};

		HAL_DMA_Init(&hal_dma_uart1_rx);
		__HAL_LINKDMA(hal_uart, hdmarx, hal_dma_uart1_rx);
		
		DMA_InitStruct = (DMA_InitTypeDef) {
			.Channel = DMA_CHANNEL_4,
			.Direction = DMA_MEMORY_TO_PERIPH,
			.PeriphInc = DMA_PINC_DISABLE,
			.MemInc = DMA_MINC_ENABLE,
			.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
			.MemDataAlignment = DMA_MDATAALIGN_BYTE,
			.Mode = DMA_NORMAL,
			.Priority = DMA_PRIORITY_LOW,
			.FIFOMode = DMA_FIFOMODE_DISABLE
		};

		hal_dma_uart1_tx = (DMA_HandleTypeDef) {
			.Instance = DMA2_Stream7,
			.Init = DMA_InitStruct
		};

		HAL_DMA_Init(&hal_dma_uart1_tx);
		__HAL_LINKDMA(hal_uart, hdmatx, hal_dma_uart1_tx);
	}
}