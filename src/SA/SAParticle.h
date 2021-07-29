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


#ifndef EmiR_SAParticle_h
#define EmiR_SAParticle_h

#include "../Base/Individual.h"

class SAParticle : public Individual {
public:
  /// Empty constructor
  SAParticle();

  /// Sa default constructor
  SAParticle(int n);

  void setVelocity(size_t, double);

  double getVelocity(size_t);

  const std::vector<double>& getBestPositionParticle() const { return m_position_best; };

  double getBestPositionComponent(size_t j);

  double getBestCostParticle();

  void setBest();

  std::vector<size_t> getSuccess();

  void upSuccess(size_t j);

  void resetSuccess();

  friend bool operator<(const SAParticle &l, const SAParticle &r) { return l.m_cost_best < r.m_cost_best; };

private:
  std::vector<size_t> m_success;
  std::vector<double> m_velocity;
  std::vector<double> m_position_best;
  double              m_cost_best;
};

#endif
