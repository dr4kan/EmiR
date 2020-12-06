#' Create a configuration object for the SA minimizer
#'
#' Create a configuration object for the SA minimizer. At minimum the number of iterations
#' (parameter `iterations`) and the number of particles (parameter `n_particles`) have
#' to be provided.
#'
#' @param iterations maximum number of iterations.
#' @param n_particles number of particles.
#' @param iterations_same_cost maximum number of consecutive iterations with the same cost before
#' ending the minimization. If `NULL` the minimization continues for the number of iterations
#' specified by the parameter `iterations`.
#' @param cognitive ???.
#' @param social ???.
#' @param dumping ???.
#' @param temperature temperature.
#' @return `config_SA` returns an object of class `SAConfig`.
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
#' config <- config_SA(iterations = 250, n_particles = 100)
#' SA <- minimize_SA(cost_function = eggholder,
#'                   parameters = l,
#'                   config = config)
#' print(SA)
#' @export
config_SA <- function(iterations,
                      n_particles,
                      iterations_same_cost = NULL,
                      cognitive = 2.0,
                      social = 2.0,
                      dumping = 0.1,
                      temperature = 50) {
  p <- new("SAConfig")
  p@iterations           <- iterations
  if (is.null(iterations_same_cost)) {
    p@iterations_same_cost <- iterations
  } else {
    p@iterations_same_cost <- iterations_same_cost
  }
  p@n_particles  <- n_particles
  p@cognitive    <- cognitive
  p@social       <- social
  p@dumping      <- dumping
  p@temperature  <- temperature
  return(p)
}


