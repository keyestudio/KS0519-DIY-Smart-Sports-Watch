/*
keyestudio smart sports watch
Project 5
DS1302
http://www.keyestudio.com
*/
#include <stdio.h>
#include <string.h>
#include <DS1302.h>
/* Set the appropriate digital I/O pin connections */
uint8_t CE_PIN   = A2;//DS1302使能脚
uint8_t IO_PIN   = A1;//DS1302数据脚
uint8_t SCLK_PIN = A0;//DS1302时钟脚
/* Create buffers */
/* Create a DS1302 object */
DS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);
void setup()
{
  Serial.begin(9600);
  rtc.write_protect(false);
  rtc.halt(false);
  Time t(2009, 5, 19, 21, 16, 37, 3);//设置时间年，月，日，时，分，秒，周
  rtc.time(t);
}
/* Loop and print the time every second */
void loop()
{
Time t = rtc.time();
Serial.print(t.yr);//年
Serial.print("-");
Serial.print(t.mon);//月
Serial.print("-");
Serial.print(t.date);//日
Serial.print("  ");
Serial.print(t.hr);//时
Serial.print(":");
Serial.print(t.min);//分
Serial.print(":");
Serial.print(t.sec);//秒
Serial.print("  ");
Serial.println(t.day);//周
delay(1000);
}
