
if [ $# -ne 1 ]; then
        echo "usage: $0 <HAL peripheral source file>"
        exit 1
fi

vim lib/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_$1.c
