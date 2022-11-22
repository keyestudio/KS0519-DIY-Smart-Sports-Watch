/*
keyestudio smart sports watch
Project 3
Voltage detection
http://www.keyestudio.com
*/
const int Electric = A5;
  void setup()
   {
  Serial.begin(9600);
  pinMode(Electric,INPUT);
   }

void loop() {
  float dian=analogRead(Electric);
  float DL=(dian/1024*3.3)*2;//电量转换
  Serial.print(DL);
  Serial.println("V");
  delay(1000);
}
