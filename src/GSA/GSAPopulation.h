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


#ifndef EmiR_GSAPopulation_h
#define EmiR_GSAPopulation_h

#include "Planet.h"
#include "GSAConfig.h"
#include "../Base/Population.h"

class GSAPopulation : public Population {
public:

  GSAPopulation(Function);

  void init();

  void setConfig(const GSAConfig&);

  /// Access the specified planet
  Planet &operator[](std::size_t t) { return m_individuals[t]; };

  /// Return the position of all planets
  std::vector<std::vector<double> > getPopulationPosition();

  /// Return the size of the population
  std::size_t getSize() {return m_individuals.size();};

  /// Return the best planet
  Planet* getBestSolution();

  void setMass();

  void setVelocity(std::size_t);

  void move(std::size_t);

  void evaluate();

  void evaluate(Planet&);

  void sort();

private:
  GSAConfig           m_config;
  std::vector<Planet> m_individuals;
  Planet              m_best_solution;
};

#endif
