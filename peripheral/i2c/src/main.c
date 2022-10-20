#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"

I2C_HandleTypeDef hal_i2c1;

void i2c1_init(void) {
	I2C_InitTypeDef I2C_InitStruct = {
		.ClockSpeed = 100000,
		.DutyCycle = I2C_DUTYCYCLE_2,
		.OwnAddress1 = 0,
		.AddressingMode = I2C_ADDRESSINGMODE_7BIT,
		.DualAddressMode = I2C_DUALADDRESS_DISABLE,
		.OwnAddress2 = 0,
		.GeneralCallMode = I2C_GENERALCALL_DISABLE,
		.NoStretchMode = I2C_NOSTRETCH_DISABLE
	};

	hal_i2c1 = (I2C_HandleTypeDef) {
		.Instance = I2C1,
		.Init = I2C_InitStruct
	};

	HAL_I2C_Init(&hal_i2c1);
}

int main(void) {

	HAL_Init();

	i2c1_init();

	while (1) {
		HAL_I2C_Master_Transmit(&hal_i2c1, 0x08 << 1, "Hello\r\n", 7, HAL_MAX_DELAY);
		HAL_Delay(1000);
	}

        return 0;
}
