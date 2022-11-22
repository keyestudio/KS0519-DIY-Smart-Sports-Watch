/*
keyestudio smart sports watch
lesson 10.1
Interrupt
http://www.keyestudio.com
*/ 
#include <MsTimer2.h>     //定时器库的头文件
int tick = 0; //计数值
//中断服务程序
void onTimer()
{
  Serial.print("timer ");
  Serial.println(tick++);
}
void setup()
{
  Serial.begin(9600); //初始化串口
    MsTimer2::set(1000, onTimer); //设置中断，每1000ms进入一次中断服务程序 onTimer()
  MsTimer2::start(); //开始计时
}
void loop()
{
}
