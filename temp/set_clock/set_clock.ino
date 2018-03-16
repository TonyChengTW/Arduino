#include <stdio.h>
#include <DS1302.h>
 
const int kCePin   = A4;  //RST
const int kIoPin   = A2;  //DAT
const int kSclkPin = A3;  //CLK
 
DS1302 rtc(kCePin, kIoPin, kSclkPin);
 
void printTime() {//顯示日期時間的函式
 Time t = rtc.time();
   char buf[50];
   snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);
    
   Serial.println(buf); 
}
 
void setup(){
  Serial.begin(9600);
  rtc.writeProtect(false);// 是否防止寫入 (日期時間設定成功後即可改成true)
  rtc.halt(false);// 是否停止計時
  Time t(2017, 9, 04, 15, 04, 50, Time::kSunday); //年 月 日 時 分 秒 星期幾 (日期時間設定成功後即可註解掉)
  rtc.time(t);//設定日期時間 (日期時間設定成功後即可註解掉)
}
void loop(){
  printTime();
  delay(1000);
}
