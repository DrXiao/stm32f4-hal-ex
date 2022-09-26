# STM32F4XX with FreeRTOS - Semaphore
```shell
make
make flash
screen /dev/ttyUSB0
```

## Demo
* Remember to connect USART1 before using screen.
### With Semaphore
* the 10 tasks will print their string in order.

![](semaphore.gif)

### Without Semaphore
* the behavior may work unnormally as following.
* The demo has been uncommented ```xSemaohoreTake``` and ```xSemaphoreGive``` in ```task``` function.

![](semaphore-err.gif)
