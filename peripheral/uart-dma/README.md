# STM32F4XX - UART with DMA
```shell
make
make flash
screen /dev/ttyUSB0
```

## Demo
* PA9 and PA10 and GND should be connected to USB-to-TTL module (ch340 or cp2102).
	* PA9  (TX) <---> RX
	* PA10 (RX) <---> TX 
	* GND       <---> GND
* Reset STM32 after using screen, and the string ```"Hello"``` will be printed by DMA

![](uart-dma.gif)
