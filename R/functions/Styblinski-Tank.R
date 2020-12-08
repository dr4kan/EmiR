#' Styblinski-Tank function
#'
#' \loadmathjax
#' Implementation of n-dimensional Schwefel function.
#'
#'
#' On an n-dimensional domain it is defined by
#'
#' \mjdeqn{f(\vec{x}) = \frac{1}{2} \sum_{i=1}^{n} \left( x_{i}^4 - 16x_{i}^2 + 5x_{i} \right),}{f(x) = 1/2 sum_1^n ( x_i^4 -16*x_i^2 +5*x_i ),}
#' and is usually evaluated on
#' \mjeqn{x_{i} \in \[ -5, 5 \]}{x_{i} in [-5, 5]}, for all
#' \mjeqn{i=1,...,n}{i=1,...,n}. The function has one global minimum at
#' \mjeqn{f(\vec{x}) = -39.16599n}{f(x) = -39.16599n} for \mjeqn{x_{i}=-2.903534}{x_i=-2.903534} for all \mjeqn{i=1,...,n}{i=1,...,n}.
#' @param x numeric or complex vector.
#' @return The value of the function.
#' @references \insertRef{Styblinski1990}{EmiR}
#' @examples
#' library(EmiR)
#'
#' x1 <- parameter("x1", -500, 500)
#' x2 <- parameter("x2", -500, 500)
#' l <- list(x1, x2)
#'
#' config <- config_PS(iterations = 250, n_particles = 150)
#' ps <- minimize_PS(cost_function = schwefel_func,
#'                   parameters = l,
#'                   config = config)
#' print(ps)
#' @export
styblinski_tank_func <- function(x) {
  stopifnot(is.numeric(x) || is.complex(x) == T)
  n <- length(x)
  value <- 0
  for (i in 1:n) {
    value <- value + (x[i]^4 - 16*x[i]^2 + 5*x[i])
  }
  value <- value * 0.5
  return(value)
}
