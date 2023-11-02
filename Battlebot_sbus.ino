#include "sbus.h"

/* SBUS object, reading SBUS */
bfs::SbusRx sbus_rx(&Serial);
/* SBUS data */
bfs::SbusData data;

/* Motor controller pinouts.
    uses one PWM signal for forward and another for reverse on each motor. 
*/
const int MOTOR_1_FORWARD = 9;
const int MOTOR_1_REVERSE = 3;
const int MOTOR_2_FORWARD = 10;
const int MOTOR_2_REVERSE = 11;

void setup() {
  /* Begin the SBUS communication */
  sbus_rx.Begin();
}

void loop () {
  if(sbus_rx.Read()){
    data = sbus_rx.data();
    double rawAxial = 0;
    rawAxial = data.ch[0]-172; // default channel range is 172-1811, change to 0-
    int axial = (((rawAxial/(1811-172))*2-1)*255);

    double rawYaw = 0;
    rawYaw = data.ch[1]-172;
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
  
}
