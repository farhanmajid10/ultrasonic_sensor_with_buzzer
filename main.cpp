#include <iostream>
#include <chrono>
#include <thread>
#include <csignal>
#include <iomanip>

#include "Ultrasonic.h"
#include "GPIO.h"
#include "PWM.h"
#include "Buzzer.h"

using namespace std;
using namespace std::chrono;

volatile bool running = true;

void signalHandler(int signum){
    cout << "Exiting." << endl;
    running = false;
}

int main(){
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    cout << "Sensor Test" << endl;

    try{
        PWM triggerPWM(0,0);
        PWM buzzerPWM(1,1);
        GPIO echoGPIO(529);

        Ultrasonic sensor(triggerPWM, echoGPIO);
        Buzzer buzzer(buzzerPWM);

        int count = 0;
        while(running){
            float distance = sensor.measureDistance();
            count++;
            if(Ultrasonic::isValidDistance(distance)){
                cout << "[" << count << "] distance: " << fixed << setprecision(2) << distance << "cm." << endl;
                if(distance < 15.0f){
                    buzzer.On(1000);
                }else{
                    buzzer.Off();
                }
            }else{
                buzzer.Off();
                cout << "[" << count << "] Distance is out of range." << endl;
            }
            this_thread::sleep_for(seconds(2));
        }
        cout << "Total readings: " << count << endl;
    }catch(const exception&  e){
        cerr << "Error: " << e.what() << endl;
        return -1;
    }
    return 0;
}