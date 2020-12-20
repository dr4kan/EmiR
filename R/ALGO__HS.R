#' Create a configuration object for the Harmony Search algorithm
#'
#' Create a configuration object for the Harmony Search algorithm (see
#' \link[EmiR]{minimize_hs} for more details on the algorithm). At minimum the number of iterations
#' (parameter `iterations`) and the number of particles (parameter `n_particles`)
#' have to be provided.
#'
#' @param iterations maximum number of iterations.
#' @param population_size number of solutions in the harmony memory.
#' @param iterations_same_cost maximum number of consecutive iterations with the same cost before
#' ending the minimization. If `NULL` the minimization continues for the number of iterations
#' specified by the parameter `iterations`.
#' @param considering_rate probability for each component of a newly generated solution
#'  to be recalled from the harmony memory.
#' @param adjusting_rate probability of the pitch adjustment in case of a component
#' recalled from the harmony memory.
#' @param distance_bandwidth amplitude of the random pitch adjustment.
#' @return `config_hs` returns an object of class `HSConfig`.
#' @export
config_hs <- function(iterations,
                       population_size,
                       iterations_same_cost = NULL,
                       considering_rate = 0.5,
                       adjusting_rate = 0.5,
                       distance_bandwidth = 0.1) {
  p <- new("HSConfig")
  p@iterations           <- iterations
  if (is.null(iterations_same_cost)) {
    p@iterations_same_cost <- iterations
  } else {
    p@iterations_same_cost <- iterations_same_cost
  }
  p@population_size    <- population_size

  p@considering_rate   <- considering_rate
  p@adjusting_rate     <- adjusting_rate
  p@distance_bandwidth <- distance_bandwidth
  return(p)
}


#' Harmony Search algorithm for function minimization
#'
#' Minimize an objective function, possibly subjected to inequality constraints, using
#' the Harmony Search (HS) algorithm.
#'
#' \loadmathjax
#' HS is a metaheuristic optimization algorithm, inspired by the process of improvisation
#' in music. When improvising, a musician tend to mix the following ideas, in the search
#' for a perfect harmony:
#' 1. playing a precise series of notes recalled from his or her memory;
#' 1. playing some random notes;
#' 1. playing something similar to what he or she already knows, by only changing
#' the pitch of some notes.
#'
#' This approach can be also applied in the context of optimization problems. The starting
#' point of the HS algorithm is the random generation of possible solutions vector to the problem,
#' creating the so-called \emph{harmony memory}. At each iteration the following steps
#' are performed:
#' 1. \emph{Generation of a new solution}: values of the decision variables,
#' forming the new solution, are either chosen from the harmony memory, with a
#' probability \mjeqn{p_{cr}}{p_{cr}}, or randomly generated.
#' \mjeqn{p_{cr}}{p_{cr}} is called \emph{considering rate} and corresponds to the
#' parameter `considering_rate` in class `HSConfig` (see \link[EmiR]{config_hs}).
#' Each component obtained from the harmony memory is also pitch-adjusted with
#' a probability \mjeqn{p_{ar}}{p_{ar}}, called \emph{pitch adjusting rate}.
#' \mjeqn{p_{ar}}{p_{ar}} corresponds to the parameter `adjusting_rate`
#' in class `HSConfig`. The amount of the random pitch adjustment is
#' tuned by the parameter `distance_bandwidth` in class `HSConfig`.
#' 1. \emph{Update of the harmony memory}: if the new solution improves the worst
#' one in the harmony memory (in terms of the cost of the objective function),
#' the latter is replaced by the new solution.
#'
#' These steps are repeated until a stopping criterion is met (maximum number of
#' iterations, maximum number of iterations without improvements to the best solution, ...).
#'
#' @param obj_func objective function be minimized.
#' @param parameters list of parameters the function is minimized with respect to.
#' Parmeters are requested to be objects of class `Parameter` (see \link[EmiR]{parameter}).
#' @param config an object of class `HSConfig` with the configuration parameters
#' used by algorithm (see \link[EmiR]{config_hs}).
#' @param constraints list of constraints. Constraints are requested to be objects of
#' class `Constraint` (see \link[EmiR]{constraint}).
#' @param silent_mode if `TRUE` no messages are shown.
#' @return `minimize_hs` returns an object of class `MinimizationResult`.
#' @importFrom Rdpack reprompt
#' @references \insertRef{Lee2004}{EmiR}
#' @export
minimize_hs <- function(obj_func, parameters, config, constraints = NULL, ...) {
  minimizer_options <- list(...)

  opt <- new("MinimizerOpts")
  if ("silent_mode" %in% names(minimizer_options)) {
    opt@silent_mode = minimizer_options[["silent_mode"]]
  }

  tictoc::tic()
  out <- cpp_minimize_hs(obj_func, constraints, parameters, config, opt)
  tictoc::toc(log = TRUE, quiet = opt@silent_mode)
  return(out)
}
