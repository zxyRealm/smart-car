/************************************************
 * 【作    者】：清翔电子
 * 【功    能】：智能小车执行黑线循迹过程中遇上障碍物则停车等待，
 * 直到障碍物移除后才继续前进。
 * 【实验要求】：把智能小车放置在贴好黑线的场地上
 * 运行，黑线宽度贴1.5厘米宽，地面颜色要求不能为
 * 深色，例如黑色地面
 ***********************************************/
#include "qxmbot1.h"

QXMBOT_cloudServo G_QXMBOT_cloudServo1(9, OUTPUT);

QXMBOT1_buzzer g_QXMBOT1_buzzer1(A3);

QXMBOT_SR04  g_QXMBOT_SR04Ult1(A4, A5);

QXMBOT1_motor  g_QXMBOT1_CarControl(2, 3, 4, 7, 5, 6);

QXMBOT1_trackSensor  g_QXMBOT1_trackSensor1(11, 8);

void IR_Tracking() {
  // 左边检测到黑线
  // 右边检测到黑线
  // 左边未检测到黑线
  // 右边检测到黑线
  // 左边检测到黑线
  // 右边未检测到黑线
  if (HIGH == digitalRead(11) && HIGH == digitalRead(8)) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarForward(100, 100);

  } else if (LOW == digitalRead(11) && HIGH == digitalRead(8)) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarRight(200, 100);
  } else if (HIGH == digitalRead(11) && LOW == digitalRead(8)) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarLeft(100, 200);
  }
}

void setup()
{
  G_QXMBOT_cloudServo1.cloudServoContrl(90,100);
  g_QXMBOT1_buzzer1.buzzerOFF(A3);
  pinMode(11, INPUT);
  pinMode(8, INPUT);
}

void loop()
{
  if (g_QXMBOT_SR04Ult1.QXMBOT_getDistance() < 7) {
    g_QXMBOT1_buzzer1.buzzerON(A3);
    g_QXMBOT1_CarControl.QXMBOT1_arCarStops(100, 100);
    delay(60);
    while (g_QXMBOT_SR04Ult1.QXMBOT_getDistance() < 7) {
      delay(60);
    }
    g_QXMBOT1_buzzer1.buzzerOFF(A3);
    if ((LOW == g_QXMBOT1_trackSensor1.getTrackStatus_L()) && (LOW == g_QXMBOT1_trackSensor1.getTrackStatus_R())) {
      g_QXMBOT1_CarControl.QXMBOT1_arCarBack(100, 100);

    }

  } else {
    for (int i = 1; i <= 3600; i = i + (1)) {
      IR_Tracking();
    }

  }

}
