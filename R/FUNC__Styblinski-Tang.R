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


#' Styblinski-Tang Function
#'
#' \loadmathjax
#' Implementation of n-dimensional Styblinski-Tang function.
#'
#'
#' On an n-dimensional domain it is defined by
#'
#' \mjdeqn{f(\vec{x}) = \frac{1}{2} \sum_{i=1}^{n} \left( x_{i}^4 - 16x_{i}^2 + 5x_{i} \right),}{f(x) = 1/2 sum_1^n ( x_i^4 -16*x_i^2 +5*x_i ),}
#' and is usually evaluated on
#' \mjeqn{x_{i} \in \[ -5, 5 \]}{x_{i} in \[-5, 5\]}, for all
#' \mjeqn{i=1,...,n}{i=1,...,n}. The function has one global minimum at
#' \mjeqn{f(\vec{x}) = -39.16599n}{f(x) = -39.16599n} for \mjeqn{x_{i}=-2.903534}{x_i=-2.903534} for all \mjeqn{i=1,...,n}{i=1,...,n}.
#' @param x numeric or complex vector.
#' @return The value of the function.
#' @references \insertRef{Styblinski1990}{EmiR}
#' @export
styblinski_tang_func <- function(x) {
  n <- length(x)
  if (n < 1) stop("at least one variable has to be provided")
  value <- 0
  for (i in 1:n) {
    value <- value + (x[[i]]^4 - 16*x[[i]]^2 + 5*x[[i]])
  }
  value <- value * 0.5
  return(value)
}
