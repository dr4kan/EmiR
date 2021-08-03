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


#ifndef EmiR_IHSPopulation_h
#define EmiR_IHSPopulation_h

#include "../Base/Individual.h"
#include "IHSConfig.h"
#include "../Base/Population.h"

class IHSPopulation : public Population {
public:

  //// Common methods ///////////////////////////////////////
  IHSPopulation(Function);

  void init();

  void setConfig(const IHSConfig&);

  /// Access the specified individual
  Individual &operator[](std::size_t t) { return m_individuals[t]; };

  /// Return the position of all individuals
  std::vector<std::vector<double> > getPopulationPosition();

  /// Return the size of the population
  std::size_t getSize() {return m_individuals.size();};

  /// Return the best individual
  Individual* getBestSolution();

  void evaluate();

  void evaluate(Individual&);
  ///////////////////////////////////////////////////////////

  //// Specific methods /////////////////////////////////////
  void updateParameters(std::size_t);

  void generateNewHarmony();

  void sort();

private:
  IHSConfig                m_config;
  std::vector<Individual>  m_individuals;
  double                   m_current_par;
  double                   m_current_bw;
  Individual               m_best_solution; /**< Best harmony */
};

#endif
