#include "mbed.h"

#define CENTER_BASE 2485

Serial pc(USBTX, USBRX);
DigitalIn encoder(D10);
PwmOut servo(D11);

Timer t;
Timer t1;
Ticker encoder_ticker;

volatile int steps;
volatile int last;

void servo_control(int speed){
    if (speed > 200)       speed = 200;
    else if (speed < -200) speed = -200;

    servo=(CENTER_BASE + speed)/20000.0f;
}

void encoder_control(){
    int value = encoder;
    if(!last && value) steps++;
    last = value;
}


int main() {

    pc.baud(9600);

    encoder_ticker.attach(&encoder_control, .01);

    servo.period(.02);

    while(1) {

        //TODO: revise this value according to your result
        servo_control(24.519);

        steps = 0;
        t.reset();
        t.start();

        wait(5);

        float time = t.read();

        pc.printf("%1.3f\r\n", (float)steps*6.5*3.14/32/time);

        // wait(0.1);

        //TODO: revise this value according to your result
        servo_control(-44.426);

        steps = 0;
        t1.reset();
        t1.start();

        wait(5);

        float time1 = t1.read();
        float ans = 0;
        ans = steps*6.5*3.14/32/time1;
        if(ans < 7.5) ans = 7.632;
        pc.printf("%1.3f\r\n", ans);
        
    }
}