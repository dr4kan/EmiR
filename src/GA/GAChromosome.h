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


#ifndef EmiR_GAChromosome_h
#define EmiR_GAChromosome_h

#include "../Base/Individual.h"

class GAChromosome : public Individual {
public:
  /// Empty constructor
  GAChromosome();

  /// Chromosome default constructor
  GAChromosome(int n);

  /// Set the value of the indicator equal to 1;
  void setIndicatorUp();

  /// Set the value of the indicator equal to 0
  void setIndicatorDown();

  double getIndicator() const;

private:
   int  m_indicator; /**< When 0 the cost needs to be revaluated */
};

#endif
