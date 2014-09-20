#ifndef hpl_hardware_h
#define hpl_hardware_h

//#include <Adafruit_MPR121.h>
#include <FastLED.h>
#include <pixeltypes.h>
#include <sam3xa/include/instance/instance_pioa.h>
#include <UARTClass.h>
#include <variant.h>
#include <Wire.h>
#include "Adafruit_MPR121.h"
#include <Adafruit_NeoPixel.h>

//led strip things
#define DATA_PIN 6
#define NUM_LEDS 40

// This is an array of LEDs.  One item for each led in your strip.
CRGB leds[NUM_LEDS];

//touch input thing
Adafruit_MPR121 touchboard[4] = { Adafruit_MPR121() };

//neonpixels
Adafruit_NeoPixel strip = Adafruit_NeoPixel(40, DATA_PIN, NEO_GRB + NEO_KHZ800);

void showLeds() {
	// Show the LEDs (only one of which is set to white, from above)
	strip.show();
}

void readButtons() {

	;
}

//set Hardware debouncing!
void setDebounce() {
	//todo: richtige masken finden!!

	int mask_1 = 	digitalPinToBitMask(1) &
					digitalPinToBitMask(1) &
					digitalPinToBitMask(1);
	// activate input filters for pin 24
	REG_PIOA_IFER = mask_1;
	// choose debounce filter as input filter for pin 24
	REG_PIOA_DIFSR = mask_1;
	// set clock divider for slow clock -> rejects pulses shorter than (DIV+1)*31µs and accepts pulses longer than 2*(DIV+1)*31µs
	REG_PIOA_SCDR = 10;

}

void portsetup() {
	//set SAM3X Hardware debouncing parameters for inputs
	setDebounce();

	//LED setup
	strip.begin();
	//FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);

	/*

	 //touch Buttons setup
	 // Default address is 0x5A, if tied to 3.3V its 0x5B
	 // If tied to SDA its 0x5C and if SCL then 0x5D
	 int addr = 0x5A;
	 for (int i = 0; i < 5; i++) {
	 //	  Adafruit_MPR121 touch = mpr[i];
	 if (touchboard[i].begin(addr)) {
	 Serial.println("MPR121 found @ ");
	 Serial.println(addr);
	 }
	 else{
	 Serial.print("not found @adr ");
	 Serial.println(addr);
	 }
	 addr += 1;
	 }
	 Serial.println("MPR121 ENDE!");
	 //trigger out
	 // define triggers!

	 //clk out
	 //pinMode(clkout, OUTPUT);

	 */

}

#endif
