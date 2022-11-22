/*
keyestudio smart sports watch
Project 6.2
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
  tft.fillScreen(DISPLAY_WHITE); //背景色为白
}

 
void loop(void)
{
  tft.drawCircle(0, 0, 20, DISPLAY_GREEN);  //draw circle
  delay(1000);
  tft.fillCircle(0, 0, 20, DISPLAY_RED);  //fill circle
  delay(1000);
  tft.fillScreen(DISPLAY_WHITE);
  tft.drawRect(-20, -20, 40, 40, DISPLAY_BLUE);  //draw rectangle
  delay(1000);
  tft.fillRect(-20, -20, 40, 40, DISPLAY_BLUE);  //fill rectangle
  delay(1000);
  tft.fillScreen(DISPLAY_WHITE);
  tft.drawTriangle(-20, -50, 0, 0, 50, 20, DISPLAY_ORANGE);  //draw triangle
  delay(1000);
  tft.fillTriangle(-20, -50, 0, 0, 50, 20, DISPLAY_ORANGE);  //fill triangle with color
  delay(1000);
  tft.fillScreen(DISPLAY_BLACK);
  tft.drawLine(-64, -64, 64, 64, DISPLAY_RED);  //draw line
  tft.drawHLine(-64, 0, 128, DISPLAY_WHITE);  //draw horizontal line
  tft.drawVLine(0, -64, 128, DISPLAY_WHITE);  //draw vertical line
  delay(1000); 
  tft.fillScreen(DISPLAY_WHITE);
}
