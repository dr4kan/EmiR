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


#ifndef EmiR_Random_h
#define EmiR_Random_h

#include <stdint.h>
#include <math.h>
#include <chrono>
#include <vector>

// Class based on splitmix64 from Sebastiano Vigna
// https://prng.di.unimi.it/
class Random {
private:
  uint64_t m_seed;

public:
  Random();

  Random(uint64_t);

  /// Returns a double number in [0, 1]
  double rand();

  /// Returns a double number in [a, b]
  double rand(double, double);

  /// Returns a vector of double numbers in [a, b]
  std::vector<double> randVector(std::size_t, double, double);

  /// Returns an unsigned integer number in [a, b)
  uint64_t randUInt(uint64_t, uint64_t);

  /// Returns a standard normal distributed random number
  double norm();

  /// Returns a normal distributed random number with specified mean and stardard deviation
  double norm(double, double);

private:
  uint64_t next();
  double toDouble(uint64_t x);
};

#endif
