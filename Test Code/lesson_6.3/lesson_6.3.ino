/*
keyestudio smart sports watch
Project 6.3
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
  tft.fillScreen(DISPLAY_BLACK); //背景色为黑
}

 
void loop(void)
{
  tft.setCursor(30, 55);  //设置字符打印的起始坐标
  tft.setTextBackground(DISPLAY_YELLOW);  //set text background to black
  tft.setTextColor(DISPLAY_BLUE);  //set text color to white
  tft.setTextSize(2);  //2 * text size, default text size: 12 * 16
  tft.print("Hello");
  tft.setCursor(30, 71);
  tft.setTextBackground(DISPLAY_GREEN);
  tft.setTextColor(DISPLAY_RED);
  tft.setTextSize(1);
  tft.print("World!");
  delay(1000);
}
