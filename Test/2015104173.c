#include<stdio.h>
#include<stdlib.h>
#include<wiringPi.h>

const int FndSelectPin[6] = { 4, 17, 18, 27, 22, 23 };
const int FndPin[8] = { 6, 12, 13, 16, 19, 20, 26, 21 };
const int FndFont[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67 };

const int Keypad[3] = { 11, 9, 10 };
static int nowKeypad = -1;

void init() {
	if(wiringPiSetupGpio() == -1) {
		printf("Error");
		exit(-1);
	}

	int i;
	
	for(i = 0; i < 6; i++) {
		pinMode(FndSelectPin[i], OUTPUT);
		pinMode(FndPin[i], OUTPUT);
		digitalWrite(FndSelectPin[i], HIGH);
		digitalWrite(FndPin[i], LOW);
	}
	
	for(i; i < 8; i++) {
		pinMode(FndPin[i], OUTPUT);
		digitalWrite(FndPin[i], LOW);
	}

    for(i = 0; i < 3; i++) 
        pinMode(Keypad[i], INPUT);
    
}

void FndSelect(int position) {
	int i;
	for(i = 0; i < 6; i++) {
		if(i == position)	digitalWrite(FndSelectPin[i], LOW);
		else	digitalWrite(FndSelectPin[i], HIGH);
	}
}

void FndDisplay(int position, int number) {
	int i;
	int flag = 0;
	int shift = 0x01;

	if(position == 2) {
		for(i = 0; i < 8; i++) {
			flag = ((FndFont[number] + 128) & shift);
			digitalWrite(FndPin[i], flag);
			shift <<= 1;
		};
	} else {
		for(i = 0; i < 8; i++) {
			flag = (FndFont[number] & shift);
			digitalWrite(FndPin[i], flag);
			shift <<= 1;
		};
	}

	FndSelect(position);
}

void KeypadRead() {
    int i;

    for(i = 0; i < 3; i++) {
        if(!digitalRead(Keypad[i])) {
            nowKeypad = i;
            break;
        }
    }
}

int main() {
    int pos;
	int second[6] = { 0, 0, 0, 0, 0, 0 };

    init();

    int isWorking = -1;

    while(1) {
        if(nowKeypad == 0) {
            isWorking = 1;

            for(pos = 0; pos < 6; pos++) {
                FndDisplay(pos, second[pos]);
                delay(1);
            }
            delay(4);
            
            second[0] += 1;
            for(pos = 0; pos < 5; pos++) {
                if(second[pos] == 10) {
                    second[pos + 1] += 1;
                    second[pos] = 0;
                }
            }

            KeypadRead();
        } else if(nowKeypad == 1) {
            isWorking = 0;

            for(pos = 0; pos < 6; pos++) {
                FndDisplay(pos, second[pos]);
                delay(1);
            }

            KeypadRead();
        } else if(nowKeypad == 2) {
            for(pos = 0; pos < 6; pos++) {
                second[pos] = 0;
                FndDisplay(pos, second[pos]);
                delay(1);
            }
            if(isWorking == 1)  nowKeypad = 0;
            else if(isWorking == 0)    nowKeypad = 1;

        }
    }
}