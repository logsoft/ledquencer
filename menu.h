/*
 menu class

 Created by hpl, sept, 2014.
 */

#ifndef menu_h
#define menu_h

#include "Arduino.h"
#include "globals.h"
#include "debug.h"
#include <vector>

namespace MenueState {
enum e_menu_buttons {
	Main = 0,    //Main is normal gui (what to show?)
	Channel = 1,
	Pattern = 2,
	Out = 4,
	Cycle = 8,
	Solo = 16,
	Shift = 32,
	FN = 64,
	Start = 128,
};

}

class Menu {
public:
	Menu(); //instance declaration
	//Menu(std::vector<Track>); //instance declaration

	void onUpdate(void(*)(int, int));  //on Update callback
	void do_your_things(int, int);
	int get_page();
	int get_bar();
	int get_upperleds();
	int get_lowerleds();

private:
	bool get_bit(int fb, int sb);
	bool check_mask(int, int);
	void set_newpage(int funcb);

	//MenueState::e_menu_buttons _page; // state of GUI according e_menu_buttons
	int _page; // state of GUI according e_menu_buttons
	int _bar_position;
	int _stepb, _funcb;
	int _old_stepb;
	int _old_funcb;

	// Callback functions
	void (*onUpdateCallback)(int, int);
	//std::vector<Track> *_tracks;

};

#endif
