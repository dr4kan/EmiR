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


test_that("Rastrigin function minimum", {
  ### 1D
  expect_equal(rastrigin_func(0), 0)
  expect_equal(rastrigin_func(c(0)), 0)
  expect_equal(rastrigin_func(list(0)), 0)

  ### 2D
  expect_equal(rastrigin_func(c(0, 0)), 0)
  expect_equal(rastrigin_func(list(0, 0)), 0)

  ### 10 D
  expect_equal(rastrigin_func(rep(0, 10)), 0)
})

test_that("Rastrigin error", {
  ### No arguments
  expect_error(rastrigin_func())
  expect_error(rastrigin_func(c()))
  expect_error(rastrigin_func(list()))

  ### Non numeric argument
  expect_error(rastrigin_func(c("0", 0)))

  ### Multiple arguments
  expect_error(rastrigin_func(0, 0, 0))
})
