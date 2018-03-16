/* Lab9 - 在 2x16 LCD 上顯示 "Hello World" 訊息  
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * 10K Potentiometer:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 This example code is in the public domain.
 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// 引用 LiquidCrystal Library
#include <LiquidCrystal.h>

// 建立 LiquidCrystal 的變數 lcd
//                 LCD 接腳:  rs, enable, d4, d5, d6, d7  
//      對應到 Arduino 接腳:  12,     11,  5,  4,  3,  2
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // 設定 LCD 的行列數目 (2 x 16)
  lcd.begin(16, 2);

  // 列印 "Hello World" 訊息到 LCD 上
  lcd.print("hello, world!");
}

void loop() {
  // 將游標設到 column 0, line 1
  // (注意: line 1 是第二行(row)，因為是從 0 開始數起):
  lcd.setCursor(0, 1);

  // 列印 Arduino 重開之後經過的秒數
  lcd.print(millis()/1000);
}
