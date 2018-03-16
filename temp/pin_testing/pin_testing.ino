const int PIN=14;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  digitalWrite(2, LOW);   // turn the LED on (HIGH is the voltage level)                       // wait for a second
  digitalWrite(3, HIGH);    // turn the LED off by making the voltage LOW
}
