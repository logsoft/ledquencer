//lightsequence V0.0
//code by hpl logsoft@gmail.com 

//imports
#include <DueTimer.h>
#include "config.h"
#include "globals.h"

//#define DEBUG

//#define USEBUS
#ifdef USEBUS

void ledtests_bus() {
	// Some example procedures showing how to display to the pixels:
	colorWipe(strip.Color(255, 0, 0), 50);// Red
	colorWipe(strip.Color(0, 255, 0), 50);// Green
	colorWipe(strip.Color(0, 0, 255), 50);// Blue
	// Send a theater pixel chase in...
	theaterChase(strip.Color(127, 127, 127), 50);// White
	theaterChase(strip.Color(127, 0, 0), 50);// Red
	theaterChase(strip.Color( 0, 0, 127), 50);// Blue

	rainbow(20);
	rainbowCycle(20);
	theaterChaseRainbow(50);

}
#endif

//#include "ledtest.h"

/*
 *  #include "funcs.h"
 * #include "clock.h"
 * #include "track.h"
 */

//debug switch
//#define DEBUG
int patlen = 16;

/*
 //clock instance
 Clock theClock(patlen);

 //track instances
 Track tracks[8] = { Track(0), Track(1), Track(2), Track(3), Track(4), Track(5), Track(6), Track(7)};
 */

/*
 * Timer 0 = ?Hz test and alive signal
 */
long sam_millis = 0;
volatile static long tmrcnt[5];
volatile static bool lifeled = 0; // todo read output?

volatile bool indicatorlamps[16];
volatile bool steplamps[16];
volatile bool functionlamps[8];
volatile bool stepbuttons[16];
volatile bool trigout[16];
volatile bool funcbuttons[8];
volatile int posi = 0;

volatile bool mux1[16];
volatile bool mux2[16];
volatile bool mux3[16];

volatile static int seqon = 0;
volatile static long seqpos = 0;
volatile static int frequ = 0;

void update() {
	mux1[0] = false;
	mux1[1] = functionlamps[5];
	mux1[2] = functionlamps[6];
	mux1[3] = functionlamps[4];
	mux1[4] = functionlamps[3];
	mux1[5] = functionlamps[2];
	mux1[6] = functionlamps[1];
	mux1[7] = functionlamps[0];
	mux1[8] = indicatorlamps[1];
	mux1[9] = steplamps[1];
	mux1[10] = indicatorlamps[0];
	mux1[11] = steplamps[0];
	mux1[12] = indicatorlamps[3];
	mux1[13] = steplamps[3];
	mux1[14] = indicatorlamps[2];
	mux1[15] = steplamps[2];

	mux2[0] = false;
	mux2[1] = steplamps[13];
	mux2[2] = indicatorlamps[13];
	mux2[3] = indicatorlamps[14];
	mux2[4] = steplamps[14];
	mux2[5] = indicatorlamps[15];
	mux2[6] = steplamps[15];
	mux2[7] = functionlamps[7];
	mux2[8] = indicatorlamps[5];
	mux2[9] = steplamps[5];
	mux2[10] = indicatorlamps[4];
	mux2[11] = steplamps[4];
	mux2[12] = indicatorlamps[7];
	mux2[13] = steplamps[7];
	mux2[14] = indicatorlamps[6];
	mux2[15] = steplamps[6];

	mux3[0] = false;
	mux3[1] = false;
	mux3[2] = false;
	mux3[3] = false;
	mux3[4] = false;
	mux3[5] = false;
	mux3[6] = indicatorlamps[12];
	mux3[7] = steplamps[12];
	mux3[8] = indicatorlamps[9];
	mux3[9] = steplamps[9];
	mux3[10] = indicatorlamps[8];
	mux3[11] = steplamps[8];
	mux3[12] = indicatorlamps[11];
	mux3[13] = steplamps[11];
	mux3[14] = indicatorlamps[10];
	mux3[15] = steplamps[10];
}

void trgUpdate(){
	digitalWrite(Tout01, trigout[0]);
	digitalWrite(Tout02, trigout[1]);
	digitalWrite(Tout03, trigout[2]);
	digitalWrite(Tout04, trigout[3]);
	digitalWrite(Tout05, trigout[4]);
	digitalWrite(Tout06, trigout[5]);
	digitalWrite(Tout07, trigout[6]);
	digitalWrite(Tout08, trigout[7]);
	digitalWrite(Tout09, trigout[8]);
	digitalWrite(Tout10, trigout[9]);
	digitalWrite(Tout11, trigout[10]);
	digitalWrite(Tout12, trigout[11]);
	digitalWrite(Tout13, trigout[12]);
	digitalWrite(Tout14, trigout[13]);
	digitalWrite(Tout15, trigout[14]);
	digitalWrite(Tout16, trigout[15]);
}

void readinSB() {

	stepbuttons[0] = digitalRead(SB01);
	stepbuttons[1] = digitalRead(SB02);
	stepbuttons[2] = digitalRead(SB03);
	stepbuttons[3] = digitalRead(SB04);
	stepbuttons[4] = digitalRead(SB05);
	stepbuttons[5] = digitalRead(SB06);
	stepbuttons[6] = digitalRead(SB07);
	stepbuttons[7] = digitalRead(SB08);
	stepbuttons[8] = digitalRead(SB09);
	stepbuttons[9] = digitalRead(SB10);
	stepbuttons[10] = digitalRead(SB11);
	stepbuttons[11] = digitalRead(SB12);
	stepbuttons[12] = digitalRead(SB13);
	stepbuttons[13] = digitalRead(SB14);
	stepbuttons[14] = digitalRead(SB15);
	stepbuttons[15] = digitalRead(SB16);

}

void readinFB() {
	funcbuttons[0] = digitalRead(FB01);
	funcbuttons[1] = digitalRead(FB02);
	funcbuttons[2] = digitalRead(FB03);
	funcbuttons[3] = digitalRead(FB04);
	funcbuttons[4] = digitalRead(FB05);
	funcbuttons[5] = digitalRead(FB06);
	funcbuttons[6] = digitalRead(FB07);
	funcbuttons[7] = digitalRead(FB08);
}

void readButtons() {
	readinSB();
	readinFB();
}

void muxoutirq(int i) {
	digitalWrite(muxlatch, true);
	delayMicroseconds(20);
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
	delayMicroseconds(20);
	digitalWrite(muxlatch, false);

}

void alive1() {
//	lifeled = !lifeled;
//	digitalWrite(13, lifeled);
	Serial.print("alive@");
	Serial.println(sam_millis);
	Serial.print("irq0@ ");
	Serial.print(tmrcnt[0]);
	Serial.print(" irq1@ ");
	Serial.print(tmrcnt[1]);
	Serial.print(" irq2@ ");
	Serial.print(tmrcnt[2]);
	Serial.print(" irq3@ ");
	Serial.print(tmrcnt[3]);

	Serial.print(" FB: ");
	for (int i = 0; i < 8; i++) {
		Serial.print(funcbuttons[i]);
	}
	Serial.print(" SB: ");
	for (int i = 0; i < 16; i++) {
		Serial.print(stepbuttons[i]);
	}
	Serial.print(" SL: ");
	for (int i = 0; i < 16; i++) {
		Serial.print(steplamps[i]);
	}
	Serial.println();
}

void timer0_handler() {
#ifdef DEBUG
	alive1();
#endif
	if (funcbuttons[0] == 1) {
		seqon = 1;
	}

	if (funcbuttons[1] == 1) {
		seqon = 0;
	}

	if (funcbuttons[2] == 1) {
		frequ = frequ - 10;
		Timer3.setFrequency(10);
		Timer3.start();
	}

	if (funcbuttons[3] == 1) {
		frequ = frequ + 10;
		Timer3.setFrequency(50);
		Timer3.start();
	}
	tmrcnt[0] += 1;
}

//timer 1 handles the led muxer update
//frequency ~2khZ ??
void timer1_handler() {
	readButtons();

	update();

	trgUpdate();

	//getMuxState(mux1*,mux2*, mux3*);
	tmrcnt[1] += 1;
}

volatile static long muxpos;
void timer2_handler() {
//	showLeds();
	tmrcnt[2] += 1;
	muxoutirq(muxpos);
	muxpos += 1;
	if (muxpos > 15)
		muxpos = 0;

}



//timer 4 handles
void timer3_handler() {
	tmrcnt[3] += 1;

	if (seqon) {
		for (int i = 0; i < 16; i++) {
			steplamps[i] = (i == seqpos);
			indicatorlamps[15 - i] = (i == seqpos);
		}
		seqpos += 1;
	}
	if (seqpos > 15) {
		seqpos = 0;
	}

	//trigger setzen
	for (int i = 0; i < 16; i++) {
		indicatorlamps[15 - i] = (i == seqpos);
		trigout[i] = indicatorlamps[i];
	}

}

void setup() {
	// put your setup code here, to run once:
	long baud = 57600;
	Serial.begin(baud);
	Serial.println("Serial OK");
	//ports setup
	portsetup();

	//pinMode(13, OUTPUT);
	Serial.println("ports OK");

	//system timer!
	Timer0.attachInterrupt(timer0_handler).setFrequency(1).start(); //Hz Alive!
	Timer1.attachInterrupt(timer1_handler).setFrequency(1000).start(); //2kHz
	Timer2.attachInterrupt(timer2_handler).setFrequency(2000).start(); //2kHz
	Timer3.attachInterrupt(timer3_handler).setFrequency(25).start(); //alle 125ms = 120BPM/16tel
	Serial.println("timer OK");

	//hello
	Serial.println("Init OK");

}

/*
 void testfbl() {

 for ( int i = 0 ; i < 15; i++) {
 indicatorlamps[i] = stepbuttons[i];
 steplamps[i] = stepbuttons[i];
 }

 //range 8-12
 //
 for ( int i = 0 ; i < 7; i++) {
 functionlamps[i] = funcbuttons[i];
 }
 }
 */

long vorher = 0;
void loop() {
	sam_millis = millis();
	long now = micros();

	//ledtests_bus();

	for (int i = 0; i < 16; i++) {

		if (!seqon) {
			steplamps[i] = stepbuttons[i];
			indicatorlamps[i] = stepbuttons[i];
		}
		/*
		 steplamps[i] = true;
		 functionlamps[15-i] = true;
		 delay(100);
		 steplamps[i] = false;
		 functionlamps[15-i] = false;
		 delay(100);
		 */

	}

	for (int i = 0; i < 8; i++) {
		functionlamps[i] = funcbuttons[i];
		/*
		 functionlamps[i] = true;
		 delay(100);
		 functionlamps[i] = false;
		 delay(100);
		 */
	}

}

