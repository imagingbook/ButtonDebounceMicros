#include <ButtonDebounceMicros.h>

ButtonDebounceMicros button(10);
void setup() {
  Serial.begin(115200);
}

void loop() {
  button.update();
  if(button.state() == HIGH){
    Serial.println("Clicked");
  }
}
