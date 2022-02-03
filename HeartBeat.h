#pragma once
//
//    FILE: HeartBeat.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: Arduino library for HeartBeat with frequency and dutyCycle
//    DATE: 2019-06-12
//     URL: https://github.com/RobTillaart/HeartBeat


#include "Arduino.h"

#define HEARTBEAT_LIB_VERSION       (F("0.2.1"))


class HeartBeat
{
public:
  HeartBeat();

  void   begin(const uint8_t pin, float frequency = 1.0);

  void   setFrequency(float frequency = 1.0);
  void   setDutyCycle(float dutyCycle = 50);
  float  getFrequency() { return _frequency; };
  float  getDutyCycle() { return _dutyCycle; };

  inline void enable()  { _running = true;  };
  inline void disable() { _running = false; };

  void    beat();
  uint8_t getState()    { return _state; };

protected:
  void     _setFreqDuty();

  float    _frequency      = 1.0;
  float    _dutyCycle      = 50;

  uint32_t _lastHeartBeat  = 0;
  uint32_t _dutyCycleHigh  = 500;
  uint32_t _dutyCycleLow   = 500;

  bool     _running        = false;
  uint8_t  _pin            = 255;
  uint8_t  _state          = LOW;
};



/////////////////////////////////////////////////////////////////////////////
//
// HEARTBEATDIAG
//
class HeartBeatDiag : public HeartBeat
{
public:
  HeartBeatDiag();

  void   beat();

  bool   errorCode(const char * str);             //  executes ONE time
  void   errorCodeOff() { _errorCodeMask = 0; };  //  explicit stop.

protected:
  uint8_t  _errorCode      = 0;  //  bit pattern 1 = LONG 0 = SHORT
  uint8_t  _errorCodeMask  = 0;  //  to extract the bit value from errorCode
  uint8_t  _errorCodeStart = 0;  //  force starting with LOW
  uint8_t  _pulseLength    = 0;  //  to track length of current pulse
};


// -- END OF FILE --

