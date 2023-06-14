// pre setup - thermocouple
#include <SPI.h>
#include "Adafruit_MAX31855.h"
// Example creating a thermocouple instance with software SPI on any three
// digital IO pins.
#define MAXDO   12
#define MAXCS   11
#define MAXCLK  10

// initialize the Thermocouple
Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) delay(1); // wait for Serial on Leonardo/Zero, etc
  Serial.println("MAX31855 test");
  // wait for MAX chip to stabilize
  delay(500);
  Serial.print("Initializing sensor...");
  if (!thermocouple.begin()) {
    Serial.println("ERROR.");
    while (1) delay(10);
  }
  Serial.println("DONE.");
}

void loop() {
  // read thermocouple
  // basic readout test, just print the current temp
  Serial.print("Internal Temp = ");
  double int_temp = thermocouple.readInternal();
  Serial.println(int_temp);

  double c = thermocouple.readCelsius();
  if (isnan(c)) {
    Serial.println("Something wrong with thermocouple!");
  } else {
    Serial.print("C (Decimal) = ");
    Serial.println(c);
    Serial.print("C (Binary) = ");
    Serial.println(floatToBinary(c));
  }

  delay(1000);
}

String floatToBinary(float value) {
  byte *ptr = (byte *)&value;
  String binaryString = "";
  for (int i = sizeof(float) - 1; i >= 0; i--) {
    for (int j = 7; j >= 0; j--) {
      binaryString += (*ptr >> j) & 1 ? '1' : '0';
    }
    ptr++;
  }
  return binaryString;
}
