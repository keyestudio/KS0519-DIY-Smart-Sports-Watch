/*
keyestudio smart sports watch
lesson 8.1
bluetooth 
http://www.keyestudio.com
*/
int ble_val; //变量，用于存放蓝牙接收到的值
void setup() {
  Serial1.begin(9600);
}
void loop() {
  if(Serial1.available() > 0)  //判断串口缓存区是否有数据
  {
    ble_val = Serial1.read();  //读取串口缓存区的数据
    Serial.println(ble_val);  //打印出来
  }
}
