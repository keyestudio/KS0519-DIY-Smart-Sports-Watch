/*
keyestudio smart sports watch
lesson 10.2
Interrupt
http://www.keyestudio.com
*/ 
#include <MsTimer2.h>
unsigned long int i = 0;  //按下次数记录
int cutscreen=0; //切屏次数
boolean xscreen=0;
  void setup()
{
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(7), use, LOW);
  MsTimer2::set(1000, onTimer); //设置中断，每100ms进入一次中断服务程序 onTimer()
  MsTimer2::start(); //开始计时
}

  void onTimer()
{
  key();
}

  void key()//--------------------按键，长按，短按----------------------
{
  if((i>12000)&&(i<30000))//-------------短按----------------
{
  i=0;
  cutscreen++;
  if(cutscreen==2)
{
  cutscreen=0;
} 
  Serial.println(cutscreen);
  Serial.println("of short");
}
  else if(i>300000) //--------------长按---------------------
{
  i=0;
  xscreen=!xscreen;
  if(xscreen==1)
{
  Serial.println("open of long"); 
}
  if(xscreen==0)
{
  Serial.println("close of long"); 
}
}
  else
{        //-----------------无效按键-----------------
  i=0;
}
}
           
  void use()//-----------------中断----------------------
{ 
  i++;
}
  
void loop() {
  // put your main code here, to run repeatedly:
Serial.println(i);
}
