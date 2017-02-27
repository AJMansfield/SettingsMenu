#include "DateTimeAdjustment.h"

bool DateTimeAdjustment::action(action_t act, int value){
	switch(act){
	case ACT_NONE:
		return false;
	case ACT_CHANGE:
		localtime_r(_timep, &_timex);
		_adj[_adj_idx]->adjust(value);
		*_timep = mktime(&_timex);
		return false;
	case ACT_ENTER:
		_adj_idx++;
		if(_adj_idx >= sizeof(_adj)/sizeof(void*)){
			_adj_idx == 0;
			return true;
		} else {
			return false;
		}
	case ACT_BACK:
		_adj_idx == 0;
		return true;
	case ACT_CTXT:
		return false;
	}
}

size_t DateTimeAdjustment::summary_string(char* buf, size_t buf_size){
	return strftime(buf, buf_size, _fmt, localtime(_timep));
}

size_t DateTimeAdjustment::full_string(char* buf, size_t buf_size){
	size_t i = strftime(buf, buf_size, _fmt, localtime(_timep));
	for(size_t i = 0; i < buf_size; i++){
		if(_hlt[i] - '0' == _adj_idx){
			fx(buf[i]);
		}
	}
	return i;
}
