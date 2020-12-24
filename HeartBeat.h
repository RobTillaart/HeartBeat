#pragma once
//
//    FILE: HeartBeat.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Arduino library for simple HeartBeat 
//    DATE: 2019-06-12
//     URL: https://github.com/RobTillaart/HeartBeat


#include "Arduino.h"

#define HEARTBEAT_LIB_VERSION "0.1.1"

class Heartbeat
{
public:
  Heartbeat();

  void  begin(const uint8_t pin, float freq = 1.0);
  void  set(float freq = 1.0);
  
  inline void  enable()  { _running = true; };
  inline void  disable() { _running = false; digitalWrite(_pin, LOW);};
  
  void  beat();

protected:
  uint32_t _lastHeartBeat;
  uint32_t _heartBeatDelay = 500000;
  bool     _running;
  uint8_t  _pin;
};

// -- END OF FILE --
