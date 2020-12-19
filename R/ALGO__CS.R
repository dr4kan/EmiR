#' Create a configuration object for the CS minimizer
#'
#' Create a configuration object for the CS minimizer. At minimum the number of iterations
#' (parameter `iterations`) and the population size (parameter `population_size`) have
#' to be provided.
#'
#' @param iterations maximum number of iterations.
#' @param population_size number of ???
#' @param iterations_same_cost maximum number of consecutive iterations with the same cost before
#' ending the minimization. If `NULL` the minimization continues for the number of iterations
#' specified by the parameter `iterations`.
#' @param discovery_rate ???.
#' @param step_size step size in the Levy flight.
#' @return `config_cs` returns an object of class `CSConfig`.
#' @export
config_cs <- function(iterations,
                      population_size,
                      iterations_same_cost = NULL,
                      discovery_rate = 0.25,
                      step_size = 1.0) {
  p <- new("CSConfig")
  p@iterations <- iterations
  if (is.null(iterations_same_cost)) {
    p@iterations_same_cost <- iterations
  } else {
    p@iterations_same_cost <- iterations_same_cost
  }
  p@population_size <- population_size
  p@discovery_rate  <- discovery_rate
  return(p)
}


#' Cuckoo Search function minimization
#'
#' Minimize an objective function, possibly subjected to inequality constraints, using
#' the Cuckoo Search (CS) algorithm.
#'
#' The Levy exponent lambda is randomly generated in [1, 3]
#' XXXIn case of a constrained optimization only inequality constraints are allowed. The
#'
#' @param obj_func objective function be minimized.
#' @param constraints list of constraints. Constraints are requested to be objects of
#' class `Constraint` (see \link[EmiR]{constraint}).
#' @param parameters list of parameters the function is minimized with respect to.
#' Parmeters are requested to be objects of class `Parameter`(see \link[EmiR]{parameter}).
#' @param config an object of class `CSConfig` with the configuration parameters
#' used by algorithm (see \link[EmiR]{config_cs}).
#' @return `minimize_cs` returns an object of class `MinimizationResult`.
#' @importFrom Rdpack reprompt
#' @references \insertRef{Yang2009}{EmiR}
#' @export
minimize_cs <- function(obj_func, constraints = NULL, parameters, config) {
  tictoc::tic()
  out <- cstr_minimize_cs(obj_func, constraints, parameters, config)
  tictoc::toc(log = TRUE)
  return(out)
}
