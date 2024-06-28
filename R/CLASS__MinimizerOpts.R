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


#' EmiR optimization options
#'
#' \loadmathjax
#' A S4 class storing the options for the optimization algorithms in EmiR.
#'
#' @slot maximize if `TRUE` the objective function is maximized instead of being minimized. Default is `FALSE`.
#' @slot silent_mode if `TRUE` no output to console is generated. Default is `FALSE`.
#' @slot save_pop_history if `TRUE` the position of all individuals in the population at
#' each iteration is stored. This is necessary for functions like `plot_population` and `animate_population`
#' to work. Default is `FALSE`.
#' @slot constrained_method method for constrained optimization. Possible values are:
#' * `"PENALTY"` - Penalty Method: the constrained problem is converted to an unconstrained one,
#' by adding a \emph{penalty function} to the objective function. The penalty function
#' consists of a \emph{penalty parameter} multiplied by a measure of violation of the constraints. The penalty
#' parameter is multiplied by a scale factor (see `penalty_scale`) at every iteration;
#' * `"BARRIER"` - Barrier Method: the value of the objective function is set equal to an arbitrary large
#' positive (or negative in case of maximization) number if any of the constraints is violated;
#' * `"ACCREJ"` - Acceptance-Rejection method: a solution violating any of the constraints is replaced by a
#' randomly generated new one in the feasible region.
#' Default is `"PENALTY"`.
#' @slot penalty_scale scale factor for the \emph{penalty parameter} at each iteration. It should
#' be greater than 1. Default is 10.
#' @slot start_penalty_param initial value of the \emph{penalty parameter}. It should
#' be greater than 0. Default is 2.
#' @slot max_penalty_param maximum value for the \emph{penalty parameter}. It should
#' be greater than 0. Default is 1.e+10.
#' @slot constr_init_pop if `TRUE` the initial population is generated in the \emph{feasible region} only.
#' Default is `TRUE`.
#' @slot oob_solutions strategy to treat out-of-bound solutions. Possible values are:
#' * `"RBC"` - Reflective Boundary Condition: the solution is placed back inside the search domain
#' at a position which is distanced from the boundary as the out-of-bound excess. Depending on the
#' optimization algorithm, the velocity of the corresponding individual of the population could be
#' also inverted;
#' * `"PBC"` - Periodic Boundary Condition: the solution is placed back inside the search domain
#' at a position which is distanced from the \emph{opposite} boundary as the out-of-bound excess;
#' * `"BAB"` - Back At Boundary: the solution is placed back at the boundaries for the out-of-bound
#'  dimensions;
#' * `"DIS"` - Disregard the solution: the solution is replaced by a new one, which is randomly
#' generated in the search space.
#' Default is `"DIS"`.
#' @slot seed seed for the internal random number generator. Accepted values are strictly positive integers.
#' If `NULL` a random seed at each execution is used. Default is `NULL`.
#' @slot initial_population manually specify the position of the initial population. A
#' \mjeqn{n \times d}{n x d} matrix has to be provided, where \mjeqn{n}{n} is the population size
#' and \mjeqn{d}{d} is the number of parameters the objective function is minimized with respect to.
#' @slot generation_function manually specify the function to generate to new solutions.
#' @name MinimizerOpts
#' @rdname MinimizerOpts
setClass (
  "MinimizerOpts",

  # Defining slot type
  slots = c(
    maximize            = "logical",
    silent_mode         = "logical",
    save_pop_history    = "logical",
    constrained_method  = "character",
    penalty_scale       = "numeric",
    start_penalty_param = "numeric",
    max_penalty_param   = "numeric",
    constr_init_pop     = "logical",
    oob_solutions       = "character",
    seed                = "numeric",
    initial_population  = "matrix",
    generation_function = "function"
  ),

  # Initializing slots
  prototype = list(
    maximize            = FALSE,
    silent_mode         = FALSE,
    save_pop_history    = FALSE,
    constrained_method  = "PENALTY",
    penalty_scale       = 10,
    start_penalty_param = 2,
    max_penalty_param   = 1e10,
    constr_init_pop     = TRUE,
    oob_solutions       = "DIS",
    seed                = 0,
    initial_population  = matrix(, nrow = 0, ncol = 0),
    generation_function = as.function(alist(NULL))
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "MinimizerOpts",
          definition = function(object) {
            cat("           maximize: ", object@maximize, sep = "")
            cat("        silent_mode: ", object@silent_mode, sep = "")
            cat("   save_pop_history: ", object@save_pop_history, sep = "")
            cat(" constrained_method: ", object@constrained_method, sep = "")
            cat("      penalty_scale: ", object@penalty_scale, sep = "")
            cat("start_penalty_param: ", object@start_penalty_param, sep = "")
            cat("  max_penalty_param: ", object@max_penalty_param, sep = "")
            cat("    constr_init_pop: ", object@constr_init_pop, sep = "")
            cat("      oob_solutions: ", object@oob_solutions, sep = "")
            cat("               seed: ", object@seed, sep = "")
            if (nrow(object@initial_population) > 0) {
              cat(" initial population: manually set")
            } else {
              cat(" initial population: randomly generated")
            }
            if (object@generation_function != as.function(alist(NULL))) {
              cat("generation function: manually set")
            } else {
              cat("generation function: default")
            }
          }
)
