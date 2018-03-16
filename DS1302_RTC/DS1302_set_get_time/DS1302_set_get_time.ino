#include <DS1302.h>

#define SERIAL_BAUD   9600

// DS1302 rtc([RST], [DAT], [CLOCK])
DS1302 rtc(A4, A2, A3);
//DS1302 rtc(11, 10, 12);

// -------- 宣告變數 DS1302 --------------
String str_date_time;

void setup() {
  Serial.begin(SERIAL_BAUD);

  rtc.writeProtect(true);// 是否防止寫入 | 日期時間設定成功後即可改成 false --> true
  rtc.halt(false);// 是否停止計時  | 若要停止可改成 false --> true
  /*
  rtc.setDOW(MONDAY);        // 設定DS1302時間模組的 "星期"
  rtc.setTime(19, 43, 00);     // 設定DS1302時間模組的 "時間"
  rtc.setDate(4, 9, 2017);   // 設定DS1302時間模組的 "天數"
  */
}

void loop() {
  delay(1000);
  //String date_time_str = get_date_time();
  //Serial.println(date_time_str);
  //將得到的日期時間顯示在Serial視窗 
   
  // 週幾
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  
  // 日期
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  // 時間
  Serial.println(rtc.getTimeStr());

}


// ----------- 自定義函式 -----------------
String get_date_time() {
  String weekday = rtc.getDOWStr();
  String original_date = rtc.getDateStr();
  String original_time = rtc.getTimeStr();
  //String substring_month = original_date.substring(3,5);
  //String substring_date = original_date.substring(0,2);
  String date_time_str = rtc.getTimeStr();
  //String substring_time = original_time.substring(0,5);
  //String date_time_str = weekday + " " + substring_month + "/" + substring_date + " " + substring_time ;
  return date_time_str;
}

