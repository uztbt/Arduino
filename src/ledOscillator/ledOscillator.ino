void setup()
{
    pinMode(14, OUTPUT);
    Serial.begin(1152000);
}

void loop()
{

    Serial.println("HIGH");
    digitalWrite(14, HIGH);
    delay(500);
    Serial.println("LOW");
    digitalWrite(14, LOW);
    delay(200);
}
