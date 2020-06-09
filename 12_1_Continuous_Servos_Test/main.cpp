#include "mbed.h"

#define CENTER_BASE 2485

PwmOut servo(D11);

void servo_control(int speed){
    //speed = 0;
    if (speed > 200)       speed = 200;
    else if (speed < -200) speed = -200;

    servo = (CENTER_BASE + speed)/20000.0f;
}

int main() {
    servo.period(.02);

    while(1) {
        servo_control(100);
        wait(2);
        servo_control(-100);
        wait(2);
    }
}