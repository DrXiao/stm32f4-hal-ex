#include <Wire.h>

void setup(){
    Wire.begin(0x8);                // Set address 0x8.
    Wire.onReceive(receiveEvent);   // Set callback function for I2C slave.
    Serial.begin(9600);
    Serial.println("Init I2C");
}

void loop(){
    delay(100);                     // Delay 0.1 s.
}

void receiveEvent(int numBytes){
    while(Wire.available()){ 
        char c = Wire.read();       // Read each byte and print it.
        Serial.print(c); 
    }
}
