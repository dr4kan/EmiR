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


#' Constraint for minimization
#'
#' Create a constraint function for constrained optimization. Only inequality constraints are
#' supported.
#'
#' @param func function describing the constraint.
#' @param inequality inequality type. Possible values: `>`, `>=`, `<=`, `<`.
#' @return `constraint` returns an object of class `Constraint`.
#' @export
#'
#' @examples
#' g1 <- function(x) 0.0193*x[3] - (x[1]*0.0625)
#' c1 <- constraint(g1, "<=")
#'
constraint <- function(func, inequality) {
  stopifnot(inequality == ">" || inequality == ">=" || inequality == "<=" || inequality == "<")
  new("Constraint", func=func, inequality=inequality)
}
