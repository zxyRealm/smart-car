/************************************************
 * 【作    者】：清翔电子
 * 【功    能】：超声波实现“魔术手”实验
 * 【说    明】：实验方法请参阅此目录下实验效果视频
 * 当手掌靠近超声波的时候小车后退，离开超声波的时候小车前进
 ***********************************************/
#include "qxmbot1.h"

QXMBOT_cloudServo G_QXMBOT_cloudServo1(9, OUTPUT);

QXMBOT_SR04  g_QXMBOT_SR04Ult1(A4, A5);

QXMBOT1_motor  g_QXMBOT1_CarControl(2, 3, 4, 7, 5, 6);

void setup()
{
  G_QXMBOT_cloudServo1.cloudServoContrl(90,100);
}

void loop()
{
  // 舵机回正

  // 当测距距离大于20cm就前进，否则后退
  if (g_QXMBOT_SR04Ult1.QXMBOT_getDistance() > 20) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarForward(110, 110);

  } else {
    g_QXMBOT1_CarControl.QXMBOT1_arCarBack(110, 110);

  }

}
