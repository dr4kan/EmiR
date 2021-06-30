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
library(ggpubr)
ob <- function(x) x[1]^2 + x[2]^2

p1 <- parameter("x1", -5, 5)
p2 <- parameter("x2", -5, 5)

algo <- "SA"
an <- list_of_algorithms()

conf <- config_algo(algorithm_id = algo, population_size = 50, iterations = 200)
results <- minimize(algorithm_id = algo,
                    obj_func = ob,
                    config = conf,
                    parameters = list(p1,p2),
                    #constraints = list(c1,c2),
                    save_pop_history = TRUE,
                    #constrained_method = "ACCREJ",
                    #constr_init_pop = FALSE,
                    #penalty_scale = 2,
                    seed = 1)
print(results)
p1  <- plot_population(results, 1)
p10 <- plot_population(results, 25)
p25 <- plot_population(results, 50)
p50 <- plot_population(results, 100)
figure <- ggarrange(p1, p10, p25, p50,
                    ncol = 2, nrow = 2)
figure <- annotate_figure(figure, top = text_grob(an[an$Id==algo,2], color = "black", face = "bold", size = 18))
plot(figure)


