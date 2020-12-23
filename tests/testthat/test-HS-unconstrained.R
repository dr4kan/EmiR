test_that("HS unconstrained: ackley_func", {
  config <- config_hs(iterations = 50000,
                      population_size = 7)
  x1 <- parameter("x1", -32.768, 32.768)
  x2 <- parameter("x2", -32.768, 32.768)
  hs <- minimize_hs(obj_func = ackley_func,
                    constraints = NULL,
                    parameters = list(x1, x2),
                    config = config,
                    silent_mode = TRUE)

  expect_equal(hs@best_cost, 0, tolerance = 1e-1)
})


test_that("HS unconstrained: rastrigin_func", {
  config <- config_hs(iterations = 50000,
                      population_size = 7)
  x1 <- parameter("x1", -5, 5)
  x2 <- parameter("x2", -5, 5)
  hs <- minimize_hs(obj_func = rastrigin_func,
                    constraints = NULL,
                    parameters = list(x1, x2),
                    config = config,
                    silent_mode = TRUE)

  expect_equal(hs@best_cost, 0, tolerance = 1e-1)
})


test_that("HS unconstrained: schwefel_func", {
config <- config_hs(iterations = 50000,
                    population_size = 5)
x1 <- parameter("x1", -500, 500)
x2 <- parameter("x2", -500, 500)
hs <- minimize_hs(obj_func = schwefel_func,
                   constraints = NULL,
                   parameters = list(x1, x2),
                   config = config,
                   silent_mode = TRUE)

expect_equal(hs@best_cost, -837.9658, tolerance = 1e-1)
})
