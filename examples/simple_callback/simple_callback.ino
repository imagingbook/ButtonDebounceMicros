#include <ButtonDebounceMicros.h>

ButtonDebounceMicros button(10);
void buttonChanged(const int state){
  Serial.println("Changed: " + String(state));
}

void setup() {
  Serial.begin(115200);
  button.setCallback(buttonChanged);
}

void loop() {
  button.update();
}
