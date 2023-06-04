/************************************************
 * 【作    者】：清翔电子
 * 【功    能】：智能小车红外避障2-基础版本
 * 【实验要求】：查阅开发指导手册相关章节
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
   analogWrite(left_motor_en,150);//左电机占空比值 取值范围0-255，255最快
   analogWrite(right_motor_en,150);//右电机占空比值取值范围0-255 ,255最快 
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
  //状态:LOW 识别到障碍物,HIGH 未识别到障碍物
  if(digitalRead(left_led2) == LOW && digitalRead(right_led2) == HIGH)
  {
    right();
    delay(100); 
   }else if(digitalRead(left_led2) == HIGH && digitalRead(right_led2) == LOW)
   {
      left();
       delay(100); 
    }else if(digitalRead(left_led2) == LOW && digitalRead(right_led2) == LOW)
    {
        right_rapidly();
        delay(100); 
      }
   else
   {
     forward();//当左右都没识别到障碍物，执行前进
    }

}
