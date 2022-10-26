#include "stm32f4xx_hal.h"

/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void){
	while (1) {
	}
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void) {
	while (1) {
	}
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void) {
	while (1) {
	}
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void){
	while (1) {
	}
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void) {
	while (1) {
	}
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void) {

}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void) {

}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void) {

}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void) {
  	HAL_IncTick();
}

extern TIM_HandleTypeDef hal_tim6;
void TIM6_DAC_IRQHandler(void) {
	HAL_TIM_IRQHandler(&hal_tim6);
}