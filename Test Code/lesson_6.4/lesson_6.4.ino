/*
keyestudio smart sports watch
Project 6.4
Screen
http://www.keyestudio.com
*/
#include <DS1302.h>
#include "KS_ST7687S_Latch.h"
uint8_t CE_PIN   = A2;//DS1302使能脚
uint8_t IO_PIN   = A1;//DS1302数据脚
uint8_t SCLK_PIN = A0;//DS1302时钟脚
uint8_t pin_cs = 8, pin_rs = 5, pin_wr = 13, pin_lck = 12, pin_spi_scl = 4, pin_spi_mosi = 6;
KS_ST7687S_Latch tft(pin_cs, pin_rs, pin_wr , pin_lck, pin_spi_scl, pin_spi_mosi);

DS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);
  
void setup(void)
{
  Serial.begin(9600);
  rtc.write_protect(false);
  rtc.halt(false);
  Time t(2009, 5, 19, 21, 16, 37, 3);//设置时间年，月，日，时，分，秒，周
  rtc.time(t);

  pinMode(11,OUTPUT);   //11引脚控制屏幕亮度
  analogWrite(11,254);  //值范围0~255
  
  tft.begin();   //初始化屏幕设置
  tft.fillScreen(DISPLAY_BLUE); //背景色为蓝色
  tft.fillCircle(0, 0, 58, DISPLAY_WHITE);
}


void loop(void)
{
  Time t = rtc.time();//更新时间
  
  tft.setCursor(15, 55);  //设置字符打印的起始坐标
  tft.setTextBackground(DISPLAY_BLUE);  //set text background to black
  tft.setTextColor(DISPLAY_RED);  //set text color to red
  tft.setTextSize(2);  //2 * text size, default text size: 12 * 16
  tft.print(t.hr/10);
  tft.print(t.hr%10);
  tft.print(":");
  tft.print(t.min/10);
  tft.print(t.min%10);
  tft.print(":");
  tft.print(t.sec/10);
  tft.print(t.sec%10);
    delay(1000);
}
