#include<wiringPi.h>
#include<softPwm.h>

#define LED_PIN 4

#define LED_ON  1
#define LED_OFF 0

void init() {
    pinMode(LED_PIN, OUTPUT);
    softPwmCreate(LED_PIN, 0, 128);
}

void MotorControl(int light) {
    softPwmCreate(LED_PIN, light);
}

int main() {
    if(wiringPiSetupGpio() == -1)   return 1;

    init();

    int i;
    while(1) {
        for(i = 0; i < 64; i++) {
            MotorControl(i * 2);
            delay(5);
        }
        for(i; i >= 0; i--) {
            MotorControl(i * 2);
            delay(5);
        }
    }

    return 0;
}
