#' Schwefel function
#'
#' \loadmathjax
#' Implementation of n-dimensional Schwefel function.
#'
#'
#' On an n-dimensional domain it is defined by
#'
#' \mjdeqn{f(\vec{x}) = \sum_{i=1}^{n} \left\[ -x_{i}\sin(\sqrt{|x_{i}|}) \right\],}{f(x) = sum_1^n [ -x_i*sin(sqrt(|x_i|) ],}
#' and is usually evaluated on
#' \mjeqn{x_{i} \in \[ -500, 500 \]}{x_{i} in [-500, 500]}, for all
#' \mjeqn{i=1,...,n}{i=1,...,n}. The function has one global minimum at
#' \mjeqn{f(\vec{x}) = -418.9829n}{f(x) = -418.9829n} for \mjeqn{x_{i}=420.9687}{x_i=420.9687} for all \mjeqn{i=1,...,n}{i=1,...,n}.
#' @param x numeric or complex vector.
#' @return The value of the function.
#' @references \insertRef{Schwefel1981}{EmiR}
#' @examples
#' library(EmiR)
#'
#' x1 <- parameter("x1", -500, 500)
#' x2 <- parameter("x2", -500, 500)
#' l <- list(x1, x2)
#'
#' config <- config_ps(iterations = 250, n_particles = 150)
#' ps <- minimize_ps(obj_func = schwefel_func,
#'                   parameters = l,
#'                   config = config)
#' print(ps)
#' @export
schwefel_func <- function(x) {
  stopifnot(is.numeric(x) || is.complex(x) == T)
  n <- length(x)
  value <- 0
  for (i in 1:n) {
    value <- value - x[i]*sin(sqrt(abs(x[i])))
  }
  return(value)
}
