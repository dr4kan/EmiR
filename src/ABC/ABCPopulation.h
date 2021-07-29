/*
###############################################################################
# Emir: EmiR: Evolutionary minimization forR                                  #
# Copyright (C) 2021 Davide Pagano & Lorenzo Sostero                          #
#                                                                             #
# This program is free software: you can redistribute it and/or modify        #
# it under the terms of the GNU General Public License as published by        #
# the Free Software Foundation, either version 3 of the License, or           #
# any later version.                                                          #
#                                                                             #
# This program is distributed in the hope that it will be useful, but         #
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY  #
# or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License    #
# for more details: <https://www.gnu.org/licenses/>.                          #
###############################################################################
*/


#ifndef EmiR_ABCPopulation_h
#define EmiR_ABCPopulation_h

#include "Bee.h"
#include "ABCConfig.h"
#include "../Base/Population.h"

class ABCPopulation : public Population {
public:

  //// Common methods ///////////////////////////////////////
  ABCPopulation(Function);

  void init();

  void setConfig(const ABCConfig&);

  /// Access the specified bee
  Bee &operator[](size_t t) { return m_individuals[t]; };

  /// Return the position of all bees
  std::vector<std::vector<double> > getPopulationPosition();

  /// Return the size of the population
  size_t getSize() {return m_individuals.size();};

  /// Return the best bee
  Bee* getBestSolution();

  void evaluate();

  void evaluate(Bee&);
  ///////////////////////////////////////////////////////////

  //// Specific methods /////////////////////////////////////
  void employedBeesEvaluation();

  void onlookerBeesEvaluation();


private:
  void generateSolution(Bee&, size_t);

  void computeProbabilities();

  /// Return a random integer in [0, pop_size-1] different from the passed value
  size_t getRandomPopulationIndex(size_t);

  // there is only one artificial employed bee for each food source

  ABCConfig           m_config;
  std::vector<Bee>    m_individuals; // the size of the entire colony
  std::vector<double> m_prob;
  std::vector<int>    m_trial;
  size_t              m_onlookers;
  size_t              m_scouters;
  double              m_fitness_sum;
  size_t              m_limit_scout; // limit for scout
  Bee                 m_best_solution;
};

#endif
