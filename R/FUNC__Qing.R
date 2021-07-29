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


#' Qing Function
#'
#' \loadmathjax
#' Implementation of n-dimensional Qing function.
#'
#'
#' On an n-dimensional domain it is defined by
#'
#' \mjdeqn{f(\vec{x}) = \sum_{i=1}^{n} \left( x_{i}^2 - i \right)^2,}{f(x) = sum_1^n ( x_i^2 - i )^2,}
#' and is usually evaluated on
#' \mjeqn{x_{i} \in \[ -500, 500 \]}{x_{i} in \[-500, 500\]}, for all
#' \mjeqn{i=1,...,n}{i=1,...,n}. The function has global minima at
#' \mjeqn{f(\vec{x}) = 0}{f(x) = 0} for \mjeqn{x_{i}=\pm \sqrt{i}}{x_i = +-sqrt(i)} for all \mjeqn{i=1,...,n}{i=1,...,n}.
#' @param x numeric or complex vector.
#' @return The value of the function.
#' @references \insertRef{Qing2006}{EmiR}
#' @export
qing_func <- function(x) {
  n <- length(x)
  if (n < 1) stop("At least one variable has to be provided")
  value <- 0
  for (i in 1:n) {
    value <- value + (x[[i]]^2 - i)^2
  }
  return(value)
}
