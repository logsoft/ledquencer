/*
 * menu.cpp
 *
 *  Created on: Jan 18, 2015
 *      Author: hpl
 */

#include "menu.h"

Menu::Menu() {
	_page = MenuEnums::Main; //set page to MAIN
	//_tracks = NULL; //no tracks init
	_old_stepb = 0; //remember old button state
	_old_funcb = 0;	//remember old button state
	_bar_position = 0; //for multibar gui which page iam
}

/*! \detail onUpdate callback detail
 \param function to call.
 gets called by ??. and processes the events
 */
void Menu::onUpdate(void (*function)(int, int)) {
	onUpdateCallback = function;
}

//Menu::Menu(std::vector<Track> tracks) {
//	_page = MenueState::Main;
//	//_tracks = &tracks;
//	_old_stepb = 0;
//	_old_funcb = 0;
//}

bool Menu::get_bit(int val, int pos) {
	return 0x01 & (val >> pos);
}
/*! \detail checks two int masks for equalness.
 * returns true/false
 */
bool Menu::check_mask_equal(int val, int mask) {
	return val == mask ? true : false;
}

int Menu::get_page() {
	return _page;
}

/*! \detail get the data for the indicator leds .
 process the datahandling to update the stepleds.
 get the according data for page.
 returns an int 16 states.
 todo: return 16 colors!.
 */
int Menu::get_indicatorleds() {
	switch (_page) {
	case MenuEnums::Main:
		return _stepb;
		break;
	case MenuEnums::Sequence:
		return MenuEnums::Sequence;
	case MenuEnums::Pattern:
		return MenuEnums::Pattern;

	default:
		return _stepb;
	}
}
/*! \detail
 process the datahandling to update the stepleds.
 get the according data for page.
 returns an int 16 states.
 todo: return 16 colors!.
 */
int Menu::get_stepleds() {
	switch (_page) {
	case MenuEnums::Main:
		return _stepb;
		break;
	case MenuEnums::Sequence:
		return 32;
	default:
		return _stepb;
	}
}

void Menu::set_newpage(int funcb) {
	///checks the Functionbutton state and switrches to according _menue page
	//no reset, new selection
	if (check_mask_equal(funcb, MenuEnums::Sequence)) {
		DEBUG("channel selected");
		_page = MenuEnums::Sequence;
	}
	if (check_mask_equal(funcb, MenuEnums::Pattern)) {
		DEBUG("Pattern selected");
		_page = MenuEnums::Pattern;
	}
	if (check_mask_equal(funcb, MenuEnums::Out)) {
		DEBUG("Out selected");
		_page = MenuEnums::Out;
	}
	if (check_mask_equal(funcb, MenuEnums::Cycle)) {
		DEBUG("Cycle selected");
		_page = MenuEnums::Cycle;
	}
	if (check_mask_equal(funcb, MenuEnums::Solo)) {
		_page = MenuEnums::Solo;
	}
	if (check_mask_equal(funcb, MenuEnums::Shift)) {
		_page = MenuEnums::Shift;
	}
	if (check_mask_equal(funcb, MenuEnums::Start)) {
	}
	if (check_mask_equal(funcb, (MenuEnums::Sequence + MenuEnums::FN))) {
	}
}

/*! \detail Menu Mainloop
 * processes all the button and led data according to selected page
 * needs to get updated regularly in mainloop
 \param functionbuttons
 \param stepbuttons
*/
void Menu::do_your_things(int fb, int sb) {
	_funcb = fb;
	_stepb = sb;

	if (_funcb != _old_funcb) {
		_old_funcb = _funcb;
		DEBUG("funcbuttons trigger ");
		DEBUG(_page);

		//reset to main
		if ((_page != MenuEnums::Main) and (_funcb != 0)) {
			DEBUG("Main selected");
			_page = MenuEnums::Main;
		} else { //no reset, new selection
			set_newpage(_funcb);
		} //end new selection
	} //end debounce funcbuttons

	if (_stepb != _old_stepb) {	//todo: mybee a debounce needed!
		_old_stepb = _stepb;
		DEBUG("stepbuttons trigger");
		DEBUG(_stepb);
		onUpdateCallback(_page, _stepb);

	}

}

