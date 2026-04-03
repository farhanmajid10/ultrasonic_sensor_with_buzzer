#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <poll.h>
#include "PWM.h"

#include "GPIO.h"

class Ultrasonic{
private:
    PWM& triggerPWM;//now PWM
    GPIO& echoPin;

    int echoFd;
    struct pollfd pfd;

    static constexpr int TIMEOUT_MS = 100;
    static constexpr float SPEED_OF_SOUND = 0.0343f;
    //here static means that all objects are sharing the same values for these.
    //constexpr is generated during compile time for all of these.
public:
    Ultrasonic(PWM& pwm, GPIO& echo);
    ~Ultrasonic();
    float measureDistance();
    static bool isValidDistance(float distance);
    //can call anywhere when the ultrasonic module is included. use like Ultrasonic::isValidDistance(vak);
};

#endif 