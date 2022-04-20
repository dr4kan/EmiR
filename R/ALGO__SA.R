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


#' Configuration object for the Simulated Annealing Algorithm
#'
#' Create a configuration object for the Simulated Annealing algorithm (SA). At minimum the number of iterations
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
#' @param T0 initial temperature. Default is `50`.
#' @param Ns number of iterations before changing velocity. Default is `3`.
#' @param Nt number of iterations before changing the temperature. Default is `3`.
#' @param c_step parameter involved in the velocity update. Default is `2`.
#' @param Rt scaling factor for the temperature. Default is `0.85`.
#' @param Wmin parameter involved in the generation of the starting point. Default is `0.25`.
#' @param Wmax parameter involved in the generation of the starting point. Default is `1.25`.
#' @return `config_sa` returns an object of class `SAConfig`.
#' @importFrom Rdpack reprompt
#' @references \insertRef{Kirkpatrick1983}{EmiR}
#' @export
#'
#' @examples
#' conf <- config_sa(iterations = 100, population_size = 50, iterations_same_cost = NULL,
#' absolute_tol = NULL, T0 = 50., Ns = 3., Nt = 3., c_step = 2., Rt = 0.85, Wmin = 0.25,
#'  Wmax = 1.25)
#'
config_sa <- function(iterations,
                      population_size,
                      iterations_same_cost = NULL,
                      absolute_tol         = NULL,
                      T0                   = 50.,
                      Ns                   = 3.,
                      Nt                   = 3.,
                      c_step               = 2.,
                      Rt                   = 0.85,
                      Wmin                 = 0.25,
                      Wmax                 = 1.25) {
  p <- new("SAConfig")
  commonOpt              <- checkCommonConfigOptions(iterations, population_size, iterations_same_cost, absolute_tol)
  p@iterations           <- commonOpt$iterations
  p@population_size      <- commonOpt$population_size
  p@iterations_same_cost <- commonOpt$iterations_same_cost
  p@absolute_tol         <- commonOpt$absolute_tol

  p@T0                 <- T0
  p@Ns                 <- Ns
  p@c_step             <- c_step
  p@Nt                 <- Nt
  p@Rt                 <- Rt
  p@Wmin               <- Wmin
  p@Wmax               <- Wmax
  return(p)
}

check_algo_options_sa <- function(p, ...) {
  config_options <- list(...)
  if (length(config_options) == 0) return(p)
  for (i in 1:length(config_options)) {
    if (names(config_options[i]) == "T0") {
      p@T0            <- config_options[[i]]
    } else if (names(config_options[i]) == "Ns") {
      p@Ns            <- config_options[[i]]
    } else if (names(config_options[i]) == "c_step") {
      p@c_step        <- config_options[[i]]
    } else if (names(config_options[i]) == "Nt") {
      p@Nt            <- config_options[[i]]
    } else if (names(config_options[i]) == "Rt") {
      p@Rt            <- config_options[[i]]
    } else if (names(config_options[i]) == "Wmin") {
      p@Wmin            <- config_options[[i]]
      } else if (names(config_options[i]) == "Wmax") {
      p@Wmax            <- config_options[[i]]
    } else {
      stop(paste0("Unknown option '", names(config_options[i]), "' for algorithm SA."))
    }
  }
  return(p)
}
