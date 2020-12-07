#' Constraint for minimization
#'
#' Create a constraint function for constrained optimization.
#'
#' @param func function describing the constraint.
#' @param inequality inequality type. Possible values: `>`, `>=`, `<=`, `<`.
#' @return `constraint` returns an object of class `Constraint`.
#' @export
constraint <- function(func, inequality) {
  stopifnot(inequality == ">" || inequality == ">=" || inequality == "<=" || inequality == "<")
  new("Constraint", func=func, inequality=inequality)
}


