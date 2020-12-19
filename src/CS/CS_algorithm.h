#ifndef EmiR_CS_algorithm_h
#define EmiR_CS_algorithm_h

#include "../Base/Algorithm.h"
#include "CSConfig.h"
#include "CSPopulation.h"

class CS_algorithm : public Algorithm {
public:
  CS_algorithm(Function, S4);

  void minimize();

  void addPopulationPosition();

  S4 getResults();

private:

  CSConfig m_algo_config;
  size_t m_iter;
  CSPopulation m_population;
};

#endif
