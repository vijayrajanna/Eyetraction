#include <SoftwareSerial.h>


#define bluetooth Serial1
//Some globals
const int MOTORS = 4;
int LEVEL = 0;
char Msg[8];
int pCount = 0;
int dAmount = 0;

void setup() {
  //Set baud rate
  Serial.begin(115200);
  bluetooth.begin(115200);
  //Define whether pins are input or output
  Serial.println("End of Setup");
}

void loop() {
  //Serial.print("TEST");

   if(bluetooth.available())  // If the bluetooth sent any characters
  {
    // Send any characters the bluetooth prints to the serial monitor
    
    int i = 0;
    while(bluetooth.available())
    {
	Msg[i] = (char)bluetooth.read();
        Serial.print(Msg[i]);
        ++i;
        if (i > 7)
          break;
        delay(100);
    }
    Serial.println(' ');
   if (Msg[0] == 'o' && Msg[1] == 'n') {
     int tmp = LEVEL;   
     Serial.println("Turn on Motors");
     pulse(pCount);
    }
    else if(Msg[0] == 'o' && Msg[1] == 'f' && Msg[2] == 'f'){
	analogWrite(MOTORS, 0);
        Serial.println("Turn off Motors");
    }
    else if (Msg[0] == 'l' && Msg[1] == 'v' && Msg[2] == 'l') {
	//Change motor level
	LEVEL = (int)Msg[3] - 48;
        Serial.println("Set motor level");
        Serial.println(LEVEL);
        Serial.println("------");
     }
     else if (Msg[0] == 'd')
     {
      int hundreds = int(Msg[1]) - 48;
      int tens = int(Msg[2])-48;
      int ones = int(Msg[3])-48;
      int tmp = (hundreds * 100)+(tens*10)+ones;
      Serial.println(tmp);
      dAmount = tmp;
      Serial.println("Set delay level");
      Serial.println(dAmount);
      Serial.println("---------------");
     }
     else if (Msg[0]=='p')
     {
        int tmp = int(Msg[1]);
        pCount = tmp - 48;
       Serial.println("Set pulse count");
       Serial.println(pCount);
       Serial.println("----------------");
     }
  } 
  if(Serial.available())  // If stuff was typed in the serial monitor
  {
    // Send any characters the Serial monitor prints to the bluetooth
    bluetooth.write((char)Serial.read());
    bluetooth.flush();
  }
}

void pulse(int pulses)
{
    int tmp = LEVEL;
    Serial.println("DELAY");
    Serial.println(dAmount);
    if (pCount < 1)  //We just want it always on
    {
       analogWrite(MOTORS, (255 - (255/(tmp+1))) );
       return;
    }
      int i = 0;
      for (i = 0; i < pCount; ++i)
      {
        Serial.println("Turning Motor On");
        analogWrite(MOTORS, (255 - (255/(tmp+1))) );
         delay(dAmount);
         Serial.println("Turning Motor Off");
         analogWrite(MOTORS, 0);
         delay(dAmount);
      }
}
boolean isDigit(char c)
{
 if (c >= '0' && c <= '9')
    return true;
 return false; 
}
