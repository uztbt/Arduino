#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <analogWrite.h>

#define SERVICE_UUID "8d73daf8-208b-432d-bb8f-631e11a37a56"
#define CHARACTERISTIC_UUID "88e7e723-b754-4394-9ef5-a6b121e8dfce"
#define BLE_DEVICE_NAME "BLECar"
#define MD1_IN1 27
#define MD1_IN2 14
#define MD1_VREF 12
#define MD2_IN1 16
#define MD2_IN2 17
#define MD2_VREF 4

void rotateLeft(bool toForward)
{
  if (toForward)
  {
    digitalWrite(MD1_IN1, HIGH);
    digitalWrite(MD1_IN2, LOW);
  }
  else
  {
    digitalWrite(MD1_IN1, LOW);
    digitalWrite(MD1_IN2, HIGH);
  }
}

void stopLeft()
{
  digitalWrite(MD1_IN1, LOW);
  digitalWrite(MD1_IN2, LOW);
}

void rotateRight(bool toForward)
{
  if (toForward)
  {
    digitalWrite(MD2_IN1, LOW);
    digitalWrite(MD2_IN2, HIGH);
  }
  else
  {
    digitalWrite(MD2_IN1, HIGH);
    digitalWrite(MD2_IN2, LOW);
  }
}

void stopRight()
{
  digitalWrite(MD2_IN1, LOW);
  digitalWrite(MD2_IN2, LOW);
}

class ServerCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *bleCharacteristic)
  {
    uint8_t value = *(bleCharacteristic->getData());
    switch (value)
    {
    Serial.println("Command Value = " + value);
    case 1:
      // Forward
      rotateLeft(true);
      rotateRight(true);
      break;
    case 2:
      // Turn Right
      rotateLeft(true);
      stopRight();
      break;
   case 3:
      // Backward
      rotateLeft(false);
      rotateRight(false);
      break;
    case 4:
      // Turn Left
      stopLeft();
      rotateRight(true);
      break;
    default:
      stopLeft();
      stopRight();
      break;
    }
  }
};

void setup()
{
  Serial.begin(115200);

  Serial.println("Setup");

  BLEDevice::init(BLE_DEVICE_NAME);

  BLEServer *bleServer = BLEDevice::createServer();
  BLEService *bleService = bleServer->createService(SERVICE_UUID);

  BLECharacteristic *bleCharacteristic = bleService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);

  bleCharacteristic->setCallbacks(new ServerCallbacks());
  bleCharacteristic->setValue("Hello World");
  bleService->start();
  BLEAdvertising *bleAdvertising = bleServer->getAdvertising();
  bleAdvertising->addServiceUUID(SERVICE_UUID);
  bleAdvertising->start();

  pinMode(MD1_IN1, OUTPUT);
  pinMode(MD1_IN2, OUTPUT);
  pinMode(MD1_VREF, OUTPUT);
  pinMode(MD2_IN1, OUTPUT);
  pinMode(MD2_IN2, OUTPUT);
  pinMode(MD2_VREF, OUTPUT);

  digitalWrite(MD1_VREF, HIGH);
  digitalWrite(MD2_VREF, HIGH);
}

void loop()
{
  Serial.println("Loop");
  delay(2000);
}
