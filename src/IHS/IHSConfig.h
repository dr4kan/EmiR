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


#ifndef EmiR_IHSConfig_h
#define EmiR_IHSConfig_h

#include "../Base/Config.h"

class IHSConfig : public Config {
public:
  /// IHSConfig default constructor
  IHSConfig();

  void setHmcr(double);

  void setParMin(double);

  void setParMax(double);

  void setBwMin(double);

  void setBwMax(double);

  double getHmcr() const;

  double getParMin() const;

  double getParMax() const;

  double getBwMin() const;

  double getBwMax() const;

private:
  double m_hmcr;    /**< Harmony memory considering rate */
  double m_par_min; /**< Minimum pitch adjusting rate */
  double m_par_max; /**< Maximum pitch adjusting rate */
  double m_bw_min;  /**< Minumum distance bandwidth */
  double m_bw_max;  /**< Maximum distance bandwidth */
};

#endif
