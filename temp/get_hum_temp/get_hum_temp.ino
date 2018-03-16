#include <DHT.h>

#define DHTTYPE DHT22   // DHT 22  (AM2302)

// NodeMCU
const int DHT22_PIN=16;

DHT dht(DHT22_PIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

int StayOnCount=0;
String str_hum_temp;
int DetectPeriod=3000;

void setup() {
  // DHT22 - 開始
  dht.begin();
  pinMode(DHT22_PIN,INPUT);
  Serial.begin(115200);
  }

void loop() {
  str_hum_temp = get_hum_temp();
  Serial.print("hum & temp:");
  Serial.println(str_hum_temp);
  delay(DetectPeriod);
}


String get_hum_temp() {
  String humidity = String(dht.readHumidity());
  String temperature = String(dht.readTemperature());
  String dht22_hum_temp = temperature.substring(0,5) + (char) 0xDF + "C  " + humidity.substring(0,4) + "%";
  return dht22_hum_temp;
}

