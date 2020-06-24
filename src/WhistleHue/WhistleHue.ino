#include "BLEDevice.h"
#include "esp32-hal-log.h"

#define CONFIG_LOG_DEFAULT_LEVEL 5

static BLEAddress bedroomLightAddress(std::string("f1:bd:ea:44:93:fd"));
// The remote service we wish to connect to.
static BLEUUID SERVICE_UUID("932C32BD-0000-47A2-835A-A8D455B859DD");
// The characteristic of the remote service we are interested in.
static BLEUUID BRIGHTNESS_UUID("932C32BD-0003-47A2-835A-A8D455B859DD");
static BLEUUID ONOFF_UUID("932C32BD-0002-47A2-835A-A8D455B859DD");

void setup()
{
    bool flag;
    Serial.begin(115200);
    log_i("Starting BLE");
    BLEDevice::init("ESP32");

    // Connect to the Peripheral
    BLEClient *pClient = BLEDevice::createClient();
    BLEDevice::setEncryptionLevel(ESP_BLE_SEC_ENCRYPT_NO_MITM);
    flag = pClient->connect(bedroomLightAddress, BLE_ADDR_TYPE_RANDOM);
    // guard(flag, "pClient->connect(bedroomLightAddress, BLE_ADDR_TYPE_RANDOM);");

    // Connect to the Service
    BLERemoteService *pRemoteService = pClient->getService(SERVICE_UUID);
    flag = pRemoteService != nullptr;
    guard(flag, "BLERemoteService *pRemoteService = pClient->getService(trueServiceUUID);");

    // Connect to the Characteristic
    BLERemoteCharacteristic *pBrightnessCharacteristic = pRemoteService->getCharacteristic(BRIGHTNESS_UUID);
    flag = pBrightnessCharacteristic != nullptr;
    guard(flag, "BLERemoteCharacteristic *pBrightnessCharacteristic = pRemoteService->getCharacteristic(BRIGHTNESS_UUID);");

    // Read the Value of the characteristic
    std::string value = pBrightnessCharacteristic->readValue();
    guard(value != "", "std::string value = pBrightnessCharacteristic->readValue();");
} // End of setup.

// This is the Arduino main loop function.
void loop()
{
    delay(1000); // Delay a second between loops.
} // End of loop

void printRemoteCharacteristic(BLERemoteCharacteristic *prc)
{
    Serial.println("****** start printRemoteCharacteristic ******");
    Serial.println(prc->toString().c_str());
    Serial.print("8bit prc: ");
    Serial.println(prc->readUInt8());
    Serial.print("16bit prc: ");
    Serial.println(prc->readUInt16());
    Serial.print("32bit prc: ");
    Serial.println(prc->readUInt32());
    // Serial.print("prc->readRawData(): ");
    // Serial.println(*(prc->readRawData()));
    Serial.print("prc->readValue(): ");
    Serial.println(prc->readValue().empty());
    Serial.println("****** end printRemoteCharacteristic ******");
}

void guard(bool f, char *str)
{
    if (f)
    {
        log_i("PASS: %s", str);
    }
    else
    {
        log_e("ERROR: %s", str);
    }
}