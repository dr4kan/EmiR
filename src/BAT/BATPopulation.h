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


#ifndef EmiR_BATPopulation_h
#define EmiR_BATPopulation_h

#include "Bat.h"
#include "BATConfig.h"
#include "../Base/Population.h"

class BATPopulation : public Population {
public:

  //// Common methods ///////////////////////////////////////
  BATPopulation(Function);

  void init();

  void setConfig(const BATConfig&);

  /// Access the specified bat
  Bat &operator[](std::size_t t) { return m_individuals[t]; };

  /// Return the position of all bats
  std::vector<std::vector<double> > getPopulationPosition();

  /// Return the size of the population
  std::size_t getSize() {return m_individuals.size();};

  /// Return the best bat
  Bat* getBestSolution();

  void evaluate();

  void evaluate(Bat&);
  ///////////////////////////////////////////////////////////

  //// Specific methods /////////////////////////////////////
  double getPulseRate() const;

  double getLoudness() const;

  void updateLoudnessAndPulse(std::size_t);

  void moveBats();


private:

  BATConfig           m_config;   /**< Configuration */
  Bat                 m_best_solution;
  std::vector<Bat>    m_individuals;    /**< Bats in the population */
  double              m_loudness;
  double              m_pulse_rate;
};

#endif
