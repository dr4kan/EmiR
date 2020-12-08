#' Rastrigin function
#'
#' Implementation of n-dimensional Rastrigin function.
#'
#' \loadmathjax
#' On an n-dimensional domain it is defined by:
#'
#' \mjdeqn{f(\vec{x}) = 20n + \sum_{i=1}^n \left( x_{i}^2 - 20\cos(2\pi x_{i}) \right),}{20n + sum_{i=0}^n [x_{i}^2 - 20cos(2*pi*x_{i})],}
#' and is usually evaluated on
#' \mjeqn{x_{i} \in \[ -5.12, 5.12 \]}{x_{i} in [-5.12, 5.12]}, for all
#' \mjeqn{i=1,...,n}{i=1,...,n}. The function has one global minimum at
#' \mjeqn{f(\vec{x})=0}{f(x)=0} for \mjeqn{x_{i}=0}{x_i=0} for all \mjeqn{i=1,...,n}{i=1,...,n}.
#' @param x numeric or complex vector.
#' @return The value of the function.
#' @importFrom Rdpack reprompt
#' @references \insertRef{rastrigin1974systems}{EmiR}
#' @examples
#' library(EmiR)
#'
#' x1 <- parameter("x1", -5.12, 5.12)
#' x2 <- parameter("x2", -5.12, 5.12)
#' x3 <- parameter("x3", -5.12, 5.12)
#' l <- list(x1, x2, x3)
#'
#' config <- config_PS(iterations = 250, n_particles = 150)
#' ps <- minimize_PS(cost_function = rastrigin_func,
#'                   parameters = l,
#'                   config = config)
#' print(ps)
#' @export
rastrigin_func <- function(x) {
  stopifnot(is.numeric(x) || is.complex(x) == T)
  n <- length(x)
  value <- 10*n
  for (i in 1:n) value = value + x[i]^2 - 10*cos(2*pi*x[i])
  return(value)
}
