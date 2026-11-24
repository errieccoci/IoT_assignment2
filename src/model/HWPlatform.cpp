#include "model/HWPlatform.h"
#include "devices/ButtonImpl.h"
#include "config.h"
#include "devices/Led.h"
#include "devices/ServoMotorImpl.h"

void wakeUp(){}

HWPlatform::HWPlatform(){
  startButton = new ButtonImpl(BT_START);
  stopButton = new ButtonImpl(BT_STOP);
  resetButton = new ButtonImpl(BT_RESET);

  greenLed = new Led(GREEN_PIN);
  redLed = new Led(RED_PIN);

  screen = new LCDScreen();
  servoMotor = new ServoMotorImpl(SERVO_PIN);
  pot = new Potentiometer(POT_PIN);
  temp = new TempSensorLM35(TEMP_PIN);
  sonar = new Sonar(SONAR_ECHO_PIN, SONAR_TRG_PIN, 10000);
  sonar->setTemperature(temp->getTemperature());
}


void HWPlatform::init(){
}

void HWPlatform::test(){
}

Button* HWPlatform::getButtonStart() {
  return startButton;
}
Button* HWPlatform::getButtonReset() {
  return resetButton;
}

Button* HWPlatform::getButtonStop() {
  return stopButton;
}

Sonar* HWPlatform::getSonarSensor() {
  return sonar;
}

Led*  HWPlatform::getRedLed() {
  return redLed;
}

Led* HWPlatform::getGreenLed() {
  return greenLed;
}

LCDScreen* HWPlatform::getLCDScreen() {
  return screen;
}

ServoMotor* HWPlatform::getMotor() {
  return servoMotor;
}

Potentiometer* HWPlatform::getPot() {
  return pot;
}

