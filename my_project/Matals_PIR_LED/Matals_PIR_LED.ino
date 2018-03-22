// Author : Tony Cheng
// Version : v0.1

const int PIN_PIR = 12;
const int PIN_LED = 13;
boolean LED_enabled = false;
int CountDown = 10;
unsigned long previousMillis_stayoncount = 0;
unsigned long currentMillis_stayoncount = 0;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_PIR,INPUT);
  pinMode(PIN_LED,OUTPUT);
}

void loop() {
  //=============== PIR process ===================
  int PIR_detected = digitalRead(PIN_PIR);
  currentMillis_stayoncount = millis();
  if ((currentMillis_stayoncount - previousMillis_stayoncount) > 1000) {
    Serial.println("PIR detect:");
    Serial.println(PIR_detected);
    Serial.println("LED_enabled:");
    Serial.println(LED_enabled);
    if (PIR_detected == HIGH and LED_enabled == false) {
      digitalWrite(PIN_LED, HIGH);
      LED_enabled = true;
      CountDown = 10;
    }
    else if (PIR_detected == HIGH and LED_enabled == true) {
      CountDown = 10;
    }
    else {
      CountDown--;
    }
    if (CountDown <= 0)  {
      digitalWrite(PIN_LED, LOW);
      LED_enabled = false;
      CountDown = 0;
    }
    Serial.println("CountDown:");
    Serial.println(CountDown);
    previousMillis_stayoncount = currentMillis_stayoncount;
  }
  //delay(1000);
}
