/*
 keyestudio smart sports watch
 lesson 1
 Vibration motor
 http://www.keyestudio.com
*/
void setup()
 { 
    pinMode(A3, OUTPUT);// initialize digital pin A3 as an output.
}
void loop() // the loop function runs over and over again forever
{
   digitalWrite(A3, HIGH); // turn the  Vibration motor on 
   delay(1000); // wait for a second
   digitalWrite(A3, LOW); // turn the  Vibration motor off 
   delay(1000); // wait for a second
}//********************************************************************
