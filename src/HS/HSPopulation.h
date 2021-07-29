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


#ifndef EmiR_HSPopulation_h
#define EmiR_HSPopulation_h

#include "../Base/Individual.h"
#include "HSConfig.h"
#include "../Base/Population.h"

class HSPopulation : public Population {
public:

  //// Common methods ///////////////////////////////////////
  HSPopulation(Function);

  void init();

  void setConfig(const HSConfig&);

  /// Access the specified individual
  Individual &operator[](size_t t) { return m_individuals[t]; };

  /// Return the position of all individuals
  std::vector<std::vector<double> > getPopulationPosition();

  /// Return the size of the population
  size_t getSize() {return m_individuals.size();};

  /// Return the best individual
  Individual* getBestSolution();

  void evaluate();

  void evaluate(Individual&);
  ///////////////////////////////////////////////////////////

  //// Specific methods /////////////////////////////////////
  void generateNewHarmony();

  void sort();

private:
  HSConfig                m_config;
  std::vector<Individual> m_individuals;
  Individual              m_best_solution; /**< Best harmony */
};

#endif
