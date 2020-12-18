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
