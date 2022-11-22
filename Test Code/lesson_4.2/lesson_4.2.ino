/*
keyestudio smart sports watch
Project 4.2
Button
http://www.keyestudio.com
*/
const int btn = 7;
int btn_val = 0;
void setup() {
  Serial.begin(9600);
  pinMode(btn,INPUT);
}
void loop() {
  btn_val = digitalRead(btn);
  //Serial.println(btn_val);
  if(btn_val == 0)
  {
    delay(100);//消抖
    if(btn_val == 0)
    {
      Serial.println("hello world");
    }
  }
}
