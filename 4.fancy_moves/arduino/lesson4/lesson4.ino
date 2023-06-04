/************************************************
 * 【作    者】：清翔电子
 * 【功    能】：智能小车花式动作
 * 智能小车会执行一系列设定动作，请把小车放置在开阔
 * 地段运行，蜂鸣器鸣笛后表示小车执行完成。
 ***********************************************/
int left_motor_en = 5;//左电机使能
int right_motor_en = 6;//右电机使能

int left_motor_go = 3;//左电机正传
int right_motor_go = 4;//右电机正传

int left_motor_back = 2;//左电机反转 
int right_motor_back = 7;//右电机反转
int buzzer = A3;//蜂鸣器
void setup() {
  //电机驱动引脚全部设置为输出模式
  pinMode(left_motor_en,OUTPUT);
  pinMode(right_motor_en,OUTPUT);
  pinMode(left_motor_go,OUTPUT);
  pinMode(right_motor_go,OUTPUT);
  pinMode(left_motor_back,OUTPUT);
  pinMode(right_motor_back,OUTPUT);
  pinMode(buzzer,OUTPUT);//蜂鸣器引脚输出模式
  digitalWrite(buzzer,HIGH);//关闭蜂鸣器
  
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
//小车单轮左转
void left()
{
   digitalWrite(left_motor_go,LOW);  //左电机停止
   digitalWrite(left_motor_back,LOW); 
   digitalWrite(right_motor_go,HIGH);  //右电机前进
   digitalWrite(right_motor_back,LOW);  
  }

//小车单轮右转
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

//小车原地左转
void left_rapidly()
{
   digitalWrite(left_motor_go,LOW);  //左电机反转
   digitalWrite(left_motor_back,HIGH); 
   digitalWrite(right_motor_go,HIGH);  //右电机正转
   digitalWrite(right_motor_back,LOW); 
  }
//小车原地右转
void right_rapidly()
{
   digitalWrite(left_motor_go,HIGH);  //左电机正转
   digitalWrite(left_motor_back,LOW); 
   digitalWrite(right_motor_go,LOW);  //右电机反转
   digitalWrite(right_motor_back,HIGH); 
  }
void loop() 
{
  int i;
  delay(1000);//s上电后延时1秒
  
  forward();//小车前进3秒
  delay(3000);
  stop_car();//停车1秒
  delay(1000);
  backward();//小车后退3秒
  delay(3000);
  stop_car();//停车1秒
  delay(1000);
  

  for(i=0; i<5; i++)//小车间歇性前进5步
  {
     forward();//小车前进
     delay(500);  
     stop_car();//停车
     delay(500);
  }
  for(i=0; i<5; i++)//小车间歇性后退5步
  {
     backward();//小车后退
     delay(500);  
     stop_car();//停车
     delay(500);
  }
  for(i=0; i<5; i++)//小车单轮左转与双轮左转各5次
  {
     left();//小车左转
     delay(1000);
     left_rapidly();//双轮实现原地左转
     delay(500);
  }
  for(i=0; i<5; i++)//小车单轮右转与双轮右转各5次
  {
     right();//小车右转
     delay(1000);
     right_rapidly();//双轮实现原地右转
     delay(500);
  }
  for(i=0; i<10; i++)//小车走S形前进路线
  {
     left();//小车左转
     delay(300);
     right();//小车右转
     delay(300);
  }
   for(i=0; i<5; i++)//小车间歇性左旋转与前进5次
  {
     forward();//小车前进
     delay(500);
     stop_car();//停车
     delay(500);//毫秒级延时
     left_rapidly();//双轮实现原地左旋转
     delay(200);
     stop_car();//停车
     delay(500);//毫秒级延时
  }
   for(i=0; i<5; i++)//小车间歇性右旋转与前进5次
  {
     forward();//小车前进
     delay(500);
     stop_car();//停车
     delay(500);//毫秒级延时
     right_rapidly();//双轮实现原地右旋转
     delay(200);
     stop_car();//停车
     delay(500);//毫秒级延时
  }
  digitalWrite(buzzer,LOW); 
  delay(2000);//鸣笛2秒
  digitalWrite(buzzer,HIGH); 
   while(1);  //程序停止
}
