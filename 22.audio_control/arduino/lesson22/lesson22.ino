/************************************************
 * 【作    者】：清翔电子
 * 【功    能】：22、语音和开源版遥控程序
 * 过近停车，直到超出预设安全距离后才继续前进。
 * 【实验要求】：请参考开发指南中的相关章节
 ***********************************************/
#include "qxmbot1.h"

volatile byte g_motorLeftSpeed;
volatile byte g_motorRightSpeed;

void serialEvent(){
  if(Serial.available()){
  g_UartData = Serial.read();
  if((g_UartData >= 51) && (g_UartData <= 150)){
  g_leftSpeed = map(g_UartData, 51, 150, 105, 255);
  analogWrite(5,g_leftSpeed);}
  if((g_UartData >= 151) && (g_UartData <= 250)){g_rightSpeed = map(g_UartData, 151, 250, 105, 255);
  analogWrite(6,g_rightSpeed);}}}
QXMBOT1_motor  g_QXMBOT1_CarControl(2, 3, 4, 7, 5, 6);

QXMBOT1_buzzer g_QXMBOT1_buzzer1(A3);

QXMBOT_cloudServo G_QXMBOT_cloudServo1(9, OUTPUT);

void setup()
{
  Serial.begin(9600);

  g_motorLeftSpeed = 100;
  g_motorRightSpeed = 100;
  G_QXMBOT_cloudServo1.cloudServoContrl(90,100);
  g_QXMBOT1_buzzer1.buzzerOFF(A3);
}

void loop()
{

  switch (g_UartData) {
   case 1:
    g_QXMBOT1_CarControl.QXMBOT1_arCarStops(g_motorLeftSpeed, g_motorRightSpeed);
    break;
   case 2:
    g_QXMBOT1_CarControl.QXMBOT1_arCarForward(g_motorLeftSpeed, g_motorRightSpeed);
    break;
   case 3:
    g_QXMBOT1_CarControl.QXMBOT1_arCarBack(g_motorLeftSpeed, g_motorRightSpeed);
    break;
   case 4:
    g_QXMBOT1_CarControl.QXMBOT1_arCarLeft(g_motorLeftSpeed, g_motorRightSpeed);
    break;
   case 5:
    g_QXMBOT1_CarControl.QXMBOT1_arCarRight(g_motorLeftSpeed, g_motorRightSpeed);
    break;
   case 6:
    g_QXMBOT1_CarControl.QXMBOT1_arCarLeftTurn(g_motorLeftSpeed, g_motorRightSpeed);
    break;
   case 7:
    g_QXMBOT1_CarControl.QXMBOT1_arCarRightTurn(g_motorLeftSpeed, g_motorRightSpeed);
    break;
   case 8:
    g_QXMBOT1_buzzer1.buzzerON(A3);
    break;
   case 9:
    g_QXMBOT1_buzzer1.buzzerOFF(A3);
    break;
   case 11:
    g_motorLeftSpeed = 100;
    g_motorRightSpeed = 100;
    break;
   case 12:
    g_motorLeftSpeed = 139;
    g_motorRightSpeed = 139;
    break;
   case 13:
    g_motorLeftSpeed = 178;
    g_motorRightSpeed = 178;
    break;
   case 14:
    g_motorLeftSpeed = 217;
    g_motorRightSpeed = 217;
    break;
   case 15:
    g_motorLeftSpeed = 255;
    g_motorRightSpeed = 255;
    break;
  }

}
