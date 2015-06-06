#include <SoftwareSerial.h>

#define bluetooth Serial1

void setup() {
    bluetooth.begin(9600); 
    Serial.begin(9600);
    delay(50);
}

void loop() {
    if (Serial.available())
    {
      bluetooth.write("HIGH"); // echo everything
      bluetooth.flush();
      Serial.println("HIGH");
    }
    delay(100);
}
