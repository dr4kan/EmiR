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


test_that("Colville function minimum", {
  ### 4D
  expect_equal(colville_func(c(1,2,3,4)), 2514.4, tolerance = 1e-1)
  expect_equal(colville_func(list(1,2,3,4)), 2514.4, tolerance = 1e-1)
})

test_that("Colville error", {
  ### No arguments
  expect_error(colville_func())
  expect_error(colville_func(c()))
  expect_error(colville_func(list()))

  ### Number of arguments different from 4
  expect_error(colville_func(c(1,2,3)))
  expect_error(colville_func(list(2,3)))

  ### Non numeric argument
  expect_error(colville_func(c("0", 0)))

  ### Multiple arguments
  expect_error(colville_func(0, 0, 0))
})
