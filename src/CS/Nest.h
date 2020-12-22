#ifndef EmiR_Nest_h
#define EmiR_Nest_h

#include "../Base/Individual.h"

class Nest : public Individual {
public:
  /// Empty constructor
  Nest();

  /// Bat default constructor
  Nest(int n);

  Nest& operator=(const Nest& rhs) {
    if (this != &rhs) {
      m_position = rhs.m_position;
      m_cost     = rhs.m_cost;
    }
    return *this;
  };

private:

};

#endif
