#ifndef ADJUSTMENTBASE_H
#define ADJUSTMENTBASE_H

#include "Adjuster.h"

#include <Arduino.h>

enum action_t { ACT_NONE, ACT_CHANGE, ACT_ENTER, ACT_BACK, ACT_CTXT };
enum exit_t { NO_EXIT, EXIT_SAVE, EXIT_CANCEL };
typedef void(*effect_t)(char&);

class AdjustmentBase {
public:
	// return true when exiting the adjustment
	virtual exit_t action(action_t act, int value = 0) = 0;

	// write a string representing the current state
	virtual size_t summary_string(char* buf, size_t buf_size) = 0;

	// write a string representing the current edit mode and state
	virtual size_t full_string(char* buf, size_t buf_size) = 0;
};




#endif