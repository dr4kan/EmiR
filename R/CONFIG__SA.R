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
  "SAConfig",

  # Defining slot type
  slots = c(
    iterations           = "numeric",
    iterations_same_cost = "numeric",
    population_size      = "numeric",
    absolute_tol         = "numeric",
    T0                   = "numeric",
    Ns                   = "numeric",
    c_step               = "numeric",
    Nt                   = "numeric",
    Rt                   = "numeric",
    Wmin                 = "numeric",
    Wmax                 = "numeric"
  ),

  # Initializing slots
  prototype = list(
    iterations           = as.integer(NULL),
    iterations_same_cost = as.integer(NULL),
    population_size      = as.integer(NULL),
    absolute_tol         = as.double(NULL),
    T0                   = as.double(NULL),
    Ns                   = as.integer(NULL),
    c_step               = as.double(NULL),
    Nt                   = as.integer(NULL),
    Rt                   = as.double(NULL),
    Wmin                 = as.double(NULL),
    Wmax                 = as.double(NULL)
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "SAConfig",
          definition = function(object) {
            cat("         SA minimizer options\n")
            cat("number of iterations:", object@iterations, "\n")
            cat("iterations same cost:", object@iterations_same_cost, "\n")
            cat("     population size:", object@population_size, "\n")
            cat("        absolute_tol:", object@absolute_tol, "\n")
            cat("                  T0:", object@T0, "\n")
            cat("                  Ns:", object@Ns, "\n")
            cat("              c_step:", object@c_step, "\n")
            cat("                  Nt:", object@Nt, "\n")
            cat("                  Rt:", object@Rt, "\n")
            cat("                  Wmin:", object@Wmin, "\n")
            cat("                  Wmax:", object@Wmax, "\n")
          }
)
