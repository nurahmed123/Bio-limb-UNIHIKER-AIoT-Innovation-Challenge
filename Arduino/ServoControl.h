/********************************* servoControl.h ********************************************/
#ifndef __SERVO_CONTROL_H__
#define __SERVO_CONTROL_H__

#include "Arduino.h"
#include <Servo.h>

class ServoControl 
{
  private:
  uint8_t _pin;
  public:
  ServoControl();
  bool initializeServoPosition( );
  bool changeServoPosition(  );
  
};

/*********************************************** func init ************************************************/
void armIdlePosition();
void takeCottonBar();
void takeCovidSample();
void sensitiveControll(int channel1, int pos1, int channel2, int pos2, int steps, uint8_t incrementFlag);
void putCottonBarInBox();
void sendBox();
void AttachServos();
void servoControll(int channel, int pos);
#endif
