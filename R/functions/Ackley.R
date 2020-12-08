#' Ackley function
#'
#' \loadmathjax
#' Implementation of n-dimensional Ackley function, with \mjeqn{a=20}{a=20},
#' \mjeqn{b=0.2}{b=0.2} and \mjeqn{c=2\pi}{c=2\pi} (see definition below).
#'
#'
#' On an n-dimensional domain it is defined by
#'
#' \mjdeqn{f(\vec{x}) = -a\exp\left(-b \sqrt{\frac{1}{n}\sum_{i=1}^n x_{i}^2} \right) -\exp\left(\frac{1}{n}\sum_{i=1}^n \cos(cx_{i}) \right) + a + \exp(1),}{-a*exp(-b*sqrt(1/n*sum_1^n (x_{i}^2)) -exp(1/n*sum_1^n (\cos(c*x_i)) + a + exp(1),}
#' and is usually evaluated on
#' \mjeqn{x_{i} \in \[ -32.768, 32.768 \]}{x_{i} in [-32.768, 32.768]}, for all
#' \mjeqn{i=1,...,n}{i=1,...,n}. The function has one global minimum at
#' \mjeqn{f(\vec{x})=0}{f(x)=0} for \mjeqn{x_{i}=0}{x_i=0} for all \mjeqn{i=1,...,n}{i=1,...,n}.
#' @param x numeric or complex vector.
#' @return The value of the function.
#' @references \insertRef{Ackley1987}{EmiR}
#' @examples
#' library(EmiR)
#'
#' x1 <- parameter("x1", -32.768, 32.768)
#' x2 <- parameter("x2", -32.768, 32.768)
#' l <- list(x1, x2)
#'
#' config <- config_PS(iterations = 250, n_particles = 150)
#' ps <- minimize_PS(cost_function = ackley_func,
#'                   parameters = l,
#'                   config = config)
#' print(ps)
#' @export
ackley_func <- function(x) {
  stopifnot(is.numeric(x) || is.complex(x) == T)
  n <- length(x)
  sum1 <- 0
  sum2 <- 0
  for (i in 1:n) {
    sum1 <- sum1 + x[i]^2
    sum2 <- sum2 + cos(2*pi*x[i])
  }

  term1 <- -20 * exp(-0.2*sqrt(sum1/n))
  term2 <- -exp(sum2/n)
  value <- term1 + term2 + 20 + exp(1)
  return(value)
}
