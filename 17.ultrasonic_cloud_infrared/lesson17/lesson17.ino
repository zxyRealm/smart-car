/************************************************
 * 【作    者】：清翔电子
 * 【功    能】：超声波云台与红外二合一避障
 * 【说    明】：请参考开发指南相关章节内容
 ***********************************************/
#include "qxmbot1.h"

volatile long g_frontDistance;
volatile long g_leftDistance;
volatile long g_rightDistance;

QXMBOT_SR04  g_QXMBOT_SR04Ult1(A4, A5);

QXMBOT1_motor  g_QXMBOT1_CarControl(2, 3, 4, 7, 5, 6);

QXMBOT_cloudServo G_QXMBOT_cloudServo1(9, OUTPUT);

QXMBOT1_avoidSensor  g_QXMBOT1_avoidSensor1(12, 13);

// 红外避障
void IR_Avoid() {
  // 当测距距离大于20cm就前进，否则后退
  if ((LOW == g_QXMBOT1_avoidSensor1.getAvoidStatus_L())) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarRight(150, 150);

  } else if ((LOW == g_QXMBOT1_avoidSensor1.getAvoidStatus_R())) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarLeft(150, 150);
  } else {
    g_QXMBOT1_CarControl.QXMBOT1_arCarForward(150, 150);

  }
}

void setup()
{
  g_frontDistance = 0;
  g_leftDistance = 0;
  g_rightDistance = 0;
  G_QXMBOT_cloudServo1.cloudServoContrl(90,100);
}

void loop()
{
  if (g_QXMBOT_SR04Ult1.QXMBOT_getDistance() < 30) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarStops(150, 150);
    G_QXMBOT_cloudServo1.cloudServoContrl(180,800);
    g_leftDistance = g_QXMBOT_SR04Ult1.QXMBOT_DistanceAvg();
    G_QXMBOT_cloudServo1.cloudServoContrl(0,800);
    g_rightDistance = g_QXMBOT_SR04Ult1.QXMBOT_DistanceAvg();
    G_QXMBOT_cloudServo1.cloudServoContrl(90,800);
    g_frontDistance = g_QXMBOT_SR04Ult1.QXMBOT_DistanceAvg();
    if (g_frontDistance < 30) {
      if (g_leftDistance > g_rightDistance) {
        g_QXMBOT1_CarControl.QXMBOT1_arCarLeftTurn(255, 255);
        delay(100);

      } else if (g_leftDistance < g_rightDistance) {
        g_QXMBOT1_CarControl.QXMBOT1_arCarRightTurn(255, 255);
        delay(100);
      }

    } else {
      g_QXMBOT1_CarControl.QXMBOT1_arCarForward(150, 150);

    }

  } else {
    for (int i = 1; i <= 3600; i = i + (1)) {
      IR_Avoid();
    }

  }

  // 舵机回正

}
