#' Create a configuration object for the PS minimizer
#'
#' Create a configuration object for the PS minimizer. At minimum the number of iterations
#' (parameter `iterations`) and the number of particles (parameter `n_particles`) have
#' to be provided.
#'
#' @param iterations maximum number of iterations.
#' @param n_particles number of particles.
#' @param iterations_same_cost maximum number of consecutive iterations with the same cost before
#' ending the minimization. If `NULL` the minimization continues for the number of iterations
#' specified by the parameter `iterations`.
#' @param cognitive cognitive learning factor.
#' @param social social learning factor.
#' @param inertia inertia factor.
#' @param max_velocity a measure of the maximum distance particles travel at each iteration.
#' @return `config_ps` returns an object of class `PSConfig`.
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
#' config <- config_ps(iterations = 250, n_particles = 100)
#' ps <- minimize_PS(cost_function = eggholder,
#'                   parameters = l,
#'                   config = config)
#' print(ps)
#' @export
config_ps <- function(iterations,
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
  p@n_particles  <- n_particles
  p@cognitive    <- cognitive
  p@social       <- social
  p@inertia      <- inertia
  p@max_velocity <- max_velocity
  return(p)
}


#' Particle Swarm minimization
#'
#' Minimize a cost function using the Particle Swarm (PS) algorithm.
#'
#' @param cost_function cost function to be minimized.
#' @param parameters a list of objects of class `Parameter` the cost function is minimized with respect to.
#' See \link[EmiR]{parameter}.
#' @param config an object of class `PSConfig` with the configuration parameters
#' for the PS algorithm. See \link[EmiR]{config_ps}.
#' @return `minimize_ps` returns an object of class `MinimizationResult`.
#' @importFrom Rdpack reprompt
#' @references \insertRef{eberhart1995new}{EmiR}
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
#' config <- config_ps(iterations = 250, n_particles = 100)
#' ps <- minimize_ps(cost_function = eggholder,
#'                   parameters = l,
#'                   config = config)
#' print(ps)
#' @export
minimize_ps <- function(cost_function, constraints = NULL, parameters, config) {
cstr_minimize_ps(cost_function, constraints, parameters, config)
}
