#ifndef TIMEADJUSTMENT_H
#define TIMEADJUSTMENT_H
#define INCLUDE_PRINTF

#include "Adjuster.h"
#include "AdjustmentBase.h"
#include <Arduino.h>
#include <time.h>
#include <string.h>

template<bool Condition, typename T> struct Has { 
	T v; 
	Has(T value): v(value) {}
	T* V(){ return &v; }
};
template<typename T> struct Has<false,T> {
	Has(T value){}
	T* V(){ return nullptr; }
};

template<bool y = false, bool m = false, bool d = false, bool H = false, bool M = false, bool S = false>
class TimeAdjustment: public AdjustmentBase {

public:
	TimeAdjustment(time_t* timestamp, const char* format, const char* highlight, effect_t fx):
		_fmt(format), _hlt(highlight), fx(fx), _timep(timestamp),
		_y(Adjuster<int16_t>(&_timex.tm_year, 100, 236, 1, false)),
		_m(Adjuster<int8_t>(&_timex.tm_mon, 0, 12, 1, true)),
		_d(Adjuster<int8_t>(&_timex.tm_mday, 0, 33, 1, true)),
		_H(Adjuster<int8_t>(&_timex.tm_hour, 0, 24, 1, true)),
		_M(Adjuster<int8_t>(&_timex.tm_min, 0, 60, 1, true)),
		_S(Adjuster<int8_t>(&_timex.tm_sec, 0, 61, 1, true))

	{
		localtime_r(_timep, &_timex);
		size_t i = 0;

		if(y) _adj[i++] = _y.V();
		if(m) _adj[i++] = _m.V();
		if(d) _adj[i++] = _d.V();
		if(H) _adj[i++] = _H.V();
		if(M) _adj[i++] = _M.V();
		if(S) _adj[i++] = _S.V();
	}

	~TimeAdjustment(){
		for(size_t i = 0; i < _size; i++){
			delete _adj[i];
		}
	}

	Has<y, Adjuster<int16_t>> _y;
	Has<m, Adjuster<int8_t>> _m;
	Has<d, Adjuster<int8_t>> _d;
	Has<H, Adjuster<int8_t>> _H;
	Has<M, Adjuster<int8_t>> _M;
	Has<S, Adjuster<int8_t>> _S;

	exit_t action(action_t act, int value = 0);

	size_t summary_string(char* buf, size_t buf_size);

	size_t full_string(char* buf, size_t buf_size);

private:
	const static size_t _size = ((size_t)y) + m + d + H + M + S;
	tm _timex;
	time_t* _timep;
	AdjusterBase* _adj[_size];
	volatile size_t _adj_idx = 0;
	char* _fmt;
	char* _hlt;
	effect_t fx;

};


template<bool y, bool m, bool d, bool H, bool M, bool S>
exit_t TimeAdjustment<y,m,d,H,M,S>::action(action_t act, int value){
	switch(act){
	case ACT_NONE:
		return E_NONE;
	case ACT_BEGIN:
		return NOEXIT;
	case ACT_CHANGE:
		localtime_r(_timep, &_timex);
		_adj[_adj_idx]->adjust(value);
		*_timep = mktime(&_timex);
		return NOEXIT;
	case ACT_ENTER:
		_adj_idx++;
		if(_adj_idx < _size) {
			return NOEXIT;
		} else {
			_adj_idx = 0;
			return EXIT_SAVE;
		}
	case ACT_BACK:
		_adj_idx == 0;
		return EXIT_CANCEL;
	case ACT_CTXT:
		return NOEXIT;
	}
}

template<bool y, bool m, bool d, bool H, bool M, bool S>
size_t TimeAdjustment<y,m,d,H,M,S>::summary_string(char* buf, size_t buf_size){
	return strftime(buf, buf_size, _fmt, localtime(_timep));
}

template<bool y, bool m, bool d, bool H, bool M, bool S>
size_t TimeAdjustment<y,m,d,H,M,S>::full_string(char* buf, size_t buf_size){
	size_t i = strftime(buf, buf_size, _fmt, localtime(_timep));


	for(size_t j = 0; j < i; j++){
		if(_hlt[j] - '0' == _adj_idx){
			fx(buf[j]);
		}
	}



	return i;
}


#endif