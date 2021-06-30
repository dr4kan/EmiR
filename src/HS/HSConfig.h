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


#ifndef EmiR_HSConfig_h
#define EmiR_HSConfig_h

#include "../Base/Config.h"

class HSConfig : public Config {
public:
  /// HSConfig default constructor
  HSConfig();

  void setHmcr(double);

  void setPar(double);

  void setBw(double);

  double getHmcr() const;

  double getPar() const;

  double getBw() const;

private:
  double m_hmcr;            /**< Harmony memory considering rate */
  double m_par;             /**< Pitch adjusting rate */
  double m_bw;              /**< Distance bandwidth */
};

#endif
