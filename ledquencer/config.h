//configuration file for hardware versions

#ifndef config_h
#define config_h

//robo or hpl hardware?
#define HPL

//config for HPL hardware 
//6x neonpixel sticks
//4 x touch input
#ifdef HPL
#include "hpl_hardware.h"
#endif
//config for ROBO Hardware
// verything IO based
#ifdef ROBO
#include "robo_hardware.h"
#endif

#endif
