#include<wiringPi.h>
#include<softPwm.h>

#define MOTOR_MT_N_PIN 17
#define MOTOR_MT_P_PIN 4

#define LEFT_ROTATE 1
#define RIGHT_ROTATE 2

void init() {
    pinMode(MOTOR_MT_N_PIN, OUTPUT);
    pinMode(MOTOR_MT_P_PIN, OUTPUT);

    softPwmCreate(MOTOR_MT_N_PIN, 0, 128);
    softPwmCreate(MOTOR_MT_P_PIN, 0, 128);
}

void MotorStop() {
    softPwmWrite(MOTOR_MT_N_PIN, 0);
    softPwmWrite(MOTOR_MT_P_PIN, 0);
}

void MotorControl(int rotate, int speed) {
    if(rotate == LEFT_ROTATE) {
        digitalWrite(MOTOR_MT_P_PIN, LOW);
        softPwmWrite(MOTOR_MT_N_PIN, speed);
    } else if(rotate == RIGHT_ROTATE) {
        digitalWrite(MOTOR_MT_N_PIN, LOW);
        softPwmWrite(MOTOR_MT_P_PIN, speed);
    }
}

int main() {
    if(wiringPiSetupGpio() == -1)   return 1;

    init();

    int i;
    while(1) {
        for(i = 1; i <= 4; i++) {
            MotorControl(LEFT_ROTATE, 32 * j);
            delay(2000);
            MotorStop();
            delay(2000);
        }
        for(i = 4; i >= 1; i--) {
            MotorControl(RIGHT_ROTATE, 32 * j);
            delay(2000);
            MotorStop();
            delay(2000);
        }
    }

    return 0;
}
