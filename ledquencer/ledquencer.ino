//lightsequence V0.0
//code by hpl logsoft@gmail.com 


//imports
#include "config.h"
#include "globals.h"
#include "funcs.h"
#include <DueTimer.h>
#include "clock.h"
#include "track.h"
#include "FastLED.h"
//#include <Wire.h>
//#include "Adafruit_MPR121.h"

//debug switch
#define DEBUG




int patlen = 16;

//clock instance
Clock theClock(patlen);

//track instances
Track tracks[8] = { Track(0), Track(1), Track(2), Track(3), Track(4), Track(5), Track(6), Track(7)};

//timer 1 handles the led muxer update
//frequency ~2khZ ??
void timer0_handler() {
  setLeds();
}

//timer 4 handles the Main Tick
void timer3_handler() {
  theClock.clk_doTick();
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Serial OK");
  //ports setup
  portsetup();
  Serial.println("ports OK");




  //system timer!
  Timer0.attachInterrupt(timer0_handler).setFrequency(2000).start(); //2kHz
  Timer3.attachInterrupt(timer3_handler).start(125); //alle 125ms = 120BPM/16tel
  Serial.println("timer OK");

  //hello
  Serial.println("Init OK");

}


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


void loop() {

  long now = micros();

  // put your main code here, to run repeatedly:

  readButtons();
  //  Serial.println("readin OK");

  testfbl();
  // Serial.println("fbl OK");

  setLeds();
  // Serial.println("all OK");


#ifdef DEBUG

  Serial.print("FB: ");
  for (int i = 0; i < 8; i++) {
    Serial.print(funcbuttons[i]);
  }
  Serial.println(" ");

  Serial.print("SB: ");
  for (int i = 0; i < 16; i++) {
    Serial.print(stepbuttons[i]);
  }
  Serial.println(" ");
  delay(1);
#endif


  /*
    muxout(mux1A0, mux1A1, mux1A2, mux1A3, mux1, posi);
    muxout(mux2A0, mux2A1, mux2A2, mux2A3, mux2, posi);
    muxout(mux3A0, mux3A1, mux3A2, mux3A3, mux3, posi);
  */

  //Serial.print("position ");
  //Serial.println(posi);

}
