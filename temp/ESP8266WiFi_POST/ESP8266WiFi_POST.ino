#include <ESP8266WiFi.h>
const char* ssid     = "CloudCube_TPE_Office";
const char* password = "cloudcube54729082";

const char* host = "www.strongniche.com.tw";
const int httpPort = 7878;

void setup() {
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

 while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 

}

void loop() {
  WiFiClient client;

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }


 //String data = "pst=temperature>" + String(random(0,100)) +"||humidity>" + String(random(0,100)) + "||data>text";
  String data = "{\"measurement\":\"temperature\",\"value\":\"30\",\"location\":\"Gobin-4F12\",\"place\":\"My Desktop\"}";
   Serial.print("Requesting POST: ");
   // Send request to the server:
   client.println("POST /v1/iot-mk2 HTTP/1.1");
   //client.println("Host: ESP8266");
   //client.println("Accept: */*");
   client.println("Content-Type: application/json");
   client.print("Content-Length: ");
   client.println(data.length());
   client.println();
   client.print(data);
   Serial.print(data);

   delay(500); // Can be changed
  if (client.connected()) { 
    client.stop();  // DISCONNECT FROM THE SERVER
  }
  Serial.println();
  Serial.println("closing connection");
  delay(5000);
}
