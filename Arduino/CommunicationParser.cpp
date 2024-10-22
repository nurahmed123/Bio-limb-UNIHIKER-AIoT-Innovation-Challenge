/********************************* communicationParser.cpp *******************************/

#define PC
#include "CommunicationParser.h"
#include "pinMapping.h"
#include "lcd.h"

bool mouthOpenFlag = 0;
bool mouthCloseFlag = 0;
bool humanDetectFlag = 0;

uint8_t mouthCloseFlagErrorCheck = 0;
uint8_t mouthCloseFlagErrorCheckValue = 4;

void CommunicationParser :: checkSerial()
{
  #ifdef PC
  if ( Serial.available() )
  {
    String serialReceiveValue = Serial.readStringUntil('\n');
    Serial.println( F("serialReceiveValue: ") );
    Serial.println( serialReceiveValue );
    requestHandle( serialReceiveValue ) ;
  }
  #else
  if ( Serial1.available() )
  {
    String serialReceiveValue = Serial1.readStringUntil('\n');
    Serial.println( F("serialReceiveValue: ") );
    Serial.println( serialReceiveValue );
    requestHandle( serialReceiveValue ) ;
  }
  #endif
  

}

void CommunicationParser :: requestHandle( String serialReceiveValue )
{
  Serial.println( serialReceiveValue );
  if ( serialReceiveValue == "CRAL" ) //check robot arm life
  {
    responseHandle( "OK" ) ;
  }
  else if (serialReceiveValue == "MO" ) //mouth open> red
  {
    responseHandle( "OK" ) ;
    show_lcd(0, 1, "                " );
    show_lcd(0, 1, "do not move" );
    delay(500);
    show_lcd(0, 1, "                " );
    show_lcd(0, 1, "Taking Sample." );
    mouthOpenFlag = 1;
  }
  else if (serialReceiveValue == "MC" )  //mouth close > blue
  {
    responseHandle( "OK" ) ;
    if ( mouthCloseFlag == 0 )
    {
      show_lcd(0, 1, "                " );
      show_lcd(0, 1, "PLZ wait." );
    }
    mouthCloseFlagErrorCheck++;
    if( mouthCloseFlagErrorCheck >= mouthCloseFlagErrorCheckValue)
    {
      mouthCloseFlag = 1;
    }
    
  }
  else if (serialReceiveValue == "NHD" ) //no human > green
  {
    responseHandle( "OK" ) ;
    show_lcd(0, 1, "                " );
    show_lcd(0, 1, "No Human Detect" );
    humanDetectFlag = 0;
    mouthCloseFlagErrorCheck = 0;
  }
  else if (serialReceiveValue == "HD" ) //no human > green
  {
    digitalWrite(13, HIGH);
    responseHandle( "OK" ) ;
    show_lcd(0, 1, "                " );
    show_lcd(0, 1, "PLZ seat down" );
    humanDetectFlag = 1;
    mouthCloseFlagErrorCheck = 0;
  }
  else
  {
    Serial.println("do nothing");
  }
}




void CommunicationParser :: responseHandle( String responsePayload )
{
  Serial.println( F("responseHandle value") );
  Serial.println( responsePayload );
  #ifdef PC
  Serial.println( responsePayload );
  #else
  Serial1.println( responsePayload );
  #endif
}

