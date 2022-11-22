/*
keyestudio smart sports watch
Project 7.3
LIS3DH
http://www.keyestudio.com
*/
#include "KS_ST7687S_Latch.h"
#include "KSRobot_Display_Clock.h"
#include "MHEtLiveLIS3DH.h"
LIS3DH SensorOne( I2C_MODE, 0x19 );//设置iic的地址为0x19

uint8_t pin_cs = 8, pin_rs = 5, pin_wr = 13, pin_lck = 12, pin_spi_scl = 4, pin_spi_mosi = 6;
KS_ST7687S_Latch tft(pin_cs, pin_rs, pin_wr , pin_lck, pin_spi_scl, pin_spi_mosi);
KSRobot_Display_Clock clk(&tft);

  float a_x, a_y, a_z;//三轴加速度的变量
  boolean flag_step,refresh=0;;//标志位
  float threshold=1.15,xyz;//threshold是一个对比值，可以调节计歩灵敏度
  int step_count;//步数变量

  void setup()
{
  // put your setup code here, to run once:
  SensorOne.begin();
  digitalWrite(11,1);
  tft.begin();
  tft.fillScreen(DISPLAY_BLUE); //背景色为蓝色
  tft.fillCircle(0, 0, 58, DISPLAY_WHITE);
  tft.setCursor(15, 60);
  tft.setTextBackground(DISPLAY_WHITE);
  tft.setTextColor(DISPLAY_RED);  //set text color to white
  tft.setTextSize(2); 
  tft.print("step:"); 
}

  void loop() 
{
  // put your main code here, to run repeatedly:
  a_x = SensorOne.readFloatAccelX();
  a_y = SensorOne.readFloatAccelY();
  a_z = SensorOne.readFloatAccelZ();
  xyz = sqrt((a_x * a_x) + (a_y * a_y) + (a_z * a_z));
         
  if((xyz > threshold) && (flag_step == 1))
{
  step_count += 1;
  //Serial.println(step_count);   //步数
  flag_step = 0;
}
  else
{
  flag_step = 1;
} 
  tft.setCursor(74, 60);
  tft.setTextBackground(DISPLAY_WHITE);
  tft.setTextColor(DISPLAY_BLUE);  //set text color to white
  tft.setTextSize(2); 
  //tft.print("step:");
  tft.print(step_count);
}
