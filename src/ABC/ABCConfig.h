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


#ifndef EmiR_ABCConfig_h
#define EmiR_ABCConfig_h

#include "../Base/Config.h"

class ABCConfig : public Config {
public:
  /// ABCConfig default constructor
  ABCConfig();

  /// Set the fraction of onlooker bees in the colony
  void setEmployedFraction(double);

  /// Set the number of scout bees
  void setNScoutBees(size_t);

  double getEmployedFraction();

  size_t getNScoutBees();

private:
  double m_frac_employed;
  size_t m_n_scout;
};

#endif
