#' Plot minimization history
#'
#' Plot the minimization history as a function of the number of iterations.
#'
#' @param minimizer_result an object of class `MinimizationResult`.
#' @param ... additional arguments, such as graphical parameters (see \link[base]{plot}).
#' @return A plot.
#' @examples
#' library(EmiR)
#'
#' x1 <- parameter("x1", -32.768, 32.768)
#' x2 <- parameter("x2", -32.768, 32.768)
#' l <- list(x1, x2)
#'
#' config <- config_ps(iterations = 250, n_particles = 150)
#' ps <- minimize_ps(obj_func = ackley_func,
#'                   parameters = l,
#'                   config = config)
#' plot_history(ps)
#' @export
plot_history <- function(minimizer_result, ...) {
  plot(minimizer_result@cost_history, type = "l", lwd = 2, xlab = "Iteration",
       ylab = "Function value", main = paste("EmiR minimizer: ", minimizer_result@algorithm), ...)
}
