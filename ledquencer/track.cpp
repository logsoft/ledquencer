#include "Arduino.h"
#include "track.h"


Track::Track(int trknum)
{
  _tracknum = trknum;
  _trackstart = 0;
  _trackend = patlen -1;
}


