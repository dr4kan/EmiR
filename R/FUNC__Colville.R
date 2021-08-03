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


#' Colville Function
#'
#' \loadmathjax
#' Implementation of 4-dimensional Colville function.
#'
#'
#' On an 4-dimensional domain it is defined by
#'
#' \mjdeqn{f(\vec{x}) = 100(x_1^2-x_2)^2+(x_1-1)^2+(x_3-1)^2+90(x_3^2-x_4)^2+10.1((x_2-1)^2+(x_4-1)^2)+19.8(x_2-1)(x_4-1),}{f(x) = 100(x_1^2-x_2)^2+(x_1-1)^2+(x_3-1)^2+90(x_3^2-x_4)^2+10.1((x_2-1)^2+(x_4-1)^2)+19.8(x_2-1)(x_4-1),}
#' and is usually evaluated on
#' \mjeqn{x_{i} \in \[ -10, 10 \]}{x_{i} in \[-10, 10\]}, for all
#' \mjeqn{i=1,...,4}{i=1,...,4}. The function has one global minimum at
#' \mjeqn{f(\vec{x}) = 0}{f(x) = 0} for \mjeqn{\vec{x} = \[ 1, 1, 1, 1 \]}{x = \[ 1, 1, 1, 1 \]}.
#' @param x numeric or complex vector.
#' @return The value of the function.
#' @references \insertRef{Grippo1989}{EmiR}
#' @export
colville_func <- function(x) {
  n <- length(x)
  if (n != 4) stop("Exactly 4 variables have to be provided")
  x1 <- x[[1]]
  x2 <- x[[2]]
  x3 <- x[[3]]
  x4 <- x[[4]]

  term1 <- 100 * (x1^2-x2)^2
  term2 <- (x1-1)^2
  term3 <- (x3-1)^2
  term4 <- 90 * (x3^2-x4)^2
  term5 <- 10.1 * ((x2-1)^2 + (x4-1)^2)
  term6 <- 19.8*(x2-1)*(x4-1)

  value <- term1 + term2 + term3 + term4 + term5 + term6
  return(value)
}
