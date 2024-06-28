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


#ifndef EmiR_SAPopulation_h
#define EmiR_SAPopulation_h

#include "SAParticle.h"
#include "SAConfig.h"
#include "../Base/Population.h"

class SAPopulation : public Population {
public:

  //// Common methods ///////////////////////////////////////
  SAPopulation(Function);

  void init();

  void setConfig(const SAConfig&);

  SAConfig& getConfig() {return m_config;}

  /// Access the specified particle
  SAParticle &operator[](std::size_t t) { return m_individuals[t]; };

  /// Return the position of all particles
  std::vector<std::vector<double> > getPopulationPosition();

  /// Return the size of the population
  std::size_t getSize() {return m_individuals.size();};

  /// Return the best particle
  SAParticle *getBestSolution() {return &m_best_solution;}

  void evaluate(SAParticle&);

  void evaluate();

  void move();

  void setVelocity();

  void setStartingPoint(std::size_t);

  void sort();

private:
  SAConfig                m_config;
  std::vector<SAParticle> m_individuals;
  SAParticle              m_best_solution;
};

#endif
