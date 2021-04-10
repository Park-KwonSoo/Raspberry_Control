#include<wiringPi.h>
#include<softPwm.h>

const int LED[8] = { 4, 17, 18, 27, 22, 23, 24, 25 };
#define LED_PIN	4

void init() {
    int i;
    for(i = 1; i < 8; i++) {
	pinMode(LED[i], OUTPUT);
	digitalWrite(LED[i], LOW);
    }
    pinMode(LED_PIN, OUTPUT);
    softPwmCreate(LED_PIN, 0, 128);
}

void MotorControl(int light) {
    softPwmWrite(LED_PIN, light);
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
