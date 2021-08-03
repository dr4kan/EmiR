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


#ifndef EmiR_GWOPopulation_h
#define EmiR_GWOPopulation_h

#include "Wolf.h"
#include "GWOConfig.h"
#include "../Base/Population.h"

class GWOPopulation : public Population {
public:

  //// Common methods ///////////////////////////////////////
  GWOPopulation(Function);

  void init();

  void setConfig(const GWOConfig&);

  /// Access the specified wolf
  Wolf &operator[](std::size_t t) { return m_individuals[t]; };

  /// Return the position of all wolves
  std::vector<std::vector<double> > getPopulationPosition();

  /// Return the size of the population
  std::size_t getSize() {return m_individuals.size();};

  /// Return the best wolf
  Wolf* getBestSolution();

  void evaluate();

  void evaluate(Wolf&);
  ///////////////////////////////////////////////////////////

  //// Specific methods /////////////////////////////////////
  void updateAParameter(std::size_t);

  void moveWolves();

private:

  GWOConfig         m_config;    /**< Configuration */
  Wolf              m_alpha;
  Wolf              m_beta;
  Wolf              m_delta;
  std::vector<Wolf> m_individuals;    /**< Wolves in the population */
  double            m_a;
  Wolf              m_best_solution;
};

#endif
