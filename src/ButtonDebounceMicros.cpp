#include "Arduino.h"
#include "ButtonDebounceMicros.h"

ButtonDebounceMicros::ButtonDebounceMicros(uint8_t pin)
  : ButtonDebounceMicros(pin, DEFAULT_DELAY, DEFAULT_SAMPLES, DEFAULT_INPUT_MODE) {}

ButtonDebounceMicros::ButtonDebounceMicros(uint8_t pin, unsigned long delay)
  : ButtonDebounceMicros(pin, delay, DEFAULT_SAMPLES, DEFAULT_INPUT_MODE) {}

ButtonDebounceMicros::ButtonDebounceMicros(uint8_t pin, unsigned long delay, int sampleCnt, uint8_t inputMode) {
  pinMode(pin, inputMode);
  _pin = pin;
  _delayTotal = delay;
  _delaySample = delay / sampleCnt;
  _lastState = digitalRead(_pin);
  _lastDebounceTime = micros();
  _lastChangeTime = _lastDebounceTime;
}

/*
  To be called as often as possible, typically inside the Arduino loop() method.
  Updates the state of this button and calls the callback method (if assigned)
  after each (debounced) state change.
*/
void ButtonDebounceMicros::update() {

  unsigned long curTime = micros();    // note that current time is retrieved only once!

  if ((curTime - _lastDebounceTime) > _delaySample) {    // time to update - was: if (isTimeToUpdate()) ...
    _lastDebounceTime = curTime;
    int curState = digitalRead(_pin);

    if (curState == _lastState) {   // button has not changed
      _lastChangeTime = _lastDebounceTime;
      return;
    }

    // button has changed but total delay period not yet over
    if (_lastDebounceTime - _lastChangeTime < _delayTotal) {
      return;
    }

    // now the required number of sample points in _delay time changed (so that counts)
    _lastState = curState;
    // invoke the associated callback method if set:
    if (_callBack != NULL) _callBack(_lastState);
  }
}

/*
  Returns the current (debounced) state of this button.
*/
int ButtonDebounceMicros::state() {
  return _lastState;
}

/*
  The callback method is invoked when this button changes its (debounced) state.
*/
void ButtonDebounceMicros::setCallback(ButtonCallback callback) {
  this->_callBack = callback;
}

// ------------------------------------------------------------------------------------

void ButtonDebounceMicros::print(String name) {
    Serial.println("*** Button " + name + " ***");
    Serial.println("  pin = " + String(_pin));
    Serial.println("  delayTotal =       " + String(_delayTotal));        // total sample time
    Serial.println("  delaySample =      " + String(_delaySample));
    Serial.println("  lastDebounceTime = " + String(_lastDebounceTime));  // microseconds
    Serial.println("  lastChangeTime =   " + String(_lastChangeTime));    // microseconds
    Serial.println("  lastState =        " + String(_lastState));
    if (_callBack == NULL)
      Serial.println("  callBack: not set");
    else
      Serial.println("  callBack: set");
    Serial.println("**************************");
}