#include <SoftwareSerial.h>

#define bluetooth Serial1
#define BAUDRATE 9600

// Analog read 0 is pin 38 

int volts = 0;
int FSR_PIN = 0;
int LED = 17;
char Msg[2] ;
char toPrint ;
bool sent = false;
char buffer[2] = {'O', 'K'};

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  Serial.begin(BAUDRATE);
  bluetooth.begin(BAUDRATE);

  /*pinMode(LED, OUTPUT);
  Serial.begin(9600);  // Begin the serial monitor at 9600bps
  bluetooth.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  bluetooth.print("$");  // Print three times individually
  bluetooth.print("$");
  bluetooth.print("$");  // Enter command mode
  delay(100);  // Short delay, wait for the Mate to send back CMD
  bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth.begin(9600);  // Start bluetooth serial at 9600*/
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
      sent = true;
      delay(400);
      digitalWrite(LED, LOW);
  }
  else
  {
      //bluetooth.write(buffer);
      //bluetooth.flush();  
      delay(100);
  }

  ///////////////////////////////////////////////////////////
  if(bluetooth.available())  // If the bluetooth sent any characters
  {
    // Send any characters the bluetooth prints to the serial monitor
    int i = 0;
    while(bluetooth.available() && (sent == true))
    {
	toPrint = (char)bluetooth.read();
        Serial.print((char)toPrint);
        i++;
        delay(200);
        if(i > 1) 
        {
          sent = false;
          break;
        }
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
