/*
keyestudio smart sports watch
Project 4.3
Button
http://www.keyestudio.com
*/
const int btn = 7;
int btn_val = 0;
int flag;
int count;
void setup() {
  Serial.begin(9600);
  pinMode(btn,INPUT);
}
void loop() {
  btn_val = digitalRead(btn);
  //Serial.println(btn_val);
  if(btn_val == 0)
  {
    delay(10);
    if(btn_val == 0)
    {
      while(1)
      {
        btn_val = digitalRead(btn);
        if(btn_val == 1)
        {
          count++;
          Serial.println(count);
          break;
        }
      }
    }
  }
}
