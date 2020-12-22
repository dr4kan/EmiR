setClass (
  "NEWConfig",

  # Defining slot type
  slots = c(
    iterations           = "numeric",
    iterations_same_cost = "numeric",
    population_size      = "numeric"
  ),

  # Initializing slots
  prototype = list(
    iterations           = as.integer(NULL),
    iterations_same_cost = as.integer(NULL),
    population_size      = as.integer(NULL)
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "NEWConfig",
          definition = function(object) {
            cat("           BAT minimizer options\n")
            cat("            iterations:", object@iterations, "\n")
            cat("  iterations same cost:", object@iterations_same_cost, "\n")
            cat("       population_size:", object@population_size, "\n")
          }
)
