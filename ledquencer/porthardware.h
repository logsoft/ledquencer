#ifndef robo_hardware_h
#define porthardware_h


#include <Arduino.h>
#include "globals.h"

// Tout   Trigger Outs
#define Tout01 26
#define Tout02 25
#define Tout03 24
#define Tout04 23
#define Tout05 22
#define Tout06 2
#define Tout07 3
#define Tout08 4
#define Tout09 5
#define Tout10 6
#define Tout11 7
#define Tout12 8
#define Tout13 9
#define Tout14 10
#define Tout15 11
#define Tout16 12

// Clocks
#define clkout 27
#define clkin  28  //inverted

#define midiout 1  // tx
#define midiin  0  // rx

// Mux Adressen / muxlatch: if high -> outputs stored
#define mux1A0 35
#define mux1A1 36
#define mux1A2 33
#define mux1A3 34
#define mux2A0 37
#define mux2A1 38
#define mux2A2 31
#define mux2A3 32
#define mux3A0 39
#define mux3A1 40
#define mux3A2 30
#define mux3A3 29

#define muxlatch 41

// SB   Step Buttons
#define SB01 A1  //Analog Ins
#define SB02 A3  //
#define SB03 A5  //
#define SB04 A7  //
#define SB05 A9  //
#define SB06 A11  //
#define SB07 53
#define SB08 51
#define SB09 49
#define SB10 47
#define SB11 45
#define SB12 43
#define SB13 48
#define SB14 46
#define SB15 44
#define SB16 42

//FB   Function Buttons from left to right
#define FB01 A0  //Analog Ins
#define FB02 A2  //
#define FB03 A4  //
#define FB04 A6  //
#define FB05 A8  //
#define FB06 A10  //
#define FB07 52
#define FB08 50


/*

int  getMuxState1() {
  //get mux 1 states
  int imux1[16];
  imux1[0] = false;
  imux1[1] = int(functionlamps[5]);
  imux1[2] = functionlamps[6];
  imux1[3] = functionlamps[4];
  imux1[4] = functionlamps[3];
  imux1[5] = functionlamps[2];
  imux1[6] = functionlamps[1];
  imux1[7] = functionlamps[0];
  imux1[8] = indicatorlamps[1];
  imux1[9] = steplamps[1];
  imux1[10] = indicatorlamps[0];
  imux1[11] = steplamps[0];
  imux1[12] = indicatorlamps[3];
  imux1[13] = steplamps[3];
  imux1[14] = indicatorlamps[2];
  imux1[15] = steplamps[2];



}


void  getMuxState2() {
  //get mux 1 states
  int imux2[16];
  //imux2
  imux2[0] = steplamps[13];
  imux2[1] = indicatorlamps[13];
  imux2[2] = indicatorlamps[14];
  imux2[3] = steplamps[14];
  imux2[4] = indicatorlamps[15];
  imux2[5] = steplamps[15];
  imux2[6] = functionlamps[7];
  imux2[7] = indicatorlamps[5];
  imux2[8] = steplamps[5];
  imux2[9] = steplamps[1];
  imux2[10] = indicatorlamps[4];
  imux2[11] = steplamps[4];
  imux2[12] = indicatorlamps[7];
  imux2[13] = steplamps[7];
  imux2[14] = indicatorlamps[6];
  imux2[15] = steplamps[6];


}

void  getMuxState3() {
  //get mux 1 states
  int imux3[16];
  //imux3
  imux3[0] = false;
  imux3[1] = false;
  imux3[2] = false;
  imux3[3] = false;
  imux3[4] = false;
  imux3[5] = false;
  imux3[6] = indicatorlamps[12];
  imux3[7] = steplamps[12];
  imux3[8] = indicatorlamps[9];
  imux3[9] = steplamps[9];
  imux3[10] = indicatorlamps[8];
  imux3[11] = steplamps[8];
  imux3[12] = indicatorlamps[11];
  imux3[13] = steplamps[11];
  imux3[14] = indicatorlamps[10];
  imux3[15] = steplamps[10];
}

*/

//set Hardware debouncing!
void setDebounce()
{
  //todo: richtige masken finden!!

  int mask_1 = digitalPinToBitMask(FB01) &
               digitalPinToBitMask(FB02) &
               digitalPinToBitMask(FB03) &
               digitalPinToBitMask(FB04) &
               digitalPinToBitMask(FB05) &
               digitalPinToBitMask(FB06) &
               digitalPinToBitMask(FB07) &
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
  pinMode (SB01, INPUT);
  pinMode (SB02, INPUT);
  pinMode (SB03, INPUT);
  pinMode (SB04, INPUT);
  pinMode (SB05, INPUT);
  pinMode (SB06, INPUT);
  pinMode (SB07, INPUT);
  pinMode (SB08, INPUT);
  pinMode (SB09, INPUT);
  pinMode (SB10, INPUT);
  pinMode (SB11, INPUT);
  pinMode (SB12, INPUT);
  pinMode (SB13, INPUT);
  pinMode (SB14, INPUT);
  pinMode (SB15, INPUT);
  pinMode (SB16, INPUT);
  //Function buttons
  pinMode (FB01, INPUT);
  pinMode (FB02, INPUT);
  pinMode (FB03, INPUT);
  pinMode (FB04, INPUT);
  pinMode (FB05, INPUT);
  pinMode (FB06, INPUT);
  pinMode (FB07, INPUT);
  pinMode (FB08, INPUT);
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


// MUX handling


void muxout(int pin0, int pin1, int pin2, int pin3, bool mask[], int pos) {
  digitalWrite(pin0, (int(mask[pos]) & 1));
  digitalWrite(pin1, (int(mask[pos]) & 2));
  digitalWrite(pin2, (int(mask[pos]) & 4));
  digitalWrite(pin3, (int(mask[pos]) & 8));
}




long then = 0;

void muxAll(int* mux1,int* mux2, int* mux3) {
  //getMuxState();
  
  
  long now = micros();
  //  if (then + 100 <= now) {
  then = now;
  bool flag = true; //mux1[posi];

/*
  posi += 1;
  int aktstate = 0;
  if (posi == 16) {
    posi = 0;
    //   }
  }
*/

}

/*
void showLeds(){
 muxAll(); 
}
*/



//unused by now

struct mux1 {
  boolean IL01; //indicator Lamps
  boolean IL02;
  boolean IL03;
  boolean IL04;
  boolean SL01; //Step Lamps
  boolean SL02;
  boolean SL03;
  boolean SL04;
  boolean FL01; //Function Lamps
  boolean FL02;
  boolean FL03;
  boolean FL04;
  boolean FL05;
  boolean FL06;
  boolean FL07;
  boolean spare16;
};

struct mux2 {
  boolean IL05;
  boolean IL06;
  boolean IL07;
  boolean IL08;
  boolean IL14;
  boolean IL15;
  boolean IL16;
  boolean SL05;
  boolean SL06;
  boolean SL07;
  boolean SL08;
  boolean SL14;
  boolean SL15;
  boolean SL16;
  boolean spare15;
  boolean spare16;
} ;

struct mux3 {
  boolean IL09;
  boolean IL10;
  boolean IL11;
  boolean IL12;
  boolean IL13;
  boolean SL09;
  boolean SL10;
  boolean SL11;
  boolean SL12;
  boolean SL13;
  boolean spare11;
  boolean spare12;
  boolean spare13;
  boolean spare14;
  boolean spare15;
  boolean spare16;
}  ;




#endif
