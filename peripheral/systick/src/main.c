#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"

/* SysTick_Config has been defined, so here uses additional prefix. */
void __SysTick_Config(void) {
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

void GPIOC_Init(void) {
	__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct = {
		.Pin = GPIO_PIN_10,
		.Mode = GPIO_MODE_OUTPUT_PP,
		.Speed = GPIO_SPEED_FREQ_LOW,
		.Pull = GPIO_NOPULL
	};

	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

/*
 * In stm32f4xx_it.c, millsec will be decrement by 1 in SysTick_Handler() if it is non-zero.
 * Remember to view stm32f4xx_it.c to know how this example implement.
 */
uint32_t millsec = 0;

void delay(uint32_t mill) {
	millsec = mill;
	while(millsec);
}

int main(void) {

	__SysTick_Config();
	GPIOC_Init();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, 0);
	
	while(1) {
		/* blink PC10 */
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_10);
		delay(1000);
	}

        return 0;
}
