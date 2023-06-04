/************************************************
 * 【作    者】：清翔电子
 * 【功    能】：智能小车红外避障3-贴圆边行驶
 * 【实验要求】：小车以顺时针方向在圆内贴边行驶
 * 把智能小车放置在自然光较弱的环境中实验，例如室内光线较弱的地方。
 * 推荐用纸皮围成直径1米以上的圆，把下车放置在其中运行。
 ***********************************************/
int left_motor_en = 5;//左电机使能
int right_motor_en = 6;//右电机使能

int left_motor_go = 3;//左电机正传
int right_motor_go = 4;//右电机正传

int left_motor_back = 2;//左电机反转 
int right_motor_back = 7;//右电机反转

int left_led2 = 12;//左避障信号 为LOW 识别到障碍物 为HIGH未识别到障碍物
int right_led2 = 13;//右避障信号 为LOW 识别到障碍物  为HIGH未识别到障碍物
void setup() {
  //电机驱动引脚全部设置为输出模式
  pinMode(left_motor_en,OUTPUT);
  pinMode(right_motor_en,OUTPUT);
  pinMode(left_motor_go,OUTPUT);
  pinMode(right_motor_go,OUTPUT);
  pinMode(left_motor_back,OUTPUT);
  pinMode(right_motor_back,OUTPUT);
  pinMode(left_led2,INPUT);//左避障信号脚设置为输入模式
  pinMode(right_led2,INPUT);//右避障信号脚设置为输入模式
  //红外避障时车速要慢，否则容易撞上障碍物
   analogWrite(left_motor_en,120);//左电机占空比值 取值范围0-255，255最快
   analogWrite(right_motor_en,120);//右电机占空比值取值范围0-255 ,255最快 
}
//小车前进
void forward()
{
   digitalWrite(left_motor_go,HIGH);  //左电机前进
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
void loop() 
{
  //状态:LOW 识别到障碍物,HIGH 未识别到障碍物
  if(digitalRead(left_led2) == LOW )
  {
   right();//小车左侧识别到障碍物，右转躲避
  }
  else
  {
     forward();//其他情况执行前进
  }
}
