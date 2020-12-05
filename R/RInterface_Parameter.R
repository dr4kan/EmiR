#' Create XXX
#'
#' @param name name.
#' @param min_val min_val.
#' @param max_val max_val.
#' @return `parameter` returns an object of class "`Parameter`".
#' @examples
#' library(EmiR)
#'
#' eggholder <- function(x) {
#'   value = -(x[2]+47)*sin(sqrt(abs(x[1]/2+x[2]+47)))+x[1]*sin(sqrt(abs(x[1]-(x[2]+47))));
#'   return(value)
#' }
#'
#' x1 <- parameter("x1", -512, 512)
#' x2 <- parameter("x2", -512, 512)
#' l <- list(x1, x2)
#'
#' config <- config_PS(iterations = 250, n_particles = 100)
#' ps <- minimize_PS(cost_function = eggholder,
#'                   parameters = l,
#'                   config = config)
#' print(ps)
#' @export
parameter <- function(name, min_val, max_val) {
  p <- new("Parameter")
  p@name <- name
  p@min_val <- min_val
  p@max_val <- max_val
  return(p);
}

