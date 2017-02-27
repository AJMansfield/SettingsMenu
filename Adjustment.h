#ifndef ADJUSTMENT_H
#define ADJUSTMENT_H

#include "Adjuster.h"
#include "AdjustmentBase.h"
#include <Arduino.h>

template<typename T>
class Adjustment: public AdjustmentBase {
public:
	Adjustment(Adjuster<T>* adjuster, char* format, effect_t fx, size_t begin, size_t end):\
			 _adj(adjuster), _fmt(format), fx(fx), _begin(begin), _end(end) {};

	exit_t action(action_t act, int value = 0);

	size_t summary_string(char* buf, size_t buf_size);

	size_t full_string(char* buf, size_t buf_size);

private:
	Adjuster<T>* _adj;
	char* _fmt;
	effect_t fx;
	size_t _begin;
	size_t _end;
};

template<typename T>
exit_t Adjustment<T>::action(action_t act, int value = 0){
	switch(act){
	case ACT_NONE:
		return NO_EXIT;
	case ACT_CHANGE:
		_adj->adjust(value);
		return NO_EXIT;
	case ACT_ENTER:
		return EXIT_SAVE;
	case ACT_BACK:
		return EXIT_CANCEL;
	case ACT_CTXT:
		return NO_EXIT;
	}
}

template<typename T>
size_t Adjustment<T>::summary_string(char* buf, size_t buf_size){
	snprintf(buf, buf_size, _fmt, *_adj->value());
}

template<typename T>
size_t Adjustment<T>::full_string(char* buf, size_t buf_size){
	size_t i = snprintf(buf, buf_size, _fmt, *_adj->value());
	fx(buf+_begin, buf+_end);
}



#endif