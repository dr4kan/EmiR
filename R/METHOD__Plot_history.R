###############################################################################
# Emir: EmiR: Evolutionary minimization forR                                  #
# Copyright (C) 2021 Davide Pagano & Lorenzo Sostero                          #
#                                                                             #
# This program is free software: you can redistribute it and/or modify        #
# it under the terms of the GNU General Public License as published by        #
# the Free Software Foundation, either version 3 of the License, or           #
# any later version.                                                          #
#                                                                             #
# This program is distributed in the hope that it will be useful, but         #
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY  #
# or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License    #
# for more details: <https://www.gnu.org/licenses/>.                          #
###############################################################################


utils::globalVariables(c("V1", "V2", "V3", "value"))

df_from_func2D <- function(n_points, min_x, max_x, min_y, max_y, func) {
  x <- seq(min_x, max_x, length.out = n_points)
  y <- seq(min_y, max_y, length.out = n_points)
  z <- matrix(0, nrow = length(y), ncol = length(x))
  for (i in 1:length(x)) {
    for (j in 1:length(y)) {
      z[j, i] <- func(c(x[i], y[j]))
    }
  }
  rownames(z) = x
  colnames(z) = y

  fdf <- as.data.frame(z)
  fdf <- tibble::rownames_to_column(fdf, var="row")
  fdf <- tidyr::pivot_longer(data = fdf, c(-row), names_to = "col", values_to = "value")
  fdf <- dplyr::mutate(fdf, row=as.numeric(row), col=as.numeric(col))

  return(fdf)
}


#' Plot minimization history
#'
#' Plot the minimization history as a function of the number of iterations.
#'
#' @param minimizer_result an object of class `OptimizationResults` (see \link[EmiR]{OptimizationResults}).
#' @param ... additional arguments, such as graphical parameters (see \link[graphics]{plot}).
#' @export
plot_history <- function(minimizer_result, ...) {
  plot(minimizer_result@cost_history, type = "l", lwd = 2, xlab = "Iteration",
       ylab = "Best function value", main = paste("EmiR minimizer: ", minimizer_result@algorithm), ...)
}


#' Plot the population position
#'
#' Plot the position of all individuals in the population, at a given iteration, for 1D and 2D functions. The plot can be
#' produced only if `save_pop_history` is `TRUE` in the options of the minimizer (see \link[EmiR]{MinimizerOpts}).
#'
#' @param minimizer_result an object of class `OptimizationResults` (see \link[EmiR]{OptimizationResults}).
#' @param iteration iteration at which the population is plotted.
#' @param n_points number of points per dimention used to draw the objective function. Default is `100`.
#' @export
plot_population <- function(minimizer_result, iteration, n_points = 100) {
  n_par = length(minimizer_result@parameter_names)

  # check if the history is present
  if (length(minimizer_result@pop_history) < 1) stop("Population history was not saved.")

  # check on number of parameters
  if (n_par > 3 || n_par < 1) stop("Only 1D and 2D functions are supported.")

  df <- as.data.frame(do.call(rbind, minimizer_result@pop_history[[iteration]]))

  if (n_par == 1) {

    x <- seq(minimizer_result@parameter_range[[1]][1], minimizer_result@parameter_range[[1]][2], length.out = n_points)
    y <- c()
    for (i in x) y <- c(y, minimizer_result@obj_function(i))
    miny <- min(y)

    df <- cbind(df, rep(miny, nrow(df)))
    names(df)[2] = "V3"

    fdf <- data.frame(x, y)

    ggplot2::theme_set(ggplot2::theme_bw(base_size = 16))
    p <- ggplot2::ggplot(fdf) +
      ggplot2::geom_line(ggplot2::aes(x = x, y = y)) +
      ggplot2::geom_point(data = df, ggplot2::aes(x = V1, y = V3)) +
      ggplot2::labs(title = paste0("Iteration #", iteration)) +
      ggplot2::xlab(minimizer_result@parameter_names[1]) +
      ggplot2::ylab(paste0("f(", minimizer_result@parameter_names[1], ")"))
    return(p)

  } else if (n_par == 2) {

    obf_df <- df_from_func2D(n_points, minimizer_result@parameter_range[[1]][1], minimizer_result@parameter_range[[1]][2],
                             minimizer_result@parameter_range[[2]][1], minimizer_result@parameter_range[[2]][2], minimizer_result@obj_function)

    # FIX: code to plot the constraint curves
    # constr_df <- list()
    # for (i in 1:length(minimizer_result@constraints)) {
    #   constr_df[[i]] <- df_from_func2D(n_points, minimizer_result@parameter_range[[1]][1], minimizer_result@parameter_range[[1]][2],
    #                                  minimizer_result@parameter_range[[2]][1], minimizer_result@parameter_range[[2]][2], minimizer_result@constraints[[i]]@func)
    # }
    #
    # ggplot2::theme_set(ggplot2::theme_bw(base_size = 16))
    # p <- ggplot2::ggplot(obf_df) +
    #   ggplot2::geom_contour(ggplot2::aes(x = row, y = col, z = value))
    #
    # for (i in 1:length(minimizer_result@constraints)) {
    #   p <-
    # }

    ggplot2::theme_set(ggplot2::theme_bw(base_size = 16))

    p <- ggplot2::ggplot(obf_df) +
      ggplot2::geom_contour(ggplot2::aes(x = row, y = col, z = value)) +
      ggplot2::geom_point(data = df, ggplot2::aes(x = V1, y = V2)) +
      ggplot2::labs(title = paste0("Iteration #", iteration)) +
      ggplot2::xlab(minimizer_result@parameter_names[1]) +
      ggplot2::ylab(minimizer_result@parameter_names[2])
    return(p)

  } else {

    plot3D::scatter3D(df$V1, df$V2, df$V3, colvar = NULL, col = "blue", pch = 16, phi = 0,
                      ticktype = "detailed", xlab = minimizer_result@parameter_names[1],
                      ylab = minimizer_result@parameter_names[2], zlab = minimizer_result@parameter_names[3],
                      main = paste0("Iteration #", iteration))

  }

}


#' Animation of population motion
#'
#' Create an animation of the population motion for the minimization of
#' 1D and 2D functions. The animation can be produced only if `save_pop_history` is `TRUE`
#' in the options of the minimizer (see \link[EmiR]{MinimizerOpts}).
#'
#' @param minimizer_result an object of class `OptimizationResults` (see \link[EmiR]{OptimizationResults}).
#' @param n_points number of points per dimension used to draw the objective function. Default is `100`.
#' @export
animate_population <- function(minimizer_result, n_points = 100) {
  n_par = length(minimizer_result@parameter_names)

  # check if the history is present
  if (length(minimizer_result@pop_history) < 1) stop("Population history was not saved.")

  # check on number of parameters
  if (n_par > 2 || n_par < 1) stop("Only 1D and 2D functions are supported.")

  df <- list()
  for (i in 1:minimizer_result@iterations) {
    df[[i]] <- as.data.frame(do.call(rbind, minimizer_result@pop_history[[i]]))
    df[[i]]$V3 <- i
  }
  df <- data.table::rbindlist(df)

  if (n_par == 1) {

    x <- seq(minimizer_result@parameter_range[[1]][1], minimizer_result@parameter_range[[1]][2], length.out = n_points)
    y <- c()
    for (i in x) y <- c(y, minimizer_result@obj_function(i))
    miny <- min(y)

    df <- cbind(df, rep(miny, nrow(df)))
    names(df) = c("V1", "V2", "V3")

    fdf <- data.frame(x, y)

    p <- ggplot2::theme_set(ggplot2::theme_bw(base_size = 16))
    ggplot2::ggplot(fdf) +
      ggplot2::geom_line(ggplot2::aes(x = x, y = y)) +
      ggplot2::geom_point(data = df, ggplot2::aes(x = V1, y = V3)) +
      gganimate::transition_time(as.integer(V2+1)) +
      ggplot2::labs(title = "Iteration #{frame_time}") +
      ggplot2::xlab(minimizer_result@parameter_names[1]) +
      ggplot2::ylab(paste0("f(", minimizer_result@parameter_names[1], ")"))
    return(p)

  } else {

    x <- seq(minimizer_result@parameter_range[[1]][1], minimizer_result@parameter_range[[1]][2], length.out = n_points)
    y <- seq(minimizer_result@parameter_range[[2]][1], minimizer_result@parameter_range[[2]][2], length.out = n_points)
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
      ggplot2::geom_contour(ggplot2::aes(x = row, y = col, z = value)) +
      ggplot2::geom_point(data = df, ggplot2::aes(x = V1, y = V2)) +
      gganimate::transition_time(V3) +
      ggplot2::labs(title = "Iteration #{frame_time}") +
      ggplot2::xlab(minimizer_result@parameter_names[1]) +
      ggplot2::ylab(minimizer_result@parameter_names[2])

  }
}
