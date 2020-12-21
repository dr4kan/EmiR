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
#' ps <- minimize_ps(obj_func = eggholder,
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
  p@n_particles       <- n_particles
  p@cognitive         <- cognitive
  p@social            <- social
  p@inertia           <- inertia
  p@max_velocity      <- max_velocity
  return(p)
}


#' Particle Swarm function minimization
#'
#' Minimize an objective function, possibly subjected to inequality constraints, using
#' the Particle Swarm (PS) algorithm.
#'
#' XXXIn case of a constrained optimization only inequality constraints are allowed. The
#'
#' @param obj_func objective function be minimized.
#' @param constraints list of constraints. Constraints are requested to be objects of
#' class `Constraint` (see \link[EmiR]{constraint}).
#' @param parameters list of parameters the function is minimized with respect to.
#' Parmeters are requested to be objects of class `Parameter`(see \link[EmiR]{parameter}).
#' @param config an object of class `PSConfig` with the configuration parameters
#' used by algorithm (see \link[EmiR]{config_ps}).
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
#' ps <- minimize_ps(obj_func = eggholder,
#'                   parameters = l,
#'                   config = config)
#' print(ps)
#' @export
minimize_ps <- function(obj_func, parameters, config, constraints = NULL, ...) {
  minimizer_options <- list(...)

  opt <- new("MinimizerOpts")
  if ("silent_mode" %in% names(minimizer_options)) {
    opt@silent_mode = minimizer_options[["silent_mode"]]
  }
  if ("save_population" %in% names(minimizer_options)) {
    opt@save_population = minimizer_options[["save_population"]]
  }

  tictoc::tic()
  out <- cpp_minimize_ps(obj_func, constraints, parameters, config, opt)
  tictoc::toc(log = TRUE, quiet = opt@silent_mode)
  return(out)
}
