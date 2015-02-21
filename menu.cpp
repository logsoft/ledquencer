/*
 * menu.cpp
 *
 *  Created on: Jan 18, 2015
 *      Author: hpl
 */

#include "menu.h"

Menu::Menu() {
	_page = MenueState::Main; //set page to MAIN
	//_tracks = NULL; //no tracks init
	_old_stepb = 0; //remember old button state
	_old_funcb = 0;	//remember old button state
	_bar_position = 0; //for multibar gui which page iam
}

void Menu::onUpdate(void(*function)(int, int)) {
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

bool Menu::check_mask(int val, int mask) {
	return val == mask ? true : false;
}

int Menu::get_page() {
	return _page;
}

 int Menu::get_upperleds(){
		switch (_page) {
			case MenueState::Main:
				return _stepb;
				break;
			case MenueState::Channel:
				return MenueState::Channel;
			case MenueState::Pattern:
				return MenueState::Pattern;

			default:
				return _stepb;
		}
 }

 int Menu::get_lowerleds(){
		switch (_page) {
			case MenueState::Main:
				return _stepb;
				break;
			case MenueState::Channel:
				return 32;
			default:
				return _stepb;
		}
 }

void Menu::set_newpage(int funcb) {
	//no reset, new selection
	if (check_mask(funcb, MenueState::Channel)) {
		DEBUG("channel selected");
		_page = MenueState::Channel;
	}
	if (check_mask(funcb, MenueState::Pattern)) {
		DEBUG("Pattern selected");
		_page = MenueState::Pattern;
	}
	if (check_mask(funcb, MenueState::Out)) {
		DEBUG("Out selected");
		_page = MenueState::Out;
	}
	if (check_mask(funcb, MenueState::Cycle)) {
		DEBUG("Cycle selected");
		_page = MenueState::Cycle;
	}
	if (check_mask(funcb, MenueState::Solo)) {
		_page = MenueState::Solo;
	}
	if (check_mask(funcb, MenueState::Shift)) {
		_page = MenueState::Shift;
	}
	if (check_mask(funcb, MenueState::Start)) {
	}
	if (check_mask(funcb, (MenueState::Channel + MenueState::FN))) {
	}
}

void Menu::do_your_things(int fb, int sb) {
	_funcb = fb;
	_stepb = sb;

	if (_funcb != _old_funcb) {
		_old_funcb = _funcb;
		DEBUG("funcbuttons trigger ");
		DEBUG(_page);

		//reset to main
		if ((_page != MenueState::Main) and (_funcb != 0)) {
			DEBUG("Main selected");
			_page = MenueState::Main;
		} else { //no reset, new selection
			set_newpage(_funcb);
		} //end new selection
	} //end debounce funcbuttons

	if (_stepb != _old_stepb) {	//todo: mybee a debounce needed!
		_old_stepb = _stepb;
		DEBUG("stepbuttons trigger");
		DEBUG(_stepb);
		onUpdateCallback(_page,_stepb);

	}




}

