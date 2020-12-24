//
//    FILE: sinusHeartBeat.ino
//  AUTHOR: Rob Tillaart 
// VERSION: 0.1.1
// PURPOSE: demo

#include "HeartBeat.h.h"

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