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

library(EmiR)

ob <- function(x) (x[1]-10)^3 + (x[2]-20)^3

g1 <- function(x) -(x[1]-5)^2 - (x[2]-5)^2 + 100
g2 <- function(x)  (x[1]-6)^2 + (x[2]-5)^2 - 82.81

c1 <- constraint(g1, "<=")
c2 <- constraint(g2, "<=")

p1 <- parameter("x1", 13, 100)
p2 <- parameter("x2", 0, 100)

conf <- config_algo(algorithm_id = "PS", population_size = 200, iterations = 10000)
results <- minimize(algorithm_id = "PS",
                    obj_func = ob,
                    config = conf,
                    parameters = list(p1,p2),
                    constraints = list(c1,c2),
                    save_pop_history = TRUE,
                    constrained_method = "PENALTY",
                    constr_init_pop = FALSE,
                    oob_solutions = "RBC",
                    penalty_scale = 5,
                    seed = 1)
print(results)
