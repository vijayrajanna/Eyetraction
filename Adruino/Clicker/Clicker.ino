#include <SoftwareSerial.h>

#define bluetooth Serial1
#define BAUDRATE 9600

// Analog read 0 is pin 38 
int volts = 0;
int FSR_PIN = 0;
int LED = 17;

char toPrint;
bool sent = false;

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
      bluetooth.clear();
      bluetooth.println('p');
      sent = true;
      digitalWrite(LED, LOW);
  }
  else
  {
    bluetooth.clear();
    Serial.println(bluetooth.available());
    sent = false;
    delay(100);
  }

  if((bluetooth.available()) && (sent == true))
  {
      Serial.println(bluetooth.available());
      bluetooth.clear();
      delay(100);
      sent = false;
   }
}
 
