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
#' @param mutation_rate ???.
#' @param penalty_parameter penalty parameter in constrained optimization.
#' @return `config_cs` returns an object of class `CSConfig`.
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
#' config <- config_cs(iterations = 250, population_size = 100)
#' ps <- minimize_CS(cost_function = eggholder,
#'                   parameters = l,
#'                   config = config)
#' print(ps)
#' @export
config_cs <- function(iterations,
                      population_size,
                      iterations_same_cost = NULL,
                      mutation_rate = 0.25,
                      penalty_parameter = 10.) {
  p <- new("CSConfig")
  p@iterations <- iterations
  if (is.null(iterations_same_cost)) {
    p@iterations_same_cost <- iterations
  } else {
    p@iterations_same_cost <- iterations_same_cost
  }
  p@population_size   <- population_size
  p@mutation_rate     <- mutation_rate
  p@penalty_parameter <- penalty_parameter
  return(p)
}


#' Cuckoo Search function minimization
#'
#' Minimize an objective function, possibly subjected to inequality constraints, using
#' the Cuckoo Search (CS) algorithm.
#'
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
#' config <- config_cs(iterations = 250, population_size = 100)
#' cs <- minimize_cs(cost_function = eggholder,
#'                   parameters = l,
#'                   config = config)
#' print(cs)
#' @export
minimize_cs <- function(obj_func, constraints = NULL, parameters, config) {
  cstr_minimize_cs(cost_function, constraints, parameters, config)
}
