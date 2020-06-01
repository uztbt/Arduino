#define PIN_IN1 2 // "D2"
#define PIN_IN2 21 // "D21"
#define PIN_VREF 3 // "D3" // PMW

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_VREF, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(PIN_VREF, 64);

  forwardBackwardRotate();

  analogWrite(PIN_VREF, 255);

  forwardBackwardRotate();

  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, LOW);
  delay(1000);
}

void forwardBackwardRotate() {
  // Rotate
  digitalWrite(PIN_IN1, HIGH);
  digitalWrite(PIN_IN2, LOW);
  delay(1000);

  // Brake
  digitalWrite(PIN_IN1, HIGH);
  digitalWrite(PIN_IN2, HIGH);

  // Rotate in Reverse
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, HIGH);
  delay(1000);

  
  // Brake
  digitalWrite(PIN_IN1, HIGH);
  digitalWrite(PIN_IN2, HIGH);
  delay(1000);
}
