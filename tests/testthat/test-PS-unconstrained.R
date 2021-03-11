test_that("PS unconstrained: ackley_func", {
  config <- config_ps(iterations = 200, population_size = 100, iterations_same_cost = 100)
  x1 <- parameter("x1", -32.768, 32.768)
  x2 <- parameter("x2", -32.768, 32.768)
  ps <- minimize_ps(obj_func = ackley_func,
                      constraints = NULL,
                      parameters = list(x1, x2),
                      config = config,
                      silent_mode = TRUE)

  expect_equal(ps@best_cost, 0, tolerance = 1e-1)
})


test_that("PS unconstrained: rastrigin_func", {
  config <- config_ps(iterations = 200,
                       population_size = 100, iterations_same_cost = 100)
  x1 <- parameter("x1", -5, 5)
  x2 <- parameter("x2", -5, 5)
  ps <- minimize_ps(obj_func = rastrigin_func,
                      constraints = NULL,
                      parameters = list(x1, x2),
                      config = config,
                      silent_mode = TRUE)

  expect_equal(ps@best_cost, 0, tolerance = 1e-1)
})


test_that("PS unconstrained: schwefel_func", {
  config <- config_ps(iterations = 200,
                       population_size = 100, iterations_same_cost = 100)
  x1 <- parameter("x1", -500, 500)
  x2 <- parameter("x2", -500, 500)
  ps <- minimize_ps(obj_func = schwefel_func,
                      constraints = NULL,
                      parameters = list(x1, x2),
                      config = config,
                      silent_mode = TRUE)

  expect_equal(ps@best_cost, -837.9658, tolerance = 1e-1)
})
