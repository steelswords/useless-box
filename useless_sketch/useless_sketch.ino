#include <Servo.h>

//const int servoArmPin = A6;
//const int servoArmPin = A7;
const int servoArmPin = 5;
//const int servoLidOpenerPin = A6;
const int servoLidOpenerPin = 3;
const int inputTooFarSwitchPin = 2;
const int inputOnSwitchPin = 7;
const int SWITCH_ACTIVATED = LOW;


const int lidClosedUsValue = 2300;
const int lidOpenedUsValue = 1550;
const int armExtendedUsValue = 2080;
const int armRetractedUsValue = 600;

Servo arm;
Servo lidOpener;

inline bool isSwitchOn()
{
  return digitalRead(inputOnSwitchPin) == SWITCH_ACTIVATED;
}

inline bool isSwitchOverextended()
{
  return digitalRead(inputTooFarSwitchPin) == SWITCH_ACTIVATED;
}

void openLidFully()
{
  lidOpener.writeMicroseconds(1500);
}


// Turns off switch
void extendArm()
{
  arm.writeMicroseconds(1500);
}

void setup()
{
  Serial.begin(9600);
  pinMode(inputOnSwitchPin, INPUT);
  pinMode(inputTooFarSwitchPin, INPUT);
  arm.attach(servoArmPin);
  //arm.attach(D8);
  lidOpener.attach(servoLidOpenerPin);

  // Set up the ISR for the button
  // TODO: Redo
  attachInterrupt(digitalPinToInterrupt(inputOnSwitchPin), handleSwitch, CHANGE);
}

void handleSwitch()
{
  bool isSwitchOn = (digitalRead(inputOnSwitchPin) == SWITCH_ACTIVATED);
  if (isSwitchOn)
    Serial.println("Close that lid!");
  else
    Serial.println("Done");
}

void loop()
{
  int writeValue = Serial.parseInt();
  if (0 != writeValue)
  {
    Serial.println("Writing " + String(writeValue) + " to servos");
    lidOpener.writeMicroseconds(writeValue);
    arm.writeMicroseconds(writeValue);
  }
#if 0
  while (isSwitchOn())
  {
    openLid();
    extendArm();
  }
  #endif
  

  //Serial.println("Button: " + String(digitalRead(inputCloseSwitchPin)));

#if 0
  Serial.println("Looping...");
  Serial.println("1500");
  arm.writeMicroseconds(1500);
  delay(1000);
  Serial.println("2800");
  Serial.println("Button: " + String(digitalRead(inputCloseSwitchPin)));
  arm.writeMicroseconds(2800);
  delay(1000);
  #endif
  #if 0
  //arm.write(0);
  //lidOpener.write(0);
  delay(1000);
  arm.write(90);
  lidOpener.write(90);
  delay(1000);
  arm.write(180);
  lidOpener.write(180);
  delay(1000);
  #endif
}
