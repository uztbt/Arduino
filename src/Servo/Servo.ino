#include <ESP32Servo.h>

#define MIN_ANGLE 50
#define MAX_ANGLE 130
#define STEERING_REF 13

Servo myservo;

void setup()
{
  Serial.begin(115200);

  Serial.println("Setup");
  myservo.attach(STEERING_REF);
}

void loop()
{
  int pos = 0;
  // put your main code here, to run repeatedly:
  for (pos = 0; pos <= MAX_ANGLE; pos += 1)
  {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 180; pos >= MIN_ANGLE; pos -= 1)
  {
    myservo.write(pos);
    delay(15);
  }
}
