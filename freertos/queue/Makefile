#======================================================================#
#Project Configuration
SRC_DIR=./src
INC_DIR=./include
STM=stm32f407xx
PERIPH=tim tim_ex rcc rcc_ex flash flash_ex flash_ramfunc \
	gpio dma dma_ex pwr pwr_ex cortex exti uart
ARCH=CM4F
FREERTOS=./lib/FreeRTOS
FREERTOS_INC=$(FREERTOS)/Source/include \
		$(FREERTOS)/Source/portable/GCC/ARM_$(ARCH)
FREERTOS_SRC=$(FREERTOS)/Source/croutine.c \
		$(FREERTOS)/Source/list.c \
		$(FREERTOS)/Source/queue.c \
		$(FREERTOS)/Source/tasks.c \
		$(FREERTOS)/Source/timers.c \
		$(FREERTOS)/Source/portable/MemMang/heap_4.c \
		$(FREERTOS)/Source/portable/GCC/ARM_$(ARCH)/port.c

#======================================================================#
#Output files
EXECUTABLE=stm32_executable.elf
BIN_IMAGE=stm32_bin_image.bin

#======================================================================#
#Cross Compiler
CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

#======================================================================#
#Flags
CFLAGS=-g -mlittle-endian -mthumb \
	-mcpu=cortex-m4 \
	-mfpu=fpv4-sp-d16 -mfloat-abi=hard \
	--specs=nano.specs \
	--specs=nosys.specs
CFLAGS+=-D USE_HAL_DRIVER
CFLAGS+=-D STM32F407xx \
        -D ARM_MATH_CM4
CFLAGS+=-I./


#stm32-flash
CFLAGS+=-Wl,-T,stm32_flash.ld

#======================================================================#
#lib

#Project libraries
CFLAGS+=-I./$(INC_DIR)

#Stm32 libraries
ST_LIB=./lib/STM32F4xx_HAL_Driver
CFLAGS+=-I./lib/CMSIS/Device/ST/STM32F4xx/Include

#CMSIS libraries
CFLAGS+=-I./lib/CMSIS/Include

#HAL includes
CFLAGS+=-I$(ST_LIB)/Inc
CFLAGS+=-I$(ST_LIB)/Inc/Legacy

#FreeRTOS includes
CFLAGS+=$(foreach rtos_inc, $(FREERTOS_INC), -I$(rtos_inc))

#======================================================================#
#Source code
HAL_PERIPH=$(foreach periph, $(PERIPH), ./lib/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_$(periph).c)

#HAL
SRC=./lib/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c \
	./lib/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \

SRC+=$(HAL_PERIPH)

#FreeRTOS
SRC+=$(FREERTOS_SRC)

#Major programs
SRC+=$(wildcard $(SRC_DIR)/*.c)

#======================================================================#
#STM32 startup file
STARTUP=./lib/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_$(STM).s

#======================================================================#
#Make rules

#Make all
all:$(BIN_IMAGE)

$(BIN_IMAGE):$(EXECUTABLE)
	$(OBJCOPY) -O binary $^ $@

STARTUP_OBJ = startup_$(STM).o

$(STARTUP_OBJ): $(STARTUP) 
	$(CC) $(CFLAGS) $^ -c $(STARTUP)

$(EXECUTABLE):$(SRC) $(STARTUP_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

#Make clean
clean:
	rm -rf $(EXECUTABLE)
	rm -rf $(BIN_IMAGE)
	rm -rf $(STARTUP_OBJ)

#Make flash
flash:
	st-flash write $(BIN_IMAGE) 0x8000000

#Make debug
debug: 
	screen -c config/screenrc

#======================================================================
.PHONY:all clean flash
