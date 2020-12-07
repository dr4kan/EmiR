#' Constrained function for minimization
#'
#' Create a constrained function for minimization. ???? quadratic loss function
#'
#' @param func original objective function.
#' @param ... one or more constraints of class `Constraint`. See \link[EmiR]{constraint}.
#' @return `constrained_function` returns an object of class `ConstrainedFunction`.
#' @export
constrained_function <- function(func, ...) {
  constraints <- list(...)
  new("ConstrainedFunction", func=func, constraint=constraints)
}
