#ifndef EmiR_HS_algorithm_h
#define EmiR_HS_algorithm_h

#include "HSPopulation.h"

class HS_algorithm : public Algorithm {
public:
  HS_algorithm(Function, S4);

  void minimize();

  void addPopulationPosition();

  S4 getResults();

private:

  HSConfig m_algo_config;
  size_t m_iter;
  HSPopulation m_population;
};

#endif
