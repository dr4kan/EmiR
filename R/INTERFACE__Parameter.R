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


#' Parameter for minimization
#'
#' Create a parameter the objective function is minimized with respect to.
#'
#' @param name name of the parameter.
#' @param min_val minimum value the parameter is allowed to assume during minimization.
#' @param max_val maximum value the parameter is allowed to assume during minimization.
#' @param integer if `TRUE` the parameter is constrained to be integer. Default is `FALSE`.
#' @return `parameter` returns an object of class `Parameter`.
#' @export
#'
#' @examples
#' p1 <- parameter("x1", 18, 32, integer = TRUE)
#'
parameter <- function(name, min_val, max_val, integer = FALSE) {
  new("Parameter", name=name, min_val=min_val, max_val=max_val, integer=integer)
}


#' Set of parameters for minimization
#'
#' \loadmathjax
#' Create the set of parameters the objective function is minimized with respect to.
#' A \mjeqn{2 \times n}{2 x n} matrix or a \mjeqn{3 \times n}{3 x n} matrix, where the
#' first row is for the lower limits, the second one is for the upper limits, and the
#' (optional) third one is to specify if a parameter is constrained to be integer.
#' In case the third row is not provided, all the parameters are treated as continuous.
#' The name of each of the \mjeqn{n}{n} parameters is automatically generated and
#' it is of the form \mjeqn{xi}{xi}, where \mjeqn{i=1,...,n}{i=1,...,n}.
#'
#' @param values a \mjeqn{2 \times n}{2 x n} matrix or a \mjeqn{3 \times n}{3 x n} matrix.
#' @return `parameters` returns a list of objects of class `Parameter`.
#' @export
parameters <- function(values) {
  if (is.matrix(values) == FALSE || (nrow(values) != 2 &&
      nrow(values) != 3) || ncol(values) < 1) {
    stop("A 2-by-n or a 3-by-n matrix is expected")
    return(NULL)
  }

  par_list <- list()
  if (nrow(values) == 2) {
    for (i in 1:ncol(values)) {
      par_list[[i]] <- new("Parameter", name=paste0("x", i),
                         min_val=values[1,i], max_val=values[2,i],
                         integer=FALSE)
    }
  } else {
    for (i in 1:ncol(values)) {
      par_list[[i]] <- new("Parameter", name=paste0("x", i),
                         min_val=values[1,i], max_val=values[2,i],
                         integer=as.logical(values[3,i]))
    }
  }
  return(par_list)
}
