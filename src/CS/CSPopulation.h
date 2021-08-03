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


#ifndef EmiR_CSPopulation_h
#define EmiR_CSPopulation_h

#include "Nest.h"
#include "CSConfig.h"
#include "../Base/Population.h"

class CSPopulation : public Population {
public:

  //// Common methods ///////////////////////////////////////
  CSPopulation(Function);

  void init();

  void setConfig(const CSConfig&);

  /// Access the specified nest
  Nest &operator[](std::size_t t) { return m_individuals[t]; };

  /// Return the position of all nests
  std::vector<std::vector<double> > getPopulationPosition();

  /// Return the size of the population
  std::size_t getSize() {return m_individuals.size();};

  /// Return the best nest
  Nest* getBestSolution();

  void evaluate();

  void evaluate(Nest&);
  ///////////////////////////////////////////////////////////

  //// Specific methods /////////////////////////////////////
  void generateCuckooEgg();

  void sort();


private:
  CSConfig          m_config;
  std::vector<Nest> m_individuals;
  Nest              m_best_solution; /**< Best nest */
};

#endif
