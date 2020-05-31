#include <ESP32Servo.h>

Servo sg90;

int pos = 0;

void setup() {
  sg90.attach(13); // Attach a pin for PWM control
}

void loop() {
  // put your main code here, to run repeatedly:
  for(pos=0; pos <= 180; pos +=1) {
    sg90.write(pos);
    delay(15);
  }
  for(pos = 180; pos >= 0; pos -= 1) {
    sg90.write(pos);
    delay(15);
  }
}
