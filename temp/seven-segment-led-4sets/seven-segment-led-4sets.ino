/*
 * show 7-segement LED by scanning.
 * Author : Tony
 */

#include <DS1302.h>

// DS1302 rtc([RST], [DAT], [CLOCK])
DS1302 rtc(A4, A2, A3);

unsigned long interval = 3; // the time we need to wait
unsigned long previousMillis = 0; // millis() returns an unsigned long.
unsigned long currentMillis = 0;
String original_time;
int digi1;
int digi2;
int digi3;
int digi4;

const short int LED_A = 2;     //LED pin13
const short int LED_B = 3;      //LED pin9
const short int LED_C = 4;      //LED pin4
const short int LED_D = 5;      //LED pin2
const short int LED_E = 6;      //LED pin1
const short int LED_F = 7;     //LED pin12
const short int LED_G = 8;      //LED pin5
const short int LED_56C = 9;    //LED pin7
const short int LED_56 = 10;     //LED pin8
const short int LED_DIG1 = 11;  //LED pin14
const short int LED_DIG2 = 12;  //LED pin11
const short int LED_DIG3 = 13;  //LED pin10
const short int LED_DIG4 = A0;   //LED pin6
const short int LED_DP = A1;   //LED pin3

// LED PIN mapping {A,B,C,D,E,F,G}
short int num0[] = {1,1,1,1,1,1,0};
short int num1[] = {0,1,1,0,0,0,0};
short int num2[] = {1,1,0,1,1,0,1};
short int num3[] = {1,1,1,1,0,0,1};
short int num4[] = {0,1,1,0,0,1,1};
short int num5[] = {1,0,1,1,0,1,1};
short int num6[] = {1,0,1,1,1,1,1};
short int num7[] = {1,1,1,0,0,1,0};
short int num8[] = {1,1,1,1,1,1,1};
short int num9[] = {1,1,1,1,0,1,1};


void setup() {
  // DS1302 - 設定時鐘為正常執行模式
  rtc.halt(false); 
  // DS1302 - 取消寫入保護，設定日期時要這行
  //rtc.writeProtect(false);
  rtc.writeProtect(true);
  //set_date_time();
  
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_C, OUTPUT);
  pinMode(LED_D, OUTPUT);
  pinMode(LED_E, OUTPUT);
  pinMode(LED_F, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_56C, OUTPUT);
  pinMode(LED_56, OUTPUT);
  pinMode(LED_DIG1, OUTPUT);
  pinMode(LED_DIG2, OUTPUT);
  pinMode(LED_DIG3, OUTPUT);
  pinMode(LED_DIG4, OUTPUT);
  pinMode(LED_DP, OUTPUT);                     
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis < interval * 1.2) {
    original_time = rtc.getTimeStr();
    digi1 = original_time.substring(0,1).toInt();
    digi2 = original_time.substring(1,2).toInt();
    digi3 = original_time.substring(3,4).toInt();
    digi4 = original_time.substring(4,5).toInt();

    switch (digi1) {
      case 0:
        lighting_led_single(1, num0);
      break;
      case 1:
        lighting_led_single(1, num1);
      break;
      case 2:
        lighting_led_single(1, num2);
      break;
    }
  }
  else if ((currentMillis - previousMillis >= interval*1) and (currentMillis - previousMillis < interval*2.4))  {
    switch (digi2) {
      case 0:
        lighting_led_single(2, num0);
      break;
      case 1:
        lighting_led_single(2, num1);
      break;
      case 2:
        lighting_led_single(2, num2);
      break;
      case 3:
        lighting_led_single(2, num3);
      break;
      case 4:
        lighting_led_single(2, num4);
      break;
      case 5:
        lighting_led_single(2, num5);
      break;
      case 6:
        lighting_led_single(2, num6);
      break;
      case 7:
        lighting_led_single(2, num7);
      break;
      case 8:
        lighting_led_single(2, num8);
      break;
      case 9:
        lighting_led_single(2, num9);
      break;
    }
  }
  else if ((currentMillis - previousMillis >= interval*2) and (currentMillis - previousMillis < interval * 3.8)) {
    switch (digi3) {
      case 0:
        lighting_led_single(3, num0);
      break;
      case 1:
        lighting_led_single(3, num1);
      break;
      case 2:
        lighting_led_single(3, num2);
      break;
      case 3:
        lighting_led_single(3, num3);
      break;
      case 4:
        lighting_led_single(3, num4);
      break;
      case 5:
        lighting_led_single(3, num5);
      break;
    }
  }
  else if ((currentMillis - previousMillis >= interval*3) and (currentMillis - previousMillis < interval*4.8)) {
    switch (digi4) {
      case 0:
        lighting_led_single(4, num0);
      break;
      case 1:
        lighting_led_single(4, num1);
      break;
      case 2:
        lighting_led_single(4, num2);
      break;
      case 3:
        lighting_led_single(4, num3);
      break;
      case 4:
        lighting_led_single(4, num4);
      break;
      case 5:
        lighting_led_single(4, num5);
      break;
      case 6:
        lighting_led_single(4, num6);
      break;
      case 7:
        lighting_led_single(4, num7);
      break;
      case 8:
        lighting_led_single(4, num8);
      break;
      case 9:
        lighting_led_single(4, num9);
      break;
    }
  }
  else if (currentMillis - previousMillis >= interval*4) {
      previousMillis = currentMillis;
  }
}

void lighting_led_single(int digi_n, short int num[]) {
  digitalWrite(LED_A, num[0]);
  digitalWrite(LED_B, num[1]);
  digitalWrite(LED_C, num[2]);
  digitalWrite(LED_D, num[3]);
  digitalWrite(LED_E, num[4]);
  digitalWrite(LED_F, num[5]);
  digitalWrite(LED_G, num[6]);
  switch (digi_n) {
    case 1: 
      digitalWrite(LED_DIG1, LOW);
      digitalWrite(LED_DIG2, HIGH);
      digitalWrite(LED_DIG3, HIGH);
      digitalWrite(LED_DIG4, HIGH);
      break;
    case 2:
      digitalWrite(LED_DIG1, HIGH);
      digitalWrite(LED_DIG2, LOW);
      digitalWrite(LED_DIG3, HIGH);
      digitalWrite(LED_DIG4, HIGH);
      break;
    case 3:
      digitalWrite(LED_DIG1, HIGH);
      digitalWrite(LED_DIG2, HIGH);
      digitalWrite(LED_DIG3, LOW);
      digitalWrite(LED_DIG4, HIGH); 
      break;
    case 4:
      digitalWrite(LED_DIG1, HIGH);
      digitalWrite(LED_DIG2, HIGH);
      digitalWrite(LED_DIG3, HIGH);
      digitalWrite(LED_DIG4, LOW);
      break; 
  }

    digitalWrite(LED_56C, LOW);
    digitalWrite(LED_56, HIGH);
/*
    digitalWrite(LED_DP, LOW);
*/
}

void lighting_led_together(int digi1[], int digi2[], int digi3[], int digi4[]) {
  digitalWrite(LED_A, digi1[0]);
  digitalWrite(LED_B, digi1[1]);
  digitalWrite(LED_C, digi1[2]);
  digitalWrite(LED_D, digi1[3]);
  digitalWrite(LED_E, digi1[4]);
  digitalWrite(LED_F, digi1[5]);
  digitalWrite(LED_G, digi1[6]);
  digitalWrite(LED_DIG1, LOW);
  digitalWrite(LED_DIG2, HIGH);
  digitalWrite(LED_DIG3, HIGH);
  digitalWrite(LED_DIG4, HIGH); 
  digitalWrite(LED_A, digi2[0]);
  digitalWrite(LED_B, digi2[1]);
  digitalWrite(LED_C, digi2[2]);
  digitalWrite(LED_D, digi2[3]);
  digitalWrite(LED_E, digi2[4]);
  digitalWrite(LED_F, digi2[5]);
  digitalWrite(LED_G, digi2[6]);
  digitalWrite(LED_DIG1, HIGH);
  digitalWrite(LED_DIG2, LOW);
  digitalWrite(LED_DIG3, HIGH);
  digitalWrite(LED_DIG4, HIGH); 
  delay(interval);
  digitalWrite(LED_A, digi3[0]);
  digitalWrite(LED_B, digi3[1]);
  digitalWrite(LED_C, digi3[2]);
  digitalWrite(LED_D, digi3[3]);
  digitalWrite(LED_E, digi3[4]);
  digitalWrite(LED_F, digi3[5]);
  digitalWrite(LED_G, digi3[6]);
  digitalWrite(LED_DIG1, HIGH);
  digitalWrite(LED_DIG2, HIGH);
  digitalWrite(LED_DIG3, LOW);
  digitalWrite(LED_DIG4, HIGH); 
  delay(interval);
  digitalWrite(LED_A, digi4[0]);
  digitalWrite(LED_B, digi4[1]);
  digitalWrite(LED_C, digi4[2]);
  digitalWrite(LED_D, digi4[3]);
  digitalWrite(LED_E, digi4[4]);
  digitalWrite(LED_F, digi4[5]);
  digitalWrite(LED_G, digi4[6]);
  digitalWrite(LED_DIG1, HIGH);
  digitalWrite(LED_DIG2, HIGH);
  digitalWrite(LED_DIG3, HIGH);
  digitalWrite(LED_DIG4, LOW); 
  delay(interval);  
}

