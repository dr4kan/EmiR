test_that("ABC unconstrained: ackley_func", {
  config <- config_abc(iterations = 1000,
                       population_size = 50)
  x1 <- parameter("x1", -32.768, 32.768)
  x2 <- parameter("x2", -32.768, 32.768)
  abc <- minimize_abc(obj_func = ackley_func,
                      constraints = NULL,
                      parameters = list(x1, x2),
                      config = config,
                      silent_mode = TRUE)

  expect_equal(abc@best_cost, 0, tolerance = 1e-4)
})


test_that("ABC unconstrained: rastrigin_func", {
  config <- config_abc(iterations = 1000,
                       population_size = 50)
  x1 <- parameter("x1", -5, 5)
  x2 <- parameter("x2", -5, 5)
  abc <- minimize_abc(obj_func = rastrigin_func,
                      constraints = NULL,
                      parameters = list(x1, x2),
                      config = config,
                      silent_mode = TRUE)

  expect_equal(abc@best_cost, 0, tolerance = 1e-6)
})


test_that("ABC unconstrained: schwefel_func", {
  config <- config_abc(iterations = 2000,
                       population_size = 50)
  x1 <- parameter("x1", -500, 500)
  x2 <- parameter("x2", -500, 500)
  abc <- minimize_abc(obj_func = schwefel_func,
                      constraints = NULL,
                      parameters = list(x1, x2),
                      config = config,
                      silent_mode = TRUE)

  expect_equal(abc@best_cost, -837.9658, tolerance = 1e-3)
})
