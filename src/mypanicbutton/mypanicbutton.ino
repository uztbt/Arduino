#include <WiFiClientSecure.h>
#include <WiFi.h>

char wifiSSID[] = "iPhoneDeYuji";
char wifiPASS[] = "startagaiN";

const char* host = "api.telegram.org";
const int httpsPort = 443;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  WiFi.begin(wifiSSID, wifiPASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("connecting");
    delay(500);
  }
  Serial.println("connected");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10000);
  WiFiClientSecure client;

  if(!client.connect(host, httpsPort)) {
    return;
  }

  String url = "/bot1080912181:AAFb1cWOz0uhKGW10W9Y2rDbjkdFkq6_9Mw/sendMessage?chat_id=-234201009&text=HELP%20my%20stash%20is%20under%20attack.%20Please%20call%20my%20local%20police%20on%20123456789.%20My%20address%20is%2015%20Funky%20Street%2C%20Lazy%20Town%2098765.";
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" +
                "Connection: close\r\n\r\n");

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }
  String line = client.readStringUntil('\n');
  Serial.println(line);
}
