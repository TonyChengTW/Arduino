#include "DHT.h"
#define DHTPIN 19
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor

void setup() {
  Serial.begin(9600);
  Serial.println("DHT11 test!");
  dht.begin();
  }

void loop() {
  delay(2000);
  float fh = dht.readHumidity();
  int h = (int) fh;
  float ft = dht.readTemperature();
  int t = (int) ft;
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
    }
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("*C\t");
}

