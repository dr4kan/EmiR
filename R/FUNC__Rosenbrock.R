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


#' Rosenbrock Function
#'
#' \loadmathjax
#' Implementation of n-dimensional Rosenbrock function, with \mjeqn{n \geq 2}{n >= 2}.
#'
#'
#' On an n-dimensional domain it is defined by
#'
#' \mjdeqn{f(\vec{x}) = \sum_{i=1}^{n-1} \left\[ 100(x_{i+1}-x_{i}^2)^2 + (x_{i}-1)^2 \right\],}{,}
#' and is usually evaluated on
#' \mjeqn{x_{i} \in \[ -5, 10 \]}{x_{i} in \[-5, 10\]}, for all
#' \mjeqn{i=1,...,n}{i=1,...,n}. The function has one global minimum at
#' \mjeqn{f(\vec{x})=0}{f(x)=0} for \mjeqn{x_{i}=1}{x_i=1} for all \mjeqn{i=1,...,n}{i=1,...,n}.
#' @param x numeric or complex vector.
#' @return The value of the function.
#' @references \insertRef{Rosenbrock1960}{EmiR}
#' @export
rosenbrock_func <- function(x) {
  n <- length(x)
  if (n < 2) stop("At least two variables have to be provided")
  value <- 0
  for (i in 1:(n-1)) {
    value <- value + 100*(x[[i+1]]-x[[i]]^2)^2 + (x[[i]]-1)^2
  }
  return(value)
}
