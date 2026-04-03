#include <iostream>
#include <fstream>
#include <stdexcept>
#include "PWM.h"

PWM::PWM(int chip, int ch): chip(chip), channel(ch), currentPeriod(0){
    if(ch < 0 || ch > 1){
        throw std::invalid_argument("Invalid PWM channel");
    }
    basePath = "/sys/class/pwm/pwmchip" + std::to_string(chip) + "/pwm" + std::to_string(ch) + "/";
}

PWM::~PWM(){
    disable();
}

bool PWM::writeToFile(const std::string& filename, int value){
    std::ofstream file(basePath + filename);
    if(!file.is_open()){
        std::cerr << "Error:Cannot open" << basePath + filename << std::endl;
        return false;
    }
    file << value;
    if(file.fail()){
        std::cerr << "Error: Failed to write " << value << " to " << basePath + filename << std::endl;
        file.close();
        return false;
    }
    file.close();
    return true;
}

bool PWM::setPeriod(int ns){
    if (ns <= 0){
        std::cerr << "Error: Period can't be negative." << std::endl;
        return false;
    }
    if(writeToFile("period", ns)){
        currentPeriod = ns;
        return true;
    }
    return false;
} 

bool PWM::setDutyCycle(int ns){
    if(ns < 0){
        std::cerr << "Error: dutycycle cant be less than 0." << std::endl;
        return false;
    }

    if(currentPeriod > 0 && ns > currentPeriod){
            std::cerr << "Error: Duty Cycle can't be greater than the period." << std::endl;
            return false;
    }

    return writeToFile("duty_cycle", ns);
}

bool PWM::enable(){
    return writeToFile("enable", 1);
}

bool PWM::disable(){
    return writeToFile("enable", 0);
}