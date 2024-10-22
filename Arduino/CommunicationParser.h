/********************************* communicationParser.h **************************************/


#ifndef __COMMUNICATION_PARSER_H__
#define __COMMUNICATION_PARSER_H__

#include "Arduino.h"

class CommunicationParser
{
  public:
  void checkSerial();
  void requestHandle( String serialReceiveValue );
  void responseHandle( String responsePayload );
};


#endif

