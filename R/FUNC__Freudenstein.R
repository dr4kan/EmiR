###############################################################################
# Emir: EmiR: Evolutionary minimization forR                                  #
# Copyright (C) 2021 Davide Pagano & Lorenzo Sostero                          #
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


#' Freudenstein Roth Function
#'
#' \loadmathjax
#' Implementation of 2-dimensional Freudenstein Roth function.
#'
#'
#' On an 2-dimensional domain it is defined by
#'
#' \mjdeqn{f(\vec{x}) = (x_{1} - 13 + ((5 - x_{2})x_{2} - 2)x_{2})^2 + (x_{1} - 29 + ((x_{2} + 1)x_{2} - 14)x_{2})^2}{f(x) = (x_{1} - 13 + ((5 - x_{2})x_{2} - 2)x_{2})^2 + (x_{1} - 29 + ((x_{2} + 1)x_{2} - 14)x_{2})^2}
#' and is usually evaluated on
#' \mjeqn{x_{i} \in \[ -10, 10 \]}{x_{i} in \[ -10, 10 \]}, for all
#' \mjeqn{i=1,2}{i=1,2}. The function has one global minimum at
#' \mjeqn{f(\vec{x}) = 0}{f(x) = 0} for \mjeqn{\vec{x} = \[ 5, 4 \]}{x = \[ 5, 4 \]}.
#' @param x numeric or complex vector.
#' @return The value of the function.
#' @references \insertRef{rao2019engineering}{EmiR}
#' @export
freudenstein_roth_func <- function(x) {
  n <- length(x)
  if (n != 2) stop("Exactly two variables have to be provided")

  x1 <- x[[1]]
  x2 <- x[[2]]

  value <- (x1 - 13 + ((5 - x2)*x2 - 2)*x2)^2 + (x1 - 29 + ((x2 + 1)*x2 - 14)*x2)^2
  return(value)
}
