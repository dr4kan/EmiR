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
