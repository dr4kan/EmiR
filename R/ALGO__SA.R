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
#' @param T0 initial temperature.
#' @param annealing_schedule ???.
#' @return `config_sa` returns an object of class `SAConfig`.
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
#' config <- config_sa(iterations = 250, n_particles = 100)
#' SA <- minimize_sa(obj_func = eggholder,
#'                   parameters = l,
#'                   config = config)
#' print(SA)
#' @export
config_sa <- function(iterations,
                      n_particles,
                      iterations_same_cost = NULL,
                      T0 = 50.,
                      annealing_schedule = "linear") {
  p <- new("SAConfig")
  p@iterations           <- iterations
  if (is.null(iterations_same_cost)) {
    p@iterations_same_cost <- iterations
  } else {
    p@iterations_same_cost <- iterations_same_cost
  }
  p@n_particles        <- n_particles
  p@T0                 <- T0
  p@annealing_schedule <- annealing_schedule
  return(p)
}


#' Simulated Annealing function minimization
#'
#' Minimize an objective function, possibly subjected to inequality constraints, using
#' the Simulated Annealing (PS) algorithm.
#'
#' XXXIn case of a constrained optimization only inequality constraints are allowed. The
#'
#' @param obj_func objective function be minimized.
#' @param constraints list of constraints. Constraints are requested to be objects of
#' class `Constraint` (see \link[EmiR]{constraint}).
#' @param parameters list of parameters the function is minimized with respect to.
#' Parmeters are requested to be objects of class `Parameter`(see \link[EmiR]{parameter}).
#' @param config an object of class `SAConfig` with the configuration parameters
#' used by algorithm (see \link[EmiR]{config_sa}).
#' @return `minimize_sa` returns an object of class `MinimizationResult`.
#' @importFrom Rdpack reprompt
#' @references \insertRef{Kirkpatrick1983}{EmiR}
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
#' config <- config_sa(iterations = 250, n_particles = 100)
#' ps <- minimize_sa(obj_func = eggholder,
#'                   parameters = l,
#'                   config = config)
#' print(ps)
#' @export
minimize_sa <- function(obj_func, parameters, config, constraints = NULL, ...) {
  minimizer_options <- list(...)

  opt <- new("MinimizerOpts")
  if ("silent_mode" %in% names(minimizer_options)) {
    opt@silent_mode = minimizer_options[["silent_mode"]]
  }
  if ("save_population" %in% names(minimizer_options)) {
    opt@save_population = minimizer_options[["save_population"]]
  }

  tictoc::tic()
  out <- cpp_minimize_sa(obj_func, constraints, parameters, config, opt)
  tictoc::toc(log = TRUE, quiet = opt@silent_mode)
  return(out)
}
