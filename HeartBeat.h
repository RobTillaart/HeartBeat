#pragma once
//
//    FILE: HeartBeat.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
// PURPOSE: Arduino library for HeartBeat with frequency and dutyCycle
//    DATE: 2019-06-12
//     URL: https://github.com/RobTillaart/HeartBeat


#include "Arduino.h"

#define HEARTBEAT_LIB_VERSION       (F("0.3.0"))


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

  //  pattern = up to 9 digits, indicating the relative length of the pulses
  //            of the error or diagnostic code
  bool   code(uint32_t pattern);        //  executes ONE time
  void   codeOff() { _codeMask = 0; };  //  explicit stop.

protected:
  uint32_t _code        = 0;  //  up to 9 digits
  uint32_t _codeMask    = 0;  //  to extract the bit value from code
  uint8_t  _codeStart   = 0;  //  force starting with LOW
  uint8_t  _pulseLength = 0;  //  to track length of current pulse
};



/////////////////////////////////////////////////////////////////////////////
//
// HEARTBEATSL  (simpler, has a smaller footprint as HeartBeatDiag
//
class HeartBeatSL : public HeartBeat
{
public:
  HeartBeatSL();

  void   beat();

  //  str = string of L (long) and S or non-L (short) characters.
  //        L is a pulse of 3 units, S is a pulse of 1 unit.
  bool   code(const char * str);        //  executes ONE time
  void   codeOff() { _codeMask = 0; };  //  explicit stop.

protected:
  uint8_t _code        = 0;  //  up to 7 bits
  uint8_t _codeMask    = 0;  //  to extract the bit value from code
  uint8_t _codeStart   = 0;  //  force starting with LOW
  uint8_t _pulseLength = 0;  //  to track length of current pulse
};


// -- END OF FILE --

