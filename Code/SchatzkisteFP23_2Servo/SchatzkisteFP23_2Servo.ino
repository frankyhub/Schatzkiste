
/************************************************************************************************* 
                                      PROGRAMMINFO
************************************************************************************************** 
Funktion: Schatzkiste

Mit diesem Projekt wird eine Schatzkiste gebaut, die sich mit dem Betätigen von vier Tasten in der 
richtigen Reihenfolge öffnen lässt. Wird eine Taste betätigt, leuchtet die darüber liegende LED. 
Ist der Tasten-Code richtig eingegeben, gehen die vier weißen LEDs über den Tasten aus, eine grüne 
LED leuchtet und der Servo-Motor öffnet den Verschluss. Ist die Schatzkiste geöffnet, kann mit jeder 
beliebigen Taste die Schatzkiste wieder verschlossen werden. Ist der Code falsch eingegeben, erlöschen 
die vier LEDS und die Schatzkiste bleibt verschlossen.
Im inneren der Schatzkiste ist ein Reed-Kontakt versteckt. Nur der Eigentümer der Schatzkiste weiß, 
wo sich der Reed-Kontakt befindet. Wird an diesen Reed-Kontakt ein Magnet gehalten, blinken die vier 
Taster-LEDs und der Code kann neu programmiert werden. Nach erfolgreicher Programmierung blinken die 
vier Taster-LEDs erneut. Der Code wird in das EEPROM des NANO geladen, so dass auch bei Spannungsausfall 
der Code erhalten bleibt.
**************************************************************************************************
*Die Hardware für die Schatzkiste
1 x NANO
2 x Servo Motor SG90
1 x Reed-Kontakt mit Magnet
4 x Taster
4 x LEDs weiß
1 x LED grün
1 x 9V Batterie
1 x 9V Batterie-Clip
1 x Gelaserte Schatzkiste (4mm Sperrholz 600x300)
**************************************************************************************************
*Version: 30.01.2023
**************************************************************************************************
Board: NANO
**************************************************************************************************
C++ Arduino IDE V1.8.13
**************************************************************************************************
Einstellungen:
https://dl.espressif.com/dl/package_esp32_index.json
http://dan.drown.org/stm32duino/package_STM32duino_index.json
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json
**************************************************************************************************
Librarys
- Servo.h  V 1.1.6
- EEPROM.h V 1.1.0
**************************************************************************************************
 */
#define PIN_LED_1         A0  //LED 1 
#define PIN_LED_2         A2  //LED 2  
#define PIN_LED_3         A4  //LED 3
#define PIN_LED_4         A5  //LED 4
#define PIN_BUTTON_1      4   //S1
#define PIN_BUTTON_2      5   //S2
#define PIN_BUTTON_3      6   //S3
#define PIN_BUTTON_4      7   //S4
#define PIN_LED_SUCCESS   8   //LED Code OK
#define PIN_SERVO1        9   //Servo1 rechts
#define PIN_SERVO2        10  //Servo2 links
#define PIN_REED_1        11  //S5 Reed-Relais


#include <Servo.h>  
#include <EEPROM.h> 

bool isDoorOpen, openDoor, buttonPressed[4];
byte buttons[4] = {PIN_BUTTON_1, PIN_BUTTON_2, PIN_BUTTON_3, PIN_BUTTON_4};
byte leds[4] = {PIN_LED_1, PIN_LED_2, PIN_LED_3, PIN_LED_4}, doorCode[4];
Servo servoMotor1;
Servo servoMotor2;

void setup()
{
  Serial.begin(115200);
  Serial.print("Init...");
  pinMode(PIN_REED_1, INPUT_PULLUP);
//  pinMode(PIN_REED_2, INPUT_PULLUP);

  pinMode(PIN_LED_SUCCESS, OUTPUT);
  digitalWrite(PIN_LED_SUCCESS, LOW);

  for (byte i = 0; i < sizeof(leds); i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(buttons[i], INPUT_PULLUP);
    buttonPressed[i] = false;
  }

  blinkLEDs();
  servoMotor1.attach(PIN_SERVO1);
  servoMotor1.write(0);
  servoMotor2.attach(PIN_SERVO2);
  servoMotor2.write(90);
  
  isDoorOpen = false;

  EEPROM.get(0, doorCode);
  Serial.println("ok");

  printDoorCode();
}

void loop()
{
  checkCode();
    if (digitalRead(PIN_REED_1) == LOW) {
// if (digitalRead(PIN_REED_1) == LOW && digitalRead(PIN_REED_2) == LOW) {
  Serial.print("Reste Code");
    resetCode();
  }
  checkDoor();
}

void checkCode()
{
  static byte foundOffset = 0, pressOffset = 0, currentState;
  openDoor = false;

  for (byte i = 0; i < sizeof(buttons); i++) {
    currentState = digitalRead(buttons[i]);
    if (!buttonPressed[i] && currentState == LOW) {
      digitalWrite(leds[i], HIGH);
      buttonPressed[i] = true;
      pressOffset++;
      if (doorCode[foundOffset] == i) {
        foundOffset++;
      }
    }
  }

  if (foundOffset >= 4) {
    openDoor = true;
    pressOffset = 0;
    foundOffset = 0;
    delay(200);
  } else {
    if (pressOffset >= 4) {
      pressOffset = 0;
      foundOffset = 0;
      for (byte i = 0; i < sizeof(buttons); i++) {
        delay(200);
        buttonPressed[i] = false;
        digitalWrite(leds[i], LOW);
      }
    }
  }
}

void checkDoor()
{
  if (!isDoorOpen) {
    if (openDoor) {
      digitalWrite(PIN_LED_SUCCESS, HIGH);
      for (byte i = 0; i < sizeof(leds); i++) {
        digitalWrite(leds[i], LOW);
      }
      delay(500);
      servoMotor1.write(90);
      servoMotor2.write(0);
      isDoorOpen = true;

      delay(1000);
      while (openDoor == true) {
        for (byte i = 0; i < sizeof(buttons); i++) {
          if (digitalRead(buttons[i]) == LOW) {
            openDoor = false;
            break;
          }
        }
      }
    }
  } else {
    if (!openDoor) {
      digitalWrite(PIN_LED_SUCCESS, LOW);
      for (byte i = 0; i < sizeof(leds); i++) {
        buttonPressed[i] = false;
        digitalWrite(leds[i], LOW);
      }
      servoMotor1.write(0);
      servoMotor2.write(90);
      isDoorOpen = false;
      delay(2000);
    }
  }
}

void resetCode()
{
  servoMotor1.write(90);
  servoMotor2.write(0);
  for (byte i = 0; i < sizeof(doorCode); i++) {
    doorCode[i] = 255;
  }
  blinkLEDs();
  openDoor = false;
  isDoorOpen = false;
  bool isExisting = false;
  byte offset = 0;
  do {
    for (byte i = 0; i < sizeof(buttons); i++) {
      isExisting = false;
      if (digitalRead(buttons[i]) == LOW && doorCode[offset] == 255) {
        for (byte j = 0; j < sizeof(doorCode); j++) {
          if (doorCode[j] == i) {
            isExisting = true;
          }
        }
        if (!isExisting) {
          digitalWrite(leds[i], HIGH);
          doorCode[offset] = i;
          offset++;
        }
      }
    }
  } while (offset < 4);

  printDoorCode();
  EEPROM.put(0, doorCode); // writing code to EEPROM
  servoMotor1.write(0);
  servoMotor2.write(90);
  blinkLEDs();
}

void blinkLEDs()
{
  for (byte j = 0; j < 9; j++) {
    for (byte i = 0; i < sizeof(leds); i++) {
      digitalWrite(leds[i], j % 2);
      delay(40);
    }
  }
}

void printDoorCode()
{
  Serial.println("Code:");
  for (byte i = 0; i < sizeof(doorCode); i++) {
    Serial.print(" ");
    Serial.print(doorCode[i]);
      Serial.println();
  }
}
