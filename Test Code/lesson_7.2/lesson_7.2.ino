 /*
keyestudio smart sports watch
Project 7.2
LIS3DH
http://www.keyestudio.com
*/
  #include "MHEtLiveLIS3DH.h"
  #include "Wire.h"

  LIS3DH SensorOne( I2C_MODE, 0x19 );

  float a_x, a_y, a_z;
  float threshold=1.15, xyz;
  bool flag_step = 1;
  int step_count;

  void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000); //relax...
  Serial.println("Processor came out of reset.\n");
  if( SensorOne.begin() != 0 )
{
  Serial.println("Problem starting the sensor at 0x19.");
}
  else
{
  Serial.println("Sensor at 0x19 started.");
}
}
  void loop()
{
  a_x = SensorOne.readFloatAccelX();
  a_y = SensorOne.readFloatAccelY();
  a_z = SensorOne.readFloatAccelZ();
  xyz = sqrt((a_x * a_x) + (a_y * a_y) + (a_z * a_z));
  if((xyz > threshold) && (flag_step == 1))
{
  step_count += 1;
  Serial.println(step_count);
  flag_step = 0;
}
  if(xyz < threshold)
{
  flag_step = 1;
}
  Serial.print("step = ");
  Serial.println(step_count);
  delay(400);
}
