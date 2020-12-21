#' Options for EmiR optimization algorithms
#'
#'
#'
#' @param silent_mode if `TRUE` no output to console is generated.
#' @rdname MinimizerOpts
setClass (
  "MinimizerOpts",

  # Defining slot type
  slots = c(
    silent_mode     = "logical",
    save_population = "logical"
  ),

  # Initializing slots
  prototype = list(
    silent_mode     = FALSE,
    save_population = FALSE
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "MinimizerOpts",
          definition = function(object) {
            cat("    silent_mode: ", object@silent_mode, sep = "")
            cat("save_population: ", object@save_population, sep = "")
          }
)
