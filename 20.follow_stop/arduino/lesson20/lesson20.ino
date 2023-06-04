/************************************************
 * 【作    者】：清翔电子
 * 【功    能】：智能小车执行物体跟随过程中与被跟随物体距离
 * 过近停车，直到超出预设安全距离后才继续前进。
 * 【实验要求】：请参考开发指南中的相关章节
 ***********************************************/
#include "qxmbot1.h"

QXMBOT_cloudServo G_QXMBOT_cloudServo1(9, OUTPUT);

QXMBOT1_buzzer g_QXMBOT1_buzzer1(A3);

QXMBOT1_avoidSensor  g_QXMBOT1_avoidSensor1(12, 13);

QXMBOT1_motor  g_QXMBOT1_CarControl(2, 3, 4, 7, 5, 6);

void IR_Follow() {
  if ((LOW == g_QXMBOT1_avoidSensor1.getAvoidStatus_L()) && (LOW == g_QXMBOT1_avoidSensor1.getAvoidStatus_R())) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarForward(110, 110);

  } else if ((HIGH == g_QXMBOT1_avoidSensor1.getAvoidStatus_L()) && (LOW == g_QXMBOT1_avoidSensor1.getAvoidStatus_R())) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarRight(110, 110);
  } else if ((LOW == g_QXMBOT1_avoidSensor1.getAvoidStatus_L()) && (HIGH == g_QXMBOT1_avoidSensor1.getAvoidStatus_R())) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarLeft(110, 110);
  } else if ((HIGH == g_QXMBOT1_avoidSensor1.getAvoidStatus_L()) && (HIGH == g_QXMBOT1_avoidSensor1.getAvoidStatus_R())) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarStops(110, 110);
  }
}

QXMBOT_SR04  g_QXMBOT_SR04Ult1(A4, A5);

void setup()
{
  G_QXMBOT_cloudServo1.cloudServoContrl(90,100);
  g_QXMBOT1_buzzer1.buzzerOFF(A3);
}

void loop()
{
  if (g_QXMBOT_SR04Ult1.QXMBOT_getDistance() < 5) {
    g_QXMBOT1_buzzer1.buzzerON(A3);
    g_QXMBOT1_CarControl.QXMBOT1_arCarStops(100, 100);
    delay(60);
    while (g_QXMBOT_SR04Ult1.QXMBOT_getDistance() < 5) {
      delay(60);
    }
    g_QXMBOT1_buzzer1.buzzerOFF(A3);

  } else {
    for (int i = 1; i <= 3600; i = i + (1)) {
      IR_Follow();
    }

  }

}
