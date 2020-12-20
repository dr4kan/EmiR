#' Parameter for minimization
#'
#' Create a parameter the cost function is minimized with respect to.
#'
#' @param name name of the parameter.
#' @param min_val minimum value the parameter is allowed to assume during minimization.
#' @param max_val maximum value the parameter is allowed to assume during minimization.
#' @return `parameter` returns an object of class `Parameter`.
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
#' config <- config_ps(iterations = 250, n_particles = 100)
#' ps <- minimize_ps(obj_func = eggholder,
#'                   parameters = l,
#'                   config = config)
#' print(ps)
#' @export
parameter <- function(name, min_val, max_val)
  new("Parameter", name=name, min_val=min_val, max_val=max_val)


