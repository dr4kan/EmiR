test_that("bat unconstrained: ackley_func", {
  config <- config_bat(iterations = 200,
                       population_size = 200)
  x1 <- parameter("x1", -32.768, 32.768)
  x2 <- parameter("x2", -32.768, 32.768)
  bat <- minimize_bat(obj_func = ackley_func,
                      constraints = NULL,
                      parameters = list(x1, x2),
                      config = config,
                      silent_mode = TRUE)

  expect_equal(bat@best_cost, 0, tolerance = 1e-4)
})


test_that("BAT unconstrained: rastrigin_func", {
  config <- config_bat(iterations = 1000,
                       population_size = 50)
  x1 <- parameter("x1", -5, 5)
  x2 <- parameter("x2", -5, 5)
  bat <- minimize_bat(obj_func = rastrigin_func,
                      constraints = NULL,
                      parameters = list(x1, x2),
                      config = config,
                      silent_mode = TRUE)

  expect_equal(bat@best_cost, 0, tolerance = 1e-6)
})


test_that("BAT unconstrained: schwefel_func", {
  config <- config_bat(iterations = 200,
                       population_size = 200)
  x1 <- parameter("x1", -500, 500)
  x2 <- parameter("x2", -500, 500)
  bat <- minimize_bat(obj_func = schwefel_func,
                      constraints = NULL,
                      parameters = list(x1, x2),
                      config = config,
                      silent_mode = TRUE)

  expect_equal(bat@best_cost, -837.9658, tolerance = 1e-5)
})
