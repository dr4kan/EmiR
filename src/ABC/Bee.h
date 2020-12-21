#ifndef EmiR_Bee_h
#define EmiR_Bee_h

#include "../Base/Individual.h"

class Bee : public Individual {
public:
  /// Empty constructor
  Bee();

  /// Bat default constructor
  Bee(int n);

  double getFitness();

private:

};

#endif
