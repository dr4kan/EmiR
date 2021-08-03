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


#ifndef EmiR_GAPopulation_h
#define EmiR_GAPopulation_h

#include "GAChromosome.h"
#include "GAConfig.h"
#include "../Base/Population.h"

class GAPopulation : public Population {
public:

  //// Common methods ///////////////////////////////////////
  GAPopulation(Function);

  void init();

  void setConfig(const GAConfig&);

  /// Access the specified chromosome
  GAChromosome &operator[](std::size_t t) { return m_individuals[t]; };

  /// Return the position of all chromosomes
  std::vector<std::vector<double> > getPopulationPosition();

  /// Return the size of the population
  std::size_t getSize() {return m_individuals.size();};

  /// Return the best chromosome
  GAChromosome* getBestSolution();

  void evaluate();

  void evaluate(GAChromosome&);
  ///////////////////////////////////////////////////////////

  //// Specific methods /////////////////////////////////////
  void sort();

  void crossover();

  void mutation();

private:
  GAConfig                  m_config;
  std::vector<GAChromosome> m_individuals;
  GAChromosome              m_best_solution;
};

#endif
