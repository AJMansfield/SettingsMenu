#include "ChoiceAdjustment.h"

exit_t ChoiceAdjustment::action(action_t act, int value = 0){
	switch(act){
	case ACT_NONE:
		return E_NONE;
	case ACT_BEGIN:
		return NOEXIT;
	case ACT_CHANGE:
		*_opt += value;
		while((signed)*_opt < 0) *_opt += _max_opt;
		*_opt %= _max_opt;
		return NOEXIT;
	case ACT_ENTER:
		return EXIT_SAVE;
	case ACT_BACK:
		return EXIT_CANCEL;
	case ACT_CTXT:
		return NOEXIT;
	}
}

size_t ChoiceAdjustment::summary_string(char* buf, size_t buf_size){
	snprintf(buf, buf_size, _fmt, *(_opts+*_opt));
}

size_t ChoiceAdjustment::full_string(char* buf, size_t buf_size){
	size_t i = snprintf(buf, buf_size, _fmt, *(_opts+*_opt));
	for(size_t j = 0; j < i; j++){
		if(_hlt[j] - '0' == 0){
			fx(buf[j]);
		}
	}
	return i;
}