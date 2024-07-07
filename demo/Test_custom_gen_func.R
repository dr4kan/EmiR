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

library(EmiR)

schaffer2 <- function(x) {
  x1 <- x[1]
  x2 <- x[2]
  fact1 <- (sin(x1^2-x2^2))^2 - 0.5
  fact2 <- (1 + 0.001*(x1^2+x2^2))^2
  y <- 0.5 + fact1/fact2
  return(y)
}

g1 <- function(x) {
  x1 <- x[1]
  x2 <- x[2]
  return(x1^2 + x2^2 - 1)
}

custom_gen <- function(x) {
  rnorm(2, 0, 1)
}

c1 <- constraint(g1, "<=")

p1 <- parameter("x1", -1000, 1000)
p2 <- parameter("x2", -1000, 1000)


conf <- config_algo(algorithm_id = "PS", population_size = 200, iterations = 10000)
results <- minimize(algorithm_id = "PS",
                    obj_func = schaffer2,
                    config = conf,
                    parameters = list(p1,p2),
                    constraints = list(c1),
                    save_pop_history = TRUE,
                    constrained_method = "PENALTY",
                    constr_init_pop = TRUE,
                    oob_solutions = "RBC",
                    penalty_scale = 5,
                    generation_function = custom_gen,
                    seed = 1)
print(results)
