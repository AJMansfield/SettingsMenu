#ifndef TIMEADJUSTMENT_H
#define TIMEADJUSTMENT_H

#include "Adjuster.h"
#include "AdjustmentBase.h"

#include <Arduino.h>
#include <time.h>
#include <string.h>

class DateTimeAdjustment: public AdjustmentBase {
public:
	DateTimeAdjustment(time_t* timestamp, char* format, char* highlight, effect_t fx): _fmt(format), _hlt(highlight), fx(fx), _timep(timestamp) {
		localtime_r(_timep, &_timex);
		const AdjusterBase* init[] = {
			new Adjuster<int16_t>(&_timex.tm_year, 0, 200, 1, true),
			new Adjuster<int8_t>(&_timex.tm_mon, 0, 12, 1, true),
			new Adjuster<int8_t>(&_timex.tm_mday, 0, 33, 1, true),
			new Adjuster<int8_t>(&_timex.tm_hour, 0, 24, 1, true),
			new Adjuster<int8_t>(&_timex.tm_min, 0, 60, 1, true),
			new Adjuster<int8_t>(&_timex.tm_sec, 0, 60, 1, true),
		};
		memcpy(_adj, init, sizeof(init));
	}

	~DateTimeAdjustment(){
		delete _adj[0];
		delete _adj[1];
		delete _adj[2];
		delete _adj[3];
		delete _adj[4];
		delete _adj[5];
	}

	bool action(action_t act, int value = 0);

	size_t summary_string(char* buf, size_t buf_size);

	size_t full_string(char* buf, size_t buf_size);

private:
	tm _timex;
	time_t* _timep;
	AdjusterBase* _adj[6];
	volatile size_t _adj_idx = 0;
	char* _fmt;
	char* _hlt;
	effect_t fx;
};

#endif