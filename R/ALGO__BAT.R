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


#' Configuration object for the Bat Algorithm
#'
#' Create a configuration object for the Bat Algorithm (BAT). At minimum the number of iterations
#' (parameter `iterations`) and the number of bats (parameter `population_size`) have
#' to be provided.
#'
#' @param iterations maximum number of iterations.
#' @param population_size number of bats.
#' @param iterations_same_cost maximum number of consecutive iterations with the \emph{same}
#' (see the parameter `absolute_tol`) best cost before ending the minimization. If `NULL` the
#' minimization continues for the number of iterations specified by the parameter `iterations`.
#' Default is `NULL`.
#' @param absolute_tol absolute tolerance when comparing best costs from consecutive iterations.
#' If `NULL` the machine epsilon is used. Default is `NULL`.
#' @param initial_loudness initial loudness of emitted pulses. Typical values are in the range \[1, 2\]. Default is `1.5`.
#' @param alpha parameter to control the linearly decreasing loudness with
#' the iterations. It should be between 0 and 1. Default is `0.9`.
#' @param initial_pulse_rate initial rate at which pulses are emitted. It should
#' be between 0 and 1. Default is `0.5`.
#' @param gamma parameter to control the exponentially decreasing pulse rate with
#' the iterations. Defatul is `0.9`.
#' @param freq_min minimum frequency value of pulses. Default is `0`.
#' @param freq_max maximum frequency value of pulses. Default is `2.0`.
#' @return `config_bat` returns an object of class `BATConfig`.
#' @importFrom Rdpack reprompt
#' @references \insertRef{yang2010new}{EmiR}
#' @export
config_bat <- function(iterations,
                       population_size,
                       iterations_same_cost = NULL,
                       absolute_tol         = NULL,
                       initial_loudness     = 1.5,
                       alpha                = 0.9,
                       initial_pulse_rate   = 0.5,
                       gamma                = 0.9,
                       freq_min             = 0.,
                       freq_max             = 2.) {
  p <- new("BATConfig")
  commonOpt              <- checkCommonConfigOptions(iterations, population_size, iterations_same_cost, absolute_tol)
  p@iterations           <- commonOpt$iterations
  p@population_size      <- commonOpt$population_size
  p@iterations_same_cost <- commonOpt$iterations_same_cost
  p@absolute_tol         <- commonOpt$absolute_tol

  p@initial_loudness   <- initial_loudness
  p@alpha              <- alpha
  p@initial_pulse_rate <- initial_pulse_rate
  p@gamma              <- gamma
  p@freq_min           <- freq_min
  p@freq_max           <- freq_max
  return(p)
}

check_algo_options_bat <- function(p, ...) {
  config_options <- list(...)
  if (length(config_options) == 0) return(p)
  for (i in 1:length(config_options)) {
    if (names(config_options[i]) == "initial_loudness") {
      p@initial_loudness      <- config_options[[i]]
    } else if (names(config_options[i]) == "alpha") {
      p@alpha            <- config_options[[i]]
    } else if (names(config_options[i]) == "initial_pulse_rate") {
      p@initial_pulse_rate            <- config_options[[i]]
    } else if (names(config_options[i]) == "gamma") {
      p@gamma            <- config_options[[i]]
    } else if (names(config_options[i]) == "freq_min") {
      p@freq_min            <- config_options[[i]]
    } else if (names(config_options[i]) == "freq_max") {
      p@freq_max            <- config_options[[i]]
    } else {
      stop(paste0("Unknown option '", names(config_options[i]), "' for algorithm BAT."))
    }
  }
  return(p)
}
