#include "WiFi.h"
#include "SPIFFS.h"
#include "ESPAsyncWebServer.h"

#include <ArduinoJson.h>

#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeSansBold18pt7b.h>

char wifiSSID[] = "iPhoneDeYuji";
char wifiPASS[] = "startagaiN";

AsyncWebServer server(80);

// VSPI
GxEPD2_BW<GxEPD2_154, GxEPD2_154::HEIGHT> display(GxEPD2_154(/*CS=5*/ SS, /*DC*/ 22, /*RST*/ 21, /*BUSY*/ 4));

const int ROTATION_TIME = 3000;
// This program returns if this time span passes without any progress
const int TIMEOUT = 60;
int timeout = TIMEOUT;

void setup()
{
    Serial.begin(115200);
    display.init(115200);
    display.setFont(&FreeSansBold18pt7b);
    display.setTextColor(GxEPD_BLACK);
    pinMode(14, OUTPUT);
    if (!SPIFFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    display.firstPage();
    do
    {
        display.fillScreen(GxEPD_WHITE);
        display.setCursor(0, 40);
        display.print(String("Connecting to\n ") + wifiSSID);
    } while (display.nextPage());

    WiFi.begin(wifiSSID, wifiPASS);

    while (WiFi.status() != WL_CONNECTED)
    {
        if (timeout <= 0)
        {
            return;
        }
        Serial.println("connecting");
        delay(1000);
        timeout--;
    }
    Serial.println("connected");
    timeout = TIMEOUT;

    server.on("/dispense", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("Got a request to /dispense");
        request->send(SPIFFS, "/dispense.html", "text/html");
        display.firstPage();
        Serial.println("Starting");
        do
        {
            display.fillScreen(GxEPD_WHITE);
            display.setCursor(0, 40);
            display.print("Started rotating");
        } while (display.nextPage());
        digitalWrite(14, HIGH);
        delay(ROTATION_TIME);
        display.firstPage();
        Serial.println("Stopping");
        digitalWrite(14, LOW);
        do
        {
            display.fillScreen(GxEPD_WHITE);
            display.setCursor(0, 40);
            display.print("Visit /dispense!");
        } while (display.nextPage());
    });
    server.begin();

    display.firstPage();
    do
    {
        display.fillScreen(GxEPD_WHITE);
        display.setCursor(0, 40);
        display.print(String("IP Address is\n") + WiFi.localIP().toString());
    } while (display.nextPage());
}

void loop()
{
    //    if (timeout <= 0)
    //    {
    //        SPIFFS.end();
    //        do
    //        {
    //            display.fillScreen(GxEPD_WHITE);
    //            display.setCursor(0, 40);
    //            display.print("Press Button to Start");
    //        } while (display.nextPage());
    //        esp_deep_sleep_start();
    //    }
    //
    //    if (challenge())
    //    {
    //        timeout = TIMEOUT;
    //     }
    //    delay(1000);
    //    timeout--;
}

String getRequestHeader(WiFiClient client)
{
    String requestHeader = "";
    String currentLine = "";
    while (client.connected() && client.available())
    {
        currentLine = client.readStringUntil('\n');
        if (currentLine == "")
        {
            break;
        }
        requestHeader += currentLine + "\n";
    }
    return requestHeader;
}

String getRequestPath(String requestHeader)
{
    int start = requestHeader.indexOf(' ') + 1;
    int end = requestHeader.indexOf(' ', start + 1);
    return requestHeader.substring(start, end);
}
