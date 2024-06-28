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


#ifndef EmiR_GSAConfig_h
#define EmiR_GSAConfig_h

#include <Rcpp.h>
using namespace Rcpp;

#include "../Base/Config.h"
#include <string>
#include "../Base/Random.h"

class GSAConfig : public Config {
public:

  /// GSAConfig default constructor
  GSAConfig();

  /// Set the gravitational constant
  void setGrav(double);

  /// Set the parameter that controls evolution in time of m_grav
  void setGravEvolution(double);


  /// Get the gravitational constant
  double getGrav() const;

  /// Get the parameter that controls evolution in time of m_grav
  double getGravEvolution() const;

private:
  double m_beta;
  double m_grav;              /**< Gravitaional constant */
};
#endif
