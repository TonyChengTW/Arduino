//
// **** Need to change to NodeMCU 1.0 (ESP-12E Module) ******
//
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
bool Light4On();
bool Light4Off();

// Change this before you flash
const char* ssid = "Tony-MiWiFi";
const char* password = "8860225231449";
const int RELAY_PIN = 16;

boolean wifiConnected = false;

UpnpBroadcastResponder upnpBroadcastResponder;

Switch *light4 = NULL;

bool isLight4On = false;

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
    light4 = new Switch("Light4", 80, Light4On, Light4Off);

    Serial.println("Adding switches upnp broadcast responder");
    upnpBroadcastResponder.addDevice(*light4);
  }
}
 
void loop()
{
	 if(wifiConnected){
      upnpBroadcastResponder.serverLoop();
      light4->serverLoop();
	 }
}

bool Light4On() {
    Serial.println("Switch 1 turn on ...");
    
    isLight4On = true;
    digitalWrite(RELAY_PIN,HIGH);    
    return isLight4On;
}

bool Light4Off() {
    Serial.println("Switch 1 turn off ...");

    isLight4On = false;
    digitalWrite(RELAY_PIN,LOW); 
    return isLight4On;
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
