/************************************************
 * 【作    者】：清翔电子
 * 【功    能】：拓展实验-WIFI遥控智能小车
 * 过近停车，直到超出预设安全距离后才继续前进。
 * 【实验要求】：请参考开发指南中的相关章节
 ***********************************************/
#include "qxmbot1.h"

QXMBOT1_WIFI_ESP8266 g_QXMBOT1_WIFI_ESP8266_1;

void serialEvent(){
  if(Serial.available()){
  g_ESP8266temDATA = Serial.read();
  if(g_ESP8266temDATA == ':'){
  g_ESP8266_EN = 1;
  }
  else if(g_ESP8266_EN == 1){
  g_ESP8266_EN = 0;
  g_UartData = g_ESP8266temDATA;
  if((g_UartData >= 51) && (g_UartData <= 150)){
  g_leftSpeed = map(g_UartData, 51, 150, 105, 255);
  analogWrite(5,g_leftSpeed);
  }
  if((g_UartData >= 151) && (g_UartData <= 250)){
  g_rightSpeed = map(g_UartData, 151, 250, 105, 255);
  analogWrite(6,g_rightSpeed);
  }
  }
  }
  }

QXMBOT1_motor  g_QXMBOT1_CarControl(2, 3, 4, 7, 5, 6);

QXMBOT1_buzzer g_QXMBOT1_buzzer1(A3);

QXMBOT_cloudServo G_QXMBOT_cloudServo1(9, OUTPUT);

void setup()
{
  Serial.begin(9600);

  g_QXMBOT1_WIFI_ESP8266_1.ESP8266Init();

  G_QXMBOT_cloudServo1.cloudServoContrl(90,100);
  g_QXMBOT1_buzzer1.buzzerOFF(A3);
}

void loop()
{

  switch (g_UartData) {
   case 1:
    g_QXMBOT1_CarControl.QXMBOT1_arCarStops(g_leftSpeed, g_rightSpeed);
    break;
   case 2:
    g_QXMBOT1_CarControl.QXMBOT1_arCarForward(g_leftSpeed, g_rightSpeed);
    break;
   case 3:
    g_QXMBOT1_CarControl.QXMBOT1_arCarBack(g_leftSpeed, g_rightSpeed);
    break;
   case 4:
    g_QXMBOT1_CarControl.QXMBOT1_arCarLeftTurn(g_leftSpeed, g_rightSpeed);
    break;
   case 5:
    g_QXMBOT1_CarControl.QXMBOT1_arCarRightTurn(g_leftSpeed, g_rightSpeed);
    break;
   case 6:
    g_QXMBOT1_CarControl.QXMBOT1_arCarLeftTurn(g_leftSpeed, g_rightSpeed);
    break;
   case 7:
    g_QXMBOT1_CarControl.QXMBOT1_arCarRightTurn(g_leftSpeed, g_rightSpeed);
    break;
   case 8:
    g_QXMBOT1_buzzer1.buzzerON(A3);
    break;
   case 9:
    g_QXMBOT1_buzzer1.buzzerOFF(A3);
    break;
   case 10:
    G_QXMBOT_cloudServo1.cloudServoContrl(180,100);
    break;
   case 11:
    G_QXMBOT_cloudServo1.cloudServoContrl(90,100);
    break;
   case 12:
    G_QXMBOT_cloudServo1.cloudServoContrl(0,100);
    break;
  }

}
