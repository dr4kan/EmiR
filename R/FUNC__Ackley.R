###############################################################################
# Emir: EmiR: Evolutionary minimization forR                                  #
# Copyright (C) 2021-2024 Davide Pagano & Lorenzo Sostero                     #
#                                                                             #
# This program is free software: you can redistribute it and/or modify        #
# it under the terms of the GNU General Public License as published by        #
# the Free Software Foundation, either version 3 of the License, or           #
# any later version.                                                          #
#                                                                             #
# This program is distributed in the hope that it will be useful, but         #
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY  #
# or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License    #
# for more details: <https://www.gnu.org/licenses/>.                          #
###############################################################################


#' Ackley Function
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
#' \mjeqn{x_{i} \in \[ -32.768, 32.768 \]}{x_{i} in \[-32.768, 32.768\]}, for all
#' \mjeqn{i=1,...,n}{i=1,...,n}. The function has one global minimum at
#' \mjeqn{f(\vec{x})=0}{f(x)=0} for \mjeqn{x_{i}=0}{x_i=0} for all \mjeqn{i=1,...,n}{i=1,...,n}.
#' @param x numeric or complex vector.
#' @return The value of the function.
#' @references \insertRef{Ackley1987}{EmiR}
#' @export
ackley_func <- function(x) {
  n <- length(x)
  if (n < 1) stop("at least one variable has to be provided")
  sum1 <- 0
  sum2 <- 0
  for (i in 1:n) {
    sum1 <- sum1 + x[[i]]^2
    sum2 <- sum2 + cos(2*pi*x[[i]])
  }

  term1 <- -20 * exp(-0.2*sqrt(sum1/n))
  term2 <- -exp(sum2/n)
  value <- term1 + term2 + 20 + exp(1)
  return(value)
}
