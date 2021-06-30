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


#ifndef EmiR_Individual_h
#define EmiR_Individual_h

#include <vector>
#include <limits>
#include <iostream>

class Individual {
public:
  /// Empty constructor
  Individual();

  virtual ~Individual() {};

  /// Individual default constructor
  Individual(int n);

  /// Set the cost
  void setCost(double);

  /// Set the positions
  void setPosition(const std::vector<double>&);

  /// Return the the number of dimensions of the search space
  size_t getDimension() const;

  /// Return the position
  std::vector<double>& getPosition() { return m_position; };

  /// Return the parameters
  std::vector<double>& getParameters() { return m_position; };

  /// Return the cost
  double getCost();

  virtual double getVelocity(size_t) {
    return 0.;
  };

  bool hasVelocity() {return m_has_velocity;}

  virtual void setVelocity(size_t, double) {};

  /// Access the specified component
  double &operator[](size_t t) { return m_position[t]; };

  /// Access the specified component
  double operator[](size_t t) const { return m_position[t]; };

  friend bool operator<(const Individual &l, const Individual &r) { return l.m_cost < r.m_cost; };

protected:

  std::vector<double> m_position;
  double              m_cost;
  bool                m_has_velocity;
};

#endif
