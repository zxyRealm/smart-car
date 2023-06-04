/************************************************
 * 【作    者】：清翔电子
 * 【功    能】：舵机云台左右转动5次
 * 【说    明】：请参考开发指南相关章节内容
 ***********************************************/
#include "qxmbot1.h"

QXMBOT_cloudServo G_QXMBOT_cloudServo1(9, OUTPUT);

void setup()
{

}

void loop()
{
  for (int i = 1; i <= 5; i = i + (1)) {
    G_QXMBOT_cloudServo1.cloudServoContrl(0,600);
    G_QXMBOT_cloudServo1.cloudServoContrl(90,600);
    G_QXMBOT_cloudServo1.cloudServoContrl(180,600);
    G_QXMBOT_cloudServo1.cloudServoContrl(90,600);
  }
  while(true);

}
