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


test_that("Griewank function minimum", {
  ### 1D
  expect_equal(griewank_func(3.45), 1.955794, tolerance = 1e-5)
  expect_equal(griewank_func(c(3.45)), 1.955794, tolerance = 1e-5)
  expect_equal(griewank_func(list(3.45)), 1.955794, tolerance = 1e-5)

  ### 2D
  expect_equal(griewank_func(c(3.45, -28.48)), 1.470856, tolerance = 1e-5)
  expect_equal(griewank_func(list(3.45, -28.48)), 1.470856, tolerance = 1e-5)

  ### 10 D
  expect_equal(griewank_func(rep(-2.903534, 10)), 1.021123, tolerance = 1e-5)
})

test_that("Griewank error", {
  ### No arguments
  expect_error(griewank_func())
  expect_error(griewank_func(c()))
  expect_error(griewank_func(list()))

  ### Non numeric argument
  expect_error(griewank_func(c("0", 0)))

  ### Multiple arguments
  expect_error(griewank_func(0, 0, 0))
})
