#include <Adafruit_SSD1306.h>

/*********************************************************************
* 
* // # Update the Adafruit SSD1306 library to make it work
* // # Description:
* // #                 show a simple animation
* 
* // # Connection:
* // #        SCL  -> A5(Uno)/D3(Leonardo)
* // #        SDA  -> A4(Uno)/D2(Leonardo)
* // #        RST  -> D4
* // #        DC  -> GND
* // #        3.3  -> 3.3v
* // #        g  -> GND
* // #
* 
* This is an example for  OLED based on SSD1306 drivers
* 
* 
* This example is for a 128x64 size display using I2C to communicate
* 3 pins are required to interface (2 I2C and one reset)
* 
* Adafruit invests time and resources providing this open source code, 
* please support Adafruit and open-source hardware by purchasing 
* products from Adafruit!
* 
* All text above, and the splash screen must be included in any redistribution
*********************************************************************/
//本程序作用将多个汉字作为多个图形显示
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 64 //图片高度
#define LOGO16_GLCD_WIDTH  128 //图片宽度
//鄭
static const unsigned char PROGMEM bmp1[] =
{ 
0x00,0x00,0x11,0x12,0x0A,0x1F,0x7F,0xD2,0x0A,0x12,0x3F,0x94,0x2A,0x94,0x31,0x92,
0x2E,0x92,0x20,0x91,0x3F,0x91,0x04,0x11,0x7F,0xDE,0x0A,0x14,0x11,0x90,0x60,0x90,
};
//任
static const unsigned char PROGMEM bmp2[] =
{ 
0x00,0x00,0x0C,0x00,0x08,0x04,0x0B,0xFE,0x10,0x20,0x18,0x20,0x30,0x20,0x50,0x22,
0x17,0xFF,0x10,0x20,0x10,0x20,0x10,0x20,0x10,0x20,0x10,0x24,0x13,0xFE,0x10,0x00,
};
//峰
static const unsigned char PROGMEM bmp3[] =
{ 
0x00,0x00,0x18,0x60,0x10,0x44,0x10,0x7E,0x54,0x84,0x55,0x48,0x54,0x30,0x54,0xCC,
0x57,0x13,0x54,0xFE,0x54,0x10,0x7C,0xFE,0x44,0x10,0x41,0xFF,0x00,0x10,0x00,0x10,
};
//是
static const unsigned char PROGMEM bmp4[] =
{ 
0x00,0x00,0x08,0x08,0x0F,0xFC,0x08,0x08,0x0F,0xF8,0x08,0x08,0x0F,0xF8,0x08,0x08,
0x00,0x02,0x7F,0xFF,0x00,0x80,0x0C,0x88,0x08,0xFC,0x0C,0x80,0x13,0x80,0x60,0xFF,
};
//大
static const unsigned char PROGMEM bmp5[] =
{ 
0x00,0x00,0x00,0xC0,0x00,0x80,0x00,0x80,0x00,0x82,0x7F,0xFF,0x00,0x80,0x00,0x80,
0x01,0x80,0x01,0x40,0x02,0x20,0x02,0x20,0x04,0x10,0x08,0x08,0x10,0x07,0x60,0x02,
};
//帥
static const unsigned char PROGMEM bmp6[] =
{ 
0x00,0x00,0x18,0x18,0x10,0x10,0x20,0x92,0x7E,0xFF,0x42,0x92,0x42,0x92,0x7E,0x92,
0x42,0x92,0x40,0x92,0x7E,0x92,0x42,0x92,0x42,0x9E,0x7E,0x94,0x40,0x10,0x00,0x10,
};
//哥
static const unsigned char PROGMEM bmp7[] =
{ 
0x00,0x00,0x00,0x04,0x7F,0xFE,0x00,0x08,0x0F,0x88,0x08,0x88,0x0F,0x88,0x08,0x88,
0x00,0x0A,0x7F,0xFF,0x00,0x08,0x1F,0x88,0x10,0x88,0x1F,0x88,0x10,0xB8,0x00,0x10,
};

void setup()   {                
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);  // initialize with the I2C addr 0x3C (for the 128x64)
  // init done
  //初始化12864屏幕
  display.display(); // show splashscreen
  //显示闪屏，我理解是12864中固化的图片

  delay(2000);
  display.clearDisplay();   // clears the screen and buffer
  //清屏



}

int WIDTH=16; //汉字点陈宽度是30
int HEIGHT=16; //汉字点陈高度是29
void aa()//显示汉字
{
  //鄭
  display.clearDisplay();  
  display.drawBitmap(0, 0,  bmp1, WIDTH,HEIGHT, WHITE);
  display.display();
  //任
  display.drawBitmap(16, 8,  bmp2, WIDTH,HEIGHT, 1);     
  display.display();
  //峰
  display.drawBitmap(32, 16,  bmp3, WIDTH,HEIGHT, 1);     
  display.display();  
  //是
  display.drawBitmap(48, 32,  bmp4, WIDTH,HEIGHT, 1);     
  display.display();  
  //大
  display.drawBitmap(64, 48,  bmp5, WIDTH,HEIGHT, 1);     
  display.display();  
  //帥
  display.drawBitmap(80, 32,  bmp6, WIDTH,HEIGHT, 1);     
  display.display();  
  //哥
  display.drawBitmap(96, 16,  bmp7, WIDTH,HEIGHT, 1);     
  display.display();  
  delay(10000);  
}

void loop() {
  aa();//显示汉字

}
