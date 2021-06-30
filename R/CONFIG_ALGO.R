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


#' Configuration object for algorithms
#'
#' Create a configuration object for one of the algorithms available in EmiR. At minimum the id of the
#' algorithm (parameter `algorithm_id`), the number of iterations (parameter `iterations`) and the
#' number of individuals in the population (parameter `population_size`) have to be provided.
#'
#' @param algorithm_id id of the algorithm to be used. See \link[EmiR]{list_of_algorithms} for
#' the list of the available algorithms.
#' @param iterations maximum number of iterations.
#' @param population_size number of individuals in the population.
#' @param iterations_same_cost maximum number of consecutive iterations with the \emph{same}
#' (see the parameter `absolute_tol`) best cost before ending the minimization. If `NULL` the
#' minimization continues for the number of iterations specified by the parameter `iterations`.
#' Default is `NULL`.
#' @param absolute_tol absolute tolerance when comparing best costs from consecutive iterations.
#' If `NULL` the machine epsilon is used. Default is `NULL`.
#' @param ... algorithm specific parameters (see specific configuration functions for more details).
#' @return `config_algo` returns a configuration object specific for the specified algorithm.
#' @importFrom Rdpack reprompt
#' @export
#'
config_algo <- function(algorithm_id,
                        iterations,
                        population_size,
                        iterations_same_cost = NULL,
                        absolute_tol         = NULL,
                        ...) {
  p <- NULL

  if      (algorithm_id == "ABC") {
    p <- config_abc(iterations, population_size, iterations_same_cost, absolute_tol)
    p <- check_algo_options_abc(p, ...)
  } else if (algorithm_id == "BAT") {
    p <- config_bat(iterations, population_size, iterations_same_cost, absolute_tol)
    p <- check_algo_options_bat(p, ...)
  } else if (algorithm_id == "CS") {
    p <- config_cs(iterations, population_size, iterations_same_cost, absolute_tol)
    p <- check_algo_options_cs(p, ...)
  } else if (algorithm_id == "GA") {
    p <- config_ga(iterations, population_size, iterations_same_cost, absolute_tol)
    p <- check_algo_options_ga(p, ...)
  } else if (algorithm_id == "GSA") {
    p <- config_gsa(iterations, population_size, iterations_same_cost, absolute_tol)
    p <- check_algo_options_gsa(p, ...)
  } else if (algorithm_id == "GWO") {
    p <- config_gwo(iterations, population_size, iterations_same_cost, absolute_tol)
    p <- check_algo_options_gwo(p, ...)
  } else if (algorithm_id == "HS") {
    p <- config_hs(iterations, population_size, iterations_same_cost, absolute_tol)
    p <- check_algo_options_hs(p, ...)
  } else if (algorithm_id == "IHS") {
    p <- config_ihs(iterations, population_size, iterations_same_cost, absolute_tol)
    p <- check_algo_options_ihs(p, ...)
  } else if (algorithm_id == "MFO") {
    p <- config_mfo(iterations, population_size, iterations_same_cost, absolute_tol)
    p <- check_algo_options_mfo(p, ...)
  } else if (algorithm_id == "PS") {
    p <- config_ps(iterations, population_size, iterations_same_cost, absolute_tol)
    p <- check_algo_options_ps(p, ...)
  } else if (algorithm_id == "SA") {
    p <- config_sa(iterations, population_size, iterations_same_cost, absolute_tol)
    p <- check_algo_options_sa(p, ...)
  } else if (algorithm_id == "WOA") {
    p <- config_woa(iterations, population_size, iterations_same_cost, absolute_tol)
    p <- check_algo_options_woa(p, ...)
  } else stop("Unknown algorithm. Use 'list_of_algorithms()' for the list of algorithms available in EmiR.")

  return(p)
}
