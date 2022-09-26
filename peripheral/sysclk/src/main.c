#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"
#include <stdio.h>
#include <string.h>

/* Let System Clock = 168 MHz 
 *
 * Notice HSE_VALUE defined in stm32f4xx_hal_conf.h 
 * is changed to 8000000U instead of 25000000U
 */
void SysClock_Config(void) {
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	RCC_OscInitTypeDef RCC_OscInitStruct = {
		.OscillatorType = RCC_OSCILLATORTYPE_HSE,
		.HSEState = RCC_HSE_ON,
		.PLL = (RCC_PLLInitTypeDef){
			.PLLState = RCC_PLL_ON,
			.PLLSource = RCC_PLLSOURCE_HSE,
			.PLLM = 4,
			.PLLN = 168,
			.PLLP = RCC_PLLP_DIV2,
			.PLLQ = 4,
		}
	};

	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	RCC_ClkInitTypeDef RCC_ClkInitStruct = {
		.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
				| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2,
		.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK,
		.AHBCLKDivider = RCC_SYSCLK_DIV1,
		.APB1CLKDivider = RCC_HCLK_DIV4,
		.APB2CLKDivider = RCC_HCLK_DIV2
	};

	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
	__HAL_RCC_GPIOH_CLK_ENABLE();
}

/* UART is just used to print the SystemCoreClock after setting it. */
UART_HandleTypeDef hal_uart1;
char send[128];
void UART1_Init(void);

int main(void) {

	HAL_Init();

	uint32_t SysCoreClockBefore = SystemCoreClock;
	
	SysClock_Config();
	
	UART1_Init();
	
	uint32_t SysCoreClockAfter = SystemCoreClock;

	sprintf(send, "SystemCoreClock: %u\r\n", SysCoreClockBefore);
	HAL_UART_Transmit(&hal_uart1, send, strlen(send), HAL_MAX_DELAY);
	sprintf(send, "SystemCoreClock: %u\r\n", SysCoreClockAfter);
	HAL_UART_Transmit(&hal_uart1, send, strlen(send), HAL_MAX_DELAY);
	while(1) {

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
