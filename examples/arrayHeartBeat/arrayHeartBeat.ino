//
//    FILE: arrayHeartBeat.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//
// HISTORY: 2019-06-12 initial version

#include "heartbeat.h"

Heartbeat HB[3];

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println(HEARTBEAT_LIB_VERSION);

  HB[0].begin(11, 1);
  HB[1].begin(12, 3);
  HB[2].begin(13, 5);
}

void loop()
{
  // update all heartbeats
  for (int i = 0; i < 3; i++) HB[i].beat();

  // do other stuff here
}

// -- END OF FILE --