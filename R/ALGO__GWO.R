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


#' Configuration object for the Grey Wolf Optimizer Algorithm
#'
#' Create a configuration object for the Grey Wolf Optimizer Algorithm (GWO). At minimum the number of iterations
#' (parameter `iterations`) and the number of wolves (parameter `population_size`) have
#' to be provided.
#'
#' @param iterations maximum number of iterations.
#' @param population_size number of wolves.
#' @param iterations_same_cost maximum number of consecutive iterations with the \emph{same}
#' (see the parameter `absolute_tol`) best cost before ending the minimization. If `NULL` the
#' minimization continues for the number of iterations specified by the parameter `iterations`.
#' Default is `NULL`.
#' @param absolute_tol absolute tolerance when comparing best costs from consecutive iterations.
#' If `NULL` the machine epsilon is used. Default is `NULL`.
#' @return `config_gwo` returns an object of class `GWOConfig`.
#' @importFrom Rdpack reprompt
#' @references \insertRef{Mirjalili2014}{EmiR}
#' @export
#'
#' @examples
#' conf <- config_gwo(iterations = 100, population_size = 50, iterations_same_cost = NULL,
#' absolute_tol = NULL)
#'
config_gwo <- function(iterations,
                       population_size,
                       iterations_same_cost = NULL,
                       absolute_tol         = NULL) {
  p <- new("GWOConfig")
  commonOpt              <- checkCommonConfigOptions(iterations, population_size, iterations_same_cost, absolute_tol)
  p@iterations           <- commonOpt$iterations
  p@population_size      <- commonOpt$population_size
  p@iterations_same_cost <- commonOpt$iterations_same_cost
  p@absolute_tol         <- commonOpt$absolute_tol

  return(p)
}

check_algo_options_gwo <- function(p, ...) {
  config_options <- list(...)
  if (length(config_options) == 0) return(p)
  for (i in 1:length(config_options)) {
    stop(paste0("Unknown option '", names(config_options[i]), "' for algorithm GWO."))
  }
  return(p)
}
