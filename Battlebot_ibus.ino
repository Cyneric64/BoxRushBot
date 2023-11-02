#include "IBusBM.h"

IBusBM IBus;

/* Motor controller pinouts.
    uses one PWM signal for forward and another for reverse on each motor. 
*/
const int LED_PIN = 5;
const int MOTOR_1_FORWARD = 9;
const int MOTOR_1_REVERSE = 3;
const int MOTOR_2_FORWARD = 10;
const int MOTOR_2_REVERSE = 11;

void setup() {
  /* Begin the SBUS communication */
  IBus.begin(Serial);
  while(IBus.cnt_rec == 0){
    FlashLED();
  }
}

void loop () {
    double rawAxial = 0;
    rawAxial = IBus.readChannel(0)-172;
    int axial = (((rawAxial/(1811-172))*2-1)*255);

    double rawYaw = 0;
    rawYaw = IBus.readChannel(1)-172;
    int yaw = (((rawYaw/(1811-172))*2-1)*255);

    int leftMotorPower = axial+yaw;
    int rightMotorPower = axial-yaw;
  /*
    analogWrite(MOTOR_1_FORWARD, max(0, leftMotorPower*-1));
    analogWrite(MOTOR_1_REVERSE, max(0, leftMotorPower));
    analogWrite(MOTOR_2_FORWARD, max(0, rightMotorPower*-1));
    analogWrite(MOTOR_2_REVERSE, max(0, rightMotorPower));
  */
    analogWrite(MOTOR_1_FORWARD, max(0, leftMotorPower*-1));
    analogWrite(MOTOR_1_REVERSE, max(0, 0));
    analogWrite(MOTOR_2_FORWARD, max(0, 0));
    analogWrite(MOTOR_2_REVERSE, max(0, 0));
  
}

void FlashLED(){
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
  delay(100);
}
