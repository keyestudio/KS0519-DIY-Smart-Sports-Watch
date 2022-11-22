/*
keyestudio smart sports watch
Project 6.1
Screen
http://www.keyestudio.com
*/
#include "KS_ST7687S_Latch.h"
int screen=1;
uint8_t pin_cs = 8, pin_rs = 5, pin_wr = 13, pin_lck = 12, pin_spi_scl = 4, pin_spi_mosi = 6;
KS_ST7687S_Latch tft(pin_cs, pin_rs, pin_wr , pin_lck, pin_spi_scl, pin_spi_mosi);
void setup(void)
{
  Serial.begin(115200);
  pinMode(11,OUTPUT);   //11引脚控制屏幕亮度
  analogWrite(11,254);  //值范围0~255
   tft.begin();   //初始化屏幕设置
}
void loop(void)
{
  tft.fillScreen(1000);  //刷新屏幕的颜色,取值为[0,65535]或4位16进制代码
  delay(1000);
  tft.fillScreen(0x0030); 
  delay(1000);
  tft.fillScreen(DISPLAY_RED);  //在函数库中已定义了19种常用颜色
  delay(1000);
  tft.fillScreen(DISPLAY_GREEN);  
  delay(1000);
  tft.fillScreen(DISPLAY_BLUE);  
  delay(1000);
  tft.fillScreen(DISPLAY_WHITE);
  delay(1000);
  tft.fillScreen(DISPLAY_BLACK);  
  delay(1000);
}
