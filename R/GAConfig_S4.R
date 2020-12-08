setClass (
  "GAConfig",

  # Defining slot type
  slots = c(
    iterations           = "numeric",
    iterations_same_cost = "numeric",
    population_size      = "numeric",
    keep_fraction        = "numeric",
    mutation_rate        = "numeric",
    penalty_parameter    = "numeric"
  ),

  # Initializing slots
  prototype = list(
    iterations           = as.integer(NULL),
    iterations_same_cost = as.integer(NULL),
    population_size      = as.integer(NULL),
    keep_fraction        = as.double(NULL),
    mutation_rate        = as.double(NULL),
    penalty_parameter    = as.double(NULL)
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "GAConfig",
          definition = function(object) {
            cat("         GA minimizer options\n")
            cat("          iterations:", object@iterations, "\n")
            cat("iterations_same_cost:", object@iterations_same_cost, "\n")
            cat("     population_size:", object@population_size, "\n")
            cat("       keep_fraction:", object@keep_fraction, "\n")
            cat("       mutation_rate:", object@mutation_rate, "\n")
            cat("   penalty_parameter:", object@penalty_parameter, "\n")
          }
)
