import serial


if __name__ == "__main__":
	COM_PORT = "/dev/ttyUSB0"
	BAUD_RATE = 9600

	stm32_serial = serial.Serial(COM_PORT, BAUD_RATE)
	
	
	stm32_serial.write(b"world\r\n")
	print(stm32_serial.read(7))
