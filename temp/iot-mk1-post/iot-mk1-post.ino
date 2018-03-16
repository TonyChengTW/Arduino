/*  
  Tony Cheng <tony.pig@gmail.com>
  Version : 0.3
  Platform : Arduino Uno R3
  Licensed under the Apache License, Version 2.0
  
  Use RESTful API to POST MQ series sensors
  and DHT series sensors via ESP8266-01 module
  The RESTful API code can be found at:
  https://github.com/TonyChengTW/iot-mk1/blob/master/iot-mk1-api.py

  ESP-8266-01 version
  AT version: 1.2.0.0 (Jul 1 2016)
  SDK version: 1.5.4.1(39cb9a32)
  Ai-Thinker Integrated AiCloud 2.0 v0.0.0.6
  Build: 1.5.4.1 May 16 2017
  2nd boot version : 1.6
  SPI Mode : DOUT
  SPI Speed : 40MHz
  SPI Flash Size & Map : 8Mbit(1MB) 512KB+512KB
*/

#include <SoftwareSerial.h>
#include <DHT.h>

#define SSID "Tony_WiFi"
#define PASS "8860225231449"
#define WIFI_RX_DPIN      7
#define WIFI_TX_DPIN      8
#define WIFI_POST_INTERVAL 10000
#define WIFI_CONNSRV_RETRY_INTERVAL 10000
#define SERIAL_BAUD       9600

#define DHT_DPIN          2
#define DHTTYPE           DHT11
#define SENSOR_MQ2_APIN   0
#define SENSOR_MQ7_APIN   1
#define SENSOR_MQ135_APIN 2

String server = "192.168.178.2"; // Tony IoT Mark1 Restful URI : http://122.116.224.14:7878/v1/iot-mk1
String uri = "/v1/iot-mk1";
String location = "Gobin-4F12";
String place = "My Desktop";
String data;

int sensor_mq2_avalue;
int sensor_mq7_avalue;
int sensor_mq135_avalue;
float sensor_temperature_dvalue;
float sensor_humidity_dvalue;

//DHT dht(DHT_DPIN, DHTTYPE); // Initialize DHT sensor
SoftwareSerial esp( WIFI_RX_DPIN, WIFI_TX_DPIN ); // RX, TX

void setup() {
    Serial.begin( SERIAL_BAUD );
    esp.begin( SERIAL_BAUD );
    esp.println("AT");
    set_wifi_mode();
    wifi_connect();
}

void loop() {
/*
    sensor_mq2_avalue = analogRead(SENSOR_MQ2_APIN);
    sensor_mq7_avalue = analogRead(SENSOR_MQ7_APIN);
    sensor_mq135_avalue = analogRead(SENSOR_MQ135_APIN);
    
    sensor_humidity_dvalue = dht.readHumidity();
    sensor_temperature_dvalue = dht.readTemperature();
    
    Serial.println("+-------------------------------------+");
    Serial.print("POST MQ2:");
    Serial.println(sensor_mq2_avalue);
    Serial.print("POST MQ7:");
    Serial.println(sensor_mq7_avalue);
    Serial.print("POST MQ135:");
    Serial.println(sensor_mq135_avalue);
    Serial.print("POST Temperature:");
    Serial.println(sensor_temperature_dvalue);
    Serial.print("POST Humidity:");
    Serial.println(sensor_humidity_dvalue);
    Serial.println("");

    // Sample : {\"measurement\":\"temperature\",\"value\":40,\"location\":\"Gobin-4F12\",\"place\":\"My Desktop\"}
*/
    //data = "{\"value1\":456}"; httppost();
    data = "{\"measurement\":\"temperature\",\"value\":40,\"location\":\"Gobin-4F12\",\"place\":\"My Desktop\"}"; httppost();
    delay(WIFI_POST_INTERVAL);
}
boolean set_wifi_mode() {
    esp.println("AT+CWMODE=1");
}

boolean connect_server() {
    Serial.println("TCP connecting.....");
    esp.println("AT+CIPSTART=\"TCP\",\"" + server + "\",7878"); //start a TCP connection.
    if( esp.find("OK")) {
        Serial.println("TCP connected!");
    }
    else {
        Serial.println("TCP connect failed, retry in 10 sec");
        delay(WIFI_CONNSRV_RETRY_INTERVAL);
        connect_server();
    }
    delay(2000);
}

void httppost() {
    connect_server();
    String postRequest =
    "POST " + uri + " HTTP/1.1\r\n" +
    "Host: " + server + "\r\n" +
    "Accept: *" + "/" + "*\r\n" +
    "Content-Length: " + data.length() + "\r\n" +
    "Content-Type: application/json\r\n" +
    "\r\n" + data;
    String sendCmd = "AT+CIPSEND=";//determine the number of caracters to be sent.
    esp.print(sendCmd);
    esp.println(postRequest.length() );
    delay(500);
    if(esp.find(">")) {
      Serial.print("Sending.. : ");
      Serial.print(postRequest);
      esp.print(postRequest);
    }
    if( esp.find("SEND OK")) {
      Serial.println("Packet sent");
    }
    
    while (esp.available()) {
      String tmpResp = esp.readString();
      Serial.println(tmpResp);
    }
    // close the connection
    esp.println("AT+CIPCLOSE");
    if( esp.find("OK")) {
      Serial.println("Close connection");
    }
}

void wifi_connect()
{
    String cmd="AT+CWJAP=\"";
    cmd+=SSID;
    cmd+="\",\"";
    cmd+=PASS;
    cmd+="\"";
    esp.println(cmd);
    Loading("wifi_connect");
}

void Loading(String state){
    for (int timeout=0 ; timeout<10 ; timeout++)
    {
      if(esp.find("OK"))
      {
          Serial.println("WiFi connected");
          break;
      }
      else if(timeout==7){
        Serial.print( state );
        Serial.println(" Can not Wifi connect: AT+CWJAP. Timeout and giveup\nExit2");
        break;
      }
      else
      {
        Serial.print("Wifi Loading...");
        delay(2000);
      }
    }
}

