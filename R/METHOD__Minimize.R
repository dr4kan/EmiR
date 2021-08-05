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


#' Return the list of algorithms in EmiR
#'
#' Return a `data.frame` with the ID, description and configuration function name of all the
#' algorithms implemented in EmiR.
#'
#' @return An object of class `data.frame`.
#' @export
list_of_algorithms <- function() {

  emir_algorithms <- data.frame(rbind(
    c("ABC", "Artificial Bee Colony Algorithm"  , "config_abc"),
    c("BAT", "Bat Algorithm"                    , "config_bat"),
    c("CS" , "Cuckoo Search Algorithm"          , "config_cs" ),
    c("GA" , "Genetic Algorithm"                , "config_ga" ),
    c("GSA", "Gravitational Search Algorithm"   , "config_gsa"),
    c("GWO", "Grey Wolf Optimizer Algorithm"    , "config_gwo"),
    c("HS" , "Harmony Search Algorithm"         , "config_hs" ),
    c("IHS", "Improved Harmony Search Algorithm", "config_ihs"),
    c("MFO", "Moth-flame Optimization Algorithm", "config_mfo"),
    c("PS" , "Particle Swarm Algorithm"         , "config_ps" ),
    c("SA" , "Simulated Annealing Algorithm"    , "config_sa" ),
    c("WOA", "Whale Optimization Algorithm"     , "config_woa")
  ))
  names(emir_algorithms) <- c("Id", "Full name", "Configuration function")

  return(emir_algorithms)
}



#' Return the list of pre-defined functions in EmiR
#'
#' Return a `data.frame` with function name, full name, and minimum and maximum number of parameters
#' accepted for all the pre-defined functions in EmiR.
#'
#' @return An object of class `data.frame`.
#' @export
list_of_functions <- function() {

  emir_functions <- data.frame(rbind(
    c("ackley_func", "Ackley Function", 1, NA),
    c("bohachevsky_func", "Bohachevsky Function", 2, 2),
    c("colville_func", "Colville Function", 4, 4),
    c("freudenstein_roth_func", "Freudenstein Roth Function", 2, 2),
    c("griewank_func", "Griewank Function"  , 1, NA),
    c("miele_cantrell_func", "Miele Cantrell Function", 4, 4),
    c("rastrigin_func", "Rastrigin Function"  , 1, NA),
    c("rosenbrock_func", "Rosenbrock Function"  , 2, NA),
    c("schwefel_func", "Schwefel Function"  , 1, NA),
    c("styblinski_tang_func", "Styblinski-Tang Function"  , 1, NA)
  ))
  names(emir_functions) <- c("Function name", "Full name", "Min dim", "Max dim")

  return(emir_functions)
}



#' Minimize an Objective Function
#'
#' Minimize (or maximize) an objective function, possibly subjected to inequality constraints, using
#' any of the algorithms available in EmiR.
#'
#' @param algorithm_id id of the algorithm to be used. See \link[EmiR]{list_of_algorithms} for
#' the list of the available algorithms.
#' @param obj_func objective function be minimized/maximized.
#' @param parameters list of parameters composing the search space for the objective function.
#' Parmeters are requested to be objects of class `Parameter` (see \link[EmiR]{parameter}).
#' @param config an object with the configuration parameters of the chosen algorithm. For each
#' algorithm there is different function for the tuning of its configuration parameter, as
#' reported in the following list:
#' \itemize{
#'  \item{\link[EmiR]{config_abc}}{ -- configuration function for the *Artificial Bee Colony Algorithm*.}
#'  \item{\link[EmiR]{config_bat}}{ -- configuration function for the *Bat Algorithm*.}
#'  \item{\link[EmiR]{config_cs} }{ -- configuration function for the *Cuckoo Search Algorithm*.}
#'  \item{\link[EmiR]{config_ga} }{ -- configuration function for the *Genetic Algorithm*.}
#'  \item{\link[EmiR]{config_gsa}}{ -- configuration function for the *Gravitational Search Algorithm*.}
#'  \item{\link[EmiR]{config_gwo}}{ -- configuration function for the *Grey Wolf Optimizer Algorithm*.}
#'  \item{\link[EmiR]{config_hs} }{ -- configuration function for the *Harmony Search Algorithm*.}
#'  \item{\link[EmiR]{config_ihs}}{ -- configuration function for the *Improved Harmony Search Algorithm*.}
#'  \item{\link[EmiR]{config_mfo}}{ -- configuration function for the *Moth-flame Optimization Algorithm*.}
#'  \item{\link[EmiR]{config_ps} }{ -- configuration function for the *Particle Swarm Algorithm*.}
#'  \item{\link[EmiR]{config_sa} }{ -- configuration function for the *Simulated Annealing algorithm*.}
#'  \item{\link[EmiR]{config_woa}}{ -- configuration function for the *Whale Optimization Algorithm*.}
#' }
#' @param constraints list of constraints. Constraints are requested to be objects of
#' class `Constraint` (see \link[EmiR]{constraint}).
#' @param ... additional options (see \link[EmiR]{MinimizerOpts}).
#' @return `minimize` returns an object of class `OptimizationResults` (see \link[EmiR]{OptimizationResults}).
#' @export

minimize <- function(algorithm_id, obj_func, parameters, config, constraints = NULL, ...) {

  algos_id <- list_of_algorithms()[,1]
  if (!(algorithm_id %in% algos_id)) stop("Unknown algorithm. Use 'list_of_algorithms()' for the list of algorithms available in EmiR.")

  if (class(config) != paste0(algorithm_id, "Config")) stop(paste0("Wrong config parameter. Expected an object of class '", algorithm_id, "Config'."))

  opt <- checkMinimizationOptions(constraints, config@population_size, length(parameters), ...)

  out <- NULL
  tictoc::tic()

  if (algorithm_id == "ABC") out <- cpp_minimize_abc(obj_func, constraints, parameters, config, opt)
  if (algorithm_id == "BAT") out <- cpp_minimize_bat(obj_func, constraints, parameters, config, opt)
  if (algorithm_id == "CS" ) out <- cpp_minimize_cs(obj_func, constraints, parameters, config, opt)
  if (algorithm_id == "GA" ) out <- cpp_minimize_ga(obj_func, constraints, parameters, config, opt)
  if (algorithm_id == "GSA") out <- cpp_minimize_gsa(obj_func, constraints, parameters, config, opt)
  if (algorithm_id == "GWO") out <- cpp_minimize_gwo(obj_func, constraints, parameters, config, opt)
  if (algorithm_id == "HS" ) out <- cpp_minimize_hs(obj_func, constraints, parameters, config, opt)
  if (algorithm_id == "IHS") out <- cpp_minimize_ihs(obj_func, constraints, parameters, config, opt)
  if (algorithm_id == "MFO") out <- cpp_minimize_mfo(obj_func, constraints, parameters, config, opt)
  if (algorithm_id == "PS" ) out <- cpp_minimize_ps(obj_func, constraints, parameters, config, opt)
  if (algorithm_id == "SA" ) out <- cpp_minimize_sa(obj_func, constraints, parameters, config, opt)
  if (algorithm_id == "WOA") out <- cpp_minimize_woa(obj_func, constraints, parameters, config, opt)

  tictoc::toc(log = TRUE, quiet = opt@silent_mode)
  log.lst <- tictoc::tic.log(format = FALSE)
  out@exec_time_sec <- unname(unlist(lapply(log.lst, function(x) x$toc - x$tic)))
  tictoc::tic.clearlog()
  return(out)
}
