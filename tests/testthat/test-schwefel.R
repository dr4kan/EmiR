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


test_that("Schwefel function minimum", {
  ### 1D
  expect_equal(schwefel_func(420.9687), -418.9829, tolerance = 1e-5)
  expect_equal(schwefel_func(c(420.9687)), -418.9829, tolerance = 1e-5)
  expect_equal(schwefel_func(list(420.9687)), -418.9829, tolerance = 1e-5)

  ### 2D
  expect_equal(schwefel_func(c(420.9687, 420.9687)), -418.9829*2, tolerance = 1e-5)
  expect_equal(schwefel_func(list(420.9687, 420.9687)), -418.9829*2, tolerance = 1e-5)

  ### 10 D
  expect_equal(schwefel_func(rep(420.9687, 10)), -418.9829*10, tolerance = 1e-5)
})

test_that("Schwefel error", {
  ### No arguments
  expect_error(schwefel_func())
  expect_error(schwefel_func(c()))
  expect_error(schwefel_func(list()))

  ### Non numeric argument
  expect_error(schwefel_func(c("0", 0)))

  ### Multiple arguments
  expect_error(schwefel_func(0, 0, 0))
})
