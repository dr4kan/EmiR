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


#ifndef EmiR_Bat_h
#define EmiR_Bat_h

#include "../Base/Individual.h"

class Bat : public Individual {
public:
  /// Empty constructor
  Bat();

  /// Bat default constructor
  Bat(int n);

  /// Set frequency range
  void setFrequency(double);

  /// Set a velocity component
  void setVelocity(size_t, double);

  /// Return a velocity component
  double getVelocity(size_t t);

  /// Return frequency range
  double getFrequency() const;

private:
  std::vector<double> m_velocity;
  double              m_freq;
};

#endif
