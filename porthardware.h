#ifndef porthardware_h
#define porthardware_h

#include <Arduino.h>


bool mux1[16];
bool mux2[16];
bool mux3[16];

bool get_bit(int val, int pos) {
	return 0x01 & (val >> pos);
}

void readinSB() {
	int tmp = 0x00;
	tmp |= int(digitalRead(SB01)) << 0;
	tmp |= int(digitalRead(SB02)) << 1;
	tmp |= int(digitalRead(SB03)) << 2;
	tmp |= int(digitalRead(SB04)) << 3;
	tmp |= int(digitalRead(SB05)) << 4;
	tmp |= int(digitalRead(SB06) << 5);
	tmp |= int(digitalRead(SB07) << 6);
	tmp |= int(digitalRead(SB08) << 7);
	tmp |= int(digitalRead(SB09) << 8);
	tmp |= int(digitalRead(SB10) << 9);
	tmp |= (digitalRead(SB11) << 10);
	tmp |= (digitalRead(SB12) << 11);
	tmp |= (digitalRead(SB13) << 12);
	tmp |= (digitalRead(SB14) << 13);
	tmp |= (digitalRead(SB15) << 14);
	tmp |= (digitalRead(SB16) << 15);
	stepbuttons = tmp;
}

void readinFB() {
	int tmp = 0x00;
	tmp |= int(digitalRead(FB01)) << 0;
	tmp |= int(digitalRead(FB02)) << 1;
	tmp |= int(digitalRead(FB03)) << 2;
	tmp |= int(digitalRead(FB04)) << 3;
	tmp |= int(digitalRead(FB05)) << 4;
	tmp |= int(digitalRead(FB06)) << 5;
	tmp |= int(digitalRead(FB07)) << 6;
	tmp |= int(digitalRead(FB08)) << 7;
	funcbuttons = tmp;
}

void readButtons() {
	readinSB();
	readinFB();
}

void update_mux(int index) {
	//update only relevant bit for MUX!
	switch (index) {
	case 0:
		mux1[0] = false;
		mux2[0] = false;
		mux3[0] = false;
		break;
	case 1:
		mux1[1] = get_bit(functionlamps, 5); //functionlamps[5];
		mux2[1] = get_bit(steplamps, 13);  //steplamps[13];
		mux3[1] = false;
		break;
	case 2:
		mux1[2] = get_bit(functionlamps, 6);
		mux2[2] = get_bit(indicatorlamps, 13);
		mux3[2] = false;
		break;
	case 3:
		mux1[3] = get_bit(functionlamps, 4);
		mux2[3] = get_bit(indicatorlamps, 14);
		mux3[3] = false;
		break;
	case 4:
		mux1[4] = get_bit(functionlamps, 3);
		mux2[4] = get_bit(steplamps, 14);
		mux3[4] = false;
		break;
	case 5:
		mux1[5] = get_bit(functionlamps, 2);
		mux2[5] = get_bit(indicatorlamps, 15);
		mux3[5] = false;
		break;
	case 6:
		mux1[6] = get_bit(functionlamps, 1);
		mux2[6] = get_bit(steplamps, 15);
		mux3[6] = get_bit(indicatorlamps, 12);
		break;
	case 7:
		mux1[7] = get_bit(functionlamps, 0);
		mux2[7] = get_bit(functionlamps, 7);
		mux3[7] = get_bit(steplamps, 12);
		break;
	case 8:
		mux1[8] = get_bit(indicatorlamps, 1);
		mux2[8] = get_bit(indicatorlamps, 5);
		mux3[8] = get_bit(indicatorlamps, 9);
		break;
	case 9:
		mux1[9] = get_bit(steplamps, 1);
		mux2[9] = get_bit(steplamps, 5);
		mux3[9] = get_bit(steplamps, 9);
		break;
	case 10:
		mux1[10] = get_bit(indicatorlamps, 0);
		mux2[10] = get_bit(indicatorlamps, 4);
		mux3[10] = get_bit(indicatorlamps, 8);
		break;
	case 11:
		mux1[11] = get_bit(steplamps, 0);
		mux2[11] = get_bit(steplamps, 4);
		mux3[11] = get_bit(steplamps, 8);
		break;
	case 12:
		mux1[12] = get_bit(indicatorlamps, 3);
		mux2[12] = get_bit(indicatorlamps, 7);
		mux3[12] = get_bit(indicatorlamps, 11);
		break;
	case 13:
		mux1[13] = get_bit(steplamps, 3);
		mux2[13] = get_bit(steplamps, 7);
		mux3[13] = get_bit(steplamps, 11);
		break;
	case 14:
		mux1[14] = get_bit(indicatorlamps, 2);
		mux2[14] = get_bit(indicatorlamps, 6);
		mux3[14] = get_bit(indicatorlamps, 10);
		break;
	case 15:
		mux1[15] = get_bit(steplamps, 2);
		mux2[15] = get_bit(steplamps, 6);
		mux3[15] = get_bit(steplamps, 10);

	}
}

void muxoutirq(int i) {
	digitalWrite(muxlatch, true);
	delayMicroseconds(10);
	digitalWrite(mux1A0, (i >> 0) & mux1[i]);
	digitalWrite(mux1A1, (i >> 1) & mux1[i]);
	digitalWrite(mux1A2, (i >> 2) & mux1[i]);
	digitalWrite(mux1A3, (i >> 3) & mux1[i]);

	digitalWrite(mux2A0, (i >> 0) & mux2[i]);
	digitalWrite(mux2A1, (i >> 1) & mux2[i]);
	digitalWrite(mux2A2, (i >> 2) & mux2[i]);
	digitalWrite(mux2A3, (i >> 3) & mux2[i]);

	digitalWrite(mux3A0, (i >> 0) & mux3[i]);
	digitalWrite(mux3A1, (i >> 1) & mux3[i]);
	digitalWrite(mux3A2, (i >> 2) & mux3[i]);
	digitalWrite(mux3A3, (i >> 3) & mux3[i]);
	delayMicroseconds(10);
	digitalWrite(muxlatch, false);

}

void update_trg() {
	digitalWrite(Tout01, get_bit(trigout, 0));
	digitalWrite(Tout02, get_bit(trigout, 1));
	digitalWrite(Tout03, get_bit(trigout, 2));
	digitalWrite(Tout04, get_bit(trigout, 3));
	digitalWrite(Tout05, get_bit(trigout, 4));
	digitalWrite(Tout06, get_bit(trigout, 5));
	digitalWrite(Tout07, get_bit(trigout, 6));
	digitalWrite(Tout08, get_bit(trigout, 7));
	digitalWrite(Tout09, get_bit(trigout, 8));
	digitalWrite(Tout10, get_bit(trigout, 9));
	digitalWrite(Tout11, get_bit(trigout, 10));
	digitalWrite(Tout12, get_bit(trigout, 11));
	digitalWrite(Tout13, get_bit(trigout, 12));
	digitalWrite(Tout14, get_bit(trigout, 13));
	digitalWrite(Tout15, get_bit(trigout, 14));
	digitalWrite(Tout16, get_bit(trigout, 15));
}

//set Hardware debouncing!
void setDebounce() {
	//todo: richtige masken finden!!

	int mask_1 = digitalPinToBitMask(FB01) |
	digitalPinToBitMask(FB02) |
	digitalPinToBitMask(FB03) |
	digitalPinToBitMask(FB04) |
	digitalPinToBitMask(FB05) |
	digitalPinToBitMask(FB06) |
	digitalPinToBitMask(FB07) |
	digitalPinToBitMask(FB08);
	// activate input filters for pin 24
	REG_PIOA_IFER = mask_1;
	// choose debounce filter as input filter for pin 24
	REG_PIOA_DIFSR = mask_1;
	// set clock divider for slow clock -> rejects pulses shorter than (DIV+1)*31µs and accepts pulses longer than 2*(DIV+1)*31µs
	REG_PIOA_SCDR = 10;

}

void portsetup() {
	//trigger out
	pinMode(Tout01, OUTPUT);
	pinMode(Tout02, OUTPUT);
	pinMode(Tout03, OUTPUT);
	pinMode(Tout04, OUTPUT);
	pinMode(Tout05, OUTPUT);
	pinMode(Tout06, OUTPUT);
	pinMode(Tout07, OUTPUT);
	pinMode(Tout08, OUTPUT);
	pinMode(Tout09, OUTPUT);
	pinMode(Tout10, OUTPUT);
	pinMode(Tout11, OUTPUT);
	pinMode(Tout12, OUTPUT);
	pinMode(Tout13, OUTPUT);
	pinMode(Tout14, OUTPUT);
	pinMode(Tout15, OUTPUT);
	pinMode(Tout16, OUTPUT);
	//clk out
	pinMode(clkout, OUTPUT);
	//mux out
	pinMode(mux1A0, OUTPUT);
	pinMode(mux1A1, OUTPUT);
	pinMode(mux1A2, OUTPUT);
	pinMode(mux1A3, OUTPUT);
	pinMode(mux2A0, OUTPUT);
	pinMode(mux2A1, OUTPUT);
	pinMode(mux2A2, OUTPUT);
	pinMode(mux2A3, OUTPUT);
	pinMode(mux3A0, OUTPUT);
	pinMode(mux3A1, OUTPUT);
	pinMode(mux3A2, OUTPUT);
	pinMode(mux3A3, OUTPUT);
	pinMode(muxlatch, OUTPUT);
	//Stepbuttons buttons
	pinMode(SB01, INPUT);
	pinMode(SB02, INPUT);
	pinMode(SB03, INPUT);
	pinMode(SB04, INPUT);
	pinMode(SB05, INPUT);
	pinMode(SB06, INPUT);
	pinMode(SB07, INPUT);
	pinMode(SB08, INPUT);
	pinMode(SB09, INPUT);
	pinMode(SB10, INPUT);
	pinMode(SB11, INPUT);
	pinMode(SB12, INPUT);
	pinMode(SB13, INPUT);
	pinMode(SB14, INPUT);
	pinMode(SB15, INPUT);
	pinMode(SB16, INPUT);
	//Function buttons
	pinMode(FB01, INPUT);
	pinMode(FB02, INPUT);
	pinMode(FB03, INPUT);
	pinMode(FB04, INPUT);
	pinMode(FB05, INPUT);
	pinMode(FB06, INPUT);
	pinMode(FB07, INPUT);
	pinMode(FB08, INPUT);
	//ablöschen
	digitalWrite(mux3A3, LOW);
	digitalWrite(mux3A2, LOW);
	digitalWrite(mux3A1, LOW);
	digitalWrite(mux3A0, LOW);
	digitalWrite(mux2A3, LOW);
	digitalWrite(mux2A2, LOW);
	digitalWrite(mux2A1, LOW);
	digitalWrite(mux2A0, LOW);
	digitalWrite(mux1A3, LOW);
	digitalWrite(mux1A2, LOW);
	digitalWrite(mux1A1, LOW);
	digitalWrite(mux1A0, LOW);
	//important! latch aktivieren!
	digitalWrite(muxlatch, true);

//set SAM3X Hardware debouncing parameters for inputs
//  setDebounce();
}

#endif
