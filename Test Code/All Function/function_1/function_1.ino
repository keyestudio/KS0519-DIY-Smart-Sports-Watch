/*
keyestudio smart sports watch
All function
http://www.keyestudio.com
*/

#include "KS_ST7687S_Latch.h"
#include "KSRobot_Display_Clock.h"
#include "stdio.h"
#include "string.h"
#include "DS1302.h"
#include "MHEtLiveLIS3DH.h"
#include <MsTimer2.h>

LIS3DH SensorOne( I2C_MODE, 0x19 );//设置iic的地址为0x19
  
float a_x, a_y, a_z;//三轴加速度的变量
boolean flag_step,refresh=0;;//标志位
float threshold=1.15,xyz;//threshold是一个对比值，可以调节计歩灵敏度
int step_count;//步数变量

#define CE_PIN  A2         //DS1302使能脚
#define IO_PIN  A1         //DS1302数据脚
#define SCLK_PIN A0        //DS1302时钟脚
#define ZD_PIN  A3         //振动引脚
#define batter A5
#define NTD0 -1
#define NTD1 294
#define NTD2 330
#define NTD3 350
#define NTD4 393
#define NTD5 441
#define NTD6 495
#define NTD7 556

#define NTDL1 147
#define NTDL2 165
#define NTDL3 175
#define NTDL4 196
#define NTDL5 221
#define NTDL6 248
#define NTDL7 278

#define NTDH1 589
#define NTDH2 661
#define NTDH3 700
#define NTDH4 786
#define NTDH5 882
#define NTDH6 990
#define NTDH7 112
//c pinlv
#define WHOLE 1
#define HALF 0.5
#define QUARTER 0.25
#define EIGHTH 0.25
#define SIXTEENTH 0.625

int tune[]=
{
  NTD3,NTD3,NTD4,NTD5,
  NTD5,NTD4,NTD3,NTD2,
  NTD1,NTD1,NTD2,NTD3,
  NTD3,NTD2,NTD2,
  NTD3,NTD3,NTD4,NTD5,
  NTD5,NTD4,NTD3,NTD2,
  NTD1,NTD1,NTD2,NTD3,
  NTD2,NTD1,NTD1,
  NTD2,NTD2,NTD3,NTD1,
  NTD2,NTD3,NTD4,NTD3,NTD1,
  NTD2,NTD3,NTD4,NTD3,NTD2,
  NTD1,NTD2,NTDL5,NTD0,
  NTD3,NTD3,NTD4,NTD5,
  NTD5,NTD4,NTD3,NTD4,NTD2,
  NTD1,NTD1,NTD2,NTD3,
  NTD2,NTD1,NTD1
};
float durt[]=
{
  1,1,1,1,
  1,1,1,1,
  1,1,1,1,
  1+0.5,0.5,1+1,
  1,1,1,1,
  1,1,1,1,
  1,1,1,1,
  1+0.5,0.5,1+1,
  1,1,1,1,
  1,0.5,0.5,1,1,
  1,0.5,0.5,1,1,
  1,1,1,1,
  1,1,1,1,
  1,1,1,0.5,0.5,
  1,1,1,1,
  1+0.5,0.5,1+1,
};
int length;
int tonepin=A4;

unsigned long int i = 0;  //按下次数记录
int cutscreen=0; //切屏次数
boolean xscreen=0;

boolean i2=1,i3=0;//标志位
boolean screen=1;//屏幕控制标志位 1亮屏  0 黑屏
char alarm_hour,alarm_minute,alarm_seconed,light=255;//闹钟,屏幕亮度变量
uint8_t pin_cs = 8, pin_rs = 5, pin_wr = 13, pin_lck = 12, pin_spi_scl = 4, pin_spi_mosi = 6;
KS_ST7687S_Latch tft(pin_cs, pin_rs, pin_wr , pin_lck, pin_spi_scl, pin_spi_mosi);
KSRobot_Display_Clock clk(&tft);
DS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);

  void setup(void)// -----------------------初始化---------------------------
{  
  
   Serial.begin(9600);
   Serial1.begin(9600);//蓝牙传输波特率
   pinMode(11,OUTPUT);  //屏幕亮度控制脚
   pinMode(ZD_PIN,OUTPUT);
   pinMode(batter,INPUT);
   pinMode(tonepin,OUTPUT);
   digitalWrite(11,1);
   rtc.write_protect(false);
   rtc.halt(false);
   attachInterrupt(digitalPinToInterrupt(7), use, LOW);
   MsTimer2::set(100, onTimer); //设置中断，每100ms进入一次中断服务程序 onTimer()
   MsTimer2::start(); //开始计时
    //Time t(2020, 6, 3, 10, 30, 30, 3);//设置时间
    //rtc.time(t);
   SensorOne.begin();
   length=sizeof(tune)/sizeof(tune[0]);
   //music();
}

  void music()
{
  for(int x=0;x<length;x++)
{
  tone(tonepin,tune[x]);
  delay(400*durt[x]);//与前一代码不同之处，这里将原来的500分为了400和100，分别控制led的开与关，对于蜂鸣器来说依然是500.
  delay(100*durt[x]);
  noTone(tonepin);
    
}
  delay(2000);
}

  void onTimer()
{
  key();
       
}

  void key()//--------------------按键，长按，短按----------------------
{
  if((i>10000)&&(i<40000))//-------------短按----------------
{
  i=0;i2=1;
  cutscreen++;
  if(cutscreen==2)
{
  cutscreen=0;
} 
  //Serial.print(cutscreen);
  //Serial.println("duan an");
  //delay(1000);
}
  else if(i>300000) //-------------------长按---------------------
{
  i=0;
  xscreen=1; 
}
  else
{                    //-----------------无效按键-----------------
  i=0;
}
}
           
 void use()         //---------------------中断----------------------
{ 
  i++; i3=1;
}
 int readbuff[11];
 char datelength,index=0;
 void blueteeth()  //蓝牙功能-------------数据接收--------------------
{    
       
  boolean readstart=0;
  while(Serial1.available())  //用蓝牙传输数据就改成Serial1.available()
{
  readbuff[index] =Serial1.read()&0xFF;//用蓝牙传输数据就改成Serial1.available()
  Serial1.write(readbuff[index]);
  Serial.println(readbuff[index]);
  if(readbuff[0]==0xff)
{
  readstart=1;
}
  if(readstart==1)//起始位正确，开始接收下个数据
{ 
  index++;
  datelength=readbuff[1];
}
  if((index==datelength)&&(readbuff[index-1]==254))//数据接收完毕，开始处理数据
{
  readstart=0;index=0;datetreating();
}
  if(index>11)
{
  readstart=0;index=0;//Serial.println(666);
}
}
}  

  void datetreating()//----------------------数据处理-----------------------------
{
  int menu;
  long int R_year;
  int R_month,R_day,R_hour,R_minute,R_seconed,R_week;
  menu=readbuff[2];
  switch(menu)
{
  case 1:  R_year=readbuff[3]+2000; //FF 0B 01 14 05 0B 0E 23 16  01 FE
           R_month=readbuff[4]; 
           R_day=readbuff[5];
           R_hour=readbuff[6];
           R_minute=readbuff[7];
           R_seconed=readbuff[8];
           R_week=readbuff[9]; 
           break;                                 //设置时间
  case 2:  alarm_hour=readbuff[3]; //FF 0B 02 0E 26 16 00 00 00 00 FE
           alarm_minute=readbuff[4];
           alarm_seconed=readbuff[5]; break;      //设置闹钟
  case 3:  light=readbuff[3];      //FF 0B 03 0E 00 00 00 00 00 00 FE                  
           break;                                 //调节亮度
  default: break;
}
  if(menu==1)
{ Time t(R_year,R_month,R_day,R_hour,R_minute,R_seconed,R_week);//设置时间
  rtc.time(t); 
  refresh=1;
}
}

  void alarm()//------------------------闹钟-------------------
{ 
  Time t = rtc.time(); 
  int alarmnum=0;
  if((alarm_hour==t.hr)&&(alarm_minute==t.min)&&(alarm_seconed==t.sec))
{ i3=0;
  do
{
  digitalWrite(ZD_PIN,HIGH);
  music();
  alarmnum++;
  if(alarmnum>=3)
{ 
  alarmnum=0;
  i3=1;
  refresh=1;  
}
}
  while(i3==0);
  digitalWrite(ZD_PIN,LOW);
}
}     
  void loop(void)//---------------------------主函数循环---------------------
{ 
  if((cutscreen==0)&&(i2==1))//-------------按键第2次按下显示日期时间步数等画面---------------
{
  i2=0;
  tft.begin();
  tft.fillScreen(DISPLAY_BLUE); //背景色为蓝色
  tft.fillCircle(0, 0, 58, DISPLAY_WHITE);
  tft.drawHLine(-58, -20, 116, DISPLAY_RED);
   
  tft.setCursor(23, 20);
  tft.setTextBackground(DISPLAY_WHITE);
  tft.setTextColor(DISPLAY_RED);  //set text color to white
  tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
  tft.print(" WATCH ");
       
  Time t = rtc.time(); 
  tft.setCursor(8, 60);
  tft.setTextColor(DISPLAY_BLUE);  //set text color to white
  tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
  tft.print(t.hr/10);
  tft.print(t.hr%10);
  tft.print(":"); 

  tft.setCursor(50, 60);
  tft.setTextColor(DISPLAY_BLUE);  //set text color to white
  tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
  tft.print(t.min/10);
  tft.print(t.min%10);
  tft.print(":");

  tft.setCursor(90, 60);
  tft.setTextColor(DISPLAY_BLUE);  //set text color to white
  tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
  tft.print(t.sec/10);
  tft.print(t.sec%10); 
  //delay(10);

  tft.setCursor(20, 84);
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
  tft.setTextColor(DISPLAY_BLUE);  //set text color to white
  tft.setTextSize(1.5);  //2 * text size, default text size: 6 * 8
  tft.print("week: ");
  tft.print(t.day);

  tft.setCursor(43, 106);
  tft.setTextColor(DISPLAY_GREEN);  //set text color to white
  tft.setTextSize(1.5); 
  tft.print("step:"); 
  do
{
  blueteeth();
  alarm();
  analogWrite(11,light);
  if(xscreen==1)
{ 
  xscreen=0;
  if(light!=0)
{
  light=0;
}
  else
{
  light=255;    
}
}
 
  int dela1,dela2,dela3,dela;//秒钟间隔延时
  dela1=millis();//获取程序运行到此处的时间
  Time t = rtc.time(); //更新时间
  if(((t.min==59)&&(t.sec==59))||(refresh==1))//小时更新
{ 
  refresh=0;
   //Time t = rtc.time(); //更新时间
  tft.setCursor(90, 60);
  tft.setTextColor(DISPLAY_BLUE);  //set text color to white
  tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
  tft.print(t.sec/10);
  tft.print(t.sec%10); 
  
  delay(1050); 
  Time t = rtc.time();
  tft.setCursor(8, 60);
  tft.setTextColor(DISPLAY_BLUE);  //set text color to white
  tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
  tft.print(t.hr/10);
  tft.print(t.hr%10);
  tft.print(":"); 

  tft.setCursor(50, 60);
  tft.setTextColor(DISPLAY_BLUE);  //set text color to white
  tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
  tft.print(t.min/10);
  tft.print(t.min%10);
  tft.print(":");

  tft.setCursor(90, 60);
  tft.setTextColor(DISPLAY_BLUE);  //set text color to white
  tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
  tft.print(t.sec/10);
  tft.print(t.sec%10);  

       
  tft.setCursor(20, 84);
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
  tft.setTextColor(DISPLAY_BLUE);  //set text color to white
  tft.setTextSize(1.5);  //2 * text size, default text size: 6 * 8
  tft.print("week: ");
  tft.print(t.day);    
}
  else if(t.sec==59) //分钟和小时刷新
{     
  //Time t = rtc.time(); //更新时间
  tft.setCursor(90, 60);
  tft.setTextColor(DISPLAY_BLUE);  //set text color to white
  tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
  tft.print(t.sec/10);
  tft.print(t.sec%10);
  delay(1050);
  Time t = rtc.time(); //更新时间

  tft.setCursor(90, 60);
  tft.setTextColor(DISPLAY_BLUE);  //set text color to white
  tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
  tft.print(t.sec/10);
  tft.print(t.sec%10);
   
  tft.setCursor(50, 60);
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
  tft.setTextColor(DISPLAY_BLUE);  //set text color to white
  tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
  tft.print(t.sec/10);
  tft.print(t.sec%10);
}
   
  a_x = SensorOne.readFloatAccelX();
  a_y = SensorOne.readFloatAccelY();
  a_z = SensorOne.readFloatAccelZ();
  xyz = sqrt((a_x * a_x) + (a_y * a_y) + (a_z * a_z));
         
  if((xyz > threshold) && (flag_step == 1))
{
  step_count += 1;
  flag_step = 0;
}
  else
{
  flag_step = 1;
} 
  tft.setCursor(74, 106);
  tft.setTextColor(DISPLAY_RED);  //set text color to white
  tft.setTextSize(1.5); 
  //tft.print("step:");
  tft.print(step_count);
      
  dela2=millis();//获取程序运行到此处的时间
  dela3=dela2-dela1;
  dela=1000-dela3;
  if(dela>0)
{
  delay(dela);}
  else
{
  delay(100);
}
}
  while(i2==0);
}
  if((cutscreen == 1)&&(i2==1))//-------------按键第2次按下显示闹钟，电量等画面---------------
{
  i2=0;
  tft.begin();
  tft.fillScreen(DISPLAY_YELLOW); //背景色为蓝色
  tft.fillCircle(0, 0, 58, DISPLAY_WHITE);
  tft.setCursor(23, 20);
      
  tft.setTextColor(DISPLAY_BLUE);  //set text color to white
  tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
  tft.print(" alarm ");
  
  tft.setCursor(20, 95);
  tft.setTextColor(DISPLAY_GREEN);  //set text color to white
  tft.setTextSize(1.5);  //2 * text size, default text size: 6 * 8
  tft.print(" Batter:");
  do
{
  blueteeth();
  alarm();
  analogWrite(11,light);
  if(xscreen==1)
{ 
  xscreen=0;
  if(light!=0)
{
  light=0;
}
  else
{
  light=255;    
}
}
     
  tft.setCursor(8, 60);
  tft.setTextColor(DISPLAY_RED);  //set text color to white
  tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
  tft.print(alarm_hour/10);
  tft.print(alarm_hour%10);
  tft.print(":"); 

  tft.setCursor(50, 60);
  tft.setTextColor(DISPLAY_RED);  //set text color to white
  tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
  tft.print(alarm_minute/10);
  tft.print(alarm_minute%10);
  tft.print(":");
  tft.setCursor(90, 60);
  tft.setTextColor(DISPLAY_RED);  //set text color to white
  tft.setTextSize(2);  //2 * text size, default text size: 6 * 8
  tft.print(alarm_seconed/10);
  tft.print(alarm_seconed%10);

  float dian=analogRead(batter);
  int DL=(dian/1024*3.3)*2*100+0.5;
  Serial.println(DL);
  tft.setCursor(70, 95);
  tft.setTextColor(DISPLAY_RED);  //set text color to white
  tft.setTextSize(1.5);  //2 * text size, default text size: 6 * 8
  tft.print(DL/100);
  tft.print(".");
  tft.print(DL%100/10);
  tft.print(DL%100%10);
  tft.print("V");
}
  while(i2==0);
     
}
}
