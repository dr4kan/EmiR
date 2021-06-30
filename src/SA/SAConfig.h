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

  /// Set the initial temperature
  void setT0(double t);

  void setNs(size_t t);

  void setNt(size_t t);

  void setC(size_t t);

  void setRt(double t);

  /// Return the initial temperature
  double getT0() const;

  size_t getNs() const;

  size_t getNt() const;

  size_t getC() const;

  double getRt() const;


  //AnnealingSchedule getAnnealingSchedule() const;

private:
  double              m_T0;    /**< Initial temperature */
  size_t              m_Ns;   /**< Maximum number of cycles before step variation  */
  size_t              m_C;    /**< Step criterion  */
  size_t              m_Nt;   /**< Maximum number of cycles before temperature variation  */
  size_t              m_Rt;   /**< Reduction coefficient for temperature  */
  };
#endif
