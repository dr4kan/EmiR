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


#' Get population positions
#'
#' Return a `data.frame` with the position of all individuals in the population at
#' the specified iteration, from an object of class `OptimizationResults` produced with
#' the option `save_pop_history` set to `TRUE` (see \link[EmiR]{MinimizerOpts}).
#'
#' @param minimizer_result an object of class `OptimizationResults` (see \link[EmiR]{OptimizationResults}).
#' @param iteration iteration number.
#' @return An object of class `data.frame`.
#' @export
get_population <- function(minimizer_result, iteration) {

  if (length(minimizer_result@pop_history) < 1) stop("Population history was not saved.")

  if (iteration < 1 || iteration > length(minimizer_result@pop_history)) stop("Iteration out of range.")

  x <- as.data.frame(do.call(rbind, minimizer_result@pop_history[[iteration]]))
  names(x) <- minimizer_result@parameter_names
  return(x)
}
