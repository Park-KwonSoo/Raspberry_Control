#include<wiringPi.h>
#include<stdbool.h>

const int LedRed[8] = { 4, 17, 18, 27, 22, 23, 24, 25 };
const int Keypad[8] = { 16, 13, 12, 6, 21, 26, 20, 19 };
bool output[8] = { false, false, false, false, false, false, false, false };

int KeypadRead() {
	int i, keypadnum = -1;

	for(i = 0; i < 8; i++) {
		if(!digitalRead(Keypad[i])) {
			keypadnum = i;
			break;
		}
	}
	
	return keypadnum;
}

int LedControl(int num) {
	if(output[num]) {
		delay(5);
		digitalWrite(LedRed[num], LOW);
	}
	else {
		delay(5);	
		digitalWrite(LedRed[num], HIGH);
	}

	output[num] = !output[num];
}

int main() {
	int i, keypadnum = -1;

	if(wiringPiSetupGpio() == -1) return 1;

	for(i = 0; i < 8; i++) {
		pinMode(Keypad[i], INPUT);
		pinMode(LedRed[i], OUTPUT);
		digitalWrite(LedRed[i], LOW);
	}

	while(1) {
		keypadnum = KeypadRead();
		LedControl(keypadnum);
	}

	return 0;
}
