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


#' EmiR optimization results
#'
#' A S4 class storing all relevant data from an optimization with EmiR.
#'
#' @slot algorithm the name of the algorithm.
#' @slot iterations the number of iterations.
#' @slot population_size the number of individuals in the population.
#' @slot obj_function the minimized/maximized objective function.
#' @slot constraints the constraints the objective function is subjected to.
#' @slot best_cost the best value of the objective function found.
#' @slot best_parameters the parameter values for which the best cost was obtained.
#' @slot parameter_range the range on the parameters.
#' @slot pop_history list containing the positions of all individuals in the
#' population at each iteration. The list is filled only if `save_pop_history`
#' is `TRUE` in the options of the minimizer (see \link[EmiR]{MinimizerOpts}).
#' @slot cost_history the vector storing the best value of the objective function at
#' each iteration.
#' @slot exec_time_sec the execution time in seconds.
#' @slot is_maximization if `TRUE` the objective function has been maximized insted of
#' being minimized.
#'
#' @name OptimizationResults
#' @rdname OptimizationResults
setClass (
  "OptimizationResults",

  # Defining slot type
  slots = c(
    algorithm       = "character",
    iterations      = "numeric",
    population_size = "numeric",
    obj_function    = "function",
    constraints     = "list",
    best_cost       = "numeric",
    best_parameters = "vector",
    parameter_names = "vector",
    parameter_range = "vector",
    pop_history     = "list",
    cost_history    = "vector",
    exec_time_sec   = "numeric",
    is_maximization = "logical"
  ),

  # Initializing slots
  prototype = list(
    algorithm       = as.character(NULL),
    iterations      = as.numeric(NULL),
    population_size = as.numeric(NULL),
    obj_function    = NULL,
    constraints     = list(),
    best_cost       = as.numeric(NULL),
    best_parameters = as.vector(NULL),
    parameter_names = as.vector(NULL),
    parameter_range = as.vector(NULL),
    pop_history     = list(),
    cost_history    = as.vector(NULL),
    exec_time_sec   = as.numeric(NULL),
    is_maximization = FALSE
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "OptimizationResults",
          definition = function(object) {
            cat("\n")
            cat("         EmiR Minimization Results \n")
            cat("  --------------------------------------- \n")
            cat("           minimizer | ", object@algorithm, "\n", sep = "")
            cat("          iterations | ", object@iterations, "\n", sep = "")
            cat("     population size | ", object@population_size, "\n", sep = "")
            if (object@is_maximization) {
              cat("       maximum value | ", object@best_cost, "\n", sep = "")
            } else {
              cat("       minimum value | ", object@best_cost, "\n", sep = "")
            }
            cat("     best parameters | ")
            for (i in 1:length(object@best_parameters)) {
              if (i == 1) {
                cat(object@parameter_names[i], " = ", object@best_parameters[i], "\n", sep = "")
              } else {
                cat("                     | ", object@parameter_names[i], " = ", object@best_parameters[i], "\n", sep = "")
              }
            }
            cat("  --------------------------------------- \n")
          }
)
