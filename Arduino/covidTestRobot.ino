/*
   project name: covid test collection robot
   author: team
   date: 29-3-2022
   descryption:



*/

// #define DEBUG_ROBOT_ARM
#define PC

/**************************** initialize library ************************/
#include "CommunicationParser.h"
#include "ServoControl.h"
#include "lcd.h"
#include "pinMapping.h"
#include "config.h"
#include "pulse_sensor.h"

extern uint8_t initialPositionValue[10];
extern bool mouthOpenFlag;
extern bool mouthCloseFlag;
extern bool humanDetectFlag;
extern bool takeCottonBarFlag;

/*************************** object create *****************************/

CommunicationParser communicationParser;



//extern Servo myservo;





void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
#ifdef PC
  Serial1.begin(9600);
#endif
  Serial.println("start");
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  pinMode(13, OUTPUT);
  pulse_sensor_setup();

  AttachServos();

  i2c_lcd_setup();
  show_lcd(0, 0, "System booting.");

#ifdef DEBUG_ROBOT_ARM
  armIdlePosition();
  takeCottonBar();
  takeCovidSample();
  //  sensitiveControll( 3, 165, 2, 125, 30, 0);
  //  delay(3000);
  //  sensitiveControll( 3, 135, 2, 95, 30, 1);
  putCottonBarInBox();
  armIdlePosition();
  //  sendBox();
#endif

  pinMode(pumpPin, OUTPUT);
  pinMode(ultravioletPin, OUTPUT);


  digitalWrite(pumpPin, HIGH);
  digitalWrite(ultravioletPin, LOW);

  delay(500);


  //  while ( !Serial1.available() )
  //  {
  //    show_lcd(0, 1, "waiting for MP" );
  //  }
  //  Serial.flush();
  //
  //  while ( !Serial1.available() )
  //  {
  //    show_lcd(0, 1, "waiting for MP" );
  //  }
  lcdClear();
}

void loop() {
  // put your main code here, to run repeatedly:


  show_lcd(0, 0, "Robot ARM Ready");

  communicationParser.checkSerial();
  if (humanDetectFlag == 1 ) {



    if (mouthCloseFlag == 1 and takeCottonBarFlag == 0) {
      show_lcd(0, 1, "                ");
      show_lcd(0, 1, "place your finger");
      int heart_rate, sp02;
      pulse_sensor_read(&heart_rate, &sp02);
      show_lcd(0, 1, "heart_rate", heart_rate);
      delay(1000);
      show_lcd(0, 1, "sp02", sp02);

      takeCottonBar();
      //takeCovidSample();   ///
      show_lcd(0, 1, "                ");
      show_lcd(0, 1, "PLZ open mouth");
      delay(1000);
      Serial1.flush();
    }

    if (mouthCloseFlag == 1 and takeCottonBarFlag == 1) {
      show_lcd(0, 1, "                ");
      show_lcd(0, 1, "PLZ open mouth");
      delay(1000);
      Serial1.flush();
      // takeCottonBar();
    }
    

    if (mouthOpenFlag == 1 and takeCottonBarFlag == 0) {

      show_lcd(0, 1, "                ");
      show_lcd(0, 1, "PLZ wait");
      takeCottonBar();  ///
      //takeCovidSample();
      Serial1.flush();
    }

    if (mouthOpenFlag == 1 and takeCottonBarFlag == 1) {
      //    takeCovidSample();
      // sensitiveControll(3, 160, 2, 130, 35, 0);
      takeCovidSample();
      // delay(3000);
      // sensitiveControll(3, 160, 2, 130, 35, 0);
      putCottonBarInBox();
      show_lcd(0, 1, "                ");
      show_lcd(0, 1, "Thank You");

      putCottonBarInBox(); image.png
      // sensitiveControll(3, 160, 2, 70, 25, 0);
      // servoControll(4, 80);

      show_lcd(0, 1, "                ");
      show_lcd(0, 1, "you may go");

      // sendBox();
      armIdlePosition();
      delay(200);
      digitalWrite(pumpPin, LOW);
      digitalWrite(ultravioletPin, HIGH);

      show_lcd(0, 1, "                ");
      show_lcd(0, 1, "UV start");
      delay(3000);

      digitalWrite(pumpPin, HIGH);
      digitalWrite(ultravioletPin, LOW);
      show_lcd(0, 1, "                ");
      show_lcd(0, 1, "UV stop");
      delay(1000);

      show_lcd(0, 1, "                ");
      show_lcd(0, 1, "Complete!!");

      delay(1000);

      communicationParser.responseHandle("DONE");

      mouthOpenFlag = 0;
      mouthCloseFlag = 0;
      humanDetectFlag = 0;
      takeCottonBarFlag = 0;
      Serial1.flush();
    } else {
    }
  }
  else{
    armIdlePosition();
    // takeCovidSample();
  }

  delay(200);
}
