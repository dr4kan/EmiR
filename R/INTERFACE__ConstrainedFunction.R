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


#' Constrained function for minimization
#'
#' Create a constrained function for minimization.
#'
#' @param func original objective function.
#' @param ... one or more constraints of class `Constraint`. See \link[EmiR]{constraint}.
#' @return `constrained_function` returns an object of class `ConstrainedFunction`.
#' @export
constrained_function <- function(func, ...) {
  constraints <- list(...)
  new("ConstrainedFunction", func=func, constraint=constraints)
}
