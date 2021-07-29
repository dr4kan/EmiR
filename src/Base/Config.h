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


#ifndef EmiR_Config_h
#define EmiR_Config_h

#include <vector>

class Config {
public:
  /// Config default constructor
  Config();

  /// Set the maximum number of iterations
  void setNMaxIterations(size_t);

  /// Set the maximum difference in between consecutive iterations to be considered to have the same cost
  void setAbsoluteTol(double);

  /// Set the maximum number of consecutive iterations with approximately the same cost
  void setNMaxIterationsAtSameCost(size_t);

  /// Set the number of individuals in the population
  void setPopulationSize(size_t);

  /// Return the maximum number of iterations
  size_t getNMaxIterations() const;

  /// Return the maximum difference in between consecutive iterations to be considered to have the same cost
  double getAbsoluteTol() const;

  /// Return the maximum number of consecutive iterations with the same cost
  size_t getNMaxIterationsSameCost() const;

  /// Return the number of individuals in the population
  size_t getPopulationSize() const;

protected:
  int    m_nmax_iter;       /**< Maximum number of iterations */
  double m_absolute_tol;    /**< Maximum difference in between consecutive iterations to be considered to have the same cost */
  int    m_nmax_iter_scost; /**< Maximum number of consecutive iterations with approximately the same cost */
  int    m_nparticles;      /**< Number of individuals in the population */

};

#endif
