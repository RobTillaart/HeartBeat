//
//    FILE: HeartBeat.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: Arduino library for HeartBeat with frequency and dutyCycle
//    DATE: 2019-06-12
//     URL: https://github.com/RobTillaart/HeartBeat
//
//  HISTORY:
//  0.1.0   2019-06-12  initial version
//  0.1.1   2020-12-24  arduino-CI 
//  0.1.2   2021-01-15  renamed all to HeartBeat
//                      added dutyCycle
//  0.1.3   2021-05-27  fix arduino-lint
//  0.2.0   2021-11-02  update Build-CI, add badges
//                      add getFrequency(), getDutyCycle();
//                      add getState().
//                      removed set()
//  0.2.1   2021-12-18  update library.json, license, minor edits



#include "HeartBeat.h"


HeartBeat::HeartBeat()
{
}


void HeartBeat::begin(const uint8_t pin, float frequency)
{
  _pin = pin;
  pinMode(_pin, OUTPUT);

  setFrequency(frequency);
  enable();
}


void HeartBeat::setFrequency(float frequency)
{
  _frequency = frequency;
  if (_frequency < 0) _frequency = -frequency;
  if (_frequency < 0.001) _frequency = 0.001;
  _setFreqDuty();
}


void HeartBeat::setDutyCycle(float dutyCycle)
{
  _dutyCycle = constrain(dutyCycle, 0, 100);  // percentage
  _setFreqDuty();
}


void HeartBeat::beat()
{
  if (_errorCodeMask == 0)  // normal mode
  {
    _errorCodeStart = 0;
    if (_running == false) 
    {
      _state = LOW;
    }
    else
    {
      uint32_t now = micros();
      if ((_state == LOW)  && (now - _lastHeartBeat) < _dutyCycleLow)  return;
      if ((_state == HIGH) && (now - _lastHeartBeat) < _dutyCycleHigh) return;
      _lastHeartBeat = now;
      _state = !_state;
    }
  }
  else  // _errorCode mode
  {
    if (_errorCodeStart == 0)
    {
      _errorCodeStart  = 1;
      _lastHeartBeat = micros();
      _state = LOW;
    }
    else
    {
      // time for next pulse
      uint32_t period = (_dutyCycleLow + _dutyCycleHigh)/2;
      uint32_t now = micros();
      if ((now - _lastHeartBeat) < period) return;
      _lastHeartBeat = now;
      if (_state == LOW)
      {
        _pulseLength = 1;
        if (_errorCode & _errorCodeMask) // HIGH
        {
          _pulseLength = 3;
        }
        _errorCodeMask >>= 1;
        _state = HIGH;
      }
      else
      {
        _pulseLength--;
        if (_pulseLength == 0)
        {
          _state = LOW;
        }
      }
    }
  }
  digitalWrite(_pin, _state);
}


bool HeartBeat::errorCode(char * str)
{
  if (_errorCodeMask > 0) return false;

  uint8_t len = strlen(str);
  if (len > 8) return false;

  _errorCode = 0;
  _errorCodeMask = 0x01;
  for (int i = 0; i < len; i++)
  {
    if (str[i] == 'L') _errorCode |= 1;
    _errorCode <<= 1;
    _errorCodeMask <<= 1;
  }
  return true;
}



/////////////////////////////////
//
//  PROTECTED
//
void HeartBeat::_setFreqDuty()
{
  float time = 10000.0/_frequency;
  _dutyCycleHigh = round(_dutyCycle * time);
  _dutyCycleLow  = round((100 - _dutyCycle) * time);
}


// -- END OF FILE --

