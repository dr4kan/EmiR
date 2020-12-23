#' Options for EmiR optimization algorithms
#'
#' Options for EmiR optimization algorithms.
#'
#' @param silent_mode if `TRUE` no output to console is generated. Default is `FALSE`.
#' @param save_population if `TRUE` the position of all individuals in the population at
#' each iteration is stored. This is necessary for `plot_population` and `animate_population`
#' functions to work, but it should not be used for optimizations involving large populations and
#' large numbers of iterations. Default is `FALSE`.
#' @param oob_solutions strategy to treat out-of-bound solutions. Possible values are:
#' * `"RBC"` - Reflective Boundary Condition: the solution is placed back inside the search domain
#' at a position which is distanced from the boundary as the out-of-bound excess. Depending on the
#' optimization algorithm, the velocity of the corresponding individual of the population could be
#' also inverted.
#' * `"PBC"` - Periodic Boundary Condition: the solution is placed back inside the search domain
#' at a position which is distanced from the \emph{opposite} boundary as the out-of-bound excess.
#' * `"BAB"` - Back At Boundary: the solution is placed back at the boundaries for the out-of-bound
#'  dimensions.
#' * `"DIS"` - Disregard the solution: the solution is replaced by a new one, which is randomly
#' generated in the search space.
#'
#' Default is `"DIS"`.
#' @name MinimizerOpts
#' @rdname MinimizerOpts
setClass (
  "MinimizerOpts",

  # Defining slot type
  slots = c(
    silent_mode     = "logical",
    save_population = "logical",
    oob_solutions   = "character"
  ),

  # Initializing slots
  prototype = list(
    silent_mode     = FALSE,
    save_population = FALSE,
    oob_solutions   = "DIS"
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "MinimizerOpts",
          definition = function(object) {
            cat("    silent_mode: ", object@silent_mode, sep = "")
            cat("save_population: ", object@save_population, sep = "")
            cat("  oob_solutions: ", object@oob_solutions, sep = "")
          }
)
