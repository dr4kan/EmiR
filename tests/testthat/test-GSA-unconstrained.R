test_that("GSA unconstrained: ackley_func", {
  config <- config_gsa(iterations =500, population_size = 50)

  x1 <- parameter("x1", -32.768, 32.768)
  x2 <- parameter("x2", -32.768, 32.768)
  gsa <- minimize_gsa(obj_func = ackley_func,
                      constraints = NULL,
                      parameters = list(x1, x2),
                      config = config,
                      silent_mode = TRUE)

  expect_equal(gsa@best_cost, 0, tolerance = 1e-1)
})

test_that("GSA unconstrained: rastrigin_func", {
  config <- config_gsa(iterations =500, population_size = 20)

  x1 <- parameter("x1", -5, 5)
  x2 <- parameter("x2", -5, 5)
  gsa <- minimize_gsa(obj_func = rastrigin_func,
                    constraints = NULL,
                    parameters = list(x1, x2),
                    config = config,
                    silent_mode = TRUE)

  expect_equal(gsa@best_cost, 0, tolerance = 1e-1)
})

test_that("GSA unconstrained: schwefel_func", {
  config <- config_gsa(iterations =500, population_size = 20)

  x1 <- parameter("x1", -500, 500)
  x2 <- parameter("x2", -500, 500)
  gsa <- minimize_gsa(obj_func = schwefel_func,
                    constraints = NULL,
                    parameters = list(x1, x2),
                    config = config,
                    silent_mode = TRUE)

  expect_equal(gsa@best_cost, -837.9658, tolerance = 1e-1)
})
