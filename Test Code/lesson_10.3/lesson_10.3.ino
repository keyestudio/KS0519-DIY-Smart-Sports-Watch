/*
keyestudio smart sports watch
lesson 10.3
Interrupt
http://www.keyestudio.com
*/ 
#include <MsTimer2.h>
#include "KS_ST7687S_Latch.h"
#include "KSRobot_Display_Clock.h"

unsigned long int i = 0;  //按下次数记录
int i2=1;
int cutscreen=0; //切屏次数
boolean xscreen=0;
boolean screen=1;//屏幕控制标志位 1亮屏  0 黑屏

uint8_t pin_cs = 8, pin_rs = 5, pin_wr = 13, pin_lck = 12, pin_spi_scl = 4, pin_spi_mosi = 6;
KS_ST7687S_Latch tft(pin_cs, pin_rs, pin_wr , pin_lck, pin_spi_scl, pin_spi_mosi);
KSRobot_Display_Clock clk(&tft);

  void setup() 
{
  // put your setup code here, to run once:
  pinMode(11,OUTPUT);
  digitalWrite(11,1);
  attachInterrupt(digitalPinToInterrupt(7), use, LOW);
  MsTimer2::set(100, onTimer); //设置中断，每100ms进入一次中断服务程序 onTimer()
  MsTimer2::start(); //开始计时
  tft.begin();
  tft.fillScreen(DISPLAY_WHITE);
}
  void key()//--------------------按键，长按，短按----------------------
{
  if((i>12000)&&(i<30000))//-------------短按----------------
{
  i=0;i2=1;
  cutscreen++;
  if(cutscreen==3)
  {
  cutscreen=0;
   } 
  Serial.print(cutscreen);
  Serial.println("Short press");
  delay(1000);
}
  else if(i>300000) //--------------长按---------------------
{
  i=0;
  xscreen=1; Serial.print(xscreen);
  Serial.println("Long press"); 
  delay(1000);
}
  else{        //-----------------无效按键-----------------
  i=0;
}
}

  void onTimer()
{
  key();
}
  void use()//-----------------中断----------------------
{ 
  i++;
}
   
  void loop() {
  if((cutscreen==0)&&(i2==1))
{ 
  i2=0;
  do
{
  tft.drawCircle(0, 0, 20, DISPLAY_GREEN);  //draw circle
  delay(1000);
  tft.fillCircle(0, 0, 20, DISPLAY_RED);  //fill circle
  delay(1000);
  tft.fillScreen(DISPLAY_WHITE);
  delay(1000);
  if(xscreen==1)
{
  xscreen=0;
  screen=!screen;
  digitalWrite(11,screen);
}
}while(i2==0);
}
  if((cutscreen==1)&&(i2==1))
{ 
  i2=0;
  do
{
  tft.drawRect(-20, -20, 40, 40, DISPLAY_BLUE);  //draw rectangle
  delay(1000);
  tft.fillRect(-20, -20, 40, 40, DISPLAY_BLUE);  //fill rectangle
  delay(1000);
  tft.fillScreen(DISPLAY_WHITE);
  delay(1000); 
  if(xscreen==1)
{
  xscreen=0;
  screen=!screen;
  digitalWrite(11,screen);
} 
}while(i2==0);
}
  if((cutscreen==2)&&(i2==1))
{ 
  i2=0;
  do{
  tft.setCursor(32, 64);
  tft.setTextBackground(DISPLAY_WHITE);  //set text background to black
  tft.setTextColor(DISPLAY_RED);  //set text color to white
  tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
  tft.print("Dream");
  delay(1000);
  if(xscreen==1)
{
  xscreen=0;
  screen=!screen;
  digitalWrite(11,screen);
}
}while(i2==0);
}  
}
