#ifndef GPIO_H
#define GPIO_H

#include <string>

class GPIO{
private:
    int pinNumber;
    std::string gpioPath;
    bool isExported;

    void exportGPIO();
    void unexportGPIO();
public:
//constructor:
    GPIO(int pin);
//destructor:
    ~GPIO();
//operations:
    //set_value
    bool setValue(int value);
    //set_direction
    bool setDirection(const std::string& direction);
    //get_value
    int getValue();
    //get_pin_number
    int getPin() const {return pinNumber;}
    void setEdge(const std::string& edge);
};

#endif
