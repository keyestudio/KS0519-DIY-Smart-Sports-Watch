/*
keyestudio smart sports watch
Project 6.6
Screen
http://www.keyestudio.com
*/

#include <DS1302.h>
uint8_t CE_PIN   = A2;//DS1302使能脚
uint8_t IO_PIN   = A1;//DS1302数据脚
uint8_t SCLK_PIN = A0;//DS1302时钟脚

DS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);
#include "KS_ST7687S_Latch.h"
uint8_t pin_cs = 8, pin_rs = 5, pin_wr = 13, pin_lck = 12, pin_spi_scl = 4, pin_spi_mosi = 6;
KS_ST7687S_Latch tft(pin_cs, pin_rs, pin_wr , pin_lck, pin_spi_scl, pin_spi_mosi);
  
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
    
      tft.begin();
     
      tft.drawHLine(-58, -20, 116, DISPLAY_RED);
      //tft.drawCircle(-1, 0, 61, DISPLAY_GREEN); 
      tft.setCursor(23, 20);
       tft.setTextBackground(DISPLAY_WHITE);
      tft.setTextColor(DISPLAY_YELLOW);  //set text color to white
      tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
      tft.print(" WATCH ");
       
      
       tft.setCursor(8, 60);
       tft.setTextBackground(DISPLAY_WHITE);
       tft.setTextColor(DISPLAY_BLUE);  //set text color to white
       tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
       tft.print(t.hr/10);
       tft.print(t.hr%10);
       tft.print(":"); 

       tft.setCursor(50, 60);
       tft.setTextBackground(DISPLAY_WHITE);
       tft.setTextColor(DISPLAY_BLUE);  //set text color to white
       tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
       tft.print(t.min/10);
       tft.print(t.min%10);
       tft.print(":");

       tft.setCursor(90, 60);
       tft.setTextBackground(DISPLAY_WHITE);
       tft.setTextColor(DISPLAY_BLUE);  //set text color to white
       tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
       tft.print(t.sec/10);
       tft.print(t.sec%10); 
       //delay(10);

       tft.setCursor(20, 84);
       tft.setTextBackground(DISPLAY_WHITE);
       //tft.setTextBackground(DISPLAY_RED);  //set text background to black
       tft.setTextColor(DISPLAY_BLUE);  //set text color to white
       tft.setTextSize(1.5);  //2 * text size, default text size: 6 * 8
       tft.print("date:");
       tft.print(t.yr);
       tft.print("-");
       tft.print(t.mon/10);
       tft.print(t.mon%10);
       tft.print("-");
       tft.print(t.date/10);
       tft.print(t.date%10);
       tft.setCursor(40, 95);
       tft.setTextBackground(DISPLAY_WHITE);
       tft.setTextColor(DISPLAY_BLUE);  //set text color to white
       tft.setTextSize(1.5);  //2 * text size, default text size: 6 * 8
       tft.print("week: ");
       tft.print(t.day);
}


void loop(void)
{  
       int dela1,dela2,dela3,dela;//秒钟间隔延时
       dela1=millis();//获取程序运行到此处的时间
       Time t = rtc.time(); //更新时间
       if((t.min==59)&&(t.sec==59))//小时更新
       { 
       //Time t = rtc.time(); //更新时间
       tft.setCursor(90, 60);
       tft.setTextBackground(DISPLAY_WHITE);
       tft.setTextColor(DISPLAY_BLUE);  //set text color to white
       tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
       tft.print(t.sec/10);
       tft.print(t.sec%10); 
      
       delay(1050); 
       Time t = rtc.time();
       tft.setCursor(8, 60);
       tft.setTextBackground(DISPLAY_WHITE);
       tft.setTextColor(DISPLAY_BLUE);  //set text color to white
       tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
       tft.print(t.hr/10);
       tft.print(t.hr%10);
       tft.print(":"); 

       tft.setCursor(50, 60);
       tft.setTextBackground(DISPLAY_WHITE);
       tft.setTextColor(DISPLAY_BLUE);  //set text color to white
       tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
       tft.print(t.min/10);
       tft.print(t.min%10);
       tft.print(":");

       tft.setCursor(90, 60);
       tft.setTextBackground(DISPLAY_WHITE);
       tft.setTextColor(DISPLAY_BLUE);  //set text color to white
       tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
       tft.print(t.sec/10);
       tft.print(t.sec%10);  

       
      tft.setCursor(20, 84);
      tft.setTextBackground(DISPLAY_WHITE);
      //tft.setTextBackground(DISPLAY_RED);  //set text background to black
      tft.setTextColor(DISPLAY_BLUE);  //set text color to white
     tft.setTextSize(1.5);  //2 * text size, default text size: 6 * 8
     tft.print("date:");
     tft.print(t.yr);
     tft.print("-");
     tft.print(t.mon/10);
     tft.print(t.mon%10);
     tft.print("-");
     tft.print(t.date/10);
     tft.print(t.date%10);
   
     tft.setCursor(40, 95);
     tft.setTextBackground(DISPLAY_WHITE);
     tft.setTextColor(DISPLAY_BLUE);  //set text color to white
     tft.setTextSize(1.5);  //2 * text size, default text size: 6 * 8
     tft.print("week: ");
     tft.print(t.day);    
         }
     else if(t.sec==59) //分钟和小时刷新
     {   //Time t = rtc.time(); //更新时间
       tft.setCursor(90, 60);
       tft.setTextBackground(DISPLAY_WHITE);
       tft.setTextColor(DISPLAY_BLUE);  //set text color to white
       tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
       tft.print(t.sec/10);
       tft.print(t.sec%10);
       delay(1050);
       Time t = rtc.time(); //更新时间

       tft.setCursor(90, 60);
       tft.setTextBackground(DISPLAY_WHITE);
       tft.setTextColor(DISPLAY_BLUE);  //set text color to white
       tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
       tft.print(t.sec/10);
       tft.print(t.sec%10);
       
       tft.setCursor(50, 60);
       tft.setTextBackground(DISPLAY_WHITE);
       tft.setTextColor(DISPLAY_BLUE);  //set text color to white
       tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
       tft.print(t.min/10);
       tft.print(t.min%10);
       tft.print(":");
            }
       else
        {
       Time t = rtc.time(); //更新时间
       tft.setCursor(90, 60);
       tft.setTextBackground(DISPLAY_WHITE);
       tft.setTextColor(DISPLAY_BLUE);  //set text color to white
       tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
       tft.print(t.sec/10);
       tft.print(t.sec%10);
         }
         
       dela2=millis();//获取程序运行到此处的时间
       dela3=dela2-dela1;
       dela=1000-dela3;
       if(dela>0)
      {delay(dela);}
      else
      {delay(100);
       }}
