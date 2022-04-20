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


#' Configuration object for the Harmony Search Algorithm
#'
#' Create a configuration object for the Harmony Search Algorithm (HS). At minimum the number of iterations
#' (parameter `iterations`) and the number of solutions in the harmony memory (parameter `population_size`)
#' have to be provided.
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
#' @param adjusting_rate probability of the pitch adjustment in case of a component
#' recalled from the harmony memory.
#' @param distance_bandwidth amplitude of the random pitch adjustment.
#' @return `config_hs` returns an object of class `HSConfig`.
#' @importFrom Rdpack reprompt
#' @references \insertRef{Lee2004}{EmiR}
#' @export
#'
#' @examples
#' conf <- config_hs(iterations = 100, population_size = 50, iterations_same_cost = NULL, absolute_tol = NULL,
#' considering_rate = 0.5, adjusting_rate = 0.5, distance_bandwidth = 0.1)
#'
#'
config_hs <- function(iterations,
                      population_size,
                      iterations_same_cost = NULL,
                      absolute_tol         = NULL,
                      considering_rate     = 0.5,
                      adjusting_rate       = 0.5,
                      distance_bandwidth   = 0.1) {
  p <- new("HSConfig")
  commonOpt              <- checkCommonConfigOptions(iterations, population_size, iterations_same_cost, absolute_tol)
  p@iterations           <- commonOpt$iterations
  p@population_size      <- commonOpt$population_size
  p@iterations_same_cost <- commonOpt$iterations_same_cost
  p@absolute_tol         <- commonOpt$absolute_tol

  p@considering_rate   <- considering_rate
  p@adjusting_rate     <- adjusting_rate
  p@distance_bandwidth <- distance_bandwidth
  return(p)
}

check_algo_options_hs <- function(p, ...) {
  config_options <- list(...)
  if (length(config_options) == 0) return(p)
  for (i in 1:length(config_options)) {
    if (names(config_options[i]) == "considering_rate") {
      p@considering_rate      <- config_options[[i]]
    } else if (names(config_options[i]) == "adjusting_rate") {
      p@adjusting_rate            <- config_options[[i]]
    } else if (names(config_options[i]) == "distance_bandwidth") {
      p@distance_bandwidth            <- config_options[[i]]
    } else {
      stop(paste0("Unknown option '", names(config_options[i]), "' for algorithm HS."))
    }
  }
  return(p)
}
