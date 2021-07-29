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

ob <- function(x) x[1]^2 + x[1]*x[2] - x[2]^2 + x[3]*x[1] - x[3]^2 + 8*x[4]^2 - 17*x[5]^2 + 6*x[6]^3 + x[6]*x[5]*x[4]*x[7] + x[8]^3 + x[9]^4 - x[10]^5 - x[10]*x[5] + 18*x[3]*x[7]*x[6]

p1 <- parameter("x1", 0, 99, TRUE)
p2 <- parameter("x2", 0, 99, TRUE)
p3 <- parameter("x3", 0, 99, TRUE)
p4 <- parameter("x4", 0, 99, TRUE)
p5 <- parameter("x5", 0, 99, TRUE)
p6 <- parameter("x6", 0, 99, TRUE)
p7 <- parameter("x7", 0, 99, TRUE)
p8 <- parameter("x8", 0, 99, TRUE)
p9 <- parameter("x9", 0, 99, TRUE)
p10 <- parameter("x10", 0, 99, TRUE)

conf <- config_algo(algorithm_id = "WOA", population_size = 100, iterations = 500)
results <- minimize(algorithm_id = "WOA",
                    obj_func = ob,
                    config = conf,
                    maximize = TRUE,
                    parameters = list(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10),
                    save_pop_history = TRUE,
                    oob_solutions = "RBC",
                    seed = 10)
print(results)
