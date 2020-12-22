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
  p@step_size       <- step_size
  return(p)
}


#' Cuckoo Search function minimization
#'
#' Minimize an objective function, possibly subjected to inequality constraints, using
#' the Cuckoo Search (CS) algorithm.
#'
#' 1. An egg represents a solution and is stored in a nest. An artificial cuckoo can
#' lay only one egg at a time.
#' 1. The cuckoo bird searches for the most suitable nest to lay the eggs in (solution)
#' to maximize its eggs’ survival rate. An elitist selection strategy is applied, so that
#' only high-quality eggs (best solutions near the optimal value) which are more similar
#' to the host bird’s eggs have the opportunity to develop (next generation) and become
#' mature cuckoos.
#' 1.	The number of host nests (population) is fixed. The host bird can discover the
#' alien egg (worse solutions away from the optimal value) with a probability of , and
#' these eggs are thrown away or the nest is abandoned and a completely new nest is built in
#' a new location. Otherwise, the egg matures and lives to the next generation. New eggs
#' (solutions) laid by a cuckoo choose the nest by Lévy flights around the current best solutions.
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
minimize_cs <- function(obj_func, parameters, config, constraints = NULL, ...) {
  minimizer_options <- list(...)

  opt <- new("MinimizerOpts")
  if ("silent_mode" %in% names(minimizer_options)) {
    opt@silent_mode = minimizer_options[["silent_mode"]]
  }
  if ("save_population" %in% names(minimizer_options)) {
    opt@save_population = minimizer_options[["save_population"]]
  }
  if ("oob_solutions" %in% names(minimizer_options)) {
    opt@oob_solutions = minimizer_options[["oob_solutions"]]
  }

  tictoc::tic()
  out <- cpp_minimize_cs(obj_func, constraints, parameters, config, opt)
  tictoc::toc(log = TRUE, quiet = opt@silent_mode)
  return(out)
}
