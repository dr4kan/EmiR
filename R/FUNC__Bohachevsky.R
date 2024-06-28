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


#' Bohachevsky Function
#'
#' \loadmathjax
#' Implementation of 2-dimensional Bohachevsky function.
#'
#'
#' On an 2-dimensional domain it is defined by
#'
#' \mjdeqn{f(\vec{x}) = x_{1}^2 + 2x_{2}^2 -0.3\cos(3\pi x_{1})-0.4\cos(4\pi x_{2})+0.7}{f(x) = x_{1}^2 + 2x_{2}^2 -0.3cos(3\pi x_{1})-0.4cos(4\pi x_{2})+0.7}
#' and is usually evaluated on
#' \mjeqn{x_{i} \in \[ -100, 100 \]}{x_{i} in \[ -100, 100 \]}, for all
#' \mjeqn{i=1,2}{i=1,2}. The function has one global minimum at
#' \mjeqn{f(\vec{x}) = 0}{f(x) = 0} for \mjeqn{\vec{x} = \[ 0, 0 \]}{x = \[ 0, 0 \]}.
#' @param x numeric or complex vector.
#' @return The value of the function.
#' @references \insertRef{bohachevsky1986generalized}{EmiR}
#' @export
bohachevsky_func <- function(x) {
  n <- length(x)
  if (n != 2) stop("Exactly two variables have to be provided")

  x1 <- x[[1]]
  x2 <- x[[2]]

  value <- x1^2 + 2*x2^2 - 0.3*cos(3*pi*x1) - 0.4*cos(4*pi*x2) + 0.7
  return(value)
}
