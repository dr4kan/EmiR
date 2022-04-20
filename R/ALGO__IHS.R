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


#' Configuration object for the Improved Harmony Search Algorithm
#'
#' Create a configuration object for the Improved Harmony Search Algorithm (IHS).
#' At minimum the number of iterations (parameter `iterations`) and the number of
#' solutions in the harmony memory (parameter `population_size`) have to be provided.
#'
#' @param iterations maximum number of iterations.
#' @param population_size number of solutions in the harmony memory.
#' @param iterations_same_cost maximum number of consecutive iterations with the \emph{same}
#' (see the parameter `absolute_tol`) best cost before ending the minimization. If `NULL` the
#' minimization continues for the number of iterations specified by the parameter `iterations`.
#' Default is `NULL`.
#' @param absolute_tol absolute tolerance when comparing best costs from consecutive iterations.
#' If `NULL` the machine epsilon is used. Default is `NULL`.
#' @param considering_rate probability for each component of a newly generated solution
#'  to be recalled from the harmony memory.
#' @param min_adjusting_rate minimum value of the pitch adjustment probability.
#' @param max_adjusting_rate maximum value of the pitch adjustment probability.
#' @param min_distance_bandwidth minimum amplitude of the random pitch adjustment.
#' @param max_distance_bandwidth maximum amplitude of the random pitch adjustment.
#' @return `config_ihs` returns an object of class `IHSConfig`.
#' @importFrom Rdpack reprompt
#' @references \insertRef{Mahdavi2007}{EmiR}
#' @export
#'
#' @examples
#' conf <- config_ihs(iterations = 100, population_size = 50, iterations_same_cost = NULL,
#' absolute_tol = NULL,considering_rate = 0.5, min_adjusting_rate = 0.3,
#' max_adjusting_rate = 0.99, min_distance_bandwidth = 0.0001, max_distance_bandwidth = 1)
#'
config_ihs <- function(iterations,
                       population_size,
                       iterations_same_cost   = NULL,
                       absolute_tol           = NULL,
                       considering_rate       = 0.5,
                       min_adjusting_rate     = 0.3,
                       max_adjusting_rate     = 0.99,
                       min_distance_bandwidth = 0.0001,
                       max_distance_bandwidth = 1) {
  p <- new("IHSConfig")
  commonOpt              <- checkCommonConfigOptions(iterations, population_size, iterations_same_cost, absolute_tol)
  p@iterations           <- commonOpt$iterations
  p@population_size      <- commonOpt$population_size
  p@iterations_same_cost <- commonOpt$iterations_same_cost
  p@absolute_tol         <- commonOpt$absolute_tol

  p@considering_rate       <- considering_rate
  p@min_adjusting_rate     <- min_adjusting_rate
  p@max_adjusting_rate     <- max_adjusting_rate
  p@min_distance_bandwidth <- min_distance_bandwidth
  p@max_distance_bandwidth <- max_distance_bandwidth
  return(p)
}

check_algo_options_ihs <- function(p, ...) {
  config_options <- list(...)
  if (length(config_options) == 0) return(p)
  for (i in 1:length(config_options)) {
    if (names(config_options[i]) == "considering_rate") {
      p@considering_rate      <- config_options[[i]]
    } else if (names(config_options[i]) == "adjusting_rate") {
      p@adjusting_rate            <- config_options[[i]]
    } else if (names(config_options[i]) == "min_adjusting_rate") {
      p@min_adjusting_rate            <- config_options[[i]]
    } else if (names(config_options[i]) == "max_adjusting_rate") {
      p@max_adjusting_rate            <- config_options[[i]]
    } else if (names(config_options[i]) == "min_distance_bandwidth") {
      p@min_distance_bandwidth            <- config_options[[i]]
    } else if (names(config_options[i]) == "max_distance_bandwidth") {
      p@max_distance_bandwidth            <- config_options[[i]]
    } else {
      stop(paste0("Unknown option '", names(config_options[i]), "' for algorithm IHS."))
    }
  }
  return(p)
}
