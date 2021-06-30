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
  "BATConfig",

  # Defining slot type
  slots = c(
    iterations           = "numeric",
    iterations_same_cost = "numeric",
    population_size      = "numeric",
    absolute_tol         = "numeric",
    initial_loudness     = "numeric",
    alpha                = "numeric",
    initial_pulse_rate   = "numeric",
    gamma                = "numeric",
    freq_min             = "numeric",
    freq_max             = "numeric"
  ),

  # Initializing slots
  prototype = list(
    iterations           = as.integer(NULL),
    iterations_same_cost = as.integer(NULL),
    population_size      = as.integer(NULL),
    absolute_tol         = as.double(NULL),
    initial_loudness     = as.double(NULL),
    alpha                = as.double(NULL),
    initial_pulse_rate   = as.double(NULL),
    gamma                = as.double(NULL),
    freq_min             = as.double(NULL),
    freq_max             = as.double(NULL)
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "BATConfig",
          definition = function(object) {
            cat("         BAT minimizer options\n")
            cat("          iterations:", object@iterations, "\n")
            cat("iterations same cost:", object@iterations_same_cost, "\n")
            cat("     population_size:", object@population_size, "\n")
            cat("        absolute_tol:", object@absolute_tol, "\n")
            cat("    initial loudness:", object@initial_loudness, "\n")
            cat("               alpha:", object@alpha, "\n")
            cat("  initial pulse rate:", object@initial_pulse_rate, "\n")
            cat("               gamma:", object@gamma, "\n")
            cat("            freq min:", object@freq_min, "\n")
            cat("            freq max:", object@freq_max, "\n")
          }
)
