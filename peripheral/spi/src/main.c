#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"

#define SPI1_ENABLE_ARDUINO_NSS() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0)
#define SPI1_DISABLE_ARDUINO_NSS() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1)

SPI_HandleTypeDef hal_spi1;

void SPI1_Init(void) {
	SPI_InitTypeDef SPI_InitStruct = {
		.Mode = SPI_MODE_MASTER,
		.Direction = SPI_DIRECTION_2LINES,
		.DataSize = SPI_DATASIZE_8BIT,
		.CLKPolarity = SPI_POLARITY_LOW,
		.CLKPhase = SPI_PHASE_1EDGE,
		.NSS = SPI_NSS_SOFT,
		.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4,
		.FirstBit = SPI_FIRSTBIT_MSB,
		.TIMode = SPI_TIMODE_DISABLE,
		.CRCCalculation = SPI_CRCCALCULATION_DISABLE,
		.CRCPolynomial = 10
	};

	hal_spi1 = (SPI_HandleTypeDef) {
		.Instance = SPI1,
		.Init = SPI_InitStruct
	};

	HAL_SPI_Init(&hal_spi1);
}

int main(void) {

	HAL_Init();

	SPI1_Init();

	char *str[] = {"Hello\r\n", "World\r\n"};
	int idx = 0;

	while (1) {
		SPI1_ENABLE_ARDUINO_NSS();
		HAL_SPI_Transmit(&hal_spi1, str[idx], 7, HAL_MAX_DELAY);
		HAL_Delay(1000);
		idx = !idx;
		SPI1_DISABLE_ARDUINO_NSS();
	}

        return 0;
}
