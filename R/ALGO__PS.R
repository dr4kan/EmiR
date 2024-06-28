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


#' Configuration object for the Particle Swarm Algorithm
#'
#' Create a configuration object for the Particle Swarm Algorithm (PS). At minimum the number of iterations
#' (parameter `iterations`) and the number of particles (parameter `population_size`) have
#' to be provided.
#'
#' @param iterations maximum number of iterations.
#' @param population_size number of particles.
#' @param iterations_same_cost maximum number of consecutive iterations with the \emph{same}
#' (see the parameter `absolute_tol`) best cost before ending the minimization. If `NULL` the
#' minimization continues for the number of iterations specified by the parameter `iterations`.
#' Default is `NULL`.
#' @param absolute_tol absolute tolerance when comparing best costs from consecutive iterations.
#' If `NULL` the machine epsilon is used. Default is `NULL`.
#' @param alpha_vel maximum velocity of particles, defined as a fraction of the range on
#' each parameter. Default is `0.5`.
#' @param  alpha_evolution parameter to control the decreasing alpha_vel value with
#' the iterations. Default is `1.0` (linear).
#' @param cognitive parameter influencing the motion of the particle on
#' the basis of distance between its current and best positions. Default is `2.0`.
#' @param social parameter influencing the motion of the particle on
#' the basis of distance between its current position and the best position in the swarm. Default is `2.0`.
#' @param inertia parameter influencing the dependency of the velocity on
#' its value at the previous iteration. Default `0.9`.
#' @return `config_ps` returns an object of class `PSConfig`.
#' @importFrom Rdpack reprompt
#' @references \insertRef{eberhart1995new}{EmiR}
#' @export
#'
#' @examples
#' conf <- config_ps(iterations = 100, population_size = 50, iterations_same_cost = NULL,
#' absolute_tol = NULL,alpha_vel = 0.5, alpha_evolution = 1.0, cognitive = 2.0,
#' social = 2.0, inertia = 0.9)
#'
config_ps <- function(iterations,
                      population_size,
                      iterations_same_cost = NULL,
                      absolute_tol         = NULL,
                      alpha_vel            = 0.5,
                      alpha_evolution      = 1.0,
                      cognitive            = 2.0,
                      social               = 2.0,
                      inertia              = 0.9) {
  p <- new("PSConfig")
  commonOpt              <- checkCommonConfigOptions(iterations, population_size, iterations_same_cost, absolute_tol)
  p@iterations           <- commonOpt$iterations
  p@population_size      <- commonOpt$population_size
  p@iterations_same_cost <- commonOpt$iterations_same_cost
  p@absolute_tol         <- commonOpt$absolute_tol

  p@cognitive         <- cognitive
  p@social            <- social
  p@alpha_vel         <- alpha_vel
  p@alpha_evolution   <- alpha_evolution
  p@inertia           <- inertia
  return(p)
}

check_algo_options_ps <- function(p, ...) {
  config_options <- list(...)
  if (length(config_options) == 0) return(p)
  for (i in 1:length(config_options)) {
    if (names(config_options[i]) == "cognitive") {
      p@cognitive      <- config_options[[i]]
    } else if (names(config_options[i]) == "social") {
      p@social            <- config_options[[i]]
    } else if (names(config_options[i]) == "alpha_vel") {
      p@alpha_vel            <- config_options[[i]]
    } else if (names(config_options[i]) == "alpha_evolution") {
      p@alpha_evolution            <- config_options[[i]]
    } else if (names(config_options[i]) == "inertia") {
      p@inertia            <- config_options[[i]]
    } else {
      stop(paste0("Unknown option '", names(config_options[i]), "' for algorithm PS."))
    }
  }
  return(p)
}
