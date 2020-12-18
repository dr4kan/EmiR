test_that("Ackley function minimum", {
  ### 1D
  expect_equal(ackley_func(0), 0)
  expect_equal(ackley_func(c(0)), 0)
  expect_equal(ackley_func(list(0)), 0)

  ### 2D
  expect_equal(ackley_func(c(0, 0)), 0)
  expect_equal(ackley_func(list(0, 0)), 0)

  ### 10 D
  expect_equal(ackley_func(rep(0, 10)), 0)
})

test_that("Ackley error", {
  ### No arguments
  expect_error(ackley_func())
  expect_error(ackley_func(c()))
  expect_error(ackley_func(list()))

  ### Non numeric argument
  expect_error(ackley_func(c("0", 0)))

  ### Multiple arguments
  expect_error(ackley_func(0, 0, 0))
})
