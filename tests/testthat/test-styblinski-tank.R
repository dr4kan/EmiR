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

library(testthat)
library(EmiR)

test_that("Styblinski-Tang function minimum", {
  ### 1D
  expect_equal(styblinski_tang_func(-2.903534), -39.16599, tolerance = 1e-5)
  expect_equal(styblinski_tang_func(c(-2.903534)), -39.16599, tolerance = 1e-5)
  expect_equal(styblinski_tang_func(list(-2.903534)), -39.16599, tolerance = 1e-5)

  ### 2D
  expect_equal(styblinski_tang_func(c(-2.903534, -2.903534)), -39.16599*2, tolerance = 1e-5)
  expect_equal(styblinski_tang_func(list(-2.903534, -2.903534)), -39.16599*2, tolerance = 1e-5)

  ### 10 D
  expect_equal(styblinski_tang_func(rep(-2.903534, 10)), -39.16599*10, tolerance = 1e-5)
})

test_that("Styblinski-Tang error", {
  ### No arguments
  expect_error(styblinski_tang_func())
  expect_error(styblinski_tang_func(c()))
  expect_error(styblinski_tang_func(list()))

  ### Non numeric argument
  expect_error(styblinski_tang_func(c("0", 0)))

  ### Multiple arguments
  expect_error(styblinski_tang_func(0, 0, 0))
})
