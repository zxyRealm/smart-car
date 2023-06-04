/************************************************
 * 【作    者】：清翔电子
 * 【功    能】：智能小车按键启动蜂鸣器报警
 * 打开智能小车电源后按下转接板上的“启动按键”
 * 小车前进3秒，每按一次前进3秒同蜂鸣器报警滴声
 ***********************************************/
int left_motor_en = 5;//左电机使能
int right_motor_en = 6;//右电机使能

int left_motor_go = 3;//左电机正传
int right_motor_go = 4;//右电机正传

int left_motor_back = 2;//左电机反转 
int right_motor_back = 7;//右电机反转
int key = A3;//启动按键
void setup() {
  //电机驱动引脚全部设置为输出模式
  pinMode(left_motor_en,OUTPUT);
  pinMode(right_motor_en,OUTPUT);
  pinMode(left_motor_go,OUTPUT);
  pinMode(right_motor_go,OUTPUT);
  pinMode(left_motor_back,OUTPUT);
  pinMode(right_motor_back,OUTPUT);
  pinMode(key,INPUT);//启动按键引脚输入模式
  
   analogWrite(left_motor_en,200);//左电机占空比值 取值范围0-255，255最快
   analogWrite(right_motor_en,200);//右电机占空比值取值范围0-255 ,255最快 
}
//小车前进
void forward()
{
   digitalWrite(left_motor_go,HIGH);  //左电机前进
   digitalWrite(left_motor_back,LOW); 
   digitalWrite(right_motor_go,HIGH);  //右电机前进
   digitalWrite(right_motor_back,LOW);  
  }
//停车
void stop_car()
{
   digitalWrite(left_motor_go,LOW);  //左电机停止
   digitalWrite(left_motor_back,LOW); 
   digitalWrite(right_motor_go,LOW);  //右电机停止
   digitalWrite(right_motor_back,LOW);
  }
void loop() 
{
  if(digitalRead(key) == LOW)//检测转接板上的启动按键是否按下
  {
  forward();//按下后小车前进3秒
  delay(3000);
  stop_car();//停车
  }
  else
  {
   stop_car();//没按下时停车 
    }
}
