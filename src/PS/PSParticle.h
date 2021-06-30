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


#ifndef EmiR_PSParticle_h
#define EmiR_PSParticle_h

#include "../Base/Individual.h"
#include <vector>

class PSParticle : public Individual {
public:
  /// Empty constructor
  PSParticle();

  /// Particle Swarm default constructor
  PSParticle(int n);

  /// Update the best position and particle
  void setPersonalBest();

  void setVelocity(size_t, double);

  double getVelocity(size_t);

  double& getVelocityAddress(size_t t) { return m_velocity[t]; };

  double getBestPositionParticle(size_t);

  const std::vector<double>& getBestPositionParticle() const { return m_position_best; };

  friend bool operator<(const PSParticle &l, const PSParticle &r) { return l.m_cost_best < r.m_cost_best; };

private:
  std::vector<double> m_velocity;
  std::vector<double> m_position_best;
  double              m_cost_best;
};

#endif
