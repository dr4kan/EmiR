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

ob <- function(x) {
  0.6224*(x[1]*0.0625)*x[3]*x[4] + 1.7781*(x[2]*0.0625)*x[3]^2 + 3.1611*(x[1]*0.0625)^2*x[4] + 19.8621*(x[1]*0.0625)^2*x[3]
}

g1 <- function(x){
  0.0193*x[3] - (x[1]*0.0625)
}
g2 <- function(x){
  0.00954*x[3] - (x[2]*0.0625)
}

g3 <- function(x){
  1296000 - pi * x[3]^2 * x[4] - 4/3 * pi * x[3]^3
}

c1 <- constraint(g1, "<=")
c2 <- constraint(g2, "<=")
c3 <- constraint(g3, "<=")

p1 <- parameter("x1", 18, 32, integer = TRUE)
p2 <- parameter("x2", 10, 32, integer = TRUE)
p3 <- parameter("x3", 10, 240)
p4 <- parameter("x4", 10, 240)

conf <- config_algo(algorithm_id = "BAT", population_size = 500, iterations = 7000)
results <- minimize(algorithm_id = "BAT",
                   obj_func = ob,
                   config = conf,
                   parameters = list(p1,p2, p3, p4),
                   constraints = list(c1,c2,c3),
                   save_pop_history = TRUE,
                   constrained_method = "BARRIER",
                   constr_init_pop = TRUE,
                   oob_solutions = "RBC",
                   seed = 1)
print(results)
