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


test_that("config parameters", {
  # population < 3
  expect_error(
    config_woa(iterations = 100, population_size = -20)
  )
  expect_error(
    config_woa(iterations = 100, population_size = 2)
  )
  expect_silent(
    config_woa(iterations = 100, population_size = 3)
  )

  # population vector
  expect_error(
    config_woa(iterations = 100, population_size = c(10, 20))
  )

  # population character
  expect_error(
    config_woa(iterations = 100, population_size = "34")
  )

  ####################################
  ####################################
  ####################################

  # iterations < 3
  expect_error(
    config_woa(iterations = -20, population_size = 20)
  )
  expect_error(
    config_woa(iterations = 2, population_size = 20)
  )
  expect_silent(
    config_woa(iterations = 3, population_size = 20)
  )

  # iterations vector
  expect_error(
    config_woa(iterations = c(10, 20), population_size = 100)
  )

  # iterations character
  expect_error(
    config_woa(iterations = "100", population_size = 20)
  )

  ####################################
  ####################################
  ####################################

  # iterations_same_cost NULL
  expect_silent(
    config_woa(iterations = 20, population_size = 20, iterations_same_cost = NULL)
  )

  # iterations_same_cost > iterations
  expect_error(
    config_woa(iterations = 20, population_size = 20, iterations_same_cost = 21)
  )

  # iterations_same_cost = iterations
  expect_silent(
    config_woa(iterations = 20, population_size = 20, iterations_same_cost = 20)
  )

  # iterations_same_cost < 0
  expect_error(
    config_woa(iterations = 20, population_size = 20, iterations_same_cost = -21)
  )

  # iterations_same_cost < 2
  expect_error(
    config_woa(iterations = 20, population_size = 20, iterations_same_cost = 1)
  )

  # iterations_same_cost character
  expect_error(
    config_woa(iterations = 20, population_size = 20, iterations_same_cost = "5")
  )

  ####################################
  ####################################
  ####################################

  # absolute_tol NULL
  expect_silent(
    config_woa(iterations = 20, population_size = 20, absolute_tol = NULL)
  )

  # absolute_tol float
  expect_silent(
    config_woa(iterations = 20, population_size = 20, absolute_tol = 0.01)
  )

  # absolute_tol < 0
  expect_error(
    config_woa(iterations = 20, population_size = 20, absolute_tol = -0.1)
  )

  # absolute_tol vector
  expect_error(
    config_woa(iterations = 20, population_size = 20, absolute_tol = c(0.5, 0.11))
  )

  # absolute_tol character
  expect_error(
    config_woa(iterations = 20, population_size = 20, absolute_tol = "0.05")
  )
})
