###############################################################################
# Emir: EmiR: Evolutionary minimization forR                                  #
# Copyright (C) 2021-2024 Davide Pagano & Lorenzo Sostero                     #
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
  "PSConfig",

  # Defining slot type
  slots = c(
    iterations           = "numeric",
    iterations_same_cost = "numeric",
    population_size      = "numeric",
    absolute_tol         = "numeric",
    cognitive            = "numeric",
    social               = "numeric",
    alpha_vel            = "numeric",
    alpha_evolution      = "numeric",
    inertia              = "numeric"
  ),

  # Initializing slots
  prototype = list(
    iterations           = as.integer(NULL),
    iterations_same_cost = as.integer(NULL),
    population_size      = as.integer(NULL),
    absolute_tol         = as.double(NULL),
    cognitive            = as.double(NULL),
    social               = as.double(NULL),
    alpha_vel            = as.double(NULL),
    alpha_evolution      = as.double(NULL),
    inertia              = as.double(NULL)
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "PSConfig",
          definition = function(object) {
            cat("         PS minimizer options\n")
            cat("          iterations:", object@iterations, "\n")
            cat("iterations_same_cost:", object@iterations_same_cost, "\n")
            cat("     population size:", object@population_size, "\n")
            cat("        absolute_tol:", object@absolute_tol, "\n")
            cat("           cognitive:", object@cognitive, "\n")
            cat("              social:", object@social, "\n")
            cat("             inertia:", object@inertia, "\n")
            cat("     alpha_evolution:", object@alpha_evolution, "\n")
            cat("           alpha_vel:", object@alpha_vel, "\n")
          }
)
