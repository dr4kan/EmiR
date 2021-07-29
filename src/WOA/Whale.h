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


#ifndef EmiR_Whale_h
#define EmiR_Whale_h

#include "../Base/Individual.h"

class Whale : public Individual {
public:
  /// Empty constructor
  Whale();

  /// Whale default constructor
  Whale(int n);

  friend bool operator<(const Whale& l, const Whale& r) {
    return l.m_cost < r.m_cost;
  }

private:

};

#endif
