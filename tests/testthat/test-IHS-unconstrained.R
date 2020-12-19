test_that("IHS unconstrained: ackley_func", {
  config <- config_ihs(iterations = 50000,
                      population_size = 7)
  x1 <- parameter("x1", -32.768, 32.768)
  x2 <- parameter("x2", -32.768, 32.768)
  ihs <- minimize_ihs(obj_func = ackley_func,
                    constraints = NULL,
                    parameters = list(x1, x2),
                    config = config,
                    silent_mode = TRUE)

  expect_equal(ihs@best_cost, 0, tolerance = 1e-4)
})


test_that("IHS unconstrained: rastrigin_func", {
  config <- config_ihs(iterations = 50000,
                       population_size = 7)
  x1 <- parameter("x1", -5, 5)
  x2 <- parameter("x2", -5, 5)
  ihs <- minimize_ihs(obj_func = rastrigin_func,
                      constraints = NULL,
                      parameters = list(x1, x2),
                      config = config,
                      silent_mode = TRUE)

  expect_equal(ihs@best_cost, 0, tolerance = 1e-6)
})


test_that("IHS unconstrained: schwefel_func", {
  config <- config_ihs(iterations = 50000,
                      population_size = 5)
  x1 <- parameter("x1", -500, 500)
  x2 <- parameter("x2", -500, 500)
  ihs <- minimize_ihs(obj_func = schwefel_func,
                    constraints = NULL,
                    parameters = list(x1, x2),
                    config = config,
                    silent_mode = TRUE)

  expect_equal(ihs@best_cost, -837.9658, tolerance = 1e-5)
})
