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
#' @return `config_GA` returns an object of class `GAConfig`.
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
#' config <- config_GA(iterations = 250, n_particles = 100)
#' GA <- minimize_GA(cost_function = eggholder,
#'                   parameters = l,
#'                   config = config)
#' print(GA)
#' @export
config_GA <- function(iterations,
                      population_size,
                      iterations_same_cost = NULL,
                      keep_fraction = 0.4,
                      m_mutation_rate = 0.1) {
  p <- new("GAConfig")
  p@iterations           <- iterations
  if (is.null(iterations_same_cost)) {
    p@iterations_same_cost <- iterations
  } else {
    p@iterations_same_cost <- iterations_same_cost
  }
  p@population_size <- population_size
  p@keep_fraction   <- keep_fraction
  p@m_mutation_rate <- m_mutation_rate
  return(p)
}


