/************************************************
 * 【作    者】：清翔电子
 * 【功    能】：拓展实验-人体感应实验
 * 【实验要求】：请参考开发指南中的相关章节
 ***********************************************/
#include "qxmbot1.h"

QXMBOT_cloudServo G_QXMBOT_cloudServo1(9, OUTPUT);

QXMBOT1_buzzer g_QXMBOT1_buzzer1(A3);

QXMBOT1_HIS_sensor  g_QXMBOT1_HIS_sensor1(A2, INPUT_PULLUP);

QXMBOT1_trackSensor  g_QXMBOT1_trackSensor1(11, 8);

QXMBOT1_motor  g_QXMBOT1_CarControl(2, 3, 4, 7, 5, 6);

void setup()
{
  G_QXMBOT_cloudServo1.cloudServoContrl(90,100);
  g_QXMBOT1_buzzer1.buzzerOFF(A3);
  delay(30000);
  while ((LOW == g_QXMBOT1_HIS_sensor1.getHIS_Status(A2))) {
  }
  g_QXMBOT1_buzzer1.buzzerON(A3);
  delay(1000);
  g_QXMBOT1_buzzer1.buzzerOFF(A3);
}

void loop()
{
  if ((HIGH == g_QXMBOT1_trackSensor1.getTrackStatus_L()) && (HIGH == g_QXMBOT1_trackSensor1.getTrackStatus_R())) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarForward(100, 100);

  } else if ((LOW == g_QXMBOT1_trackSensor1.getTrackStatus_L()) && (HIGH == g_QXMBOT1_trackSensor1.getTrackStatus_R())) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarRight(200, 100);
  } else if ((HIGH == g_QXMBOT1_trackSensor1.getTrackStatus_L()) && (LOW == g_QXMBOT1_trackSensor1.getTrackStatus_R())) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarLeft(100, 200);
  }

}
