const int PIR_PIN=2;
const int RELAY_PIN=3;
const int DetectPeriod=2500;

int StayOnCount=0;
boolean PIR_STAT=false;

void setup() {
  pinMode(RELAY_PIN,OUTPUT);
  pinMode(PIR_PIN,INPUT);
  Serial.begin(115200);
  relay_low(RELAY_PIN);
  }

void loop() {
  int detected=digitalRead(PIR_PIN);
  if (detected==HIGH and PIR_STAT==false) {
    PIR_STAT=true;
    relay_high(RELAY_PIN);
    StayOnCount=10;
  }
  else if (detected==LOW and PIR_STAT==true) {
    if (StayOnCount==0) {
      PIR_STAT=false;
      relay_low(RELAY_PIN);
    }
    else {
      StayOnCount--;
    }
  }
  else if (detected==HIGH and PIR_STAT==true)  {
    StayOnCount=10;
  }
  Serial.print("StayOnCount=");
  Serial.println(StayOnCount);
  delay(DetectPeriod);
}

void relay_low(int led) {
    digitalWrite(led,HIGH);
}

void relay_high(int led) {
    digitalWrite(led,LOW);
}

void blink_led(int led) {
    digitalWrite(led,HIGH);
    delay(500);
    digitalWrite(led,LOW);
}

