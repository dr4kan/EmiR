#' Create a configuration object for the PS minimizer
#'
#' Description XXX
#'
#' @param iterations maximum number of iterations.
#' @param iterations_same_cost maximum number of consecutive iterations with the same cost before
#' ending the minimization. If `NULL` the minimization continues for the number of iterations
#' specified by the parameter `iterations`.
#' @param n_particles number of particles.
#' @param cognitive cognitive learning factor.
#' @param social social learning factor.
#' @param inertia inertia factor.
#' @param max_velocity a measure of the maximum distance particles travel at each iteration.
#' @return `config_PS` returns an object of class "`PSConfig`".
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
#' config <- config_PS(iterations = 250, n_particles = 100)
#' ps <- minimize_PS(cost_function = eggholder,
#'                   parameters = l,
#'                   config = config)
#' print(ps)
#' @export
config_PS <- function(iterations,
                      n_particles,
                      iterations_same_cost = NULL,
                      cognitive = 2.0,
                      social = 2.0,
                      inertia = 0.4,
                      max_velocity = 0.1) {
  p <- new("PSConfig")
  p@iterations           <- iterations
  if (is.null(iterations_same_cost)) {
    p@iterations_same_cost <- iterations
  } else {
    p@iterations_same_cost <- iterations_same_cost
  }
  if (!is.null(n_particles))          p@n_particles          <- n_particles
  if (!is.null(cognitive))            p@cognitive            <- cognitive
  if (!is.null(social))               p@social               <- social
  if (!is.null(inertia))              p@inertia              <- inertia
  if (!is.null(max_velocity))         p@max_velocity         <- max_velocity
  return(p)
}


