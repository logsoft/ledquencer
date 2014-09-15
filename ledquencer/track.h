/*
  track class

  Created by hpl, sept, 2014.
*/

#ifndef track_h
#define track_h

#include "Arduino.h"

extern int patlen;  //pull in from main!

class Track
{
  public:

    Track(int trknum);
//    Track(int trknum, int trkstart, int trkend);
    void setField(int field);
    void setStart(int start);
    void setEnd(int end);
    
    int  getField(); //lest make the tick (this is for the timer call)

  private:
    int _tracknum;
    int _trackpos;
    int _trackstart;
    int _trackend;
    
//    e_states _state; // 0=stop 1=run 2=pause
 //   e_mode _mode;    //clockmode
  //  e_mode _mode_old;    //clockmode
};

#endif


