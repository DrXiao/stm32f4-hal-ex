#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"
#define PERIOD 1600
#define PRESCALER 100

TIM_HandleTypeDef hal_tim2;

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *);

void TIM2_Init(void) {
	TIM_Base_InitTypeDef TIM_Base_InitStruct = {
		.Prescaler = PRESCALER - 1,
		.Period = PERIOD - 1,
		.CounterMode = TIM_COUNTERMODE_UP,
	};

	hal_tim2 = (TIM_HandleTypeDef){
		.Instance = TIM2,
		.Init = TIM_Base_InitStruct
	};

	HAL_TIM_Base_Init(&hal_tim2);

	TIM_OC_InitTypeDef TIM_OC_InitStruct = {
		.OCMode = TIM_OCMODE_PWM1,
		.Pulse = 0,
		.OCPolarity = TIM_OCPOLARITY_LOW,
		.OCFastMode = TIM_OCFAST_DISABLE
	};

	HAL_TIM_PWM_ConfigChannel(&hal_tim2, &TIM_OC_InitStruct, TIM_CHANNEL_2);
	HAL_TIM_PWM_ConfigChannel(&hal_tim2, &TIM_OC_InitStruct, TIM_CHANNEL_3);

	HAL_TIM_PWM_Start(&hal_tim2, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&hal_tim2, TIM_CHANNEL_3);
	HAL_TIM_MspPostInit(&hal_tim2);
}

int main(void) {

	HAL_Init();
	TIM2_Init();
	
	int pwm = 0;
	int status = 0;
	while(1) {
		if(!status) 
			pwm += 160;
		else
			pwm -= 160;

		if (pwm == PERIOD)
			status = !status;
		else if(pwm == 0)
			status = !status;

		TIM2->CCR2 = pwm;
		TIM2->CCR3 = PERIOD - pwm;
		HAL_Delay(100);
	}

        return 0;
}
