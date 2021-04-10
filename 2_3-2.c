#include<wiringPi.h>
const LedRed[8] = { 4, 17, 18, 27, 22, 23, 24, 25 };
const Keypad[3] = { 6, 12, 13 };

int KeypadRead() {
	int i, keypadnum = -1;

	for(i = 0; i < 3; i++) {
		if(!digitalRead(Keypad[i])) {
			keypadnum = i;
			break;
		}
	}

	return keypadnum;
}

void LedControl(int num) {
	int i;
	for(i = 0; i < 8; i++) {
		if(i == num)	digitalWrite(LedRed[i], HIGH);
		else	digitalWrite(LedRed[i], LOW);
	}
}

int main() {
	int i, isKey3 = 0, keypadnum = -1;
	if(wiringPiSetupGpio() == -1)	return 1;

	for(i = 0; i < 8; i++) {
		pinMode(LedRed[i], OUTPUT);
		digitalWrite(LedRed[i], LOW);
	}

	for(i = 0; i < 3; i++) {
		pinMode(Keypad[i], INPUT);
	}

	while(1) {
		keypadnum = KeypadRead();
		if(keypadnum == 0) {
			while(1) {
				for(i = 0; i < 8; i++) {
					LedControl(i);
					delay(500);
					if(KeypadRead() == 2) {
						isKey3 = 1;
						break;
					}
				}
				digitalWrite(LedRed[i-1], LOW);
				if(isKey3) break;
			}
		} else if(keypadnum == 1) {
			while(1) {
				for(i = 7; i >= 0; i--) {
					LedControl(i);
					delay(500);
					if(KeypadRead() == 2) {
						isKey3 = 1;
						break;
					}
				}
				digitalWrite(LedRed[i+1], LOW);
				if(isKey3) break;
			}
		} else if(keypadnum == 2 || isKey3) 
			for(i = 0; i < 8; i++)	digitalWrite(LedRed[i], LOW);

		isKey3 = 0;
	}	


	return 0;
}
