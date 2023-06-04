/************************************************
 * 【作    者】：清翔电子
 * 【功    能】：智能小车前后左右综合实验
 ***********************************************/
int left_motor_en = 5;//左电机使能
int right_motor_en = 6;//右电机使能

int left_motor_go = 3;//左电机正传
int right_motor_go = 4;//右电机正传

int left_motor_back = 2;//左电机反转 
int right_motor_back = 7;//右电机反转
void setup() {
  //电机驱动引脚全部设置为输出模式
  pinMode(left_motor_en,OUTPUT);
  pinMode(right_motor_en,OUTPUT);
  pinMode(left_motor_go,OUTPUT);
  pinMode(right_motor_go,OUTPUT);
  pinMode(left_motor_back,OUTPUT);
  pinMode(right_motor_back,OUTPUT);

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
//小车后退
void backward()
{
   digitalWrite(left_motor_go,LOW);  //左电机反转
   digitalWrite(left_motor_back,HIGH); 
   digitalWrite(right_motor_go,LOW);  //右电机反转
   digitalWrite(right_motor_back,HIGH); 
  }
//小车左转
void left()
{
   digitalWrite(left_motor_go,LOW);  //左电机停止
   digitalWrite(left_motor_back,LOW); 
   digitalWrite(right_motor_go,HIGH);  //右电机前进
   digitalWrite(right_motor_back,LOW);  
  }

//小车右转
void right()
{
   digitalWrite(left_motor_go,HIGH);  //左电机前进
   digitalWrite(left_motor_back,LOW); 
   digitalWrite(right_motor_go,LOW);  //右电机停止
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
void loop() {
  forward();//小车前进
  delay(3000);//毫秒级延时=3秒
  
  stop_car();//停车
  delay(3000);//毫秒级延时

  backward();//小车后退
  delay(3000);//毫秒级延时

   stop_car();//停车
   delay(3000);//毫秒级延时

   left();//小车左转
   delay(3000);//毫秒级延时

   stop_car();//停车
   delay(3000);//毫秒级延时

   right();//小车右转
   delay(3000);//毫秒级延时

   stop_car();//停车
   while(1);  //程序停止
}
