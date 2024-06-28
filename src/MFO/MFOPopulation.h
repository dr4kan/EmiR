/*
###############################################################################
# Emir: EmiR: Evolutionary minimization forR                                  #
# Copyright (C) 2021-2024 Davide Pagano & Lorenzo Sostero                     #
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


#ifndef EmiR_MFOPopulation_h
#define EmiR_MFOPopulation_h

#include "Moth.h"
#include "MFOConfig.h"
#include "../Base/Population.h"

class MFOPopulation : public Population {
public:

  //// Common methods ///////////////////////////////////////
  MFOPopulation(Function);

  void init();

  void setConfig(const MFOConfig&);

  /// Access the specified moth
  Moth &operator[](std::size_t t) { return m_individuals[t]; };

  /// Return the position of all moths
  std::vector<std::vector<double> > getPopulationPosition();

  /// Return the size of the population
  std::size_t getSize() {return m_individuals.size();};

  /// Return the best moth
  Moth* getBestSolution();

  void evaluate();

  void evaluate(Moth&);
  ///////////////////////////////////////////////////////////

  //// Specific methods /////////////////////////////////////

  /// Flames are the best moth
  void createFlames();

  void updateParameters(std::size_t);

  void moveMoths();

private:

  MFOConfig          m_config;       /**< Configuration */
  std::vector<Moth>  m_individuals;  /**< Moths in the population */
  std::vector<Moth>  m_flames;       /**< Moths in the population */
  Moth               m_best_solution;
  double             m_a;
  std::size_t             m_n_flame;
};

#endif
