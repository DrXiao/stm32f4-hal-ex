# STM32F4XX - UART with Interrupt
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
* Press keyboard after using screen, and then STM32 becomes a typewriter
* The behaviors of receiving and sending are based on interrupt.

![](uart-it.gif)
