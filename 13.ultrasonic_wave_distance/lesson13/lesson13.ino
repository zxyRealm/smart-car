/************************************************
 * 【作    者】：清翔电子
 * 【功    能】：串口显示超声波测距距离。
 ***********************************************/
#include "qxmbot1.h"

QXMBOT_SR04  g_QXMBOT_SR04Ult1(A4, A5);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  delay(200);
  Serial.print(g_QXMBOT_SR04Ult1.QXMBOT_getDistance());
  Serial.println("CM");

}
