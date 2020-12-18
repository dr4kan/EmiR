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
