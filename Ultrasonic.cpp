#include "Ultrasonic.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <stdexcept>

#include <fcntl.h>
#include <unistd.h>

using namespace std::chrono;

Ultrasonic::Ultrasonic(PWM& pwm,GPIO& echo): triggerPWM(pwm), echoPin(echo){
    triggerPWM.setPeriod(100000);
    triggerPWM.setDutyCycle(10000);

    echoPin.setDirection("in");
    echoPin.setEdge("both");

    echoFd = open("/sys/class/gpio/gpio529/value", O_RDONLY);
    if(echoFd < 0){
        std::cerr << "[ultrasonic sennsor] failed to set gpio." << std::endl;
        throw std::runtime_error("cannot open echo GPIO");
    }

    pfd.fd = echoFd;
    pfd.events = POLLPRI | POLLERR;

    char dummy;
    read(echoFd,&dummy, 1);
}

Ultrasonic::~Ultrasonic(){
    close(echoFd);
}

bool Ultrasonic::isValidDistance(float distance){
    return ((distance >= 2.0f) && (distance <= 400.0f));
}

float Ultrasonic::measureDistance(){
    char dummy;
    
    triggerPWM.enable();
    std::this_thread::sleep_for(microseconds(20));
    triggerPWM.disable();

    int ret = poll(&pfd,1,TIMEOUT_MS);
    if(ret <= 0){
        std::cerr << "[ultrasonic sensor] timeout waiting for echo High" << std::endl;
        return -1.0f;
    }

    lseek(echoFd, 0, SEEK_SET);
    read(echoFd, &dummy, 1);
    auto startTime = steady_clock::now();

    ret = poll(&pfd, 1, TIMEOUT_MS);
    if(ret <= 0){
        std::cerr << "[ultrasonic sensor] timeout waiting for echo Low" << std::endl;
        return -1.0f;
    }

    lseek(echoFd, 0, SEEK_SET);
    read(echoFd, &dummy, 1);
    auto endTime = steady_clock::now();

    auto duration = duration_cast<microseconds> (endTime - startTime).count();
    float distance = (static_cast<float> (duration) * SPEED_OF_SOUND)/2.0f;

    return distance;
}