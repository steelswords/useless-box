#include <Servo.h>

const int servoArmPin = 3;
const int servoLidOpenerPin = 5;
const int inputTooFarSwitchPin = 7;
const int inputOnSwitchPin = 2;
const int SWITCH_ACTIVATED = HIGH;

const int lidClosedUsValue = 2300;
const int lidOpenedUsValue = 1550;
const int armExtendedUsValue = 2080;
const int armRetractedUsValue = 400;

const int delayLidCloseMs = 200;

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
  lidOpener.writeMicroseconds(lidOpenedUsValue);
}

void closeLidFully()
{
  lidOpener.writeMicroseconds(lidClosedUsValue);
}

// Turns off switch
void extendArm()
{
  arm.writeMicroseconds(armExtendedUsValue);
}

void retractArm()
{
  arm.writeMicroseconds(armRetractedUsValue);
  Serial.println("Writing " + String(armRetractedUsValue) + " to arm");
}

void handleSwitch()
{
  if (isSwitchOn())
    Serial.println("Close that lid!");
  else
    Serial.println("Done");
  delay(50);
}


void setup()
{
  Serial.begin(9600);
  pinMode(inputOnSwitchPin, INPUT);
  pinMode(inputTooFarSwitchPin, INPUT);
  arm.attach(servoArmPin);
  lidOpener.attach(servoLidOpenerPin);
  closeLidFully();
  retractArm();

  // Set up the ISR for the button
  // TODO: Redo
  //attachInterrupt(digitalPinToInterrupt(inputOnSwitchPin), handleSwitch, CHANGE);
}

void printState()
{
  Serial.println("isSwitchOn() = " + String(isSwitchOn()));
  Serial.println("isSwitchOverextended() = " + String(isSwitchOverextended()));
}


void loop()
{
// Polling method
#if 1
  printState();
  while (isSwitchOn())
  {
    Serial.println("Closing that **** switch!");
    openLidFully();
    delay(400); // For sassiness
    extendArm();
  }
  Serial.println("Done!");
  delay(100);
  retractArm();
  delay(delayLidCloseMs);
  closeLidFully();
#endif

// For calibrating servo values
#if 0
  int writeValue = Serial.parseInt();
  if (0 != writeValue)
  {
    Serial.println("Writing " + String(writeValue) + " to servos");
    lidOpener.writeMicroseconds(writeValue);
    arm.writeMicroseconds(writeValue);
  }
#endif
}
