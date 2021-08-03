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


#' Griewank Function
#'
#' \loadmathjax
#' Implementation of n-dimensional Griewank function.
#'
#'
#' On an n-dimensional domain it is defined by
#'
#' \mjdeqn{f(\vec{x}) = 1 + \sum_{i=1}^{n} \frac{x_i^{2}}{4000} - \prod_{i=1}^{n}\cos\left(\frac{x_i}{\sqrt{i}}\right),}{f(x) = 1 + \sum_{i=1}^{n} \frac{x_i^{2}}{4000} - \prod_{i=1}^{n}cos(\frac{x_i}{\sqrt{i}}),}
#' and is usually evaluated on
#' \mjeqn{x_{i} \in \[ -600, 600 \]}{x_{i} in \[-600, 600\]}, for all
#' \mjeqn{i=1,...,n}{i=1,...,n}. The function has global minima at
#' \mjeqn{f(\vec{x}) = 0}{f(x) = 0} for \mjeqn{x_{i}=0}{x_i = 0} for all \mjeqn{i=1,...,n}{i=1,...,n}.
#' @param x numeric or complex vector.
#' @return The value of the function.
#' @references \insertRef{griewank1981generalized}{EmiR}
#' @export
griewank_func <- function(x) {
  n <- length(x)
  if (n < 1) stop("At least one variable has to be provided")
  A <- 0
  B <- 1
  for (i in 1:n) {
    A <- A + (x[[i]]^2/4000)
    B <- B * cos(x[[i]]/sqrt(i))
  }
  return(1 + A - B)
}
