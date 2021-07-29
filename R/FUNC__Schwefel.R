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


#' Schwefel Function
#'
#' \loadmathjax
#' Implementation of n-dimensional Schwefel function.
#'
#'
#' On an n-dimensional domain it is defined by
#'
#' \mjdeqn{f(\vec{x}) = \sum_{i=1}^{n} \left\[ -x_{i}\sin(\sqrt{|x_{i}|}) \right\],}{f(x) = sum_1^n \[ -x_i*sin(sqrt(|x_i|) \],}
#' and is usually evaluated on
#' \mjeqn{x_{i} \in \[ -500, 500 \]}{x_{i} in \[-500, 500\]}, for all
#' \mjeqn{i=1,...,n}{i=1,...,n}. The function has one global minimum at
#' \mjeqn{f(\vec{x}) = -418.9829n}{f(x) = -418.9829n} for \mjeqn{x_{i}=420.9687}{x_i=420.9687} for all \mjeqn{i=1,...,n}{i=1,...,n}.
#' @param x numeric or complex vector.
#' @return The value of the function.
#' @references \insertRef{Schwefel1981}{EmiR}
#' @export
schwefel_func <- function(x) {
  n <- length(x)
  if (n < 1) stop("At least one variable has to be provided")
  value <- 0
  for (i in 1:n) {
    value <- value - x[[i]]*sin(sqrt(abs(x[[i]])))
  }
  return(value)
}
