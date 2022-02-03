//
//    FILE: HeartBeat_errorcode.ino
//  AUTHOR: Rob Tillaart 
// PURPOSE: demo


#include "HeartBeat.h"


HeartBeat HB;

bool flag = true;

void setup() 
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println(HEARTBEAT_LIB_VERSION);

  HB.begin(13, 1);  // PIN 13 with frequency 1
}


void loop()
{
  HB.beat();

  if (millis() > 4000) HB.errorCode("LLSLL");
  if (millis() > 20000) HB.errorCodeOff();
}


// -- END OF FILE --
