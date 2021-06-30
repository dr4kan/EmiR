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


# Adapted from 'Evolutionary Computation with Biogeography-based Optimization'
# Haiping Ma and Dan Simon.

library(EmiR)
library(ggpubr)
ob <- function(x) (x[1]-10)^3 + (x[2]-20)^3

g1 <- function(x) -(x[1]-5)^2 - (x[2]-5)^2 + 100
g2 <- function(x)  (x[1]-6)^2 + (x[2]-5)^2 - 82.81

c1 <- constraint(g1, "<=")
c2 <- constraint(g2, "<=")

p1 <- parameter("x1", 14, 16)
p2 <- parameter("x2", -2, 12)

algo <- "SA"
an <- list_of_algorithms()

conf <- config_algo(algorithm_id = algo, population_size = 100, iterations = 500)
results <- minimize(algorithm_id = algo,
                    obj_func = ob,
                    config = conf,
                    parameters = list(p1,p2),
                    constraints = list(c1,c2),
                    save_pop_history = TRUE,
                    constrained_method = "BARRIER", #or PENALTY or ACCREJ
                    constr_init_pop = FALSE,
                    oob_solutions = "BAB",
                    penalty_scale = 2)
print(results)
p1  <- plot_population(results, 1)
p10 <- plot_population(results, 50)
p25 <- plot_population(results, 200)
p50 <- plot_population(results, 500)
figure <- ggarrange(p1, p10, p25, p50,
                    ncol = 2, nrow = 2)
figure <- annotate_figure(figure, top = text_grob(an[an$Id==algo,2], color = "black", face = "bold", size = 18))
plot(figure)
