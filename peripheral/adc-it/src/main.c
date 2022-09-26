#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"
#include <stdio.h>
#include <string.h>

ADC_HandleTypeDef hal_adc3;
uint16_t adc_val;

void ADC3_Init(void) {
	ADC_InitTypeDef ADC_InitStruct = {
		.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2,
		.Resolution = ADC_RESOLUTION_12B,
		.ScanConvMode = DISABLE,
		.ContinuousConvMode = ENABLE,
		.DiscontinuousConvMode = DISABLE,
		.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE,
		.ExternalTrigConv = ADC_SOFTWARE_START,
		.DataAlign = ADC_DATAALIGN_RIGHT,
		.NbrOfConversion = 1,
		.DMAContinuousRequests = DISABLE,
		.EOCSelection = ADC_EOC_SINGLE_CONV
	};

	hal_adc3 = (ADC_HandleTypeDef){
		.Instance = ADC3,
		.Init = ADC_InitStruct
	};

	HAL_ADC_Init(&hal_adc3);

	ADC_ChannelConfTypeDef ADC_ChannelConfStruct = {
		.Channel = ADC_CHANNEL_3,
		.Rank = 1,
		.SamplingTime = ADC_SAMPLETIME_3CYCLES
	};

	HAL_ADC_ConfigChannel(&hal_adc3, &ADC_ChannelConfStruct);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hal_adc) {
	if(hal_adc->Instance == ADC3) {
		adc_val = HAL_ADC_GetValue(hal_adc);
	}
}

UART_HandleTypeDef hal_uart1;
char send[128];
void UART1_Init(void);

int main(void) {

	HAL_Init();
	ADC3_Init();
	UART1_Init();
	
	while(1) {
		HAL_ADC_Start_IT(&hal_adc3);
		HAL_Delay(1000);
		sprintf(send, "ADC: %u\r\n", adc_val);
		HAL_UART_Transmit(&hal_uart1, send, strlen(send), HAL_MAX_DELAY);
	}

        return 0;
}

void UART1_Init(void) {
	UART_InitTypeDef UART_InitStruct = {
		.BaudRate = 9600,
		.WordLength = UART_WORDLENGTH_8B,
		.StopBits = UART_STOPBITS_1,
		.Parity = UART_PARITY_NONE,
		.Mode = UART_MODE_TX_RX,
	};

	hal_uart1 = (UART_HandleTypeDef) {
		.Instance = USART1,
		.Init = UART_InitStruct
	};

	HAL_UART_Init(&hal_uart1);
}
