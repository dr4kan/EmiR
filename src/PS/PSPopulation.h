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


#ifndef EmiR_PSPopulation_h
#define EmiR_PSPopulation_h

#include "PSParticle.h"
#include "PSConfig.h"
#include "../Base/Population.h"

class PSPopulation : public Population {
public:

  //// Common methods ///////////////////////////////////////
  PSPopulation(Function);

  void init();

  void setConfig(const PSConfig&);

  /// Access the specified particle
  PSParticle &operator[](std::size_t t) { return m_individuals[t]; };

  /// Return the position of all particles
  std::vector<std::vector<double> > getPopulationPosition();

  /// Return the size of the population
  std::size_t getSize() {return m_individuals.size();};

  /// Return the best particle
  PSParticle* getBestSolution();

  void evaluate();

  void evaluate(PSParticle&);
  ///////////////////////////////////////////////////////////

  //// Specific methods /////////////////////////////////////
  void setVelocity(std::size_t);

  void moveParticles(std::size_t);

private:
  PSConfig                m_config;
  std::vector<PSParticle> m_individuals;
  PSParticle              m_best_solution;
};

#endif
