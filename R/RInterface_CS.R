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
                      mutation_rate = 0.25) {
  p <- new("CSConfig")
  p@iterations <- iterations
  if (is.null(iterations_same_cost)) {
    p@iterations_same_cost <- iterations
  } else {
    p@iterations_same_cost <- iterations_same_cost
  }
  p@population_size <- population_size
  p@mutation_rate <- mutation_rate
  return(p)
}


#' Cuckoo Search constrained minimization
#'
#' Minimize a cost function, subjected to one or more constraints, using
#' the Cuckoo Search (CS) algorithm.
#'
#' @param cost_function cost function to be minimized.
#' @param parameters a list of objects of class `Parameter` the cost function is minimized with respect to.
#' See \link[EmiR]{parameter}.
#' @param config an object of class `CSConfig` with the configuration parameters
#' for the CS algorithm. See \link[EmiR]{config_cs}.
#' @return `minimize_cs` returns an object of class `MinimizationResult`.
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
minimize_cs <- function(cost_function, constraints = NULL, parameters, config) {
cstr_minimize_cs(cost_function, constraints, parameters, config)
}
