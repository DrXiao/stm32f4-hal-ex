#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"
#define PERIOD 1000
#define PRESCALER 16

TIM_HandleTypeDef hal_tim3;

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *);

void TIM2_Init(void) {
	TIM_Base_InitTypeDef TIM_Base_InitStruct = {
		.Prescaler = PRESCALER - 1,
		.Period = PERIOD - 1,
		.CounterMode = TIM_COUNTERMODE_UP,
	};

	hal_tim3 = (TIM_HandleTypeDef){
		.Instance = TIM3,
		.Init = TIM_Base_InitStruct
	};

	HAL_TIM_Base_Init(&hal_tim3);

	TIM_OC_InitTypeDef TIM_OC_InitStruct = {
		.OCMode = TIM_OCMODE_PWM1,
		.Pulse = 0,
		.OCPolarity = TIM_OCPOLARITY_LOW,
		.OCFastMode = TIM_OCFAST_DISABLE
	};

	HAL_TIM_PWM_ConfigChannel(&hal_tim3, &TIM_OC_InitStruct, TIM_CHANNEL_1);
	HAL_TIM_PWM_ConfigChannel(&hal_tim3, &TIM_OC_InitStruct, TIM_CHANNEL_2);

	HAL_TIM_PWM_Start(&hal_tim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&hal_tim3, TIM_CHANNEL_2);
	HAL_TIM_MspPostInit(&hal_tim3);
}

int main(void) {

	HAL_Init();
	TIM2_Init();
	
	int pwm = 0;
	int status = 0;
	while(1) {
		if(!status) 
			pwm += PERIOD / 10;
		else
			pwm -= PERIOD / 10;

		if (pwm == PERIOD)
			status = !status;
		else if(pwm == 0)
			status = !status;

		TIM3->CCR1 = pwm;
		TIM3->CCR2 = PERIOD - pwm;
		HAL_Delay(1000);
	}

        return 0;
}
