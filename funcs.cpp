/*
 * funcs.c
 *
 *  Created on: Jan 18, 2015
 *      Author: hpl
 */

#include "funcs.h"

inline bool debounce(bool akt, int statenr) {
	if (akt != last_state[statenr]) {
		last_state[statenr] = akt;
		if (akt)
			return last_state[statenr];
	}
	return false;
}

