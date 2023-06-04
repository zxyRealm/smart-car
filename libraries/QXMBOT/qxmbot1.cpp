#include "qxmbot1.h"

byte g_leftSpeed = 255;
byte g_rightSpeed = 255;
byte g_UartData = 1;
byte g_ESP8266temDATA = 1;
bool g_ESP8266_EN = 0;

QXMBOT1_headlight::QXMBOT1_headlight(byte t_pin)
    :m_pinName(t_pin)
{
    pinMode(m_pinName, OUTPUT);
}

QXMBOT1_headlight::~QXMBOT1_headlight()
{
    pinMode(m_pinName, INPUT);
}


void QXMBOT1_headlight::headlightON(byte t_pinNum)
{
    digitalWrite(t_pinNum, LOW);
}

void QXMBOT1_headlight::headlightOFF(byte t_pinNum)
{
    digitalWrite(t_pinNum, HIGH);
}


QXMBOT1_button::QXMBOT1_button(byte t_pinNum)
    :m_pinName(t_pinNum)
{
    pinMode(m_pinName, INPUT);
}

QXMBOT1_button::~QXMBOT1_button()
{
    pinMode(m_pinName, OUTPUT);
}

void QXMBOT1_button::startButton(byte t_pinNum)
{
    for(;;) //死循环
    {
        if(!digitalRead(t_pinNum))// 检测按键是否按下
        {
            delay(5); //软件消抖
            if(!digitalRead(t_pinNum))//检测按键是否按下
            {
                while(!digitalRead(t_pinNum));//松手检测
                break;      //退出FOR死循环
            }
        }
    }
}

QXMBOT1_buzzer::QXMBOT1_buzzer(byte t_pinNum)
    :m_pinName(t_pinNum)
{
    pinMode(m_pinName, OUTPUT);
}

QXMBOT1_buzzer::~QXMBOT1_buzzer()
{
    pinMode(m_pinName, INPUT);
}

void QXMBOT1_buzzer::buzzerON(byte t_pinNum)
{
    digitalWrite(t_pinNum, LOW);
}

void QXMBOT1_buzzer::buzzerOFF(byte t_pinNum)
{
    digitalWrite(t_pinNum, HIGH);
}

QXMBOT1_motor::QXMBOT1_motor(byte t_lGo, byte t_lBack, byte t_rGo, byte t_rBack, byte t_lEn, byte t_rEn)
    :m_leftMotorGo(t_lGo),m_leftMotorBack(t_lBack),m_rightMotorGo(t_rGo),m_rightotorBack(t_rBack),
      m_leftMotorEn(t_lEn),m_rightMotorEn(t_rEn)
{
    pinMode(m_leftMotorGo, OUTPUT);
    pinMode(m_leftMotorBack, OUTPUT);
    pinMode(m_rightMotorGo, OUTPUT);
    pinMode(m_rightotorBack, OUTPUT);
    pinMode(m_leftMotorEn, OUTPUT);
    pinMode(m_rightMotorEn, OUTPUT);
}

QXMBOT1_motor::~QXMBOT1_motor()
{
    digitalWrite(m_leftMotorGo, LOW);
    digitalWrite(m_leftMotorBack, LOW);
    digitalWrite(m_rightMotorGo, LOW);
    digitalWrite(m_rightotorBack, LOW);
    digitalWrite(m_leftMotorEn, LOW);
    digitalWrite(m_rightMotorEn, LOW);

    pinMode(m_leftMotorGo, INPUT);
    pinMode(m_leftMotorBack, INPUT);
    pinMode(m_rightMotorGo, INPUT);
    pinMode(m_rightotorBack, INPUT);
    pinMode(m_leftMotorEn, INPUT);
    pinMode(m_rightMotorEn, INPUT);
}


QXMBOT1_trackSensor::QXMBOT1_trackSensor(byte t_leftPin, byte t_rightPin)
    :m_trackSensorLeft(t_leftPin),m_trackSensorRight(t_rightPin)
{
    pinMode(m_trackSensorLeft, INPUT_PULLUP);
    pinMode(m_trackSensorRight, INPUT_PULLUP);
}

QXMBOT1_trackSensor::~QXMBOT1_trackSensor()
{

}


QXMBOT1_avoidSensor::QXMBOT1_avoidSensor(byte t_leftPin, byte t_rightPin)
    :m_avoidSensorLeft(t_leftPin),m_avoidSensorRight(t_rightPin)
{
    pinMode(m_avoidSensorLeft, INPUT_PULLUP);
    pinMode(m_avoidSensorRight, INPUT_PULLUP);
}

QXMBOT1_avoidSensor::~QXMBOT1_avoidSensor()
{
}


QXMBOT1_followSpot::QXMBOT1_followSpot(byte t_leftPin, byte t_senterPin, byte t_rightPin)
    :m_leftLightSensor(t_leftPin),m_senterLightSensor(t_senterPin),m_rightLightSensor(t_rightPin)
{
    pinMode(m_leftLightSensor, INPUT_PULLUP);
    pinMode(m_senterLightSensor, INPUT_PULLUP);
    pinMode(m_rightLightSensor, INPUT_PULLUP);
}

QXMBOT1_followSpot::~QXMBOT1_followSpot()
{
}

//unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout) {
//  pinMode(pin, INPUT);
//  uint32_t start = micros();
//  while(digitalRead(pin) == state && (micros() - start) < timeout);
//  while(digitalRead(pin) != state && (micros() - start) < timeout);
//  start = micros();
//  while(digitalRead(pin) == state && (micros() - start) < timeout);
//  return micros() - start;
//}


QXMBOT_SR04::QXMBOT_SR04(int t_echoPin, int t_triggerPin)
    :m_echoPin(t_echoPin),m_triggerPin(t_triggerPin),
      m_duration(0),m_currentDistance(0)
{
    pinMode(m_echoPin, INPUT);
    pinMode(m_triggerPin, OUTPUT);
}

QXMBOT_SR04::~QXMBOT_SR04()
{
}

long QXMBOT_SR04::QXMBOT_getDistance()
{

    m_currentDistance = 0;
    m_duration = 0;
    digitalWrite(m_triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(m_triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(m_triggerPin, LOW);
    delayMicroseconds(2);
    m_duration = pulseIn(m_echoPin, HIGH, QX_PULSE_TIMEOUT);
    m_currentDistance = MicrosecondsToCentimeter(m_duration);
//    delay(25);
    return m_currentDistance;
}

long QXMBOT_SR04::QXMBOT_DistanceAvg(int t_wait, int t_count)
{
    long min, max, avg, d;
    min = 999;
    max = 0;
    avg = d = 0;

    if (t_wait < 25) {
        t_wait = 25;
    }
    if (t_count < 1) {
        t_count = 1;
    }

    for (int x = 0; x < t_count + 2; x++) {
        d = QXMBOT_getDistance();

        if (d < min) {
            min = d;
        }

        if (d > max) {
            max = d;
        }

        avg += d;
    }

    // substract highest and lowest value
    avg -= (max + min);
    // calculate average
    avg /= t_count;
    delay(t_wait);
    return avg;
}

long QXMBOT_SR04::MicrosecondsToCentimeter(long t_duration)
{
    long d = (t_duration * 100) / 5882;
    //d = (d == 0)?999:d;
    return d;
}


QXMBOT_cloudServo::QXMBOT_cloudServo(byte t_pinName, byte t_PinMode)
    :m_pinName(t_pinName),m_PinMode(t_PinMode)
{
    pinMode(m_pinName, m_PinMode);
    digitalWrite(m_pinName, LOW);
}

QXMBOT_cloudServo::~QXMBOT_cloudServo()
{
    digitalWrite(m_pinName, LOW);
    pinMode(m_pinName, INPUT);
}

void QXMBOT_cloudServo::cloudServoContrl(int t_angle, int t_defaultDelay)
{
    for(int i = 15; i > 0; i--)
    {
        int Angle = map(t_angle, 0,180, 500,2480);
        digitalWrite(m_pinName, HIGH);  //将舵机接口电平至高
        delayMicroseconds(Angle);       //延时脉宽值的微秒数
        digitalWrite(m_pinName, LOW);   //将舵机接口电平至低
        delayMicroseconds(20000 - t_angle);
    }

    delay(t_defaultDelay);
}


QXMBOT1_AHA_sensor::QXMBOT1_AHA_sensor(byte t_pinName, byte t_PinMode)
    :m_pinName(t_pinName),m_PinMode(t_PinMode)
{
    pinMode(m_pinName, m_PinMode);
}

QXMBOT1_AHA_sensor::~QXMBOT1_AHA_sensor()
{
}


QXMBOT1_Microphone::QXMBOT1_Microphone(byte t_pinName, byte t_PinMode)
    :m_pinName(t_pinName),m_PinMode(t_PinMode)
{
    pinMode(m_pinName, m_PinMode);
}

QXMBOT1_Microphone::~QXMBOT1_Microphone()
{
}


QXMBOT1_HIS_sensor::QXMBOT1_HIS_sensor(byte t_pinName, byte t_PinMode)
    :m_pinName(t_pinName),m_PinMode(t_PinMode),m_defaultDelay(0)
{
    pinMode(m_pinName, m_PinMode);
}

QXMBOT1_HIS_sensor::~QXMBOT1_HIS_sensor()
{
}

bool QXMBOT1_HIS_sensor::getHIS_Status(byte t_pinName)
{
    bool s = 0;
    m_defaultDelay = 0;
    if(!digitalRead(t_pinName))
    {
        m_defaultDelay = pulseIn(t_pinName, HIGH, 3333333L);
        if(m_defaultDelay >= 300000)
        {
            s = 1;
        }
    }
    return s;
}


void QXMBOT1_WIFI_ESP8266::ESP8266Init()
{
    byte i = 5;
    delay(5000);
    do
    {
        CIPMUX = "AT+CIPMUX=1\r\n";
        while(*CIPMUX != '\0')
        {
            Serial.write(*(CIPMUX++));
        }
        delay(2000);
    }while(--i);
    i = 5;
    do
    {
        CIPSERVER = "AT+CIPSERVER=1,8080\r\n";
        while(*CIPSERVER != '\0')
        {
            Serial.write(*(CIPSERVER++));
        }
        delay(2000);
    }while(--i);
}