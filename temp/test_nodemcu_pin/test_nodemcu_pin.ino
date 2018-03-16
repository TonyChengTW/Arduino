#include <DHT.h>

#define DHTTYPE DHT22   // DHT 22  (AM2302)

// NodeMCU
const int TOUCH_PIN=16;
int sw=0;

void setup() {
    Serial.begin(115200);
    pinMode(TOUCH_PIN,INPUT);
  }

void loop() {
 int detected=digitalRead(TOUCH_PIN);
 if(detected == 1 and sw == 0) {
  sw = 1;
 }
 else if(detected == 1 and sw == 1) {
  sw = 0;
 }
 Serial.print("touch detect:");
 Serial.println(detected);
 Serial.print("sw:");
 Serial.println(sw);
 delay(1000);
}

void blink_led(int led) {
    digitalWrite(led,HIGH);
    delay(500);
    digitalWrite(led,LOW);
}

