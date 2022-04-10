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


test_that("Rosenbrock function minimum", {
  ### 1D
  expect_error(rosenbrock_func(0))
  expect_error(rosenbrock_func(c(0)))
  expect_error(rosenbrock_func(list(0)))

  ### 2D
  expect_equal(rosenbrock_func(c(1, 1)), 0)
  expect_equal(rosenbrock_func(list(1, 1)), 0)

  ### 10 D
  expect_equal(rosenbrock_func(rep(1, 10)), 0)
})

test_that("Rosenbrock error", {
  ### No arguments
  expect_error(rosenbrock_func())
  expect_error(rosenbrock_func(c()))
  expect_error(rosenbrock_func(list()))

  ### Non numeric argument
  expect_error(rosenbrock_func(c("0", 0)))

  ### Multiple arguments
  expect_error(rosenbrock_func(0, 0, 0))
})
