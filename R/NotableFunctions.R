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
#_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


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
#_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


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
#' config <- config_PS(iterations = 250, n_particles = 150)
#' ps <- minimize_PS(cost_function = rosenbrock_func,
#'                   parameters = l,
#'                   config = config)
#' print(ps)
#' @export
rosenbrock_func <- function(x) {
  stopifnot(is.numeric(x) || is.complex(x) == T)
  n <- length(x)
  stopifnot(n >= 2)
  value <- 0
  for (i in 1:(n-1)) {
    value <- value + 100*(x[i+1]-x[i]^2)^2 + (x[i]-1)^2
  }
  return(value)
}
#_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


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
#' config <- config_PS(iterations = 250, n_particles = 150)
#' ps <- minimize_PS(cost_function = schwefel_func,
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
#_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


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
#_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
