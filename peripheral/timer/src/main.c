#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"
#define PRESCALER 1600
#define PERIOD 10000

TIM_HandleTypeDef hal_tim6;

void TIM6_Init(void) {
	__HAL_RCC_TIM6_CLK_ENABLE();

	TIM_Base_InitTypeDef TIM_Base_InitStruct = {
		.Prescaler = PRESCALER - 1,
		.Period = PERIOD - 1,
		.CounterMode = TIM_COUNTERMODE_UP,
	};

	hal_tim6 = (TIM_HandleTypeDef){
		.Instance = TIM6,
		.Init = TIM_Base_InitStruct
	};
	HAL_TIM_Base_Init(&hal_tim6);
	HAL_TIM_Base_Start_IT(&hal_tim6);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *hal_tim) {
	if(hal_tim->Instance == TIM6) {
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_10);
	}
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

int main(void) {

	HAL_Init();
	GPIOC_Init();
	TIM6_Init();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, 0);

	while(1) {

	}

        return 0;
}
