#include<wiringPi.h>
#include<stdio.h>
#include<stdlib.h>

const int FndSelectPin[6] = { 4, 17, 18, 27, 22, 23 };
const int FndPin[8] = { 6, 12, 13, 16, 19, 20, 26, 21 };
const int FndFont[6] = { 0b01110110, 0b01111001, 0b00111000, 0b00111000, 0b00111111, 0b00000000 };

void init() {
	int i;

	if(wiringPiSetupGpio() == -1) {
		printf("wiringPiSetupGpio() error\n");
		exit(-1);
	}
	
	for(i = 0; i < 6; i++) {
		pinMode(FndSelectPin[i], OUTPUT);
		digitalWrite(FndSelectPin[i], HIGH);
	}
	
	for(i = 0; i < 8; i++) {
		pinMode(FndPin[i], OUTPUT);
		digitalWrite(FndPin[i], LOW);
	}

}

void FndSelect(int position) {
	int i;

	for(i = 0; i < 6; i++) {
		if(i == position)	digitalWrite(FndSelectPin[i], LOW);
		else	digitalWrite(FndSelectPin[i], HIGH);
	}

}

void FndDisplay(int position, int num) {
	int i;
	int flag;
	int shift = 0x01;

	for(i = 0; i < 8; i++) {
		flag = (FndFont[num] & shift);
		digitalWrite(FndPin[i], flag);
		shift <<= 1;
	}

	FndSelect(position);
}

int main() {
	int pos, j = 0;
	int data[6] = { 0, 1, 2, 3, 4, 5 };
	unsigned long prev = millis(), current;
	
	init();

	while(1) {
		current = millis();
		for(pos = 0; pos < 6; pos++) {
			FndDisplay(5 - pos, data[(pos + j) % 6]);
			delay(1);
		}
		
		if(current - prev >= 500) {
			prev = current;
			j++;
		}
	}
}
