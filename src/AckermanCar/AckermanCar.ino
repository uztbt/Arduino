#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <ESP32Servo.h>

#define SERVICE_UUID "49662679-5858-4a57-8253-3b29f954643a"
#define STEERING_CHARACTERISTIC_UUID "dbba9389-a24f-49f4-9063-8bc7e479bc35"
#define MOTOR_CHARACTERISTIC_UUID "43a5be68-47a6-4bf7-a903-89405a0fc603"
#define BLE_DEVICE_NAME "AckermanCar"
#define MIN_ANGLE 50
#define MAX_ANGLE 130
#define STEERING_REF 13
#define MD_IN1 27
#define MD_IN2 14
#define MD_VREF 12

Servo steering;

bool steer(uint8_t direction)
{
  switch (direction)
  {
  case 0:
    steering.write(0);
    return true;
  case 1:
    steering.write(MIN_ANGLE);
    return true;
  case 2:
    steering.write(MAX_ANGLE);
    return true;
  default:
    return false;
  }
}

bool drive(uint8_t direction)
{
  switch (direction)
  {
  case 0:
    digitalWrite(MD_IN1, LOW);
    digitalWrite(MD_IN2, LOW);
    return true;
  case 1:
    digitalWrite(MD_IN1, LOW);
    digitalWrite(MD_IN2, HIGH);
    return true;
  case 2:
    digitalWrite(MD_IN1, HIGH);
    digitalWrite(MD_IN2, LOW);
    return true;
  default:
    return false;
  }
}

class SteeringCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *bleCharacteristic)
  {
    uint8_t value = *(bleCharacteristic->getData());
    Serial.println("Steering, Command Value = " + String(value));
    bool successful = steer(value);
    if (!successful)
    {
      Serial.println("Error!");
    }
  }
};

class MotorCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *bleCharacteristic)
  {
    uint8_t value = *(bleCharacteristic->getData());
    Serial.println("Motor, Command Value = " + String(value));
    bool successful = drive(value);
    if (!successful)
    {
      Serial.println("Error!");
    }
  }
};

void setup()
{
  Serial.begin(115200);

  Serial.println("Setup");

  pinMode(STEERING_REF, OUTPUT);
  pinMode(MD_IN1, OUTPUT);
  pinMode(MD_IN2, OUTPUT);
  pinMode(MD_VREF, OUTPUT);

  BLEDevice::init(BLE_DEVICE_NAME);

  BLEServer *bleServer = BLEDevice::createServer();
  BLEService *bleService = bleServer->createService(SERVICE_UUID);

  BLECharacteristic *steeringCharacteristic = bleService->createCharacteristic(
      STEERING_CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);

  BLECharacteristic *motorCharacteristic = bleService->createCharacteristic(
      MOTOR_CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);

  steeringCharacteristic->setCallbacks(new SteeringCallbacks());
  motorCharacteristic->setCallbacks(new MotorCallbacks());

  bleService->start();
  BLEAdvertising *bleAdvertising = bleServer->getAdvertising();
  bleAdvertising->addServiceUUID(SERVICE_UUID);
  bleAdvertising->start();
  Serial.println("BLE ad started");
}

void loop()
{
  Serial.println("Loop");
  delay(5000);
}
