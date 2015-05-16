#include <SoftwareSerial.h>

#define bluetooth Serial1
#define BAUDRATE 115200

// Analog read 0 is pin 38 

int volts = 0;
int FSR_PIN = 0;
int LED = 17;
char Msg[2] ;
char buffer[2] = {'O', 'K'};

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

      bluetooth.write(buffer);
      bluetooth.flush();
      //delay(400);
      digitalWrite(LED, LOW);
  }
  else
  {
      delay(100);
  }

  ///////////////////////////////////////////////////////////
  if(bluetooth.available())  // If the bluetooth sent any characters
  {
    // Send any characters the bluetooth prints to the serial monitor
    int i = 0;
    while(bluetooth.available())
    {
	Msg[i] = (char)bluetooth.read();
        Serial.print((char)Msg[i]);
        i++;
        delay(200);
        if(i > 1) break;
    }
  }
  
  ////////////////////////////////////////////////////////////////
  if(Serial.available())  // If stuff was typed in the serial monitor
  {
    // Send any characters the Serial monitor prints to the bluetooth
    bluetooth.write((char)Serial.read());
    bluetooth.flush();
  }
}
