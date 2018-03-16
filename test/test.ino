#include "LCD12864RSPI.h"
#define AR_SIZE( a ) sizeof( a ) / sizeof( a[0] )

unsigned char show0[]={0xD6,0xD0,0xB1,0xB4,0xCB,0xB9,0xCC,0xD8};//中贝斯特
unsigned char show1[]="zhongBEST ";
 
void setup()
{
LCDA.Initialise(); // 屏幕初始化
delay(100);
}
 
void loop()
{
LCDA.CLEAR();//清屏
delay(100);
LCDA.DisplayString(0,0,show0,AR_SIZE(show0));//第一行第一格开始，显示中贝斯特
delay(100);
LCDA.DisplayString(2,0,show1,AR_SIZE(show1));//第三行第一格开始，显示网址zhongbest
delay(5000);
}
