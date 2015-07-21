#include <SoftwareSerial.h>

#define bluetooth Serial1
#define BAUDRATE 9600

// Analog read 0 is pin 38 
int volts = 0;
int FSR_PIN = 0;
int LED = 17;

char toPrint = '\0';
bool sent = false;
char state = ' ';

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  Serial.begin(BAUDRATE);
  bluetooth.begin(BAUDRATE);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  volts = analogRead(FSR_PIN);

  if(volts > 500)
  {
      //Serial.println("HIGH");
      digitalWrite(LED, HIGH);
      bluetooth.write(state);
      bluetooth.flush();
      sent = true;
      digitalWrite(LED, LOW);
  }
  else
  {
      delay(100);
  }

  ///////////////////////////////////////////////////////////
  if((bluetooth.available()) && (sent == true))
  {
        Serial.println("printing : ");
        toPrint = (char)bluetooth.read();
        Serial.println((char)toPrint);
        sent = false;
   }
}
 
