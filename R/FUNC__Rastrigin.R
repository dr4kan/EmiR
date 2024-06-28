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


#' Rastrigin Function
#'
#' Implementation of n-dimensional Rastrigin function.
#'
#' \loadmathjax
#' On an n-dimensional domain it is defined by:
#'
#' \mjdeqn{f(\vec{x}) = 20n + \sum_{i=1}^n \left( x_{i}^2 - 20\cos(2\pi x_{i}) \right),}{20n + sum_{i=0}^n [x_{i}^2 - 20cos(2*pi*x_{i})],}
#' and is usually evaluated on
#' \mjeqn{x_{i} \in \[ -5.12, 5.12 \]}{x_{i} in \[-5.12, 5.12\]}, for all
#' \mjeqn{i=1,...,n}{i=1,...,n}. The function has one global minimum at
#' \mjeqn{f(\vec{x})=0}{f(x)=0} for \mjeqn{x_{i}=0}{x_i=0} for all \mjeqn{i=1,...,n}{i=1,...,n}.
#' @param x numeric or complex vector.
#' @return The value of the function.
#' @importFrom Rdpack reprompt
#' @references \insertRef{rastrigin1974systems}{EmiR}
#' @export
rastrigin_func <- function(x) {
  n <- length(x)
  if (n < 1) stop("At least one variable has to be provided")
  value <- 10*n
  for (i in 1:n) value = value + x[[i]]^2 - 10*cos(2*pi*x[[i]])
  return(value)
}
