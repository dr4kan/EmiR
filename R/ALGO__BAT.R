#' Create a configuration object for the BAT minimizer
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
#' @return `config_bat` returns an object of class `BATConfig`.
#' @export
config_bat <- function(iterations,
                       population_size,
                       iterations_same_cost = NULL,
                       initial_loudness = 1.5,
                       alpha = 0.9,
                       initial_pulse_rate = 0.5,
                       gamma = 0.9,
                       freq_min = 0.,
                       freq_max = 2.) {
  p <- new("BATConfig")
  p@iterations           <- iterations
  if (is.null(iterations_same_cost)) {
    p@iterations_same_cost <- iterations
  } else {
    p@iterations_same_cost <- iterations_same_cost
  }
  p@population_size    <- population_size

  p@initial_loudness   <- initial_loudness
  p@alpha              <- alpha
  p@initial_pulse_rate <- initial_pulse_rate
  p@gamma              <- gamma
  p@freq_min           <- freq_min
  p@freq_max           <- freq_max
  return(p)
}


#' Bat algorithm for function minimization
#'
#' Minimize an objective function, possibly subjected to inequality constraints, using
#' the Bat (BAT) algorithm.
#'
#' \loadmathjax
#' Proposed in 2010 by Xin-She Yang, BAT is a heuristic algorithm that operates by
#' mimicking the echolocation behavior of bats to perform global optimization. It is
#' based on three rules, which mimic the natural behaviour of bats:
#' 1. All bats use echolocation to sense the distance.
#' 1. Bats fly with the velocity \mjeqn{v_{i}}{v_{i}} at position \mjeqn{x_{i}}{x_{i}} and
#' and emit pulses of frequency \mjeqn{f_{i} \in \[f_{min}, f_{max}\]}{f_{i} \in [f_{min}, f_{max}]},
#' with rate \mjeqn{r_{i} \in \[0, 1\]}{r_{i} \in [0, 1]} and loudness
#' \mjeqn{A_{i} \in \[A_{min}, A_{0}\]}{A_{i} \in [A_{min}, A_{0}]}.
#' 1. The loudness varies from a large (positive) \mjeqn{A_{0}}{A_{0}} to a minimum constant value \mjeqn{A_{min}}{A_{min}}.
#'
#' BAT is an iterative algorithm which, after an initial random generation of bats (solutions)
#' in the search space, performs the following steps at each iteration:
#' * \emph{Generation of a new solution}: XXX
#'
#' @param obj_func objective function be minimized.
#' @param constraints list of constraints. Constraints are requested to be objects of
#' class `Constraint` (see \link[EmiR]{constraint}).
#' @param parameters list of parameters composing the search space for the objective function.
#' Parmeters are requested to be objects of class `Parameter`(see \link[EmiR]{parameter}).
#' @param config an object of class `BATConfig` with the configuration parameters
#' used by algorithm (see \link[EmiR]{config_bat}).
#' @param ... additional options (see \link[EmiR]{MinimizerOpts}).
#' @return `minimize_bat` returns an object of class `MinimizationResult`.
#' @importFrom Rdpack reprompt
#' @references \insertRef{yang2010new}{EmiR}
#' @export
minimize_bat <- function(obj_func, parameters, config, constraints = NULL, ...) {
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
  out <- cpp_minimize_bat(obj_func, constraints, parameters, config, opt)
  tictoc::toc(log = TRUE, quiet = opt@silent_mode)
  return(out)
}
