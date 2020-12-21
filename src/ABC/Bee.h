#ifndef EmiR_Bee_h
#define EmiR_Bee_h

#include "../Base/Individual.h"

class Bee : public Individual {
public:
  /// Empty constructor
  Bee();

  /// Bat default constructor
  Bee(int n);

private:
  // for onlooker bee
  std::vector<double> m_best_solution; // for onlooker bee
  double              m_best_cost;

};

#endif
