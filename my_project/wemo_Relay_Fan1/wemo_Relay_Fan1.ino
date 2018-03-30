#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <functional>
#include "switch.h"
#include "UpnpBroadcastResponder.h"
#include "CallbackFunction.h"

// prototypes
boolean connectWifi();

//on/off callbacks 
bool Fan1On();
bool Fan1Off();

// Change this before you flash
const char* ssid = "Tony-MiWiFi";
const char* password = "8860225231449";
const int RELAY_PIN = 16;

boolean wifiConnected = false;

UpnpBroadcastResponder upnpBroadcastResponder;

Switch *fan1 = NULL;

bool isFan1On = false;

void setup()
{
  Serial.begin(115200);
  pinMode(RELAY_PIN,OUTPUT);
   
  // Initialise wifi connection
  wifiConnected = connectWifi();
  
  if(wifiConnected){
    upnpBroadcastResponder.beginUdpMulticast();
    
    // Define your switches here. Max 10
    // Format: Alexa invocation name, local port no, on callback, off callback
    fan1 = new Switch("fan1", 80, Fan1On, Fan1Off);

    Serial.println("Adding switches upnp broadcast responder");
    upnpBroadcastResponder.addDevice(*fan1);
  }
}
 
void loop()
{
	 if(wifiConnected){
      upnpBroadcastResponder.serverLoop();
      fan1->serverLoop();
	 }
}

bool Fan1On() {
    Serial.println("Switch 1 turn on ...");
    
    isFan1On = true;
    digitalWrite(RELAY_PIN,HIGH);    
    return isFan1On;
}

bool Fan1Off() {
    Serial.println("Switch 1 turn off ...");

    isFan1On = false;
    digitalWrite(RELAY_PIN,LOW); 
    return isFan1On;
}

// connect to wifi – returns true if successful or false if not
boolean connectWifi(){
  boolean state = true;
  int i = 0;
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting ...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 10){
      state = false;
      break;
    }
    i++;
  }
  
  if (state){
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("");
    Serial.println("Connection failed.");
  }
  
  return state;
}
