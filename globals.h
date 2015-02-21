//dirty globals h

#ifndef globals_h
#define globals_h

#define PATLEN 16

volatile static int indicatorlamps;
volatile static int steplamps;
volatile static int functionlamps;
volatile static int stepbuttons;
volatile static int funcbuttons;
volatile static int trigout;

volatile static int debug_int;
static volatile bool last_state[255];
volatile static long timercounters[5];

////////////////////////////////////////// Hardware defines
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

#endif

