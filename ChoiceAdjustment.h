#ifndef CHOICEADJUSTMENT_H
#define CHOICEADJUSTMENT_H

#include "AdjustmentBase.h"
#include <Arduino.h>

class ChoiceAdjustment: public AdjustmentBase {
public:
	ChoiceAdjustment(size_t* choice, const char** options, const size_t opt_count, const char* format, const char* highlight, const effect_t fx):
		_opt(choice), _opts(options), _max_opt(opt_count), _fmt(format), _hlt(highlight), fx(fx) {}

	~ChoiceAdjustment(){}

	exit_t action(action_t act, int value = 0);

	size_t summary_string(char* buf, size_t buf_size);

	size_t full_string(char* buf, size_t buf_size);

private:

	size_t* _opt;
	const char** _opts;
	const size_t _max_opt;
	
	const char* _fmt;
	const char* _hlt;
	const effect_t fx;

};



#endif