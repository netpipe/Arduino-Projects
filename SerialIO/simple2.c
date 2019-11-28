#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

char buffer[256];

void setup() {
    Serial.begin(9600);	// opens serial port, sets data rate to 9600 bps
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
}

void loop() {

	// send data only when you receive data:
	if (Serial.available() > 0) {

	// read the data
        Serial.readBytes(buffer, 256);
               
	// say what you got:
        lcd.print(buffer);

	}

}

