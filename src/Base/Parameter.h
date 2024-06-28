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


#ifndef EmiR_Parameter_h
#define EmiR_Parameter_h

#include <string>
#include "Random.h"

class Parameter {
public:

  /// Constructor with all parameters
  Parameter(const std::string&, double, double, bool = false);

  /// Empty constructor
  Parameter();

  /// Constructor with specified name for the parameter
  Parameter(const std::string&);

  /// Set the name of the parameter
  void setName(const std::string&);

  /// Set the range on the parameter
  void setRange(double,  double);

  /// Set integer parameter
  void setIsInteger(bool);

  /// Return the name of the parameter
  const std::string& getName() const;

  /// Return the min value of the range
  double getMin() const;

  /// Return the min value of the range
  double getMax() const;

  /// Return the width of the range
  double getWidth() const;

  /// Return if the parameter is constrained to be integer
  bool isInteger() const;

private:
  std::string  m_name;    /**< Name of the parameter */
  double       m_min_val; /**< Minimum value of the range */
  double       m_max_val; /**< Maximum value of the range */
  bool         m_integer; /**< If TRUE the parameter is constrained to be integer */
};
#endif
