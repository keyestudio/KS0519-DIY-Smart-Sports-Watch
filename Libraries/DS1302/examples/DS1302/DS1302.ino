#include <DS1302.h>
DS1302 rtc(2, 5, 7);
void setup()
{
 
  rtc.halt(false);
  rtc.writeProtect(false);
 
  rtc.setDOW(SATURDAY);        // 设置星期
  rtc.setTime(22, 56,00);     //设置时间
  rtc.setDate(9, 11, 2013);   // 设置日期2013年11月9日
  rtc.writeProtect(true);
  Serial.begin(9600);
}
void loop()
{
  char * t=rtc.getTimeStr();
  char * d=rtc.getDateStr(FORMAT_LONG,FORMAT_BIGENDIAN, '-');
  char * w=rtc.getDOWStr(FORMAT_LONG);
  Serial.println(t);
  Serial.println(d);
  Serial.println(w);
  delay(1000);
 
}

