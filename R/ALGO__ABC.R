#' Create a configuration object for the ABC minimizer
#'
#' Create a configuration object for the BAT minimizer. At minimum the number of iterations
#' (parameter `iterations`) and the number of particles (parameter `n_particles`) have
#' to be provided.
#'
#' @param iterations maximum number of iterations.
#' @param population_size number of bats.
#' @param iterations_same_cost maximum number of consecutive iterations with the same cost before
#' ending the minimization. If `NULL` the minimization continues for the number of iterations
#' specified by the parameter `iterations`.
#' @param initial_loudness ???
#' @param alpha ???
#' @param initial_pulse_rate ???
#' @param gamma ???
#' @param freq_min ???
#' @param freq_max ???
#' @return `config_abc` returns an object of class `ABCConfig`.
#' @export
config_abc <- function(iterations,
                       population_size,
                       iterations_same_cost = NULL,
                       employed_frac = 0.5,
                       n_scout = 1) {
  p <- new("ABCConfig")
  p@iterations           <- iterations
  if (is.null(iterations_same_cost)) {
    p@iterations_same_cost <- iterations
  } else {
    p@iterations_same_cost <- iterations_same_cost
  }
  p@population_size    <- population_size

  p@employed_frac      <- employed_frac
  p@n_scout            <- n_scout
  return(p)
}


#' Artificial Bee Colony algorithm for function minimization
#'
#' Minimize an objective function, possibly subjected to inequality constraints, using
#' the Artificial Bee Colony (ABC) algorithm.
#'
#'
#' @param obj_func objective function be minimized.
#' @param constraints list of constraints. Constraints are requested to be objects of
#' class `Constraint` (see \link[EmiR]{constraint}).
#' @param parameters list of parameters composing the search space for the objective function.
#' Parmeters are requested to be objects of class `Parameter`(see \link[EmiR]{parameter}).
#' @param config an object of class `ABCConfig` with the configuration parameters
#' used by algorithm (see \link[EmiR]{config_abc}).
#' @param ... additional options (see \link[EmiR]{MinimizerOpts}).
#' @return `minimize_abc` returns an object of class `MinimizationResult`.
#' @importFrom Rdpack reprompt
#' @references \insertRef{yang2010new}{EmiR}
#' @export
minimize_abc <- function(obj_func, parameters, config, constraints = NULL, ...) {
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
  out <- cpp_minimize_abc(obj_func, constraints, parameters, config, opt)
  tictoc::toc(log = TRUE, quiet = opt@silent_mode)
  return(out)
}
