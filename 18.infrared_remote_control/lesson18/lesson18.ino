/************************************************
 * 【作    者】：清翔电子
 * 【功    能】：智能小车红外无线遥控
 * 【实验要求】：参考此目录内接线图插好红外接收头
 * 红外遥控器初次使用时尾部有隔离胶片的需要取掉。
 * 因为红外通信自身的原因，遥控体验会比较差，必须对准
 * 红外接收头才能遥控到。推荐使用蓝牙或者wifi做无线遥控
 **********************************************/
 #include <IRremote.h>
int RECV_PIN = A1;   //红外线接收器OUTPUT端接在A1
IRrecv irrecv(RECV_PIN);   // 定义IRrecv 对象来接收红外线信号
decode_results results;   //解码结果放在decode_results构造的对象results里

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
  irrecv.enableIRIn();          //启动红外解码
  //控制车速
   analogWrite(left_motor_en,220);//左电机占空比值 取值范围0-255，255最快
   analogWrite(right_motor_en,220);//右电机占空比值取值范围0-255 ,255最快 
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
 if (irrecv.decode(&results))
 {         //解码成功，收到一组红外线信号
    switch(results.value){                     //判定按下的是哪个按键
      case 0xFF18E7: forward();     break;//数字“2”键，前进
      case 0xFF4AB5: backward();    break;//数字“8”键，后退
      case 0xFF10EF: left();        break;//数字“4”键，左转
      case 0xFF5AA5: right();       break;//数字“6”键，右转
      case 0xFF38C7: stop_car();    break;//数字“5”键，停车
    }
    irrecv.resume(); 
 }
}
