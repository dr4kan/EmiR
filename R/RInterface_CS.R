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
#' @return `config_CS` returns an object of class `CSConfig`.
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
#' config <- config_CS(iterations = 250, n_particles = 100)
#' ps <- minimize_PS(cost_function = eggholder,
#'                   parameters = l,
#'                   config = config)
#' print(ps)
#' @export
config_CS <- function(iterations,
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


