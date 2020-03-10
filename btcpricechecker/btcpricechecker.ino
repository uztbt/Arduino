#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

char wifiSSID[] = "iPhoneDeYuji";
char wifiPASS[] = "startagaiN";

const char* host = "blockchain.info";
const int httpPort = 443;
const String on_currency = "JPY";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  WiFi.begin(wifiSSID, wifiPASS);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.println("connecting");
    delay(500);
  }
  Serial.println("connected");

  WiFiClientSecure client;
  if (!client.connect(host, httpPort)) {
    return;
  }

  String path = "/ticker";
  client.print(String("GET ") + path + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" +
                "User-Agent: ESP32\r\n" +
                "Connection: close\r\n\r\n");
  
  while(client.connected()) {
    String line = client.readStringUntil('\n');
    Serial.println(line); // Debug
    if (line == "\r") {
      client.readStringUntil('\n');
      break;
    }
  }
  Serial.println("End of the Header");
  String jsonStr = "";
  while(client.connected()) {
    String line = client.readStringUntil('\n');
    Serial.println(line); // Debug
    if (line == "\r") {
      client.readStringUntil('\n');
      break;
    }
    jsonStr = jsonStr + line;
  }
  jsonStr.remove(jsonStr.length()-2); // Remove the mysterious 0
  Serial.println(jsonStr);
  DynamicJsonDocument doc(8192);
  DeserializationError error = deserializeJson(doc, jsonStr);
  if (error) {
    Serial.println(String("Error: ") + error.c_str());
    return;
  }
  
  String priceStr = doc[on_currency]["15m"];
  String symbolStr = doc[on_currency]["symbol"];
  Serial.println(symbolStr + priceStr);
}

void loop() {
  // put your main code here, to run repeatedly:

}
