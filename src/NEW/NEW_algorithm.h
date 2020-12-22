#ifndef EmiR_NEW_algorithm_h
#define EmiR_NEW_algorithm_h

#include "../Base/Algorithm.h"
#include "NEWConfig.h"
#include "NEWPopulation.h"

class NEW_algorithm : public Algorithm {
public:
  NEW_algorithm(Function, S4);

  void minimize();

  void addPopulationPosition();

  S4 getResults();

private:

  NEWConfig m_algo_config;
  size_t m_iter;
  NEWPopulation m_population;
};

#endif
