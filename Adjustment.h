#ifndef ADJUSTMENT_H
#define ADJUSTMENT_H

#include "Adjuster.h"
#include "AdjustmentBase.h"
#include <Arduino.h>

template<typename T>
class Adjustment: public AdjustmentBase {
public:
	Adjustment(Adjuster<T>* adjuster, char* format, char* highlight, effect_t fx):\
			 _adj(adjuster), _fmt(format), _hlt(highlight), fx(fx) {};

	exit_t action(action_t act, int value = 0);

	size_t summary_string(char* buf, size_t buf_size);

	size_t full_string(char* buf, size_t buf_size);

private:
	Adjuster<T>* _adj;
	char* _fmt;
	char* _hlt;
	effect_t fx;
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
	for(size_t j = 0; j < i; j++){
		if(_hlt[j] - '0' == 0){
			fx(buf[j]);
		}
	}
	return i;
}



#endif