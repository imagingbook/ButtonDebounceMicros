/*
  ButtonDebounceMicros.h - Library for Button Debounce using microsecond timing.

  Based on the 'ButtonDebounce' library (https://github.com/maykon/ButtonDebounce)
  originally created by Maykon L. Capellari, September 30, 2017.

  Adapted by Wilhelm Burger, May 2025.
*/
#ifndef ButtonDebounceMicros_h
#define ButtonDebounceMicros_h

#include "Arduino.h"

typedef std::function<void(const int)> ButtonCallback;

const int DEFAULT_SAMPLES = 8;              // require 8 identical samples in a row
const unsigned long DEFAULT_DELAY = 5000;   // 5ms
const uint8_t DEFAULT_INPUT_MODE = INPUT_PULLUP;

class ButtonDebounceMicros{

  private:
    uint8_t _pin;
    unsigned long _delayTotal;        // total sample time
    unsigned long _delaySample;
    unsigned long _lastDebounceTime;  // microseconds
    unsigned long _lastChangeTime;    // microseconds
    int _lastState;
    ButtonCallback _callBack = NULL;
    bool isTimeToUpdate();

  public:
    ButtonDebounceMicros(uint8_t pin);     // simple constructor
    ButtonDebounceMicros(uint8_t pin, unsigned long delayMicros);   // for backward compatibility
    ButtonDebounceMicros(uint8_t pin, unsigned long delayMicros, int sampleCnt, uint8_t inputMode);  // full constructor
    void update();
    int state();
    void setCallback(ButtonCallback);
    void print(String name);  // for debugging
};

#endif
