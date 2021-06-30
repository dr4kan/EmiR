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


setClass (
  "IHSConfig",

  # Defining slot type
  slots = c(
    iterations             = "numeric",
    iterations_same_cost   = "numeric",
    population_size        = "numeric",
    absolute_tol           = "numeric",
    considering_rate       = "numeric",
    min_adjusting_rate     = "numeric",
    max_adjusting_rate     = "numeric",
    min_distance_bandwidth = "numeric",
    max_distance_bandwidth = "numeric"
  ),

  # Initializing slots
  prototype = list(
    iterations             = as.integer(NULL),
    iterations_same_cost   = as.integer(NULL),
    population_size        = as.integer(NULL),
    absolute_tol           = as.double(NULL),
    considering_rate       = as.double(NULL),
    min_adjusting_rate     = as.double(NULL),
    max_adjusting_rate     = as.double(NULL),
    min_distance_bandwidth = as.double(NULL),
    max_distance_bandwidth = as.double(NULL)
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "IHSConfig",
          definition = function(object) {
            cat("          BAT minimizer options\n")
            cat("             iterations:", object@iterations, "\n")
            cat("   iterations same cost:", object@iterations_same_cost, "\n")
            cat("        population size:", object@population_size, "\n")
            cat("           absolute_tol:", object@absolute_tol, "\n")
            cat("       considering rate:", object@hmcr, "\n")
            cat("     min adjusting rate:", object@min_adjusting_rate, "\n")
            cat("     max adjusting rate:", object@max_adjusting_rate, "\n")
            cat(" min distance bandwidth:", object@min_distance_bandwidth, "\n")
            cat(" max distance bandwidth:", object@max_distance_bandwidth, "\n")
          }
)
