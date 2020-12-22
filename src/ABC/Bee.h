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

  Bee& operator=(const Bee& rhs) {
    if (this != &rhs) {
      m_position = rhs.m_position;
      m_cost = rhs.m_cost;
    }
    return *this;
  };

private:

};

#endif
