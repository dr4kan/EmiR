setClass (
  "ABCConfig",

  # Defining slot type
  slots = c(
    iterations           = "numeric",
    iterations_same_cost = "numeric",
    population_size      = "numeric",
    employed_frac        = "numeric",
    n_scout              = "numeric"
  ),

  # Initializing slots
  prototype = list(
    iterations           = as.integer(NULL),
    iterations_same_cost = as.integer(NULL),
    population_size      = as.integer(NULL),
    employed_frac        = as.double(NULL),
    n_scout              = as.integer(NULL)
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "ABCConfig",
          definition = function(object) {
            cat("           BAT minimizer options\n")
            cat("            iterations:", object@iterations, "\n")
            cat("  iterations same cost:", object@iterations_same_cost, "\n")
            cat("       population_size:", object@population_size, "\n")
            cat("fraction employed bees:", object@employed_frac, "\n")
            cat("  number of scout bees:", object@n_scout, "\n")
          }
)
