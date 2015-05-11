//lightsequence V0.0
//code by hpl logsoft@gmail.com 

//imports

#include <DueTimer.h>
#include <UARTClass.h>
#include <variant.h>
#include <wiring.h>
#include <wiring_constants.h>

#include "debug.h"
#include "globals.h"
#include "menu.h"
#include "porthardware.h"
#include "sequence.h"

int debugging_enabled = 1;

long sam_millis = 0;
volatile int posi = 0;
volatile static long seqpos = 0;
volatile static int Sequence_freq = 25;
bool send_debug = false;
long vorher = 0;
void alive1();

// clock instance
// Clock theClock(patlen);

//track instances
//Track tracks[16];
//Track tracks[16] = { Track(0), Track(1), Track(2), Track(3), Track(4), Track(
//		5), Track(6), Track(7), Track(8), Track(9), Track(10), Track(11), Track(
//		12), Track(13), Track(14), Track(15) };

//#include <vector>
//std::vector<Track> tracksvec(16);
//Menu menu = Menu(tracksvec);

Menu menu = Menu();
int pattern2;
int pattern3;

void test(int page, int buttons){

	Serial.print("callback hey oida!!: ");
	Serial.println(page);
	Serial.print(" - ");
	Serial.println(buttons,BIN);
	Serial.print(" - ");
	Serial.println(pattern,BIN);

	switch (page) {
	case MenuEnums::Main:
		//pattern = buttons;
		break;
	case MenuEnums::Pattern:
		pattern2 = (pattern2 ^ buttons);
		break;
	case MenuEnums::Sequence:
		pattern = (pattern ^ buttons);
		break;
	default:
		break;

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
	Timer0.attachInterrupt(timer0_handler).setFrequency(1).start(); //1Hz Alive and debug msg!
	Timer1.attachInterrupt(timer1_handler).setFrequency(1000).start(); //1kHz Buttons
	Timer2.attachInterrupt(timer2_handler).setFrequency(1000).start(); //2kHz Led muxes
	//Timer3.attachInterrupt(timer3_handler).setFrequency(Sequence_freq).start(); //sequencing alle 125ms = 120BPM/16tel
	Serial.println("timer OK");

	//hello
	Serial.println("Init OK");

//	for (uint i = 0; i < tracksvec.size(); i++) {
//		tracksvec[i].init(i); //init trk number
//	}

	menu.onUpdate(test);

}



void loop() {
	sam_millis = millis();
//	long now = micros();

	//tests


	menu.do_your_things(funcbuttons, stepbuttons);
//	steplamps = stepbuttons;
//	indicatorlamps = stepbuttons;
	stepleds = pattern; //menu.get_indicatorleds();
	indicatorleds = pattern2 ;//menu.get_stepleds();
	functionleds = menu.get_page();

//send debug messages
	if (send_debug)
		alive1();

}

//timer 0 handles the input handling @1Hz
void timer0_handler() {
	//send debug message out
	send_debug = debugging_enabled ? 1 : 0;
	timercounters[0] += 1;
}

//timer 1 handles button update @1kHZ
void timer1_handler() {
	timercounters[1] += 1;
	readButtons();
}

//timer 2 handles the led muxer update @2khZ
volatile static long muxpos;
void timer2_handler() {
//	showLeds();
	timercounters[2] += 1;
	update_mux(muxpos);
	muxoutirq(muxpos);
	update_trg();
	muxpos += 1;
	if (muxpos > 15)
		muxpos = 0;
}

//timer 3 handles the clock
void timer3_handler() {
	timercounters[3] += 1;
	seqpos += 1;
	if (seqpos > 15) {
		seqpos = 0;
	}
	//trigger setzen
}

void alive1() {
	send_debug = false;
	Serial.print("Sequence freq Hz: ");
	Serial.println(Sequence_freq);

	Serial.print(" FB: ");
	Serial.print(funcbuttons, BIN);

//	for (int i = 0; i < 8; i++) {
//		Serial.print(funcbuttons[i]);
//	}
	Serial.print(" SB: ");
	Serial.print(stepbuttons, BIN);
//	for (int i = 0; i < 16; i++) {
//		Serial.print(stepbuttons[i]);
//	}
	Serial.print(" SL: ");
	Serial.print(stepleds, BIN);
//	for (int i = 0; i < 16; i++) {
//		Serial.print(steplamps[i]);
//	}

	Serial.print(" Menu: ");
	Serial.print(menu.get_page());

	Serial.print(" DEBUG: ");
	Serial.print(debug_int);

	Serial.println();
}
