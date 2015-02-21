/*
 track class
 Created by hpl, sept, 2014.
 */

#ifndef track_h
#define track_h
#include <vector>
#include "Arduino.h"
#include "globals.h"
#include "debug.h"

extern int patlen;  //pull in from main!

///This is the sequence data namespace.\n it defines sequence related enumerations used across the programm
namespace SequenceEnum {
/*! States the sequence can be in */
	enum e_runStates {
		Run, Start, Restart, Stop, Pause, Reset,
	};
	/*! playing mode track can has */
	enum e_runMode {
		Forward, /*!< Play sequence forward*/
		Backward, /*!< Play sequence reverse*/
		Pendulum, /*!< Play sequence pendular*/
		Random, /*!< Play sequence random*/
		Brownian, /*!< Play sequence in brownian pattern*/
	};

	///Basic struct of one step - data. used on all step data operations
	struct StepData {
		bool gate; /*!< Gate ON !*/
		bool glide; /*!< Glide this?*/
		bool skip; /*!< Skip ?*/
		bool length[4]; /*!< Gate length*/
		int cv;	/*!< Cv Value 4 step*/
	};

	/// some ssquence metadata for internal handling
	struct SequenceMeta {
		int seqnum;  /*!< Internal sequence Number */
		int seqpos;	///Position of play pointer in sequence
		int seqstart; ///start position for play pointer
		int seqend;   ///end for play pointer
		int shufflepos; ///position to shuffle
		int shuffleamount;  /// amount of shuffle in track
	};
}

volatile static std::vector<SequenceEnum::StepData> trackdata(PATLEN*TRACKS);

//! Sequence class.
/*! This is the Sequence class.\n it defines one sequence of the pattern! */
class Sequence {
public:
	Sequence();
	Sequence(int trknum);
//    Sequence(int trknum, int trkstart, int trkend);
	void init(int);
	void setPattern(int pattern);
	void setStart(int start);
	void setEnd(int end);
	int getPattern();
	bool getTrigger(int position);
	bool get_bit(int val, int pos);
	int getNum();
	static void Callback(Sequence* instance, int x);
	SequenceEnum::e_runStates getState();

private:
	SequenceEnum::SequenceMeta _meta;
	SequenceEnum::e_runStates _state; // 0=stop 1=run 2=pause
	SequenceEnum::e_runMode _mode;    //clockmode
	SequenceEnum::StepData _data[PATLEN];
};

#endif

