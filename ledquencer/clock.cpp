#include "Arduino.h"
#include "clock.h"


Clock::Clock(int clklen)
{
  _clocklen = clklen;
}

void Clock::clk_setState(e_states state)
{
  _state = state;
}

// do the ticking!
void Clock::clk_doTick()
{
  if (_state == Run) {          //do other modes!
    if (_mode == Forward) {
      _clockpos += 1;
    }
    if (_mode == Backward) {
      _clockpos -= 1;
    }
  }
  else if (_state == Stop)
  {
    _clockpos = 0;
  }
  else if (_state == Reset)
  {
    _clockpos = 0;
    _state = Stop;
  }
  else if (_state == Restart)
  {
    _clockpos = 0;
    _state = Run;
  }

//reset at end
  if (_clockpos >= _clocklen) _clockpos = 0;


} //lest make the tick (this is for the timer call)

double Clock::getClock() {
  return _clockpos;
}
