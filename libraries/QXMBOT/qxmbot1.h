#ifndef QXMBOT1_H
#define QXMBOT1_H

#include "Arduino.h"

#define QX_PULSE_TIMEOUT 75000L // 50ms
#define DEFAULT_DELAY 60
#define DEFAULT_PINGS 3


extern byte g_leftSpeed;
extern byte g_rightSpeed;
extern byte g_UartData;
extern byte g_ESP8266temDATA;
extern bool g_ESP8266_EN;

//车灯控制
class QXMBOT1_headlight
{
public:

    void headlightON(byte t_pinNum);
    void headlightOFF(byte t_pinNum);

    QXMBOT1_headlight(byte t_pin);
    ~QXMBOT1_headlight();

private:

    byte m_pinName;
};


class QXMBOT1_button
{
public:

    QXMBOT1_button(byte t_pinNum);
    ~QXMBOT1_button();

    void startButton(byte t_pinNum);

private:

    byte m_pinName;
};

class QXMBOT1_buzzer
{
public:

    QXMBOT1_buzzer(byte t_pinNum);
    ~QXMBOT1_buzzer();

    void buzzerON(byte t_pinNum);
    void buzzerOFF(byte t_pinNum);

private:

    byte m_pinName;
};

class QXMBOT1_motor
{
public:

    QXMBOT1_motor(byte t_lGo,byte t_lBack,byte t_rGo, byte t_rBack, byte t_lEn, byte t_rEn);
    ~QXMBOT1_motor();

   inline void QXMBOT1_arCarForward(int t_lSpeed = 255, int t_rSpeed = 255)
   {
       analogWrite(m_leftMotorEn, t_lSpeed);//PWM比例0~255调速，左右轮差异略增减
       analogWrite(m_rightMotorEn, t_rSpeed);//PWM比例0~255调速，左右轮差异略增减

       digitalWrite(m_leftMotorGo, LOW);
       digitalWrite(m_leftMotorBack, HIGH);

       digitalWrite(m_rightMotorGo, HIGH);
       digitalWrite(m_rightotorBack, LOW);
   }
   inline void QXMBOT1_arCarBack(int t_lSpeed = 255, int t_rSpeed = 255)
   {
       analogWrite(m_leftMotorEn, t_lSpeed);//PWM比例0~255调速，左右轮差异略增减
       analogWrite(m_rightMotorEn, t_rSpeed);//PWM比例0~255调速，左右轮差异略增减

       digitalWrite(m_leftMotorGo, HIGH);
       digitalWrite(m_leftMotorBack, LOW);

       digitalWrite(m_rightMotorGo, LOW);
       digitalWrite(m_rightotorBack, HIGH);
   }
   inline void QXMBOT1_arCarLeft(int t_lSpeed = 255, int t_rSpeed = 255)
   {
       analogWrite(m_leftMotorEn, t_lSpeed);//PWM比例0~255调速，左右轮差异略增减
       analogWrite(m_rightMotorEn, t_rSpeed);//PWM比例0~255调速，左右轮差异略增减

       digitalWrite(m_leftMotorGo, LOW);
       digitalWrite(m_leftMotorBack, LOW);

       digitalWrite(m_rightMotorGo, HIGH);
       digitalWrite(m_rightotorBack, LOW);
   }
   inline void QXMBOT1_arCarRight(int t_lSpeed = 255, int t_rSpeed = 255)
   {
       analogWrite(m_leftMotorEn, t_lSpeed);//PWM比例0~255调速，左右轮差异略增减
       analogWrite(m_rightMotorEn, t_rSpeed);//PWM比例0~255调速，左右轮差异略增减

       digitalWrite(m_leftMotorGo, LOW);
       digitalWrite(m_leftMotorBack, HIGH);

       digitalWrite(m_rightMotorGo, LOW);
       digitalWrite(m_rightotorBack, LOW);
   }
   inline void QXMBOT1_arCarRightTurn(int t_lSpeed = 255, int t_rSpeed = 255)
   {
       analogWrite(m_leftMotorEn, t_lSpeed);//PWM比例0~255调速，左右轮差异略增减
       analogWrite(m_rightMotorEn, t_rSpeed);//PWM比例0~255调速，左右轮差异略增减

       digitalWrite(m_leftMotorGo, LOW);
       digitalWrite(m_leftMotorBack, HIGH);

       digitalWrite(m_rightMotorGo, LOW);
       digitalWrite(m_rightotorBack, HIGH);
   }
   inline void QXMBOT1_arCarLeftTurn(int t_lSpeed = 255, int t_rSpeed = 255)
   {
       analogWrite(m_leftMotorEn, t_lSpeed);//PWM比例0~255调速，左右轮差异略增减
       analogWrite(m_rightMotorEn, t_rSpeed);//PWM比例0~255调速，左右轮差异略增减

       digitalWrite(m_leftMotorGo, HIGH);
       digitalWrite(m_leftMotorBack, LOW);

       digitalWrite(m_rightMotorGo, HIGH);
       digitalWrite(m_rightotorBack, LOW);
   }
   inline void QXMBOT1_arCarStops(int t_lSpeed = 255, int t_rSpeed = 255)
   {
       analogWrite(m_leftMotorEn, t_lSpeed);//PWM比例0~255调速，左右轮差异略增减
       analogWrite(m_rightMotorEn, t_rSpeed);//PWM比例0~255调速，左右轮差异略增减
       digitalWrite(m_leftMotorGo, LOW);
       digitalWrite(m_leftMotorBack, LOW);

       digitalWrite(m_rightMotorGo, LOW);
       digitalWrite(m_rightotorBack, LOW);
   }

private:

    byte m_leftMotorGo;
    byte m_leftMotorBack;
    byte m_rightMotorGo;
    byte m_rightotorBack;
    byte m_leftMotorEn;
    byte m_rightMotorEn;
};

class QXMBOT1_trackSensor
        {
public:

    QXMBOT1_trackSensor(byte t_leftPin,byte t_rightPin);
    ~QXMBOT1_trackSensor();

    inline int getTrackStatus_L()
    {
        return digitalRead(m_trackSensorLeft);
    }
    inline int getTrackStatus_R()
    {
        return digitalRead(m_trackSensorRight);
    }

private:

    byte m_trackSensorLeft;
    byte m_trackSensorRight;

};

class QXMBOT1_avoidSensor
        {
public:

    QXMBOT1_avoidSensor(byte t_leftPin,byte t_rightPin);
    ~QXMBOT1_avoidSensor();

    inline int getAvoidStatus_L()
    {
        return digitalRead(m_avoidSensorLeft);
    }
    inline int getAvoidStatus_R()
    {
        return digitalRead(m_avoidSensorRight);
    }

private:

    byte m_avoidSensorLeft;
    byte m_avoidSensorRight;

};

class   QXMBOT1_followSpot
{
public:

    QXMBOT1_followSpot(byte t_leftPin,byte t_senterPin,byte t_rightPin);
    ~QXMBOT1_followSpot();

    inline int getFollowSpotStatus_L()
    {
        return digitalRead(m_leftLightSensor);
    }

    inline int getFollowSpotStatus_S()
    {
        return digitalRead(m_senterLightSensor);
    }

    inline int getFollowSpotStatus_R()
    {
        return digitalRead(m_rightLightSensor);
    }

private:

    byte m_leftLightSensor;
    byte m_senterLightSensor;
    byte m_rightLightSensor;

};


class QXMBOT_SR04
{
public:

    QXMBOT_SR04(int t_echoPin = A4, int t_triggerPin = A5);
    ~QXMBOT_SR04();

    long QXMBOT_getDistance();
    long QXMBOT_DistanceAvg(int t_wait=DEFAULT_DELAY,int t_count=DEFAULT_PINGS);


private:

    long MicrosecondsToCentimeter(long t_duration);
    int m_echoPin, m_triggerPin;
    long m_duration, m_currentDistance;
};


class QXMBOT_cloudServo
{
public:

          QXMBOT_cloudServo(byte t_pinName, byte t_PinMode = OUTPUT);
          ~QXMBOT_cloudServo();

          /*舵机云台控制*/
          void cloudServoContrl(int t_angle, int t_defaultDelay);

private:
     byte m_pinName;
     byte m_PinMode;

};

class QXMBOT1_AHA_sensor
{
public:

    QXMBOT1_AHA_sensor(byte t_pinName, byte t_PinMode = INPUT_PULLUP);
    ~QXMBOT1_AHA_sensor();

    inline int getAHA_sensorStatus()
    {
        return digitalRead(m_pinName);
    }

private:
    byte m_pinName;
    byte m_PinMode;
};

class QXMBOT1_Microphone
{
public:

    QXMBOT1_Microphone(byte t_pinName, byte t_PinMode = INPUT_PULLUP);
    ~QXMBOT1_Microphone();

    inline int getMicrophoneStatus()
    {
        return digitalRead(m_pinName);
    }

private:
    byte m_pinName;
    byte m_PinMode;
};

class QXMBOT1_HIS_sensor
{
public:

    QXMBOT1_HIS_sensor(byte t_pinName, byte t_PinMode = INPUT_PULLUP);
    ~QXMBOT1_HIS_sensor();

    bool getHIS_Status(byte t_pinName);

private:
    byte m_pinName;
    byte m_PinMode;
    long m_defaultDelay;
};


class QXMBOT1_WIFI_ESP8266
{
public:

   void ESP8266Init();

private:

   unsigned char *CIPMUX;
   unsigned char *CIPSERVER;
};

#endif // QXMBOT1_H
