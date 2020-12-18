test_that("Styblinski-Tank function minimum", {
  ### 1D
  expect_equal(styblinski_tank_func(-2.903534), -39.16599, tolerance = 1e-5)
  expect_equal(styblinski_tank_func(c(-2.903534)), -39.16599, tolerance = 1e-5)
  expect_equal(styblinski_tank_func(list(-2.903534)), -39.16599, tolerance = 1e-5)

  ### 2D
  expect_equal(styblinski_tank_func(c(-2.903534, -2.903534)), -39.16599*2, tolerance = 1e-5)
  expect_equal(styblinski_tank_func(list(-2.903534, -2.903534)), -39.16599*2, tolerance = 1e-5)

  ### 10 D
  expect_equal(styblinski_tank_func(rep(-2.903534, 10)), -39.16599*10, tolerance = 1e-5)
})

test_that("Styblinski-Tank error", {
  ### No arguments
  expect_error(styblinski_tank_func())
  expect_error(styblinski_tank_func(c()))
  expect_error(styblinski_tank_func(list()))

  ### Non numeric argument
  expect_error(styblinski_tank_func(c("0", 0)))

  ### Multiple arguments
  expect_error(styblinski_tank_func(0, 0, 0))
})
