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
  "ABCConfig",

  # Defining slot type
  slots = c(
    iterations           = "numeric",
    iterations_same_cost = "numeric",
    population_size      = "numeric",
    absolute_tol         = "numeric",
    employed_frac        = "numeric",
    n_scout              = "numeric"
  ),

  # Initializing slots
  prototype = list(
    iterations           = as.integer(NULL),
    iterations_same_cost = as.integer(NULL),
    population_size      = as.integer(NULL),
    absolute_tol         = as.double(NULL),
    employed_frac        = as.double(NULL),
    n_scout              = as.integer(NULL)
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "ABCConfig",
          definition = function(object) {
            cat("           BAT minimizer options\n")
            cat("            iterations:", object@iterations, "\n")
            cat("  iterations same cost:", object@iterations_same_cost, "\n")
            cat("       population_size:", object@population_size, "\n")
            cat("          absolute_tol:", object@absolute_tol, "\n")
            cat("fraction employed bees:", object@employed_frac, "\n")
            cat("  number of scout bees:", object@n_scout, "\n")
          }
)
