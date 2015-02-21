#include "Arduino.h"
#include "sequence.h"
#include "menu.h"

Sequence::Sequence() {
	_meta.seqnum = 0;
	_meta.seqstart = 0;
	_meta.seqpos = 0;
	_state = SequenceEnum::Stop;
	_mode = SequenceEnum::Forward;
	_meta.seqend = PATLEN - 1;
}

Sequence::Sequence(int trknum) {
	_meta.seqnum = trknum;
	_meta.seqstart = 0;
	_meta.seqpos = 0;
	_state = SequenceEnum::Stop;
	_mode = SequenceEnum::Forward;
	_meta.seqend = PATLEN - 1;
}

void Sequence::init(int trknum) {
	_meta.seqnum = trknum;
}
bool Sequence::get_bit(int val, int pos) {
	return 0x01 & (val >> pos);
}

void Sequence::setPattern(int pattern) {
	for (int i = 0; i < 15; i++) {
		_data[i].gate = get_bit(pattern, i);
//		seqdata.at(i);   // =  get_bit(pattern, i);
	}

}

int Sequence::getNum() {
	return _meta.seqnum;
}

SequenceEnum::e_runStates Sequence::getState() {
	return _state;
}

/*! \def Callback(instance,x)
\brief Callback for sequence.
gets called by
*/
void Callback(Sequence* instance, int x) {
	DEBUG("the callback fired");
	DEBUG();
	int i = MenuEnums::Solo;

}
