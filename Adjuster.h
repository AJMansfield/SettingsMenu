#ifndef ADJUSTER_H
#define ADJUSTER_H

#define if_while(x) if ((x)) while ((x))

#include <Arduino.h>


class AdjusterBase {
public:
	virtual ~AdjusterBase(){}
	
	virtual void adjust(const int delta) = 0;

	AdjusterBase * chain;
};

class DummyAdjuster: public AdjusterBase {
public:

	static DummyAdjuster& getInstance(){
		static DummyAdjuster dummy;
		return dummy;
	}

	void adjust(const int delta);

	AdjusterBase * chain;

private:
	DummyAdjuster(AdjusterBase * chain = nullptr): chain(chain) {};
	~DummyAdjuster(){};
};


template<typename T>
class Adjuster : public AdjusterBase {
public:
	AdjusterBase * chain;

	Adjuster(T* variable, T min_value, T max_value, T step_size,
					bool wrap = false, AdjusterBase * chain = &DummyAdjuster::getInstance()):
			chain(chain),
			_var(variable), _min(min_value), _max(max_value), _step(step_size),	_wrap(wrap) {};
	~Adjuster(){};
	
	void adjust(const int delta);
	T* value();

private:
	T * const _var;
	const T _min, _max, _step;
	const bool _wrap;
	T limit(T result);
};


template<typename T>
void Adjuster<T>::adjust(const int delta){
	*_var = limit(*_var + delta * _step);
}

template<typename T>
T Adjuster<T>::limit(T result){
	if (result < _min) {
		chain->adjust(-1);
	} else if (result >= _max){
		chain->adjust(1);
	}

	if(_wrap){
		if (result < _min) {
			result = _max - (_min - result) % (_max - _min);
		} else { //} (result >= _max){
			result = _min + (result - _min) % (_max - _min);
		}

	} else {
		result = constrain(result, _min, _max-1);
	}
	return result;
}

template<typename T>
T* Adjuster<T>::value(){
	return _var;
}

#endif // ADJUSTER_H