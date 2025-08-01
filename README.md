This library is a fork of [`ButtonDebounce`](https://github.com/maykon/ButtonDebounce) adapted to use **microsecond timing**, noting that the original millisecond timing
(as used by most other debouncing libraries) is unnecessarily slow, particularly on faster hardware such as ESP32.
As bounce times for typical mechanical switches are in the 
[100μs range](https://forum.arduino.cc/t/debouncing-a-switch-on-an-interrupt-pin/632166/3), 
debounce filters with a total delay of about 1ms should be sufficient but
are impossible to implement if the smallest time step is already 1ms.

The following is largely adapted from the original README file:

# Button Debounce 

Pushbuttons often generate improper open/close transitions when pressed, due to mechanical and physical issues: these transitions may be read as multiple presses in a very short time fooling the program, without debouncing, pressing the button once may cause unpredictable results.

This library will sample the button repeatedly; and if it sees the button in its new state for `N` (= 8 by default) consecutive checks (equally spaced within 'delay' in microseconds) -- will report the state as changed.

 Usage
============

## SETUP


Declare a `ButtonDebounceMicros` object with `pin` and `delayMicros` to debounce as parameter, and define a callback function.

Example:

```
void onButtonChange(const int state) {
  Serial.println("Changed: " + String(state));
}
ButtonDebounceMicros button(3, 5000); // assign button to PIN 3 with 5000us = 5ms debounce time
button.setCallback(onButtonChange);
```

Or - in a more anonymous style:

```
ButtonDebounceMicros button(3, 5000); // assign button to PIN 3 with 5000us = 5ms debounce time
button.setCallback([](const int state) {
  Serial.println("Changed: " + String(state));
});
```

Important: buttons don't share resources. The following methods are avaliable:

* `update()` called in `loop method`, used to verify the debounce timer and the button state changes,
* `state()` return the last button state,
* `setCallback(function)` set the callback function that will executed on button state changes,
* `print()` outputs the current state of this button (for debugging).

Note that this constructor by default also sets the `INPUT_PULLUP` pinmode() on the pin. 
This can be changed by using the full constructor instead. Here is the complete list of constructors:

* `ButtonDebounceMicros(uint8_t pin)`: simple constructor using default parameters,
* `ButtonDebounceMicros(uint8_t pin, unsigned long delayMicros)` for backward compatibility,
* `ButtonDebounceMicros(uint8_t pin, unsigned long delayMicros, int sampleCnt, uint8_t inputMode)` full constructor.

If not specified, the value of `delayMicros` is 5.000 microseconds (= 5 ms),
the default value of `sampleCnt` is 8 (min. = 1).
Possible values for `inputMode` are `INPUT` or `INPUT_PULLUP`, as defined by the `pinMode()` method
in the Arduino API.

## LOOP

Due the time buffer used in each button, please call the `update()` method in `loop`, so it can be update and reflect all state changes.
```
#include <ButtonDebounceMicros.h>
...
ButtonDebounceMicros buttonUp(3);
ButtonDebounceMicros buttonDown(4);
...
void loop() {
  buttonUp.update();
  buttonDown.update();
}
```
**Be advised:** Do not invoke `delay()` before the update functions, as it may interfere with the bounce time buffer.

## Contributors

See [`ButtonDebounce`](https://github.com/maykon/ButtonDebounce) for the list of contributors to the original library.
