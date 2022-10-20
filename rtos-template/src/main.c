#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"
#include "FreeRTOS.h"
#include "task.h"

int main(void) {
	
	__disable_irq();
	
	HAL_Init();


	__enable_irq();

	vTaskStartScheduler();

        return 0;
}
