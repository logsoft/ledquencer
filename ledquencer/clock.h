/*
  Clock generation class

  Created by hpl, sept, 2014.
*/

#ifndef Clock_h
#define Clock_h

#include "Arduino.h"


enum e_states {
  Run,
  Start,
  Restart,
  Stop,
  Pause,
  Reset,
};

enum e_mode{
  Forward,
  Backward,
  Pendulum,
  Random,
};

class Clock
{

  public:

    Clock(int clklen);
    void clk_setState(e_states state);
    void clk_doTick(); //lest make the tick (this is for the timer call)
    double getClock();

  private:
    int _clockpos;
    int _clocklen;
    e_states _state; // 0=stop 1=run 2=pause
    e_mode _mode;    //clockmode
    e_mode _mode_old;    //clockmode
};

#endif
