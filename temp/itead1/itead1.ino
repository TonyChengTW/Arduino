#include "ESP8266.h"
#include <SoftwareSerial.h>

SoftwareSerial sSerial(12, 13);  //(RX:D10, TX:D11)
ESP8266 wifi(sSerial);  //建立名為 wifi 的 ESP8266 物件

void setup() {
  Serial.begin(115200);  //啟始硬體序列埠 (debug 用)   
  Serial.println("*** WeeESP8266 WiFi Library Function Test ***"); 
  
  if (wifi.kick()) {
    Serial.println("Reset ESP8266 ... OK");
  }  //重啟 ESP8266
  else {
    Serial.println("Reset ESP8266 ... Error");
  }  
  Serial.println("Firmware Version ... " + wifi.getVersion()); //傳回 AT 韌體版本   
  Serial.println("Local IP ... " + wifi.getLocalIP()); //傳回本地 IP
  
  //測試工作模式 
  if (wifi.setOprToSoftAP()) {
    Serial.println("Set Operation Mode=AP ... OK");
    } 
  else {
    Serial.println("Set Operation Mode=AP ... Error");
    }  //設為 AP 模式 (2)
    
  delay(3000); 
  
  Serial.println("Local IP ... " + wifi.getLocalIP()); //傳回本地 IP
   
  if (wifi.setOprToStationSoftAP()) {
    Serial.println("Set Operation Mode=Station+AP ... OK");
    }  
  else {
    Serial.println("Set Operation Mode=Station+AP ... Error");
    }  //設為 STA+AP 模式 (3)
    
  delay(5000); //等待 DHCP 指派 IP
  
  Serial.println("Local IP ... " + wifi.getLocalIP()); //傳回本地 IP  
  if (wifi.setOprToStation()) {
    Serial.println("Set Operation Mode=Station ... OK");
    }  
  else {
    Serial.println("Set Operation Mode=Station ... Error");
    }  //設為 STA 模式 (1)
    
  delay(3000); //等待 DHCP 指派 IP
  
  Serial.println("Local IP ... " + wifi.getLocalIP()); //傳回本地 IP 
  Serial.print("List available APs ... ");  
  Serial.println(wifi.getAPList().c_str()); //傳回附近可用的 AP    
  if (wifi.restart()) {
    Serial.println("Restart ESP8266 ... OK");
    }  //重啟 ESP8266
  else {
    Serial.println("Restart ESP8266 ... Error");
    }  
  }
  
void loop() {
  if (sSerial.available()) {   //若軟體序列埠 Rx 收到資料 (來自 ESP8266)
    Serial.write(sSerial.read());  //讀取後寫入硬體序列埠 Tx (PC)
    }
  if (Serial.available()) {  //若硬體序列埠 Rx 收到資料 (來自 PC)
    sSerial.write(Serial.read());  //讀取後寫入軟體序列埠 Tx (ESP8266)
    }   
  }
