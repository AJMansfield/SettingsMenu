#ifndef ADJUSTMENT_H
#define ADJUSTMENT_H

#include "AdjustmentBase.h"
#include <Arduino.h>

class ChoiceAdjustment: public AdjustmentBase {
public:
	ChoiceAdjustment(size_t* choice, char** options, size_t opt_count, char* format, char* highlight, effect_t fx):
		_opt(choice), _opts(options), _max_opt(opt_count), _fmt(format), _hlt(highlight), fx(fx) {}

	~ChoiceAdjustment(){}

	exit_t action(action_t act, int value = 0);

	size_t summary_string(char* buf, size_t buf_size);

	size_t full_string(char* buf, size_t buf_size);

private:

	size_t* _opt;
	char** _opts;
	size_t _max_opt;
	
	char* _fmt;
	char* _hlt;
	effect_t fx;

};



#endif