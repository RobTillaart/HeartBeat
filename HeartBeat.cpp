//
//    FILE: HeartBeat.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: HeartBeat library for Arduino
//    DATE: 2019-06-12
//
// HISTORY:
// 0.1.0 - 2019-06-12 initial version
//

#include "HeartBeat.h"

Heartbeat::Heartbeat()
{
}

void Heartbeat::begin(const uint8_t pin, float freq)
{
  _pin = pin;
  pinMode(_pin, OUTPUT);

  set(freq);
  enable();
}

void Heartbeat::set(float freq)
{
  _lastHeartBeat = 0;
  _heartBeatDelay = round(500000.0/freq);
}

void Heartbeat::beat()
{
  if (!_running) return;
  uint32_t now = micros();
  if ((now - _lastHeartBeat) < _heartBeatDelay) return;
  _lastHeartBeat = now;
  digitalWrite(_pin, !digitalRead(_pin));
}

// -- END OF FILE --
