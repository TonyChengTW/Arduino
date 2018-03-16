// Author : Tony Cheng
// Version : v0.5

//#include <DS1302.h>
#include <DHT.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// -------- 宣告變數 LCD --------------
const int SCREEN_REFRESH = 300;
const int SCREEN_HOLD = 3000;

// -------- 宣告變數 DS1302 --------------
String str_date_time;

// -------- 宣告變數 DHT22 --------------
const int WIFI_POST_IVLCOUNT = 60;
String str_hum_temp;

// -------- 宣告變數 ESP8266 -----------
int wifi_sample_count;


// -------- 初始化 LiquidCrystal ---------------
//                 LCD 接腳:  rs, enable, d4, d5, d6, d7  
//      對應到 Arduino 接腳:  12,     11,  5,  4,  3,  2
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// -------- 初始化 DS1302 ----------------------
// DS1302 rtc([RST], [DAT], [CLOCK])
//DS1302 rtc(10, 9, 8);

// --------- 初始化 DHT22 --------------------------------
#define DHTPIN 14     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

// --------- 初始化 ESP8266 -----------------------------
#define WIFI_RX_DPIN      6
#define WIFI_TX_DPIN      7
#define SERIAL_BAUD       9600
#define SSID "Tony-MiWiFi"
#define PASS "8860225231449"
#define API_SERVER1 "192.168.178.2"
#define API_SERVER1_PORT1 "7878"


SoftwareSerial wifi( WIFI_RX_DPIN, WIFI_TX_DPIN ); // RX, TX

// --------- Setup 開始 -------------------------------
void setup() {
  Serial.begin(SERIAL_BAUD);
  // WiFi - 初始化檢查
  init_wifi();
  // WiFi - 連線 AP
  delay(2000);
  connect_ap();
  
  // LCD - 設定 LCD 的行列數目 (2 x 16)
  lcd.begin(16, 2);
/*  
  // DS1302 - 設定時鐘為正常執行模式
  rtc.halt(false); 
  // DS1302 - 取消寫入保護，設定日期時要這行
  rtc.writeProtect(false);
  // DHT22 - 開始
  dht.begin();
*/
}

void loop() {
  // LCD Page 1
//  str_date_time = get_date_time_lcd();
  str_hum_temp = get_hum_temp_lcd();
  lcd.clear();
  //lcd.setCursor(0, 0);
  //lcd.print(str_date_time);
  lcd.setCursor(0, 1);
  lcd.print(str_hum_temp);
  //delay(SCREEN_HOLD);

  // LCD Page 2
  /* str_date_time = "1234567890123456";
  //str_hum_temp = "abcdefghijklmnop";
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(str_date_time);
  lcd.setCursor(0, 1);
  lcd.print(str_hum_temp);
  delay(SCREEN_HOLD);
  */
  if (wifi_sample_count == WIFI_POST_IVLCOUNT) {
    String *array_hum_temp = get_hum_temp_post();
    Serial.println(array_hum_temp[0]);
    Serial.println(array_hum_temp[1]);
    wifi_sample_count = 0;
    // POST temp & hum to API Server
    post_hum(array_hum_temp[0]);
    post_temp(array_hum_temp[1]);
  }
  wifi_sample_count++;
  Serial.println(wifi_sample_count);
  lcd.setCursor(0, 0);
  lcd.print(wifi_sample_count);
  lcd.setCursor(3, 0);
  lcd.print("/60(Counter)");

  delay (SCREEN_REFRESH);
}
/*
// ----------- 自定義函式 -----------------
String get_date_time_lcd() {
  String weekday = rtc.getDOWStr();
  String original_date = rtc.getDateStr();
  String original_time = rtc.getTimeStr();
  String substring_month = original_date.substring(3,5);
  String substring_date = original_date.substring(0,2);
  String substring_time = original_time.substring(0,5);
  String date_time_str = weekday + " " + substring_month + "/" + substring_date + " " + substring_time ;
  return date_time_str;
}

void set_date_time() {
  // 以下是設定時間的方法，在電池用完之前，只要設定一次就行了
  rtc.setDOW(SATURDAY);        // 設定週幾，如FRIDAY
  rtc.setTime(16, 58, 0);     // 設定時間 時，分，秒 (24hr format)
  rtc.setDate(29, 7, 2017);   // 設定日期 日，月，年
}
*/

String get_hum_temp_lcd() {
  String humidity = String(dht.readHumidity());
  String temperature = String(dht.readTemperature());
  String dht22_hum_temp = temperature.substring(0,5) + (char) 0xDF + "C  " + humidity.substring(0,4) + "%";
  return dht22_hum_temp;
}

String * get_hum_temp_post() {
  static String hum_temp[2];
  hum_temp[0] = String(dht.readHumidity());
  hum_temp[1] = String(dht.readTemperature());
  return hum_temp;
}

boolean init_wifi() {
  wifi.begin( SERIAL_BAUD );
  //wifi.println("AT+RST");
  wifi.println("AT");
  for (int timeout=0 ; timeout<10 ; timeout++)
    {
      if(wifi.find("OK"))
      {
        lcd.setCursor(0, 0);
        lcd.print("WiFi init OK");
        delay(3000);
        lcd.clear();
        return true;
        // break;
      }
      else if(timeout==9)
      {
        lcd.setCursor(0, 0);
        lcd.print("WiFi init fail");   // Can not Wifi connect: AT+CWJAP. Timeout and giveup\nExit2");
        delay(3000);
        lcd.clear();
        return false;
        // break;
      }
      else
      {
        lcd.setCursor(0, 0);
        lcd.print("Wifi:Initialize");
        delay(2000);
      }
    }
}

boolean connect_ap() {
  wifi.println("AT+CWMODE=1");
  String cmd="AT+CWJAP=\"";  //連線指定之基地台 (Join AP)
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  wifi.println(cmd);
  for (int timeout=0 ; timeout<10 ; timeout++)
    {
      if(wifi.find("OK"))
      {
        lcd.setCursor(0, 0);
        lcd.print("AP Connect OK");
        delay(3000);
        lcd.clear();
        return true;
        // break;
      }
      else if(timeout==9)
      {
        lcd.setCursor(0, 0);
        lcd.print("AP Connect Fail");   // Can not Wifi connect: AT+CWJAP. Timeout and giveup\nExit2");
        delay(3000);
        lcd.clear();
        return false;
        // break;
      }
      else
      {
        lcd.setCursor(0, 0);
        lcd.print("Wifi Connecting");
        delay(2000);
      }
    }
}

void post_hum(String hum)
{    
    String hum_body = concatenate_header_body("humidity",hum,"Gobin-4F12","My Desktop");
    connect_api_server();
    //Serial.print("----------------- hum_body=");
    //Serial.println(hum_body);
    post_api_server(hum_body);
}

void post_temp(String temp)
{    
    String temp_body = concatenate_header_body("temperature",temp,"Gobin-4F12","My Desktop");
    connect_api_server();
    //Serial.print("----------------- temp_body=");
    //Serial.println(temp_body);
    post_api_server(temp_body);
}

void connect_api_server()
{
    // 設定 ESP8266 作為 Client 端
    String cmd = "AT+CIPSTART=\"TCP\",\"";
    cmd += API_SERVER1;
    cmd += "\",";
    cmd += API_SERVER1_PORT1;
    //String cmd_debug = "AT+CIPSTART=\"TCP\",\"192.168.178.2\",7878";
    
    Serial.println(cmd);
    //Serial.println(cmd_debug);  //it should be --> AT+CIPSTART="TCP","192.168.178.2",7878
    wifi.println(cmd);
    // cmd = "";  // 清除 cmd 變數內容
    if( wifi.find( "Error" ) )
    {
        Serial.print( "RECEIVED: Error\nExit1" );
        return;
    }
}

String concatenate_header_body(String measurement, String value, String location, String place)
{
    // Tony - IoT Mark2 POST   , data format is --> {"measurement":"temperature","value":"40","location":"Gobin-4F12","place":"My Desktop"}
    String body = "{\"measurement\":\"" + measurement + "\",\"value\":\"" + value + "\",\"location\":\"" + location + "\",\"place\":\"" + place + "\"}";
    String header = "POST /v1/iot-mk2 HTTP/1.1\r\n";

    // header += "User-Agent: Tony KTduino UNO 1/1.0\r\n";
    header += "Content-Type: application/json\r\n";
    header += "Content-Length: " + String(body.length()) + "\r\n";
    header += "\r\n";
    String header_with_body = header + body;
    return header_with_body;
}

void post_api_server(String header_with_body)
{
    Serial.println("header_with_body:");
    Serial.println(header_with_body);
    Serial.println("ready to send AT+CIPSEND");
    wifi.print( "AT+CIPSEND=" );
    wifi.println( header_with_body.length() );
    delay(1000);  //等待 大於符號 回應
    if(wifi.find( ">" ) )
    {
        wifi.print(header_with_body);
        header_with_body = "";
    }
    else
    {
        Serial.println( "AT+CIPCLOSE" );
        wifi.println( "AT+CIPCLOSE" );   // 關閉 IP 連線
        header_with_body = "";
    }

    if( wifi.find("OK") )
    {
        Serial.println( "Send: OK" );
        header_with_body = "";
        lcd.setCursor(0, 0);
        lcd.print("iot-mk2 POST ok");
    }
    else
    {
        Serial.println( "Send: Sent Head+Body Failed \nExit3" );
        header_with_body = "";
        lcd.setCursor(0, 0);
        lcd.print("POST failed");
        // Serial.print("debug s2: cipsend?= "); //偵錯
        // Serial.println(debug.println( "AT+CIPSEND?" )); //偵錯
    }
}

