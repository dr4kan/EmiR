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
  "CSConfig",

  # Defining slot type
  slots = c(
    iterations           = "numeric",
    iterations_same_cost = "numeric",
    population_size      = "numeric",
    absolute_tol         = "numeric",
    discovery_rate       = "numeric",
    step_size            = "numeric"
  ),

  # Initializing slots
  prototype = list(
    iterations           = as.integer(NULL),
    iterations_same_cost = as.integer(NULL),
    population_size      = as.integer(NULL),
    absolute_tol         = as.double(NULL),
    discovery_rate       = as.double(NULL),
    step_size            = as.double(NULL)
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "CSConfig",
          definition = function(object) {
            cat("         CS minimizer options\n")
            cat("          iterations:", object@iterations, "\n")
            cat("iterations_same_cost:", object@iterations_same_cost, "\n")
            cat("     population_size:", object@population_size, "\n")
            cat("        absolute_tol:", object@absolute_tol, "\n")
            cat("      discovery_rate:", object@discovery_rate, "\n")
            cat("           step_size:", object@step_size, "\n")
          }
)
