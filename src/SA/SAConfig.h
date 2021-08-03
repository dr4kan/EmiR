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


#ifndef EmiR_SAConfig_h
#define EmiR_SAConfig_h

#include "../Base/Config.h"
#include <string>

class SAConfig : public Config {
public:

  /// SAConfig default constructor
  SAConfig();

  void setT0(double t);

  void setNs(std::size_t t);

  void setNt(std::size_t t);

  void setC(std::size_t t);

  void setRt(double t);

  void setWmax(double t);

  void setWmin(double t);

  void setRouletteWheel();

  double getT0() const;

  std::size_t getNs() const;

  std::size_t getNt() const;

  std::size_t getC() const;

  double getRt() const;

  double getWmax() const;

  double getWmin() const;

  /// Return m_prob
  double getProb(int) const;


private:
  double              m_T0;    /**< Initial temperature */
  std::size_t              m_Ns;   /**< Maximum number of cycles before step variation  */
  std::size_t              m_C;    /**< Step criterion  */
  std::size_t              m_Nt;   /**< Maximum number of cycles before temperature variation  */
  double              m_Rt;   /**< Reduction coefficient for temperature  */
  double              m_Wmax; /**< Maximum value of the weight employed in the formula for the starting point  */
  double              m_Wmin; /**< Minimum value of the weight employed in the formula for the starting point  */
  std::vector<double> m_Prob; /**< Vector of probabilities used in the Roulette Wheel selection */
  };
#endif
