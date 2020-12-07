#' Create a configuration object for the GA minimizer
#'
#' Create a configuration object for the GA minimizer. At minimum the number of iterations
#' (parameter `iterations`) and the number of chromosomes (parameter `population_size`) have
#' to be provided.
#'
#' @param iterations maximum number of iterations.
#' @param population_size number of chromosomes.
#' @param iterations_same_cost maximum number of consecutive iterations with the same cost before
#' ending the minimization. If `NULL` the minimization continues for the number of iterations
#' specified by the parameter `iterations`.
#' @param keep_fraction ???.
#' @param m_mutation_rate ???.
#' @param penalty_parameter penalty parameter in constrained optimization.
#' @return `config_ga` returns an object of class `GAConfig`.
#' @examples
#' library(EmiR)
#'
#' eggholder <- function(x) {
#'   value = -(x[2]+47)*sin(sqrt(abs(x[1]/2+x[2]+47)))+x[1]*sin(sqrt(abs(x[1]-(x[2]+47))));
#'   return(value)
#' }
#'
#' x1 <- parameter("x1", -512, 512)
#' x2 <- parameter("x2", -512, 512)
#' l <- list(x1, x2)
#'
#' config <- config_ga(iterations = 250, n_particles = 100)
#' GA <- minimize_GA(cost_function = eggholder,
#'                   parameters = l,
#'                   config = config)
#' print(GA)
#' @export
config_ga <- function(iterations,
                      population_size,
                      iterations_same_cost = NULL,
                      keep_fraction = 0.4,
                      m_mutation_rate = 0.1,
                      penalty_parameter = 10.) {
  p <- new("GAConfig")
  p@iterations           <- iterations
  if (is.null(iterations_same_cost)) {
    p@iterations_same_cost <- iterations
  } else {
    p@iterations_same_cost <- iterations_same_cost
  }
  p@population_size   <- population_size
  p@keep_fraction     <- keep_fraction
  p@m_mutation_rate   <- m_mutation_rate
  p@penalty_parameter <- penalty_parameter
  return(p)
}


#' Genetic Algorithm function minimization
#'
#' Minimize an objective function, possibly subjected to inequality constraints, using
#' a Genetic Algorithm (GA).
#'
#' XXXIn case of a constrained optimization only inequality constraints are allowed. The
#'
#' @param obj_func objective function be minimized.
#' @param constraints list of constraints. Constraints are requested to be objects of
#' class `Constraint` (see \link[EmiR]{constraint}).
#' @param parameters list of parameters the function is minimized with respect to.
#' Parmeters are requested to be objects of class `Parameter`(see \link[EmiR]{parameter}).
#' @param config an object of class `GAConfig` with the configuration parameters
#' used by algorithm (see \link[EmiR]{config_ga}).
#' @return `minimize_ga` returns an object of class `MinimizationResult`.
#' @examples
#' library(EmiR)
#'
#' eggholder <- function(x) {
#'   value = -(x[2]+47)*sin(sqrt(abs(x[1]/2+x[2]+47)))+x[1]*sin(sqrt(abs(x[1]-(x[2]+47))));
#'   return(value)
#' }
#'
#' x1 <- parameter("x1", -512, 512)
#' x2 <- parameter("x2", -512, 512)
#' l <- list(x1, x2)
#'
#' config <- config_ga(iterations = 250, population_size = 100)
#' ga <- minimize_ga(cost_function = eggholder,
#'                   parameters = l,
#'                   config = config)
#' print(ga)
#' @export
minimize_ga <- function(cost_function, constraints = NULL, parameters, config) {
  cstr_minimize_ga(cost_function, constraints, parameters, config)
}
