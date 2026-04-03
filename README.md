Ultrasonic Distance Sensor with Buzzer Alarm
A BeagleBone Black project written in C++ that measures distance with an HC-SR04 ultrasonic sensor and sounds a passive buzzer when an object gets within 15cm.

Hardware

BeagleBone Black
HC-SR04 Ultrasonic Sensor
Passive Buzzer
2N2222 NPN Transistor
1kΩ resistor (transistor base)
1kΩ and 2kΩ resistors (voltage divider for echo pin)


BeagleBone Setup:
Running Debian 12 on kernel 6.12.66-bone44.
The ultrasonic trigger uses P9_14 (EHRPWM1, pwmchip0) and the buzzer uses P8_13 (EHRPWM2, pwmchip1). They must be on separate EHRPWM modules because channels on the same module share a hardware timer and cannot run at different frequencies.
Add these overlays to /boot/uEnv.txt and reboot:
uboot_overlay_addr4=BB-EHRPWM1-P9_14-P9_16.dtbo
uboot_overlay_addr5=BB-EHRPWM2-P8_13-P8_19.dtbo
The echo pin on the HC-SR04 outputs 5V but the BBB GPIO is 3.3V only. A voltage divider using 1kΩ and 2kΩ resistors brings it down to a safe level before connecting to P9_23.
The buzzer needs more current than the BBB PWM pin can supply, so a 2N2222 transistor is used as a switch with the base driven through a 1kΩ resistor from P8_13.

Building and Running:
bashmake
sudo ./ultrasonic_with_buzzer
