test_that("GA unconstrained: ackley_func", {
  config <- config_ga(iterations = 100, population_size = 100, iterations_same_cost = 100)
  x1 <- parameter("x1", -32.768, 32.768)
  x2 <- parameter("x2", -32.768, 32.768)
  ga <- minimize_ga(obj_func = ackley_func,
                      constraints = NULL,
                      parameters = list(x1, x2),
                      config = config,
                      silent_mode = TRUE)

  expect_equal(ga@best_cost, 0, tolerance = 1e-1)
})


test_that("GA unconstrained: rastrigin_func", {
  config <- config_ga(iterations = 100,
                       population_size = 100, iterations_same_cost = 100)
  x1 <- parameter("x1", -5, 5)
  x2 <- parameter("x2", -5, 5)
  ga <- minimize_ga(obj_func = rastrigin_func,
                      constraints = NULL,
                      parameters = list(x1, x2),
                      config = config,
                      silent_mode = TRUE)

  expect_equal(ga@best_cost, 0, tolerance = 1e-1)
})


test_that("GA unconstrained: schwefel_func", {
  config <- config_ga(iterations = 100,
                       population_size = 100)
  x1 <- parameter("x1", -500, 500)
  x2 <- parameter("x2", -500, 500)
  ga <- minimize_ga(obj_func = schwefel_func,
                      constraints = NULL,
                      parameters = list(x1, x2),
                      config = config,
                      silent_mode = TRUE)

  expect_equal(ga@best_cost, -837.9658, tolerance = 1e-1)
})
