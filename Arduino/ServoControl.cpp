/**************************** servoControl.cpp ************************************/


#include "ServoControl.h"
bool takeCottonBarFlag = 0;
uint8_t delayTime = 40;


Servo servos[5];


/****************************************** servo position init ******************************************/
int servoCount = 5;
int servoPins[] = {3, 4, 5, 6, 7};
int servosValue[] = {90, 85, 120, 80, 90};


int armIdlePositionArr[][2] = { {0, 90}, {1, 90}, {2, 90}, {3, 90}, {4, 98} } ;
int takeCottonBarArr[][2] = { {0, 178}, {4, 40}, {1, 80}, {2, 0}, {3, 55}, {4, 98}, {3, 90}, {2, 90}, {1, 90}, {0, 90}, };  //   {2, 175}, {3, 165};
//int takeCovidSampleArr[][2] = { {0, 100}, {1, 70}, {3, 150}, {2, 100}, {2, 98}, {3, 148}, {2, 96}, {3, 146}, {2, 94}, {3, 144} };
int takeCovidSampleArr[][2] = { {0, 90}, {1, 90}, {3, 130}, {2, 65}, {3, 80}, {3, 120}, {2, 90} };

//int putCottonBarInBoxArr[][2] = {{0, 0}, {1, 70}, {2, 45}, {3, 150}, {4, 80} }; //orginal
int putCottonBarInBoxArr[][2] = {{0, 163}, {1, 75}, {3, 30}, {2, 25}, {4, 40}, {4, 98}, {3, 90}, {2, 90}, {1, 90}, {0, 90} };

//int sendBoxArr[][2] = {{0, 0}, {1, 70}, {2, 10}, {3, 120}, {0, 5}, {4, 130}, {2, 60}, {0, 40}, {2, 15}, {4, 80}, {2, 90}, {0, 90} };

int sendBoxArr[][2] = {{4, 120}, {0, 40}, {1, 70}, {2, 30}, {3, 120}, {0, 23}, {2, 25}, {3, 110}, {2, 20}, {2, 40}, {0, 20}, {2, 20}, {2, 45}, {4, 80}, {0, 11}, {2, 23}, {4, 125}, {0, 0}, {2, 55}, {0, 20}, {3, 110}, {2, 35}, {4, 80}, {2, 130} };








void AttachServos() {
  for (int i = 0; i < servoCount; i++)
  {
    servos[i].attach(servoPins[i]);
  }
}



void sensitiveControll(int channel1, int pos1, int channel2, int pos2, int steps, uint8_t incrementFlag)
{
  Serial.println("sensitiveControll");
  for ( int i = 0; i < steps; i++ )
  {
    if ( incrementFlag == 1)
    {
      pos1++;
      pos2++;
    }
    else if( incrementFlag == 0 )
    {
      pos1--;
      pos2--;
    }
    else
    {
      pos1++;
      pos2--;
    }

    servos[channel1].write( pos1 );
    delay(delayTime);
    servos[channel2].write( pos2 );
    delay(delayTime);

    Serial.print("channel1: ");
    Serial.print(channel1);
    Serial.print(" pos1: ");
    Serial.print(pos1);

    Serial.print("\tchannel2: ");
    Serial.print(channel2);
    Serial.print(" pos2: ");
    Serial.println(pos2);
  }

}




void servoControll(int channel, int pos)
{

  while ( servosValue[channel] <= pos )
  {

    servos[channel].write( servosValue[channel] );
    servosValue[channel]++;
    delay(delayTime);
  }

  while ( servosValue[channel] > pos )
  {

    servos[channel].write( servosValue[channel] );
    servosValue[channel]--;
    delay(delayTime);
  }

  servosValue[channel] = pos;
  Serial.print("Channel: ");
  Serial.print(channel  );
  Serial.print("\tPosition: ");
  Serial.println(pos);

}



void armIdlePosition()
{
  Serial.println("armIdlePosition");
  int rows = sizeof(armIdlePositionArr) / sizeof(armIdlePositionArr[0]); // returns rows
  int cols = sizeof(armIdlePositionArr[0]) / sizeof(int); // returns col
  for ( int i = 0; i < rows; i++ )
  {
    for ( int j = 0; j < cols; j += 2 )
    {
      servoControll( armIdlePositionArr[i][j], armIdlePositionArr[i][j + 1] );
    }
  }
}




void takeCottonBar()
{
  Serial.println("takeCottonBar");
  int rows = sizeof(takeCottonBarArr) / sizeof(takeCottonBarArr[0]); // returns rows
  int cols = sizeof(takeCottonBarArr[0]) / sizeof(int); // returns col
  for ( int i = 0; i < rows; i++ )
  {
    for ( int j = 0; j < cols; j += 2 )
    {
      servoControll( takeCottonBarArr[i][j], takeCottonBarArr[i][j + 1] );
    }
  }
  takeCottonBarFlag = 1;
}





void takeCovidSample()
{
  Serial.println("takeCovidSample");
  int rows = sizeof(takeCovidSampleArr) / sizeof(takeCovidSampleArr[0]); // returns rows
  int cols = sizeof(takeCovidSampleArr[0]) / sizeof(int); // returns col
  Serial.print( "rows: " );
  Serial.print( rows );
  Serial.print( "\tcols: " );
  Serial.println( cols );
  for ( int i = 0; i < rows; i++ )
  {
    for ( int j = 0; j < cols; j += 2 )
    {
      servoControll( takeCovidSampleArr[i][j], takeCovidSampleArr[i][j + 1] );
    }
  }
}





void putCottonBarInBox()
{
  Serial.println("putCottonBarInBox");
  int rows = sizeof(putCottonBarInBoxArr) / sizeof(putCottonBarInBoxArr[0]); // returns rows
  int cols = sizeof(putCottonBarInBoxArr[0]) / sizeof(int); // returns col
  for ( int i = 0; i < rows; i++ )
  {
    for ( int j = 0; j < cols; j += 2 )
    {
      servoControll( putCottonBarInBoxArr[i][j], putCottonBarInBoxArr[i][j + 1] );
    }
  }
}


void sendBox()
{
  Serial.println("sendBox");
  int rows = sizeof(sendBoxArr) / sizeof(sendBoxArr[0]); // returns rows
  int cols = sizeof(sendBoxArr[0]) / sizeof(int); // returns col
  //  Serial.print( "rows: " );
  //  Serial.print( rows );
  //  Serial.print( "\tcols: " );
  //  Serial.println( cols );

  for ( int i = 0; i < rows; i++ )
  {
    for ( int j = 0; j < cols; j += 2 )
    {
      servoControll( sendBoxArr[i][j], sendBoxArr[i][j + 1] );
    }
  }
}
