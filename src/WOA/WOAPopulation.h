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


#ifndef EmiR_WOAPopulation_h
#define EmiR_WOAPopulation_h

#include "Whale.h"
#include "WOAConfig.h"
#include "../Base/Population.h"

class WOAPopulation : public Population {
public:

  //// Common methods ///////////////////////////////////////
  WOAPopulation(Function);

  void init();

  void setConfig(const WOAConfig&);

  /// Access the specified whale
  Whale &operator[](std::size_t t) { return m_individuals[t]; };

  /// Return the position of all whales
  std::vector<std::vector<double> > getPopulationPosition();

  /// Return the size of the population
  std::size_t getSize() {return m_individuals.size();};

  /// Return the best whale
  Whale* getBestSolution();

  void evaluate();

  void evaluate(Whale&);
  ///////////////////////////////////////////////////////////

  //// Specific methods /////////////////////////////////////
  void moveWhales();

  void updateParameters(std::size_t);

private:

  WOAConfig          m_config;     /**< Configuration */
  std::vector<Whale> m_individuals;     /**< Whales in the population */
  Whale              m_best_solution; /**< Best whale */
  double             m_a;
  double             m_a2;
};

#endif
