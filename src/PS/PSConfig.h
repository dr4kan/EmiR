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


#ifndef EmiR_PSConfig_h
#define EmiR_PSConfig_h

#include <Rcpp.h>
using namespace Rcpp;

#include "../Base/Config.h"
#include <string>
#include "../Base/Random.h"

class PSConfig : public Config {
public:

  /// PSConfig default constructor
  PSConfig();

  void setAlpha(NumericVector);

  void setAlphaEvolution(double);

  /// Set the initial parameters
  void setCognitiveParameter(double);

  void setSocialParameter(double);

  void setInertia(double);

  NumericVector getAlpha() const;

  double getAlphaEvolution() const;

  /// Return the initial parameters
  double getCognitiveParameter() const;

  double getSocialParameter() const;

  double getInertia() const;

private:

  NumericVector m_alpha;                /**< Maximum velocity in % of the range of parameters */
  double        m_h;                    /**< Parameter involved in updating velocities with iterations */
  double        m_social;               /**< Social parameter */
  double        m_cognitive;            /**< Cognitive parameter */
  double        m_inertia;              /**< Inertia factor */
};
#endif
