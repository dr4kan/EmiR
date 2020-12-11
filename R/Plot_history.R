#' Plot minimization history
#'
#' Plot the minimization history as a function of the number of iterations.
#'
#' @param minimizer_result an object of class `MinimizationResult`.
#' @param ... additional arguments, such as graphical parameters (see \link[base]{plot}).
#' @return A plot.
#' @examples
#' library(EmiR)
#'
#' x1 <- parameter("x1", -32.768, 32.768)
#' x2 <- parameter("x2", -32.768, 32.768)
#' l <- list(x1, x2)
#'
#' config <- config_ps(iterations = 250, n_particles = 150)
#' ps <- minimize_ps(obj_func = ackley_func,
#'                   parameters = l,
#'                   config = config)
#' plot_history(ps)
#' @export
plot_history <- function(minimizer_result, ...) {
  plot(minimizer_result@cost_history, type = "l", lwd = 2, xlab = "Iteration",
       ylab = "Function value", main = paste("EmiR minimizer: ", minimizer_result@algorithm), ...)
}


#' Plot population
#'
#' Plot the XXX.
#'
#' @param minimizer_result an object of class `MinimizationResult`.
#' @param iteration iteration.
#' @param ... additional arguments, such as graphical parameters (see \link[graphics]{contour}).
#' @return A plot.
#' @examples
#' library(EmiR)
#'
#' x1 <- parameter("x1", -32.768, 32.768)
#' x2 <- parameter("x2", -32.768, 32.768)
#' l <- list(x1, x2)
#'
#' config <- config_ps(iterations = 250, n_particles = 150)
#' ps <- minimize_ps(obj_func = ackley_func,
#'                   parameters = l,
#'                   config = config)
#' plot_history(ps)
#' @export
plot_population <- function(minimizer_result, iteration, n_points = 1000, ...) {
  n_par = length(minimizer_result@parameter_names)
  try(if(n_par > 2 || n_par < 1) stop("only 1D and 2D functions are supported"))
  try(if(iteration < 1 || iteration > minimizer_result@iterations) stop("iteration out of range"))

  df <- as.data.frame(do.call(rbind, minimizer_result@particles))
  df <- df[df[, ncol(df)] == (iteration-1),]

  if (n_par == 1) {

    x <- seq(minimizer_result@parameter_range[[1]][1], minimizer_result@parameter_range[[1]][2], length.out = n_points)
    y <- c()
    for (i in x) y <- c(y, minimizer_result@obj_function(i))
    miny <- min(y)

    df <- cbind(df, rep(miny, nrow(df)))
    names(df)[3] = "V3"

    fdf <- data.frame(x, y)

    ggplot2::theme_set(ggplot2::theme_bw(base_size = 16))
    ggplot2::ggplot(fdf) +
      ggplot2::geom_line(ggplot2::aes(x = x, y = y)) +
      ggplot2::geom_point(data = df, ggplot2::aes(x = V1, y = V3)) +
      ggplot2::labs(title = paste0("Iteration #", iteration)) +
      ggplot2::xlab(minimizer_result@parameter_names[1]) +
      ggplot2::ylab(paste0("f(", minimizer_result@parameter_names[1], ")"))

  } else {

    x <- seq(minimizer_result@parameter_range[[1]][1], minimizer_result@parameter_range[[1]][2], length.out = round(sqrt(n_points)))
    y <- seq(minimizer_result@parameter_range[[2]][1], minimizer_result@parameter_range[[2]][2], length.out = round(sqrt(n_points)))
    z <- matrix(0, nrow = length(y), ncol = length(x))
    for (i in 1:length(x)) {
      for (j in 1:length(y)) {
        z[j, i] <- minimizer_result@obj_function(c(x[i], y[j]))
      }
    }
    rownames(z) = x
    colnames(z) = y

    fdf <- as.data.frame(z)
    fdf <- tibble::rownames_to_column(fdf, var="row")
    fdf <- tidyr::pivot_longer(data = fdf, c(-row), names_to = "col", values_to = "value")
    fdf <- dplyr::mutate(fdf, row=as.numeric(row), col=as.numeric(col))

    ggplot2::theme_set(ggplot2::theme_bw(base_size = 16))
    ggplot2::ggplot(fdf) +
      ggplot2::geom_contour(ggplot2::aes(x = col, y = row, z = value)) +
      ggplot2::geom_point(data = df, ggplot2::aes(x = V1, y = V2)) +
      ggplot2::labs(title = paste0("Iteration #", iteration)) +
      ggplot2::xlab(minimizer_result@parameter_names[1]) +
      ggplot2::ylab(minimizer_result@parameter_names[2])

  }
}


#' Animation of particles motion for 1D and 2D function minimization
#'
#' XXXX
#'
#' @param minimizer_result an object of class `MinimizationResult`.
#' @param ... additional arguments, such as graphical parameters (see \link[graphics]{contour}).
#' @return ???
#' @examples
#' library(EmiR)
#'
#' x1 <- parameter("x1", -32.768, 32.768)
#' x2 <- parameter("x2", -32.768, 32.768)
#' l <- list(x1, x2)
#'
#' config <- config_ps(iterations = 250, n_particles = 150)
#' ps <- minimize_ps(obj_func = ackley_func,
#'                   parameters = l,
#'                   config = config)
#' plot_history(ps)
#' @export
animate_population <- function(minimizer_result, n_points = 1000, ...) {
  n_par = length(minimizer_result@parameter_names)
  try(if(n_par > 2 || n_par < 1) stop("only 1D and 2D functions are supported"))

  df <- as.data.frame(do.call(rbind, minimizer_result@particles))

  if (n_par == 1) {

    x <- seq(minimizer_result@parameter_range[[1]][1], minimizer_result@parameter_range[[1]][2], length.out = n_points)
    y <- c()
    for (i in x) y <- c(y, minimizer_result@obj_function(i))
    miny <- min(y)

    df <- cbind(df, rep(miny, nrow(df)))
    names(df)[3] = "V3"

    fdf <- data.frame(x, y)

    ggplot2::theme_set(ggplot2::theme_bw(base_size = 16))
    ggplot2::ggplot(fdf) +
      ggplot2::geom_line(ggplot2::aes(x = x, y = y)) +
      ggplot2::geom_point(data = df, ggplot2::aes(x = V1, y = V3)) +
      gganimate::transition_time(as.integer(V2+1)) +
      ggplot2::labs(title = "Iteration #{frame_time}") +
      ggplot2::xlab(minimizer_result@parameter_names[1]) +
      ggplot2::ylab(paste0("f(", minimizer_result@parameter_names[1], ")"))

  } else {

    x <- seq(minimizer_result@parameter_range[[1]][1], minimizer_result@parameter_range[[1]][2], length.out = round(sqrt(n_points)))
    y <- seq(minimizer_result@parameter_range[[2]][1], minimizer_result@parameter_range[[2]][2], length.out = round(sqrt(n_points)))
    z <- matrix(0, nrow = length(y), ncol = length(x))
    for (i in 1:length(x)) {
      for (j in 1:length(y)) {
        z[j, i] <- minimizer_result@obj_function(c(x[i], y[j]))
      }
    }
    rownames(z) = x
    colnames(z) = y

    fdf <- as.data.frame(z)
    fdf <- tibble::rownames_to_column(fdf, var="row")
    fdf <- tidyr::pivot_longer(data = fdf, c(-row), names_to = "col", values_to = "value")
    fdf <- dplyr::mutate(fdf, row=as.numeric(row), col=as.numeric(col))

    ggplot2::theme_set(ggplot2::theme_bw(base_size = 16))
    ggplot2::ggplot(fdf) +
      ggplot2::geom_contour(ggplot2::aes(x = col, y = row, z = value)) +
      ggplot2::geom_point(data = df, ggplot2::aes(x = V1, y = V2)) +
      gganimate::transition_time(as.integer(V3+1)) +
      ggplot2::labs(title = "Iteration #{frame_time}") +
      ggplot2::xlab(minimizer_result@parameter_names[1]) +
      ggplot2::ylab(minimizer_result@parameter_names[2])

  }
}
