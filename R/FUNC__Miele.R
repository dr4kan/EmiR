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


#' Miele Cantrell Function
#'
#' \loadmathjax
#' Implementation of 4-dimensional Miele Cantrell Function.
#'
#'
#' On an 4-dimensional domain it is defined by
#'
#' \mjdeqn{f(\vec{x}) = \left(e^{-x_{1}} - x_{2} \right)^4 + 100(x_{2} - x_{3})^6 + \left(\tan(x_{3} - x_{4})\right)^4 + x_{1}^8}{f(x) = (e^{-x_{1}} - x_{2} )^4 + 100(x_{2} - x_{3})^6 + (tan(x_{3} - x_{4}))^4 + x_{1}^8}
#' and is usually evaluated on
#' \mjeqn{x_{i} \in \[ -2, 2 \]}{x_{i} in \[ -2, 2 \]}, for all
#' \mjeqn{i=1,...,4}{i=1,...,4}. The function has one global minimum at
#' \mjeqn{f(\vec{x}) = 0}{f(x) = 0} for \mjeqn{\vec{x} = \[ 0, 1, 1, 1 \]}{x = \[ 0, 1, 1, 1 \]}.
#' @param x numeric or complex vector.
#' @return The value of the function.
#' @references \insertRef{cragg1969study}{EmiR}
#' @export
miele_cantrell_func <- function(x) {
  n <- length(x)
  if (n != 4) stop("Exactly 4 variables have to be provided")

  x1 <- x[[1]]
  x2 <- x[[2]]
  x3 <- x[[3]]
  x4 <- x[[4]]

  value <- (exp(-x1) - x2)^4 + 100*(x2 - x3)^6 + (tan(x3 - x4))^4 + x1^8
  return(value)
}
