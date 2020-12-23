test_that("CS unconstrained: ackley_func", {
  config <- config_cs(iterations = 200,
                       population_size = 200)
  x1 <- parameter("x1", -32.768, 32.768)
  x2 <- parameter("x2", -32.768, 32.768)
  cs <- minimize_cs(obj_func = ackley_func,
                      constraints = NULL,
                      parameters = list(x1, x2),
                      config = config,
                      silent_mode = TRUE)

  expect_equal(cs@best_cost, 0, tolerance = 1e-1)
})


test_that("CS unconstrained: rastrigin_func", {
  config <- config_cs(iterations = 1000,
                       population_size = 50)
  x1 <- parameter("x1", -5, 5)
  x2 <- parameter("x2", -5, 5)
  cs <- minimize_cs(obj_func = rastrigin_func,
                      constraints = NULL,
                      parameters = list(x1, x2),
                      config = config,
                      silent_mode = TRUE)

  expect_equal(cs@best_cost, 0, tolerance = 1e-1)
})


test_that("CS unconstrained: schwefel_func", {
  config <- config_cs(iterations = 200,
                       population_size = 200)
  x1 <- parameter("x1", -500, 500)
  x2 <- parameter("x2", -500, 500)
  cs <- minimize_cs(obj_func = schwefel_func,
                      constraints = NULL,
                      parameters = list(x1, x2),
                      config = config,
                      silent_mode = TRUE)

  expect_equal(cs@best_cost, -837.9658, tolerance = 1e-1)
})
