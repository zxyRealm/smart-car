/************************************************
 * 【作    者】：清翔电子
 * 【功    能】：8、黑线寻迹8字形赛道
 * 【实验要求】：把智能小车放置在贴好黑线的场地上
 * 运行，黑线宽度贴1.5厘米宽，地面颜色要求不能为
 * 深色，例如黑色地面
 ***********************************************/
int left_motor_en = 5;//左电机使能
int right_motor_en = 6;//右电机使能

int left_motor_go = 3;//左电机正传
int right_motor_go = 4;//右电机正传

int left_motor_back = 2;//左电机反转 
int right_motor_back = 7;//右电机反转

int left_led1 = 11;//左寻迹信号 为LOW 没有识别到黑线 为HIGH识别到黑线
int right_led1 = 8;//右寻迹信号 为LOW 没有识别到黑线 为HIGH识别到黑线
void setup() {
  //电机驱动引脚全部设置为输出模式
  pinMode(left_motor_en,OUTPUT);
  pinMode(right_motor_en,OUTPUT);
  pinMode(left_motor_go,OUTPUT);
  pinMode(right_motor_go,OUTPUT);
  pinMode(left_motor_back,OUTPUT);
  pinMode(right_motor_back,OUTPUT);
  pinMode(left_led1,INPUT);//左寻迹信号脚设置为输入模式
  pinMode(right_led1,INPUT);//右寻迹信号脚设置为输入模式
}
//小车前进
void forward()
{
   digitalWrite(left_motor_go,HIGH);  //左电机前进
   digitalWrite(left_motor_back,LOW); 
   digitalWrite(right_motor_go,HIGH);  //右电机前进
   digitalWrite(right_motor_back,LOW);  
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

void loop() 
{
  //状态:LOW 没有识别到黑线,HIGH识别到黑线
  if(digitalRead(left_led1) == HIGH && digitalRead(right_led1) == HIGH)
  {
      //黑线循迹时速度要慢，否则很容易出线
   analogWrite(left_motor_en,100);//左电机占空比值 取值范围0-255，255最快
   analogWrite(right_motor_en,100);//右电机占空比值取值范围0-255 ,255最快 
    forward();//当左右探头识别到黑线执行前进
  }else if(digitalRead(left_led1) == LOW && digitalRead(right_led1) == HIGH)
  {
    analogWrite(left_motor_en,200);//左电机占空比值 取值范围0-255，255最快
    right();//左边出线，执行右转修正
  }else if(digitalRead(left_led1) == HIGH && digitalRead(right_led1) == LOW)
  {
       analogWrite(right_motor_en,200);//右电机占空比值取值范围0-255 ,255最快
       left();//右边出线，执行左转修正
    }
}
