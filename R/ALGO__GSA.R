#' Create a configuration object for the GSA minimizer
#'
#' Create a configuration object for the GSA minimizer. At minimum the number of iterations
#' (parameter `iterations`) and the number of planets (parameter `population_size`) have
#' to be provided.
#'
#' @param iterations maximum number of iterations.
#' @param population_size number of planets.
#' @param iterations_same_cost maximum number of consecutive iterations with the same cost before
#' ending the minimization. If `NULL` the minimization continues for the number of iterations
#' specified by the parameter `iterations`.
#' @param gravitation Gravitational constant
#' @param velocity_max  Maximum velocity in % of the range of parameters
#' @return `config_gsa` returns an object of class `GSAConfig`.
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
#' config <- config_gsa(iterations = 250, population_size = 100)
#' GSA <- minimize_gsa(obj_func = eggholder,
#'                   parameters = l,
#'                   config = config)
#' print(GSA)
#' @export
config_gsa <- function(iterations,
                      population_size,
                      iterations_same_cost = NULL,
                      gravitation = 100,
                      velocity_max = 0.01) {
  p <- new("GSAConfig")
  p@iterations           <- iterations
  if (is.null(iterations_same_cost)) {
    p@iterations_same_cost <- iterations
  } else {
    p@iterations_same_cost <- iterations_same_cost
  }
  p@population_size    <- population_size
  p@gravitation        <- gravitation
  p@velocity_max <- velocity_max
  return(p)
}


#' Gravitational Search Algorithm minimization
#'
#' Minimize an objective function, possibly subjected to inequality constraints, using
#' the Gravitational Search Algorithm (GSA) algorithm.
#'
#' In case of a constrained optimization only inequality constraints are allowed...
#'
#' @param obj_func objective function be minimized.
#' @param constraints list of constraints. Constraints are requested to be objects of
#' class `Constraint` (see \link[EmiR]{constraint}).
#' @param parameters list of parameters the function is minimized with respect to.
#' Parmeters are requested to be objects of class `Parameter`(see \link[EmiR]{parameter}).
#' @param config an object of class `GSAConfig` with the configuration parameters
#' used by algorithm (see \link[EmiR]{config_gsa}).
#' @return `minimize_gsa` returns an object of class `MinimizationResult`.
#' @importFrom Rdpack reprompt
#' @references \insertRef{XXX}{EmiR}
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
#' config <- config_gsa(iterations = 250, population_size = 100)
#' gsa <- minimize_gsa(obj_func = eggholder,
#'                   parameters = l,
#'                   config = config)
#' print(gsa)
#' @export
minimize_gsa <- function(obj_func, parameters, config, constraints = NULL, ...) {
  minimizer_options <- list(...)

  opt <- new("MinimizerOpts")
  if ("silent_mode" %in% names(minimizer_options)) {
    opt@silent_mode = minimizer_options[["silent_mode"]]
  }
  if ("save_population" %in% names(minimizer_options)) {
    opt@save_population = minimizer_options[["save_population"]]
  }
  if ("oob_solutions" %in% names(minimizer_options)) {
    opt@oob_solutions = minimizer_options[["oob_solutions"]]
  }

  tictoc::tic()
  out <- cpp_minimize_gsa(obj_func, constraints, parameters, config, opt)
  tictoc::toc(log = TRUE, quiet = opt@silent_mode)
  return(out)
}
