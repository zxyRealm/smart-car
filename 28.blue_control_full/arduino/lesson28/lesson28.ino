/************************************************
 * 【作    者】：清翔电子
 * 【功    能】：综合实验-蓝牙遥控综合程序
 * 【实验要求】：请参考开发指南中的相关章节
 ***********************************************/
#include "qxmbot1.h"

volatile long g_frontDistance;
volatile long g_leftDistance;
volatile long g_rightDistance;

QXMBOT_cloudServo G_QXMBOT_cloudServo1(9, OUTPUT);

QXMBOT1_buzzer g_QXMBOT1_buzzer1(A3);

void serialEvent(){
  if(Serial.available()){
  g_UartData = Serial.read();
  if((g_UartData >= 51) && (g_UartData <= 150)){
  g_leftSpeed = map(g_UartData, 51, 150, 105, 255);
  analogWrite(5,g_leftSpeed);}
  if((g_UartData >= 151) && (g_UartData <= 250)){g_rightSpeed = map(g_UartData, 151, 250, 105, 255);
  analogWrite(6,g_rightSpeed);}}}
QXMBOT1_motor  g_QXMBOT1_CarControl(2, 3, 4, 7, 5, 6);

QXMBOT1_headlight g_QXMBOT1_headlight1(10);

QXMBOT_SR04  g_QXMBOT_SR04Ult1(A4, A5);

QXMBOT1_avoidSensor  g_QXMBOT1_avoidSensor1(12, 13);

void PTZ_Avoid() {
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
      if ((LOW == g_QXMBOT1_avoidSensor1.getAvoidStatus_L())) {
        g_QXMBOT1_CarControl.QXMBOT1_arCarRight(150, 150);

      } else if ((LOW == g_QXMBOT1_avoidSensor1.getAvoidStatus_R())) {
        g_QXMBOT1_CarControl.QXMBOT1_arCarLeft(150, 150);
      } else {
        g_QXMBOT1_CarControl.QXMBOT1_arCarForward(150, 150);

      }
    }

  }
}

QXMBOT1_trackSensor  g_QXMBOT1_trackSensor1(11, 8);

void TrackingAvoid() {
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
    for (int a = 1; a <= 3600; a = a + (1)) {
      if ((HIGH == g_QXMBOT1_trackSensor1.getTrackStatus_L()) && (HIGH == g_QXMBOT1_trackSensor1.getTrackStatus_R())) {
        g_QXMBOT1_CarControl.QXMBOT1_arCarForward(100, 100);

      } else if ((LOW == g_QXMBOT1_trackSensor1.getTrackStatus_L()) && (HIGH == g_QXMBOT1_trackSensor1.getTrackStatus_R())) {
        g_QXMBOT1_CarControl.QXMBOT1_arCarRight(200, 100);
      } else if ((HIGH == g_QXMBOT1_trackSensor1.getTrackStatus_L()) && (LOW == g_QXMBOT1_trackSensor1.getTrackStatus_R())) {
        g_QXMBOT1_CarControl.QXMBOT1_arCarLeft(100, 200);
      }
    }

  }
}

void IR_Avoid4() {
  if ((LOW == g_QXMBOT1_avoidSensor1.getAvoidStatus_L()) && (HIGH == g_QXMBOT1_avoidSensor1.getAvoidStatus_R())) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarRight(150, 150);

  } else if ((HIGH == g_QXMBOT1_avoidSensor1.getAvoidStatus_L()) && (LOW == g_QXMBOT1_avoidSensor1.getAvoidStatus_R())) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarLeft(150, 150);
  } else if ((LOW == g_QXMBOT1_avoidSensor1.getAvoidStatus_L()) && (LOW == g_QXMBOT1_avoidSensor1.getAvoidStatus_R())) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarStops(150, 150);
    delay(100);
    g_QXMBOT1_CarControl.QXMBOT1_arCarBack(150, 150);
    delay(100);
    g_QXMBOT1_CarControl.QXMBOT1_arCarLeftTurn(150, 150);
    delay(300);
  } else {
    g_QXMBOT1_CarControl.QXMBOT1_arCarForward(150, 150);

  }
}

QXMBOT1_followSpot  g_QXMBOT1_followSpot1(A1, A0, A2);

void FollowSpot() {
  if ((LOW == g_QXMBOT1_followSpot1.getFollowSpotStatus_S()) && ((HIGH == g_QXMBOT1_followSpot1.getFollowSpotStatus_L()) && (HIGH == g_QXMBOT1_followSpot1.getFollowSpotStatus_R()))) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarForward(150, 150);

  } else if ((LOW == g_QXMBOT1_followSpot1.getFollowSpotStatus_S()) && ((LOW == g_QXMBOT1_followSpot1.getFollowSpotStatus_L()) && (HIGH == g_QXMBOT1_followSpot1.getFollowSpotStatus_R()))) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarForward(85, 180);
  } else if ((LOW == g_QXMBOT1_followSpot1.getFollowSpotStatus_S()) && ((HIGH == g_QXMBOT1_followSpot1.getFollowSpotStatus_L()) && (LOW == g_QXMBOT1_followSpot1.getFollowSpotStatus_R()))) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarForward(180, 85);
  } else if ((HIGH == g_QXMBOT1_followSpot1.getFollowSpotStatus_S()) && ((HIGH == g_QXMBOT1_followSpot1.getFollowSpotStatus_L()) && (LOW == g_QXMBOT1_followSpot1.getFollowSpotStatus_R()))) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarRight(150, 150);
  } else if ((HIGH == g_QXMBOT1_followSpot1.getFollowSpotStatus_S()) && ((LOW == g_QXMBOT1_followSpot1.getFollowSpotStatus_L()) && (HIGH == g_QXMBOT1_followSpot1.getFollowSpotStatus_R()))) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarLeft(150, 150);
  } else {
    g_QXMBOT1_CarControl.QXMBOT1_arCarStops(150, 150);

  }
}

void FollowAvoid() {
  if (g_QXMBOT_SR04Ult1.QXMBOT_getDistance() < 5) {
    g_QXMBOT1_buzzer1.buzzerON(A3);
    g_QXMBOT1_CarControl.QXMBOT1_arCarStops(100, 100);
    delay(60);
    while (g_QXMBOT_SR04Ult1.QXMBOT_getDistance() < 5) {
      delay(60);
    }
    g_QXMBOT1_buzzer1.buzzerOFF(A3);

  } else {
    for (int b = 1; b <= 3600; b = b + (1)) {
      if ((LOW == g_QXMBOT1_avoidSensor1.getAvoidStatus_L()) && (LOW == g_QXMBOT1_avoidSensor1.getAvoidStatus_R())) {
        g_QXMBOT1_CarControl.QXMBOT1_arCarForward(110, 110);

      } else if ((HIGH == g_QXMBOT1_avoidSensor1.getAvoidStatus_L()) && (LOW == g_QXMBOT1_avoidSensor1.getAvoidStatus_R())) {
        g_QXMBOT1_CarControl.QXMBOT1_arCarRight(110, 110);
      } else if ((LOW == g_QXMBOT1_avoidSensor1.getAvoidStatus_L()) && (HIGH == g_QXMBOT1_avoidSensor1.getAvoidStatus_R())) {
        g_QXMBOT1_CarControl.QXMBOT1_arCarLeft(110, 110);
      } else {
        g_QXMBOT1_CarControl.QXMBOT1_arCarStops(110, 110);

      }
    }

  }
}

void IR_Avoid1() {
  if ((LOW == g_QXMBOT1_avoidSensor1.getAvoidStatus_L())) {
    g_QXMBOT1_CarControl.QXMBOT1_arCarRight(100, 0);

  } else {
    g_QXMBOT1_CarControl.QXMBOT1_arCarForward(150, 150);

  }
}

void setup()
{
  G_QXMBOT_cloudServo1.cloudServoContrl(90,100);
  g_QXMBOT1_buzzer1.buzzerOFF(A3);
  Serial.begin(9600);

  g_frontDistance = 0;
  g_leftDistance = 0;
  g_rightDistance = 0;
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
   case 15:
    g_QXMBOT1_headlight1.headlightOFF(10);
    break;
   case 16:
    g_QXMBOT1_headlight1.headlightON(10);
    break;
   case 17:
    PTZ_Avoid();
    break;
   case 18:
    TrackingAvoid();
    break;
   case 19:
    IR_Avoid4();
    break;
   case 20:
    FollowSpot();
    break;
   case 21:
    FollowAvoid();
    break;
   case 22:
    IR_Avoid1();
    break;
   default:
    g_QXMBOT1_CarControl.QXMBOT1_arCarStops(200, 200);
    break;
  }

}
