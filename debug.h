/*
 * debug.h
 *
 *  Created on: Jan 26, 2015
 *      Author: hpl
 */

#ifndef DEBUG_H_
#define DEBUG_H_

extern int debugging_enabled;

#define DEBUG(x) do {if (debugging_enabled) { Serial.println(x);}} while (0)

#endif /* DEBUG_H_ */
