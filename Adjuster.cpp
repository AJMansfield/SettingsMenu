#include "Adjuster.h"



void DummyAdjuster::adjust(const int delta){
  if(chain != nullptr)
    chain->adjust(delta);
}