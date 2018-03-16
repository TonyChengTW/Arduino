#include <DHT.h>

#define DHTTYPE DHT22   // DHT 22  (AM2302)

// NodeMCU
const int DHT_PIN=5;
const int PIR_PIN=4;
const int RELAY_PIN=0;
const int DetectPeriod=2400;
boolean PIR_STAT=false;
int StayOnCount=0;

DHT dht(DHT_PIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

void setup() {
    Serial.begin(115200);
    pinMode(DHT_PIN,INPUT);
    pinMode(RELAY_PIN,OUTPUT);
  }

void loop() {
  //=============== PIR process ===================
  int pir_detected = digitalRead(PIR_PIN);
  if (pir_detected == HIGH and PIR_STAT == false) {
    PIR_STAT = true;
    relay_high(RELAY_PIN);
    StayOnCount=10;
  }
  else if (pir_detected == LOW and PIR_STAT == true) {
    if (StayOnCount==0) {
      PIR_STAT=false;
      relay_low(RELAY_PIN);
    }
    else {
      StayOnCount--;
    }
  }
  else if (pir_detected == HIGH and PIR_STAT == true)  {
    StayOnCount=10;
  }
  Serial.print("StayOnCount=");
  Serial.println(StayOnCount);
 
  //=============== DHT process ===================
 String hum_temp = get_hum_temp_lcd();
 Serial.println(hum_temp);

  //=============== post process ===================
 delay(DetectPeriod);
}

void blink_led(int led) {
    digitalWrite(led,HIGH);
    delay(500);
    digitalWrite(led,LOW);
}

String get_hum_temp_lcd() {
  String humidity = String(dht.readHumidity());
  String temperature = String(dht.readTemperature());
  String dht22_hum_temp = temperature.substring(0,5) + (char) 0xDF + "C  " + humidity.substring(0,4) + "%";
  return dht22_hum_temp;
}

void relay_low(int pin) {
    digitalWrite(pin,LOW);
}

void relay_high(int pin) {
    digitalWrite(pin,HIGH);
}

