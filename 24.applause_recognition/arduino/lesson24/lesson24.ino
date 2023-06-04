/************************************************
 * 【作    者】：清翔电子
 * 【功    能】：拓展实验-掌声识别
 * 过近停车，直到超出预设安全距离后才继续前进。
 * 【实验要求】：请参考开发指南中的相关章节
 ***********************************************/
#include "qxmbot1.h"

QXMBOT1_motor  g_QXMBOT1_CarControl(2, 3, 4, 7, 5, 6);

void setup()
{
  pinMode(10, INPUT);
}

void loop()
{
  if (digitalRead(10) == LOW) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarForward(200, 200);
    delay(200);

  } else {
    g_QXMBOT1_CarControl.QXMBOT1_arCarStops(200, 200);

  }

}
