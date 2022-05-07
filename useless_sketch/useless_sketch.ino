#include <Servo.h>

const int servoPin = A3;
const int inputSwitchPin = 2;
const int SWITCH_ACTIVATED = LOW;
Servo arm;

void setup()
{
  Serial.begin(9600);
  pinMode(inputSwitchPin, INPUT_PULLUP);
  arm.attach(servoPin);

  // Set up the ISR for the button
  attachInterrupt(digitalPinToInterrupt(inputSwitchPin), handleSwitch, CHANGE);
}

void handleSwitch()
{
  bool isSwitchOn = (digitalRead(inputSwitchPin) == SWITCH_ACTIVATED);
  if (isSwitchOn)
    Serial.println("Button");  
  else
    Serial.println("Done");
}

void loop()
{
  arm.write(0);
  delay(1000);
  arm.write(90);
  delay(1000);
  arm.write(180);
  delay(1000);
}
