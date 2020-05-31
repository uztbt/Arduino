// From https://randomnerdtutorials.com/esp32-servo-motor-web-server-arduino-ide/

#include <WiFi.h>
#include <ESP32Servo.h>

Servo servo;

static const int servoPin = 13; // PWM pin

const char *SSID = "iPhoneDeYuji";
const char *PASSWORD = "startagaiN";

// Set the web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String requestHeader;

// Decode HTTP GET value
String valueString = String(5);
int pos1 = 0;
int pos2 = 0;

void setup()
{
    Serial.begin(115200);
    servo.attach(servoPin);

    // Connect to the WiFi network
    Serial.println(String("Connecting to ") + SSID);
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    // Print local IP address and start the web server
    Serial.println("\nWiFi connected.");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    server.begin();
}

void loop()
{
    WiFiClient client = server.available(); // Listen for incoming clients

    if (client)
    {
        Serial.println("New Client.");
        String currentLine = "";
        while (client.connected())
        {
            if (client.available())
            {                           // If there is bytes to read from the client
                char c = client.read(); // read a byte
                requestHeader += c;
                if (c == '\n')
                {
                    if (currentLine.length() == 0)
                    {
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();

                        /// Display the HTML web page
                        client.println("<!DOCTYPE html><html>");
                        client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                        client.println("<link rel=\"icon\" href=\"data:,\">");
                        // CSS to style the on/off buttons
                        // Feel free to change the background-color and font-size attributes to fit your preferences
                        client.println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Arial; margin-left:auto; margin-right:auto;}");
                        client.println(".slider { width: 300px; }</style>");
                        client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");

                        // Web Page
                        client.println("</head><body><h1>ESP32 with Servo</h1>");
                        client.println("<p>Position: <span id=\"servoPos\"></span></p>");
                        client.println("<input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSlider\" onchange=\"servo(this.value)\" value=\"" + valueString + "\"/>");

                        client.println("<script>var slider = document.getElementById(\"servoSlider\");");
                        client.println("var servoP = document.getElementById(\"servoPos\"); servoP.innerHTML = slider.value;");
                        client.println("slider.oninput = function() { slider.value = this.value; servoP.innerHTML = this.value; }");
                        client.println("$.ajaxSetup({timeout:1000}); function servo(pos) { ");
                        client.println("$.get(\"/?value=\" + pos + \"&\"); {Connection: close};}</script>");

                        client.println("</body></html>");

                        if (requestHeader.indexOf("GET /?value=") >= 0)
                        {
                            pos1 = requestHeader.indexOf('=');
                            pos2 = requestHeader.indexOf('&');
                            valueString = requestHeader.substring(pos1 + 1, pos2);

                            // Rotate the servo
                            servo.write(valueString.toInt());
                            Serial.println(valueString);
                        }
                        client.println();
                        break;
                    }
                    else
                    { // When you get a newline, clear currentLine
                        currentLine = "";
                    }
                }
                else if (c != '\r')
                {
                    currentLine += c;
                }
            }
        }
        requestHeader = "";
        client.stop();
        Serial.println("Client disconnected.");
        Serial.println("");
    }
}
