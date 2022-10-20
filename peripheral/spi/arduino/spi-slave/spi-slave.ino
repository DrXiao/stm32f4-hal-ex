# include <SPI.h>
char str[50] = "";
volatile byte i;
volatile bool pin;

void setup(void) {
    Serial.begin (9600);        // set baud rate to 115200 for usart
    Serial.println("Hello I'm SPI UNO_SLAVE");
    pinMode(MISO, OUTPUT);      // have to send on Master in so it set as output
    SPCR |= _BV(SPE);           // turn on SPI in slave mode
    i = 0; // buffer empty
    pin = false;
    SPI.attachInterrupt();      // turn on interrupt
}

void loop(void) {
    static int count = 0;
    if (pin) {
        SPI.detachInterrupt();
        count++;
        Serial.print(count);
        Serial.print(" : ");
      
        Serial.println(str); //print the array on serial monitor
      
        i= 0;           //reset button to zero
        pin = false;    //reset the pin
        SPI.attachInterrupt();
    }
}

// Interrupt function
ISR (SPI_STC_vect) {
    char c = SPDR;          // read byte from SPI Data Register
    if (i < sizeof(str)) {
        str [i++] = c;        // save data in the next index in the array buff
        if ( (c == '\n') ) {  //check for the end of the word
            pin = true;
            str[i++] = '\0';
        }
    }
}
