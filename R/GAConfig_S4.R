setClass (
  "GAConfig",

  # Defining slot type
  slots = c(
    iterations           = "numeric",
    iterations_same_cost = "numeric",
    population_size      = "numeric",
    keep_fraction        = "numeric",
    m_mutation_rate      = "numeric"
  ),

  # Initializing slots
  prototype = list(
    iterations           = as.integer(NULL),
    iterations_same_cost = as.integer(NULL),
    population_size      = as.integer(NULL),
    keep_fraction        = as.double(NULL),
    m_mutation_rate      = as.double(NULL)
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
            cat("     m_mutation_rate:", object@m_mutation_rate, "\n")
          }
)
