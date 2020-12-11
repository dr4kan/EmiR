#' Rosenbrock function
#'
#' \loadmathjax
#' Implementation of n-dimensional Rosenbrock function, with \mjeqn{n \geq 2}{n >= 2}.
#'
#'
#' On an n-dimensional domain it is defined by
#'
#' \mjdeqn{f(\vec{x}) = \sum_{i=1}^{n-1} \left\[ 100(x_{i+1}-x_{i}^2)^2 + (x_{i}-1)^2 \right\],}{,}
#' and is usually evaluated on
#' \mjeqn{x_{i} \in \[ -5, 10 \]}{x_{i} in [-5, 10]}, for all
#' \mjeqn{i=1,...,n}{i=1,...,n}. The function has one global minimum at
#' \mjeqn{f(\vec{x})=0}{f(x)=0} for \mjeqn{x_{i}=1}{x_i=1} for all \mjeqn{i=1,...,n}{i=1,...,n}.
#' @param x numeric or complex vector.
#' @return The value of the function.
#' @references \insertRef{Rosenbrock1960}{EmiR}
#' @examples
#' library(EmiR)
#'
#' x1 <- parameter("x1", -5, 10)
#' x2 <- parameter("x2", -5, 10)
#' l <- list(x1, x2)
#'
#' config <- config_ps(iterations = 250, n_particles = 150)
#' ps <- minimize_ps(obj_func = rosenbrock_func,
#'                   parameters = l,
#'                   config = config)
#' print(ps)
#' @export
rosenbrock_func <- function(x) {
  n <- length(x)
  stopifnot(n >= 2)
  value <- 0
  for (i in 1:(n-1)) {
    value <- value + 100*(x[i+1]-x[[i]]^2)^2 + (x[[i]]-1)^2
  }
  return(value)
}
