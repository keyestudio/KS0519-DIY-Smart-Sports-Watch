/*
keyestudio smart sports watch
lesson 9.2
Interrupt
http://www.keyestudio.com
*/ 
unsigned int i;
unsigned int count;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);  
attachInterrupt(digitalPinToInterrupt(7), use, LOW);
}
void use()//-----------------中断----------------------
  { 
  i=1;
 }
void loop()
{
   // put your main code here, to run repeatedly:
 if(i==1)
 {
  delay(400);
  if(i==1)
  {
   i=0;
   count++;
   Serial.println(count);
  }
  }
}
