#ifndef PICKADJUSTMENT_H
#define PICKADJUSTMENT_H

#include "AdjustmentBase.h"
#include <Arduino.h>

class PickAdjustment: public AdjustmentBase {
public:
	PickAdjustment(AdjustmentBase** adjustments, const char** names, const size_t count, const size_t cols):
		_opts(adjustments), _opt_names(names), _max_opt(count), _cols(cols) {}

	~PickAdjustment(){}

	exit_t action(action_t act, int value = 0);

	size_t summary_string(char* buf, size_t buf_size);

	size_t full_string(char* buf, size_t buf_size);

private:

	AdjustmentBase** _opts;
	const char** _opt_names;
	size_t _opt;
	bool _active;
	const size_t _max_opt;
	const size_t _cols;


};



#endif