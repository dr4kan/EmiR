#' Options for EmiR optimization algorithms
#'
#'
#'
#' @param silent_mode if `TRUE` no output to console is generated. Default is `FALSE`.
#' @param save_population if `TRUE` the position of all individuals in the population at
#' each iteration is stored. This is necessary for `plot_population` and `animate_population`
#' functions to work, but it should not be used for optimizations involving large populations and/or
#' large numbers of iterations.
#' @param oob_solutions strategy to treat out-of-bound solutions. Possible values are:
#' * `"PBC"` - Periodic Boundary Condition
#' * `"RBC"` - Reflective Boundary Condition
#' * `"BAB"` - Back At Boundary
#' * `"DIS"` - Disregard the solution and generate a new one
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
    oob_solutions   = "RBC"
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
