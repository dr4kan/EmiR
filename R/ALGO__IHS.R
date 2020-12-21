#' Create a configuration object for the Improved Harmony Search algorithm
#'
#' Create a configuration object for the Improved Harmony Search algorithm, as proposed
#' by Mahdavi \emph{et al.} in 2007 (see \link[EmiR]{minimize_ihs} for more details on the algorithm).
#' At minimum the number of iterations (parameter `iterations`) and the number of
#' solutions in the harmony memory (parameter `population_size`) have to be provided.
#'
#' @param iterations maximum number of iterations.
#' @param population_size number of solutions in the harmony memory.
#' @param iterations_same_cost maximum number of consecutive iterations with the same cost before
#' ending the minimization. If `NULL` the minimization continues for the number of iterations
#' specified by the parameter `iterations`.
#' @param considering_rate probability for each component of a newly generated solution
#'  to be recalled from the harmony memory.
#' @param min_adjusting_rate minimum value of the pitch adjustment probability.
#' @param max_adjusting_rate maximum value of the pitch adjustment probability.
#' @param min_distance_bandwidth minimum amplitude of the random pitch adjustment.
#' @param max_distance_bandwidth maximum amplitude of the random pitch adjustment.
#' @return `config_ihs` returns an object of class `IHSConfig`.
#' @export
config_ihs <- function(iterations,
                       population_size,
                       iterations_same_cost   = NULL,
                       considering_rate       = 0.5,
                       min_adjusting_rate     = 0.3,
                       max_adjusting_rate     = 0.99,
                       min_distance_bandwidth = 0.0001,
                       max_distance_bandwidth = 1) {
  p <- new("IHSConfig")
  p@iterations           <- iterations
  if (is.null(iterations_same_cost)) {
    p@iterations_same_cost <- iterations
  } else {
    p@iterations_same_cost <- iterations_same_cost
  }
  p@population_size        <- population_size
  p@considering_rate       <- considering_rate
  p@min_adjusting_rate     <- min_adjusting_rate
  p@max_adjusting_rate     <- max_adjusting_rate
  p@min_distance_bandwidth <- min_distance_bandwidth
  p@max_distance_bandwidth <- max_distance_bandwidth
  return(p)
}


#' Improved Harmony Search algorithm for function minimization
#'
#' Minimize an objective function, possibly subjected to inequality constraints, using
#' the Improved Harmony Search (IHS) algorithm, as as proposed by Mahdavi \emph{et al.} in 2007.
#'
#' \loadmathjax
#' IHS is a more general version of the Harmony Search algorithm, where the \emph{pitch adjusting rate}
#' (\mjeqn{p_{ar}}{p_{ar}}) and the amount of the random pitch adjustment (\mjeqn{A_{ar}}{A_{ar}}) evolve with the iterations, instead
#' of being fixed, as in the original algorithm (see \link[EmiR]{minimize_hs}).
#'
#' The evolution of \mjeqn{p_{ar}}{p_{ar}} with the iteration \mjeqn{n}{n} is
#' \mjdeqn{p_{ar}(n) = p_{ar}^{min} + n \cdot \frac{p_{ar}^{max} - p_{ar}^{min}}{n_{T}},}{p_{ar}(n) = p_{ar,min} + n x (p_{ar,max} - p_{ar,min})/n_{T}}
#' where \mjeqn{p_{ar}^{min}}{p_{ar}^{min}} and \mjeqn{p_{ar}^{max}}{p_{ar}^{max}} are minimum and maximum
#' values for \mjeqn{p_{ar}}{p_{ar}}, set by the parameters `min_adjusting_rate` and
#' `max_adjusting_rate`, and \mjeqn{n_{T}}{n_{T}} is the total number of iterations (see \link[EmiR]{config_ihs}).
#'
#' The evolution of \mjeqn{A_{ar}}{A_{ar}} with \mjeqn{n}{n} is
#' \mjdeqn{A_{ar}(n) = A_{ar}^{max} \exp\left\[ \ln\left( \frac{A_{ar}^{min}}{A_{ar}^{max}} \right) \cdot \frac{n}{n_{T}} \right\],}{A_{ar}(n) = A_{ar}^{max} exp[ ln( A_{ar}^{min}/A_{ar}^{max} ) x n/n_{T} ]}
#' where \mjeqn{A_{ar}^{min}}{A_{ar}^{min}} and \mjeqn{A_{ar}^{max}}{A_{ar}^{max}} are minimum and maximum
#' values for \mjeqn{A_{ar}}{A_{ar}}, set by the parameters `min_distance_bandwidth` and `max_distance_bandwidth` (see \link[EmiR]{config_ihs}).
#'
#' @param obj_func objective function be minimized.
#' @param parameters list of parameters the function is minimized with respect to.
#' Parmeters are requested to be objects of class `Parameter`(see \link[EmiR]{parameter}).
#' @param config an object of class `IHSConfig` with the configuration parameters
#' used by algorithm (see \link[EmiR]{config_ihs}).
#' @param constraints list of constraints. Constraints are requested to be objects of
#' class `Constraint` (see \link[EmiR]{constraint}).
#' @param silent_mode if `TRUE` no messages are shown.
#' @return `minimize_ihs` returns an object of class `MinimizationResult`.
#' @importFrom Rdpack reprompt
#' @references \insertRef{Mahdavi2007}{EmiR}
#' @export
minimize_ihs <- function(obj_func, parameters, config, constraints = NULL, ...) {
  minimizer_options <- list(...)

  opt <- new("MinimizerOpts")
  if ("silent_mode" %in% names(minimizer_options)) {
    opt@silent_mode = minimizer_options[["silent_mode"]]
  }
  if ("save_population" %in% names(minimizer_options)) {
    opt@save_population = minimizer_options[["save_population"]]
  }

  tictoc::tic()
  out <- cpp_minimize_ihs(obj_func, constraints, parameters, config, opt)
  tictoc::toc(log = TRUE, quiet = opt@silent_mode)
  return(out)
}
