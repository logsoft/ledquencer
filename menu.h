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

//! menu enumerations.
/*! This is the Menu namespace.\n it defines menue related enumerations used across the programm! */
namespace MenuEnums{
//! functionbuttons enum.
/*! functionbutton enumeration. */
enum e_menu_buttons {
	Main = 0,    /*!< No Button*/
	Sequence = 1, /*!< Sequnce Button */
	Pattern = 2, /*!< Pattern Button */
	Out = 4,	/*!< Out Button */
	Cycle = 8, /*!< Cycle Button */
	Solo = 16, /*!< Solo Button*/
	Shift = 32,/*!< Shift Button*/
	FN = 64,/*!< FN Button*/
	Start = 128,/*!< Start Button*/
};
}

//! \brief menu class for menu handling.
/*! \detail Menu It defines menu related functions and callbacks! */
class Menu {
public:
	Menu(); //instance declaration
	//Menu(std::vector<Track>); //instance declaration

	void onUpdate(void(*)(int, int));  /*!< \brief on Update callback brief */
	void do_your_things(int, int); /*!< \brief this is the mainloop of menu */
	int get_page();/*!< \brief returns actual page as int*/
	int get_bar();/*!< \brief returns actual bar position as int*/
	int get_indicatorleds();/*!< \brief get indicatorleds */
	int get_stepleds();/*!< \brief get stepleds*/

private:
	bool get_bit(int val, int pos);/*!< \brief returns true/false from bitposition (&mask)*/
	bool check_mask_equal(int, int); /*!< \brief compares masks returns true if equal */
	void set_newpage(int funcb);/*!< \brief sets menu to a new page*/

	int _page; /*!< state of GUI according e_menu_buttons */
	int _bar_position; /*!< viewed scope of sequence*/
	int _stepb, _funcb;/*!< internal stepbuttons and functionbuttons*/
	int _old_stepb;/*!< old state for flanks*/
	int _old_funcb;/*!< old state for flanks*/

	// Callback functions
	void (*onUpdateCallback)(int, int);
	//std::vector<Track> *_tracks;

};

#endif
