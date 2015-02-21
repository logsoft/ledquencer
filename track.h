/*
 track class
 Created by hpl, sept, 2014.
 */

#ifndef track_h
#define track_h

#include "Arduino.h"
#include "globals.h"
#include "debug.h"

extern int patlen;  //pull in from main!

namespace TrackData {
enum e_states {
	Run, Start, Restart, Stop, Pause, Reset,
};

enum e_mode {
	Forward, Backward, Pendulum, Random,
};

struct StepData {
	bool gate;
	bool tie;
	bool skip;
	bool mute;
	bool length[4];
	bool delay[4];
	int cv;
};

struct TrackMeta {
	int tracknum;
	int trackpos;
	int trackstart;
	int trackend;
};
}

class Track {
public:

	Track();
	Track(int trknum);
//    Track(int trknum, int trkstart, int trkend);
	void init(int);
	void setPattern(int pattern);
	void setStart(int start);
	void setEnd(int end);
	int getPattern();
	bool getTrigger(int position);
	bool get_bit(int val, int pos);
	int getNum();
	static void Callback(Track* instance, int x);
	TrackData::e_states getState();

private:
	TrackData::TrackMeta _trackmeta;
	TrackData::e_states _state; // 0=stop 1=run 2=pause
	TrackData::e_mode _mode;    //clockmode
	TrackData::StepData _trackdata[PATLEN];

};

#endif

