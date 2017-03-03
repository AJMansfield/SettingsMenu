#ifndef EXITADJUSTMENT_H
#define EXITADJUSTMENT_H

#include "AdjustmentBase.h"
#include <Arduino.h>

template<exit_t exit>
class ExitAdjustment: public AdjustmentBase {
public:
	ExitAdjustment(){};
	~ExitAdjustment(){}

	exit_t action(action_t, int);
	size_t summary_string(char*, size_t);
	size_t full_string(char*, size_t);
};


template<exit_t exit>
exit_t ExitAdjustment<exit>::action(action_t, int){
	return exit;
}

template<exit_t exit>
size_t ExitAdjustment<exit>::summary_string(char*, size_t){
	return 0;
}

template<exit_t exit>
size_t ExitAdjustment<exit>::full_string(char*, size_t){
	return 0;
}

#endif