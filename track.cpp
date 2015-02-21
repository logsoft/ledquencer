#include "Arduino.h"
#include "track.h"
#include "menu.h"

Track::Track() {
	_trackmeta.tracknum = 0;
	_trackmeta.trackstart = 0;
	_trackmeta.trackpos = 0;
	_state = TrackData::Stop;
	_mode = TrackData::Forward;
	_trackmeta.trackend = PATLEN - 1;
}

Track::Track(int trknum) {
	_trackmeta.tracknum = trknum;
	_trackmeta.trackstart = 0;
	_trackmeta.trackpos = 0;
	_state = TrackData::Stop;
	_mode = TrackData::Forward;
	_trackmeta.trackend = PATLEN - 1;
}

void Track::init(int trknum) {
	_trackmeta.tracknum = trknum;
}
bool Track::get_bit(int val, int pos) {
	return 0x01 & (val >> pos);
}

void Track::setPattern(int pattern) {
	for (int i = 0; i < 15; i++) {
		_trackdata[i].gate = get_bit(pattern, i);
	}

}

int Track::getNum() {
	return _trackmeta.tracknum;
}

TrackData::e_states Track::getState() {
	return _state;
}

void Callback(Track* instance, int x) {
	DEBUG("the callback fired");
	DEBUG();
	int i = MenueState::Solo;

}
