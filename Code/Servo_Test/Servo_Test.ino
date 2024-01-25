/*************************************************************************************************
                                      PROGRAMMINFO
**************************************************************************************************
  Funktion: Schatzkiste Servo Test
          Die Servos müssen sich zum öffnen der Schazkiste entgegengesetzt bewegen

  Servo links D9
  Servo rechte D10
  Taster  D7 betätigt/geschlossen => GND, 

**************************************************************************************************
  Version: 28.01.2023
**************************************************************************************************
  Board: NANO 1.6.21
**************************************************************************************************
  Libraries:
  https://github.com/espressif/arduino-esp32/tree/master/libraries
  C:\Users\User\Documents\Arduino
  D:\gittemp\Arduino II\A156_Wetterdaten_V3
**************************************************************************************************
  C++ Arduino IDE V1.8.19

**************************************************************************************************
  Einstellungen:
  https://dl.espressif.com/dl/package_esp32_index.json
  http://dan.drown.org/stm32duino/package_STM32duino_index.json
  http://arduino.esp8266.com/stable/package_esp8266com_index.json
**************************************************************************************************/
#include <Servo.h>

Servo myservo_li; //Servo links
Servo myservo_re; //Servo rechts

int pos = 0;
int button = 7;  //button = LOW -> Schatzkiste zu


void setup()
{
  myservo_li.attach(9);  // Servo links
  myservo_re.attach(10);  // Servo rechts
  pinMode(pos, OUTPUT);
  pinMode(button, INPUT);

  digitalWrite (button, HIGH);
}

void loop()
{
//******* Servo links ********************
  if (digitalRead(button) == LOW)
    for (pos = 0; pos < 90; pos += 90)
    {
      myservo_li.write(pos);
    }
  if (digitalRead(button) == HIGH)
    for (pos = 90; pos >= 90; pos -= 90)
    {
      myservo_li.write(pos);
      delay(50);
    }
//******* Servo rechts ********************
  for (pos = 90; pos >= 90; pos -= 90)
  {
    myservo_re.write(pos);
  }
  if (digitalRead(button) == HIGH)
    for (pos = 0; pos < 90; pos += 90)
    {
      myservo_re.write(pos);
      delay(50);
    }
}
