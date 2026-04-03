#include "GPIO.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

GPIO::GPIO(int pin): pinNumber(pin), isExported(false){
    gpioPath = "/sys/class/gpio/gpio" + std::to_string(pinNumber);
    exportGPIO();
}

GPIO::~GPIO(){
    unexportGPIO();
}

void GPIO:: exportGPIO(){
    std::ofstream exportFile("/sys/class/gpio/export");
    if(exportFile.is_open()){
        exportFile << pinNumber;
        exportFile.close();
        //always forget to put this here. Kernel needs time to create the gpio files.
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        isExported = true;
        std::cout << "[GPIO] Exported GPIO " << pinNumber << std::endl;
    }else{
        std::cerr << "[GPIO] Failed to export GPIO " << pinNumber << std::endl;
    }
}

void GPIO:: unexportGPIO(){
    if(isExported){
        std::ofstream unexportFile("/sys/class/gpio/unexport");
        if(unexportFile.is_open()){
            unexportFile << pinNumber;
            unexportFile.close();
            isExported = false;
            std::cout << "Unexported GPIO " << pinNumber << std::endl;
        }else{
            std::cerr << "Failed to unexport GPIO " << pinNumber << std::endl;
        }
    }
}

bool GPIO::setValue(int value){
    std::ofstream valueFile(gpioPath + "/value");
    if(valueFile.is_open()){
        valueFile << value;
        valueFile.close();
        //std::cout << "Value set for GPIO " << pinNumber << " to " << value << std::endl; 
        return true;
    }else{
        //std::cerr << "Failed to set value for GPIO " << pinNumber << " to " << value << std::endl;
        return false;
    }
}

bool GPIO::setDirection(const std::string& direction){
    std::ofstream directionFile(gpioPath + "/direction");
    if(directionFile.is_open()){
        directionFile << direction;
        directionFile.close();
        //sleep not needed since it is only one write.
        //std::this_thread:sleep_for(std::chrono::milliseconds(100));
        std::cout << "Direction set to " << direction << std::endl;
        return true;
    }else{
        std::cerr << "Failed to set Direction to " << direction << std::endl;
        return false;
    }
}

int GPIO::getValue(){
    //int result = 0;
    char value;
    std::ifstream valueFile(gpioPath + "/value");
    if(valueFile.is_open()){
        valueFile >> value;
        valueFile.close();
        //std::cout << "Value received is " << value << std::endl;
        return (value == '1')? 1:0;
    }else{
        //std::cout << "Failed to read value from GPIO " << pinNumber << std::endl;
        return -1;
    }
}

void GPIO::setEdge(const std::string& edge){
    std::ofstream edgeFile(gpioPath + "/edge");
    if(!edgeFile.is_open()){
        std::cout << "[GPIO] The edge for gpio" << std::to_string(pinNumber) << " failed to set." << std::endl;
        return;
    }
    edgeFile << edge;
    edgeFile.close();
}