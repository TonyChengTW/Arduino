#include <DHT.h>
#include <ESP8266WiFi.h>

#define DHTTYPE DHT22   // DHT 22  (AM2302)
const char* ssid     = "Tony-WiFi";
const char* password = "8860225231449";
const char* host = "192.168.178.2";
const int httpPort = 7878;

// NodeMCU
const int DHT_PIN = 5;
const int PIR_PIN = 4;
const int RELAY_PIN = 0;
const int TOUCH_PIN = 13;
const int SW_LED_PIN = 12;
boolean PIR_STAT = false;
boolean SWITCH = false;
int StayOnCount = 0;
int wifi_dht_interval_count;
int DetectPeriod = 1000;
int wifi_dht_interval = 60000;

DHT dht(DHT_PIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

void setup() {
  Serial.begin(115200);
  pinMode(DHT_PIN,INPUT);
  pinMode(TOUCH_PIN,INPUT);
  pinMode(PIR_PIN,INPUT);
  pinMode(RELAY_PIN,OUTPUT);
  pinMode(SW_LED_PIN,OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.print("WiFi connected!  IP address: ");
  Serial.println(WiFi.localIP()); 
}

void loop() {
  //=============== PIR & Switch process ===================
  int pir_detected = digitalRead(PIR_PIN);
  int touch_detected = digitalRead(TOUCH_PIN);
  
  // define SWITCH
  if (touch_detected == HIGH and SWITCH == false) {
    SWITCH = true;
    digitalWrite(SW_LED_PIN, HIGH);
  }
  else if (touch_detected == HIGH and SWITCH == true) {
    SWITCH = false;
    digitalWrite(SW_LED_PIN, LOW);
  }
      
  //  relay --> high
  if ((pir_detected == HIGH and PIR_STAT == false) or (SWITCH == true)) {
    PIR_STAT=true;
    relay_high(RELAY_PIN);
    StayOnCount=10;
  }
  else if ((pir_detected == HIGH and PIR_STAT == true) and (SWITCH == false)) {
    if ((StayOnCount < 5) and (StayOnCount > 3))  {
       StayOnCount=25;
    }
    if (StayOnCount <= 3) {
       StayOnCount=30;
    }
  }
  // relay --> low
  else if ((pir_detected == LOW and PIR_STAT == true) or (SWITCH == false)) {
    if (StayOnCount==0) {
      PIR_STAT=false;
      relay_low(RELAY_PIN);
    }
    else {
      StayOnCount--;
      delay(500);
    }
  }

  Serial.print("StayOnCount=");
  Serial.println(StayOnCount);
  Serial.print("pir_detected=");
  Serial.println(pir_detected);
  Serial.print("PIR_STAT=");
  Serial.println(PIR_STAT);
  Serial.print("touch_detected=");
  Serial.println(touch_detected);
  Serial.print("SWITCH=");
  Serial.println(SWITCH);
  Serial.print("wifi_dht_interval_count=");
  Serial.print(wifi_dht_interval_count);
  Serial.println();
 
  //=============== DHT & WiFi POST process ===================

  if (wifi_dht_interval_count == 0) {
    String *array_hum_temp = get_hum_temp_post();
    Serial.println(array_hum_temp[0]);
    Serial.println(array_hum_temp[1]);
    
    // post humidity
    String hum_header_body = concatenate_header_body("humidity", array_hum_temp[0], "Gobin-4F12", "My bedroom");
    post_hum_temp(hum_header_body);
    
    // post temperature
    hum_header_body = concatenate_header_body("temperature", array_hum_temp[1], "Gobin-4F12", "My bedroom");
    post_hum_temp(hum_header_body);

    //reset wifi_dht_interval_count
    wifi_dht_interval_count = wifi_dht_interval/DetectPeriod;
  }
  wifi_dht_interval_count--;

  //===============Detect Period ==================
  delay(DetectPeriod);
}

//============= Function ==========================
String * get_hum_temp_post() {
  static String hum_temp[2];
  hum_temp[0] = String(dht.readHumidity());
  hum_temp[1] = String(dht.readTemperature());
  return hum_temp;
}

void relay_low(int pin) {
    digitalWrite(pin,LOW);
}

void relay_high(int pin) {
    digitalWrite(pin,HIGH);
}


String concatenate_header_body(String measurement, String value, String location, String place)
{
    // Tony - IoT Mark2 POST   , data format is --> {"measurement":"temperature","value":"40","location":"Gobin-4F12","place":"My Desktop"}
    String body = "{\"measurement\":\"" + measurement + "\",\"value\":\"" + value + "\",\"location\":\"" + location + "\",\"place\":\"" + place + "\"}";
    String header = "POST /v1/iot-mk2 HTTP/1.1\r\n";

    // header += "User-Agent: Tony KTduino UNO 1/1.0\r\n";
    header += "Content-Type: application/json\r\n";
    header += "Content-Length: " + String(body.length()) + "\r\n";
    header += "\r\n";
    String header_with_body = header + body;
    return header_with_body;
}

void post_hum_temp(String header_body) {
    WiFiClient client;
    if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return;
    }
    
    wifi_dht_interval_count = wifi_dht_interval/DetectPeriod;
    client.print(header_body);
    Serial.print(header_body);
    
    if (client.connected()) { 
      client.stop();  // DISCONNECT FROM THE SERVER
    }
    Serial.println();
    Serial.println("closing connection");
}