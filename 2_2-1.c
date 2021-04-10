#include<wiringPi.h>

#define	LED_ON	1
#define	LED_OFF	0

const LED[16] = {
	4, 17, 18, 27, 22, 23, 24, 25,
	6, 12, 13, 16, 19, 20, 26, 21
};

void LedControl(int pinnum) {
	int i;
	for(i = 0; i < 16; i++) {
		if(i == pinnum)	digitalWrite(LED[i], LED_ON);
		else	digitalWrite(LED[i], LED_OFF);
	}
}

int main() {
	if(wiringPiSetupGpio() == -1)	return 1;

	int i;
	for(i = 0; i < 16; i++) {
		pinMode(LED[i], OUTPUT);
		digitalWrite(LED[i], LED_OFF);
	}

	while(1) {
		for(i = 0; i < 16; i += 2) {
			LedControl(i);
			delay(500);
		}	
		for(i = 1; i < 16; i += 2) {
			LedControl(i);
			delay(500);
		}	
	}

	return 0;
}

