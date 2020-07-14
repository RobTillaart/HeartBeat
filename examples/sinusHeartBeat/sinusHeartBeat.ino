//
//    FILE: sinusHeartBeat.ino
//  AUTHOR: Rob Tillaart 
// VERSION: 0.1.0
// PURPOSE: demo
//
// HISTORY: 2019-06-12 initial version

#include "heartbeat.h"

Heartbeat HB;

int frequency = 1;

void setup() 
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println(HEARTBEAT_LIB_VERSION);

  HB.begin(13, frequency);
}

void loop()
{
  HB.beat();

  float f = 5 * (1 + sin(millis()/10000));
  HB.set(f);
  
  // do other stuff here
}

// -- END OF FILE --