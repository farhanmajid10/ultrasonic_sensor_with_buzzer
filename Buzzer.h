#ifndef BUZZER_H
#define BUZZER_H

#include "PWM.h"

class Buzzer{
private:
    PWM& buzzerPWM;
public:
    Buzzer(PWM& pwm);
    ~Buzzer();

    void On(int freqHz);
    void Off();
};

#endif 