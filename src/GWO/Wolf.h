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


#ifndef EmiR_Wolf_h
#define EmiR_Wolf_h

#include "../Base/Individual.h"

class Wolf : public Individual {
public:
  /// Empty constructor
  Wolf();

  /// Wolf default constructor
  Wolf(int n);

  friend bool operator<(const Wolf& l, const Wolf& r) {
    return l.m_cost < r.m_cost;
  }

private:

};

#endif
