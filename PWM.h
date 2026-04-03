#ifndef PWM_H
#define PWM_H

#include <string>

class PWM{
private:
    int chip;
    int channel;
    std::string basePath;

    int currentPeriod;
    bool writeToFile(const std::string& filename, int value);

public:
    PWM(int chip, int ch);
    ~PWM();

    bool setPeriod(int ns);
    bool setDutyCycle(int ns);
    bool enable();
    bool disable();
};

#endif