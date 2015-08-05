#include <SoftwareSerial.h>

#define bluetooth Serial1
#define BAUDRATE 9600

// Analog read 0 is pin 38
int volts = 0;
int FSR_PIN = 0;
int LED = 17;

char toSend = '1';
void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  Serial.begin(BAUDRATE);
  bluetooth.begin(BAUDRATE);
}

void loop() {

  // put your main code here, to run repeatedly:
   char incomingByte;
   volts = analogRead(FSR_PIN);
  if((volts > 500) )
  {
      digitalWrite(LED, HIGH);
      bluetooth.print(toSend);
      digitalWrite(LED, LOW);
  }
}
