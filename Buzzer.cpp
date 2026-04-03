#include "Buzzer.h"

Buzzer::Buzzer(PWM& pwm) : buzzerPWM(pwm){}

Buzzer::~Buzzer(){
    Off();
}

void Buzzer::On(int freqHz){
    int periodNs = 1000000000/freqHz;
    buzzerPWM.disable();
    buzzerPWM.setDutyCycle(0);
    buzzerPWM.setPeriod(periodNs);
    buzzerPWM.setDutyCycle(periodNs/2);
    buzzerPWM.enable();
}

void Buzzer::Off(){
    buzzerPWM.disable();
}