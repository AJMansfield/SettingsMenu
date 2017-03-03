#include "PickAdjustment.h"

exit_t PickAdjustment::action(action_t act, int value){
	if(_active){
		switch(_opts[_opt]->action(act,value)){
		case EXIT:
			_active = false;
		case NOEXIT:
			return NOEXIT;
		case EXIT_SAVE:
			_active = false;
		case NOEXIT_SAVE:
			return NOEXIT_SAVE;
		case EXIT_CANCEL:
			_active = false;
		case NOEXIT_CANCEL:
			return NOEXIT_CANCEL;
		case E_NONE:
			return E_NONE;
		}
	}

	switch(act){
	case ACT_NONE:
		return E_NONE;
	case ACT_BEGIN:
		return NOEXIT;
	case ACT_CHANGE:
		_opt += value;
		while((signed)_opt < 0) _opt += _max_opt;
		_opt %= _max_opt;
		return NOEXIT;
	case ACT_ENTER:
		switch(_opts[_opt]->action(ACT_BEGIN)){
		case NOEXIT:
			_active = true;
			return NOEXIT;
		case NOEXIT_SAVE:
			_active = true;
			return NOEXIT_SAVE;
		case NOEXIT_CANCEL:
			_active = true;
			return NOEXIT_CANCEL;
		case EXIT:
			return EXIT;
		case EXIT_SAVE:
			return EXIT_CANCEL;
		case EXIT_CANCEL:
			return EXIT_CANCEL;
		case E_NONE:
			return E_NONE;
		}
	case ACT_BACK:
		return EXIT_SAVE;
	case ACT_CTXT:
		return NOEXIT;
	}

}

size_t PickAdjustment::summary_string(char* buf, size_t buf_size){
	snprintf(buf, buf_size, " ... %s", _opt_names[_opt]);
}

size_t PickAdjustment::full_string(char* buf, size_t buf_size){
	size_t written = 0;



	if(_active){
		written += _opts[_opt]->full_string(buf, buf_size);
	} else {
		buf[0] = '>';

		for(size_t i = 0; i < (buf_size / _cols); i++){
			size_t tag = strlcpy(buf+i*_cols+2, _opt_names[(_opt+i)%_max_opt], _cols-2) + 2;
			written += _cols;
		}
	}


	return written;
}