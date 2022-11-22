/*
  keyestudio smart sports watch
  lesson 8.2
  Bluetooth
  http://www.keyestudio.com
*/
#include < DS1302.h > uint8_t CE_PIN = A2; //DS1302enable pin
uint8_t IO_PIN = A1; //DS1302data pin
uint8_t SCLK_PIN = A0; //DS1302 clock pin
DS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN); #include "KS_ST7687S_Latch.h"uint8_t pin_cs = 8,
                                                                           pin_rs = 5,
                                                                           pin_wr = 13,
                                                                           pin_lck = 12,
                                                                           pin_spi_scl = 4,
                                                                           pin_spi_mosi = 6;
KS_ST7687S_Latch tft(pin_cs, pin_rs, pin_wr, pin_lck, pin_spi_scl, pin_spi_mosi);
int readbuff[11];
char datelength,
     index = 0;
124 www.keyestudio.com boolean refresh;
void setup(void) {
  Serial1.begin(9600);
  rtc.write_protect(false);
  rtc.halt(false);
  // Time t(2009, 5, 19, 21, 16, 37, 3);//Set time, month, day, time,
  hour,
  minute,
  second,
  week
  // rtc.time(t);
  Time t = rtc.time();
  pinMode(11, OUTPUT);
  //Pin 11 controls the brightness of screen
  analogWrite(11, 254);
  //value is in the range of 0~255
  tft.begin();
  //Initialize the screen setting
  tft.fillScreen(DISPLAY_BLUE); //background is blue
  tft.fillCircle(0, 0, 58, DISPLAY_WHITE);
  tft.begin();
  tft.drawHLine( - 58, -20, 116, DISPLAY_RED);
  //tft.drawCircle(-1, 0, 61, DISPLAY_GREEN);
  tft.setCursor(23, 20);
  tft.setTextBackground(DISPLAY_WHITE);
  tft.setTextColor(DISPLAY_YELLOW);
  //set text color to white
  125 www.keyestudio.com tft.setTextSize(2);
  //2 * text size, default text size: 6 * 8
  tft.print(" WATCH ");
  tft.setCursor(8, 60);
  tft.setTextBackground(DISPLAY_WHITE);
  tft.setTextColor(DISPLAY_BLUE);
  //set text color to white
  tft.setTextSize(2);
  //2 * text size, default text size: 6 * 8
  tft.print(t.hr / 10);
  tft.print(t.hr % 10);
  tft.print(":");
  tft.setCursor(50, 60);
  tft.setTextBackground(DISPLAY_WHITE);
  tft.setTextColor(DISPLAY_BLUE);
  //set text color to white
  tft.setTextSize(2);
  //2 * text size, default text size: 6 * 8
  tft.print(t.min / 10);
  tft.print(t.min % 10);
  tft.print(":");
  tft.setCursor(90, 60);
  tft.setTextBackground(DISPLAY_WHITE);
  tft.setTextColor(DISPLAY_BLUE);
  //set text color to white
  tft.setTextSize(2);
  //2 * text size, default text size: 6 * 8
  126 www.keyestudio.com tft.print(t.sec / 10);
  tft.print(t.sec % 10);
  //delay(10);
  tft.setCursor(20, 84);
  tft.setTextBackground(DISPLAY_WHITE);
  //tft.setTextBackground(DISPLAY_RED);
  //set
  text background to black tft.setTextColor(DISPLAY_BLUE);
  //set text color to white
  tft.setTextSize(1.5);
  //2 * text size, default text size: 6 * 8
  tft.print("date:");
  tft.print(t.yr);
  tft.print("-");
  tft.print(t.mon / 10);
  tft.print(t.mon % 10);
  tft.print("-");
  tft.print(t.date / 10);
  tft.print(t.date % 10);
  tft.setCursor(40, 95);
  tft.setTextBackground(DISPLAY_WHITE);
  tft.setTextColor(DISPLAY_BLUE);
  //set text color to white
  tft.setTextSize(1.5);
  //2 * text size, default text size: 6 * 8
  tft.print("week: ");
  127 www.keyestudio.com tft.print(t.day);
}
void blueteeth() //Bluetooth Function ------Data Reception ------
{
  boolean readstart = 0;
  while (Serial1.available()) //the usb transmission is changed into
    Serial.available() {
    readbuff[index] = Serial1.read() & 0xFF; //the usb transmission
    is changed into Serial.available()() Serial.println(index);
    Serial.println(readbuff[index]);
    // Serial1.write(index);
    //Serial1.write(readbuff[index]);
    //Serial1.write("QQ");
    if (readbuff[0] == 0xff) {
      //Serial1.write("A");
      readstart = 1;
    }
    if (readstart == 1) //initial bit is correct, and start receiving
      128 www.keyestudio.com next data {
      index++;
      datelength = readbuff[1];
      //Serial.println(datelength);
      //
      Serial1.write("B");
    }
    if ((index == datelength) && (readbuff[index - 1] == 254)) / / After receiving the data, start processing data
    {
      readstart = 0; index = 0; datetreating(); / / Serial1.write("C");
      //Serial.print("datelength=");
      //Serial.println(datelength);
    }
    if (index > 11) {
      readstart = 0;
      index = 0; //Serial.println(666);
    }
  }
}
129 www.keyestudio.com void datetreating() //----------process data -------------
{
  int menu,
      clock1 = 0,
      light = 0;
  long int R_year;
  int R_month,
      R_day,
      R_hour,
      R_minute,
      R_seconed,
      R_week;
  menu = readbuff[2];
  /*Serial.print("menu=");
    Serial.println(menu);*/
  switch (menu) {
    case 1:
      R_year = readbuff[3] + 2000; //FF 0B 00 14 05 0B 0E 23 16
      01 FE R_month = readbuff[4];
      R_day = readbuff[5];
      R_hour = readbuff[6];
      R_minute = readbuff[7];
      R_seconed = readbuff[8];
      R_week = readbuff[9];
      break;
    //set time
    case 2:
      /*alarm_hour=readbuff[3]; //FF 0B 01 0E 26 16 00 00
        00 00 FE
        alarm_minute=readbuff[4];
        130
        www.keyestudio.com
        alarm_seconed=readbuff[5];*/
      break;
      //set
      alarm clock
    case 3:
      /* light=66;
      */
      break; //adjust
      brightness
    default:
      break;
  }
  if (menu == 1) {
    Time t(R_year, R_month, R_day, R_hour, R_minute, R_seconed, R_week); //set
    time rtc.time(t);
    refresh = 1;
  }
  /* Serial.println(R_year);
    Serial.println(R_month);
    Serial.println(R_day);
    Serial.println(R_hour);
    Serial.println(R_minute);
    Serial.println(R_seconed);
    Serial.println(R_week);
    Serial.println(clock1);
    Serial.println(light);
  */
  131 www.keyestudio.com
}
void loop(void) {
  blueteeth();
  int dela1,
      dela2,
      dela3,
      dela; //delay in interval
  dela1 = millis(); //obtain the time when program runs
  Time t = rtc.time(); //Update time
  if ((t.min == 59) && (t.sec == 59) || (refresh == 1)) //update hour
  {
    refresh = 0;
    //Time t = rtc.time(); //Update time
    tft.setCursor(90, 60);
    tft.setTextBackground(DISPLAY_WHITE);
    tft.setTextColor(DISPLAY_BLUE);
    //set text color to white
    tft.setTextSize(2);
    //2 * text size, default text size: 6 * 8
    tft.print(t.sec / 10);
    tft.print(t.sec % 10);
    delay(1050);
    Time t = rtc.time();
    tft.setCursor(8, 60);
    tft.setTextBackground(DISPLAY_WHITE);
    tft.setTextColor(DISPLAY_BLUE);
    //set text color to white
    132 www.keyestudio.com tft.setTextSize(2);
    //2 * text size, default text size: 6 * 8
    tft.print(t.hr / 10);
    tft.print(t.hr % 10);
    tft.print(":");
    tft.setCursor(50, 60);
    tft.setTextBackground(DISPLAY_WHITE);
    tft.setTextColor(DISPLAY_BLUE);
    //set text color to white
    tft.setTextSize(2);
    //2 * text size, default text size: 6 * 8
    tft.print(t.min / 10);
    tft.print(t.min % 10);
    tft.print(":");
    tft.setCursor(90, 60);
    tft.setTextBackground(DISPLAY_WHITE);
    tft.setTextColor(DISPLAY_BLUE);
    //set text color to white
    tft.setTextSize(2);
    //2 * text size, default text size: 6 * 8
    tft.print(t.sec / 10);
    tft.print(t.sec % 10);
    tft.setCursor(20, 84);
    tft.setTextBackground(DISPLAY_WHITE);
    //tft.setTextBackground(DISPLAY_RED);
    //set text background
    133 www.keyestudio.com to black tft.setTextColor(DISPLAY_BLUE);
    //set text color to white
    tft.setTextSize(1.5);
    //2 * text size, default text size: 6 * 8
    tft.print("date:");
    tft.print(t.yr);
    tft.print("-");
    tft.print(t.mon / 10);
    tft.print(t.mon % 10);
    tft.print("-");
    tft.print(t.date / 10);
    tft.print(t.date % 10);
    tft.setCursor(40, 95);
    tft.setTextBackground(DISPLAY_WHITE);
    tft.setTextColor(DISPLAY_BLUE);
    //set text color to white
    tft.setTextSize(1.5);
    //2 * text size, default text size: 6 * 8
    tft.print("week: ");
    tft.print(t.day);
  } else if (t.sec == 59) //refresh hour and minute
  {
    //Time t = rtc.time(); //Update time
    tft.setCursor(90, 60);
    tft.setTextBackground(DISPLAY_WHITE);
    134 www.keyestudio.com tft.setTextColor(DISPLAY_BLUE);
    //set text color to white
    tft.setTextSize(2);
    //2 * text size, default text size: 6 * 8
    tft.print(t.sec / 10);
    tft.print(t.sec % 10);
    delay(1050);
    Time t = rtc.time(); //Update time
    tft.setCursor(90, 60);
    tft.setTextBackground(DISPLAY_WHITE);
    tft.setTextColor(DISPLAY_BLUE);
    //set text color to white
    tft.setTextSize(2);
    //2 * text size, default text size: 6 * 8
    tft.print(t.sec / 10);
    tft.print(t.sec % 10);
    tft.setCursor(50, 60);
    tft.setTextBackground(DISPLAY_WHITE);
    tft.setTextColor(DISPLAY_BLUE);
    //set text color to white
    tft.setTextSize(2);
    //2 * text size, default text size: 6 * 8
    tft.print(t.min / 10);
    tft.print(t.min % 10);
    tft.print(":");
  } else {
    135 www.keyestudio.com Time t = rtc.time(); //Update time
    tft.setCursor(90, 60);
    tft.setTextBackground(DISPLAY_WHITE);
    tft.setTextColor(DISPLAY_BLUE);
    //set text color to white
    tft.setTextSize(2);
    //2 * text size, default text size: 6 * 8
    tft.print(t.sec / 10);
    tft.print(t.sec % 10);
  }
  dela2 = millis(); //obtain the time when program runs
  dela3 = dela2 - dela1;
  dela = 1000 - dela3;
  if (dela > 0) {
    delay(dela);
  } else {
    delay(100);
  }
}
//*******************************************************
