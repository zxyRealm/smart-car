/************************************************
 * 【作    者】：清翔电子
 * 【功    能】：拓展实验-智能寻光
 * 过近停车，直到超出预设安全距离后才继续前进。
 * 【实验要求】：请参考开发指南中的相关章节
 ***********************************************/
#include "qxmbot1.h"

QXMBOT1_followSpot  g_QXMBOT1_followSpot1(A1, A0, A2);

QXMBOT1_motor  g_QXMBOT1_CarControl(2, 3, 4, 7, 5, 6);

void setup()
{

}

void loop()
{
  if ((LOW == g_QXMBOT1_followSpot1.getFollowSpotStatus_S()) && ((HIGH == g_QXMBOT1_followSpot1.getFollowSpotStatus_L()) && (HIGH == g_QXMBOT1_followSpot1.getFollowSpotStatus_R()))) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarForward(150, 150);

  } else if ((LOW == g_QXMBOT1_followSpot1.getFollowSpotStatus_S()) && ((LOW == g_QXMBOT1_followSpot1.getFollowSpotStatus_L()) && (HIGH == g_QXMBOT1_followSpot1.getFollowSpotStatus_R()))) {
    // 差速实现左转
    g_QXMBOT1_CarControl.QXMBOT1_arCarForward(85, 180);
  } else if ((LOW == g_QXMBOT1_followSpot1.getFollowSpotStatus_S()) && ((HIGH == g_QXMBOT1_followSpot1.getFollowSpotStatus_L()) && (LOW == g_QXMBOT1_followSpot1.getFollowSpotStatus_R()))) {
    // 差速实现右转
    g_QXMBOT1_CarControl.QXMBOT1_arCarForward(180, 85);
  } else if ((HIGH == g_QXMBOT1_followSpot1.getFollowSpotStatus_S()) && ((HIGH == g_QXMBOT1_followSpot1.getFollowSpotStatus_L()) && (LOW == g_QXMBOT1_followSpot1.getFollowSpotStatus_R()))) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarRight(150, 150);
  } else if ((HIGH == g_QXMBOT1_followSpot1.getFollowSpotStatus_S()) && ((LOW == g_QXMBOT1_followSpot1.getFollowSpotStatus_L()) && (HIGH == g_QXMBOT1_followSpot1.getFollowSpotStatus_R()))) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarLeft(150, 150);
  } else {
    g_QXMBOT1_CarControl.QXMBOT1_arCarStops(150, 150);

  }

}
