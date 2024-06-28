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


checkMinimizationOptions <- function(constraints, p_size, d_size, ...) {
  minimizer_options <- list(...)
  opt <- new("MinimizerOpts")
  opt_list <- names(minimizer_options)

  if ("maximize" %in% opt_list) {
    tmp = minimizer_options[["maximize"]]
    # check if is logical
    if (is.logical(tmp) == FALSE || length(tmp) > 1) {
      stop("Option 'maximize' only accepts logical values.\n")
    }
    opt@maximize = tmp
    opt_list <- opt_list[!opt_list %in% "maximize"]
  }

  if ("silent_mode" %in% opt_list) {
    tmp = minimizer_options[["silent_mode"]]
    # check if is logical
    if (is.logical(tmp) == FALSE || length(tmp) > 1) {
      stop("Option 'silent_mode' only accepts logical values.\n")
    }
    opt@silent_mode = tmp
    opt_list <- opt_list[!opt_list %in% "silent_mode"]
  }

  if ("save_pop_history" %in% opt_list) {
    tmp = minimizer_options[["save_pop_history"]]
    # check if is logical
    if (is.logical(tmp) == FALSE || length(tmp) > 1) {
      stop("Option 'save_pop_history' only accepts logical values.\n")
    }
    opt@save_pop_history = tmp
    opt_list <- opt_list[!opt_list %in% "save_pop_history"]
  }

  if ("constrained_method" %in% opt_list) {
    tmp = minimizer_options[["constrained_method"]]
    # check if the user provided a valid method
    if (!(tmp %in% c("PENALTY", "ACCREJ", "BARRIER"))) {
      stop("Possible values for option 'constrained_method' are 'PENALTY', 'BARRIER' and 'ACCREJ'.\n")
    }
    opt@constrained_method = tmp
    opt_list <- opt_list[!opt_list %in% "constrained_method"]
  }

  if ("penalty_scale" %in% opt_list) {
    tmp = minimizer_options[["penalty_scale"]]
    # check if the penalty_scale is > 1
    if (is.numeric(tmp) == FALSE || length(tmp) > 1 || tmp <= 1) {
      stop("Option 'penalty_scale' only accepts numbers greater than 1.\n")
    }
    opt@penalty_scale = tmp
    opt_list <- opt_list[!opt_list %in% "penalty_scale"]
  }

  if ("start_penalty_param" %in% opt_list) {
    tmp = minimizer_options[["start_penalty_param"]]
    # check if the start_penalty_param is > 1
    if (is.numeric(tmp) == FALSE || length(tmp) > 1 || tmp <= 0) {
      stop("Option 'start_penalty_param' only accepts numbers greater than 0.\n")
    }
    opt@start_penalty_param = tmp
    opt_list <- opt_list[!opt_list %in% "start_penalty_param"]
  }

  if ("max_penalty_param" %in% opt_list) {
    tmp = minimizer_options[["max_penalty_param"]]
    # check if the max_penalty_param is > 1
    if (is.numeric(tmp) == FALSE || length(tmp) > 1 || tmp <= 1) {
      stop("Option 'max_penalty_param' only accepts numbers greater than 1.\n")
    }
    opt@max_penalty_param = tmp
    opt_list <- opt_list[!opt_list %in% "max_penalty_param"]
  }

  if ("constr_init_pop" %in% opt_list) {
    tmp = minimizer_options[["constr_init_pop"]]
    # check if is logical
    if (is.logical(tmp) == FALSE || length(tmp) > 1) {
      stop("Option 'constr_init_pop' only accepts logical values.\n")
    }
    opt@constr_init_pop = tmp
    opt_list <- opt_list[!opt_list %in% "constr_init_pop"]
  }

  if ("oob_solutions" %in% opt_list) {
    tmp = minimizer_options[["oob_solutions"]]
    # check if the user provided a valid method
    if (!(tmp %in% c("PBC", "BAB", "DIS", "RBC"))) {
      stop("Possible values for option 'oob_solutions' are 'PBC', 'BAB', 'DIS' and 'RBC'.\n")
    }
    # for constrained optimization problem only DIS is supported
    # if (length(constraints) > 0 && tmp != "DIS") {
    #   stop("For constrained optimization problems only 'DIS' is supported.\n")
    # }
    opt@oob_solutions = tmp
    opt_list <- opt_list[!opt_list %in% "oob_solutions"]
  }

  if ("seed" %in% opt_list) {
    if (is.null(minimizer_options[["seed"]])) {
      opt@seed = 0
    } else {
      tmp = minimizer_options[["seed"]]
      # check if the seed is 0 or positive
      if (is.numeric(tmp) == FALSE || length(tmp) > 1 || tmp%%1 != 0 || tmp < 0) {
        stop("Option 'seed' only accepts 0 or positive integers.\n")
      }
      opt@seed = tmp
    }
    opt_list <- opt_list[!opt_list %in% "seed"]
  }

  if ("initial_population" %in% opt_list) {
    tmp = minimizer_options[["initial_population"]]
    # check if it is a matrix of the right size
    if (is.matrix(tmp) == FALSE || nrow(tmp) != p_size || ncol(tmp) != d_size) {
      stop("Option 'initial_population' only accepts a n x d matrix where n is the population size and d the number of parameters .\n")
    }
    opt@initial_population = tmp
    opt_list <- opt_list[!opt_list %in% "initial_population"]
  }

  if (length(opt_list) > 0) {
    stop(paste("Unknown option(s):", paste(opt_list, collapse = ", ")))
  }

  return(opt)
}



checkCommonConfigOptions <- function(iterations, population_size, iterations_same_cost, absolute_tol) {
  commonOpt <- list(iterations = 0, population_size = 0, iterations_same_cost = 0, absolute_tol = 0)

  if (is.numeric(iterations) == FALSE || length(iterations) > 1 || iterations%%1 != 0 || iterations < 3) {
    stop("Option 'iterations' only accepts positive integers greater or equal to 3.\n")
  }
  commonOpt$iterations = iterations

  if (is.numeric(population_size) == FALSE || length(population_size) > 1 || population_size%%1 != 0 || population_size < 3) {
    stop("Option 'population_size' only accepts positive integers greater or equal to 3.\n")
  }
  commonOpt$population_size = population_size

  if (!is.null(iterations_same_cost)) {
    if (is.numeric(iterations_same_cost) == FALSE || length(iterations_same_cost) > 1 || iterations_same_cost%%1 != 0 || iterations_same_cost > iterations || iterations_same_cost < 2) {
      stop("Option 'iterations_same_cost' only accepts NULL or positive integers greater that 1 and less or equal to the number of iterations.\n")
    }
    commonOpt$iterations_same_cost = iterations_same_cost
  } else commonOpt$iterations_same_cost = iterations

  if (!is.null(absolute_tol)) {
    if (is.numeric(absolute_tol) == FALSE || length(absolute_tol) > 1 || absolute_tol < 0) {
      stop("Option 'absolute_tol' only accepts NULL or positive numbers.\n")
    }
    commonOpt$absolute_tol = absolute_tol
  } else commonOpt$absolute_tol = 0

  return(commonOpt)
}


checkIsSingleNumber <- function(x) {
  if (is.numeric(x) == FALSE || length(x) > 1) return(FALSE)
  return(TRUE)
}
