//configuration file for hardware versions

#ifndef config_h
#define config_h

//useports or usebus hardware?
#define USEBUS

//config for HPL hardware 
//6x neonpixel sticks
//4 x touch input
#ifdef USEBUS
#include "bushardware.h"
#endif
//config for ROBO Hardware
// verything IO based
#ifdef USEPORTS
#include "porthardware.h"
#endif

#endif
