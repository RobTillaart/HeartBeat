//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the HeartBeat
//          https://github.com/RobTillaart/HeartBeat
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// https://github.com/Arduino-CI/arduino_ci/blob/master/cpp/unittest/Assertion.h#L33-L42
// ----------------------------
// assertEqual(expected, actual)
// assertNotEqual(expected, actual)
// assertLess(expected, actual)
// assertMore(expected, actual)
// assertLessOrEqual(expected, actual)
// assertMoreOrEqual(expected, actual)
// assertTrue(actual)
// assertFalse(actual)
// assertNull(actual)
// assertNotNull(actual)

#include <ArduinoUnitTests.h>

#define assertEqualFloat(arg1, arg2, arg3)  assertOp("assertEqualFloat", "expected", fabs(arg1 - arg2), compareLessOrEqual, "<=", "actual", arg3)
#define assertEqualINF(arg)  assertOp("assertEqualINF", "expected", INFINITY, compareEqual, "==", "actual", arg)
#define assertEqualNAN(arg)  assertOp("assertEqualNAN", "expected", true, compareEqual, "==", "actual", isnan(arg))


#include "Arduino.h"
#include "HeartBeat.h"


unittest_setup()
{
}

unittest_teardown()
{
}

/*
unittest(test_new_operator)
{
  assertEqualINF(exp(800));
  assertEqualINF(0.0/0.0);
  assertEqualINF(42);
  
  assertEqualNAN(INFINITY - INFINITY);
  assertEqualNAN(0.0/0.0);
  assertEqualNAN(42);
}
*/

unittest(test_constructor)
{
  GodmodeState* state = GODMODE();
  state->reset();

  Heartbeat HB;
  HB.begin(13, 4);

  uint32_t start = millis();
  while (millis() - start <= 1000)
  {
    delay(10);
    HB.beat();
  }
  
  assertEqual(8, state->digitalPin[13].queueSize());
  bool expected[8] = {LOW, HIGH, LOW, HIGH, LOW, HIGH, LOW, HIGH};
  bool actual[8];
  int  changes = state->digitalPin[13].toArray(actual, 8);
  assertEqual(8, changes);

  // verify each element
  for (int i = 0; i < 8; ++i) 
  {
    assertEqual(expected[i], actual[i]);
  }
}

unittest_main()

// --------
