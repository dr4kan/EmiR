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


#ifndef EmiR_Utility_h
#define EmiR_Utility_h

#include <sstream>
#include <limits>
#include <math.h>
#include <numeric>

class Utility {
public:

  /// Check if two numbers are approximately equal
  template<typename T>
  static typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type areEqual(T x, T y, int ulp = 2) {
    return fabs(x-y) <= std::numeric_limits<T>::epsilon() * fabs(x+y) * ulp
    || fabs(x-y) < std::numeric_limits<T>::min();
  }

  template<typename T>
  static int sgn(T val) {
    return (T(0) < val) - (val < T(0));
  }

  /// Center-align a string within a field of specified width
  static std::string centerAlign(const std::string s, const int w) {
    std::stringstream ss, spaces;
    int padding = w - s.size();
    for(int i=0; i<padding/2; ++i) spaces << " ";
    ss << spaces.str() << s << spaces.str();
    if (padding>0 && padding%2!=0) ss << " ";
    return ss.str();
  };

  /// Right-align a string within a field of specified width
  static std::string rightAlign(const std::string s, const int w) {
    std::stringstream ss, spaces;
    int padding = w - s.size();
    for(int i=0; i<padding; ++i) spaces << " ";
    ss << spaces.str() << s;
    return ss.str();
  };

  /// Left-align a string within a field of specified width
  static std::string leftAlign(const std::string s, const int w) {
    std::stringstream ss, spaces;
    int padding = w - s.size();
    for(int i=0; i<padding; ++i) spaces << " ";
    ss << s << spaces.str();
    return ss.str();
  };

  /// Convert a double to string
  static std::string toStringScientific(double d) {
    std::stringstream ss;
    ss << std::scientific << d;
    return ss.str();
  };

  /// Return the magnitude (norm) of a vector
  template<typename T>
  static double magnitude(const std::vector<T>& t) {
    return sqrt(inner_product(t.begin(), t.end(), t.begin(), 0.0L));
  }
  //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

};
#endif
