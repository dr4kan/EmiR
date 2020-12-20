setClass (
  "CSConfig",

  # Defining slot type
  slots = c(
    iterations           = "numeric",
    iterations_same_cost = "numeric",
    population_size      = "numeric",
    discovery_rate       = "numeric",
    step_size            = "numeric"
  ),

  # Initializing slots
  prototype = list(
    iterations           = as.integer(NULL),
    iterations_same_cost = as.integer(NULL),
    population_size      = as.integer(NULL),
    discovery_rate       = as.double(NULL),
    step_size            = as.double(NULL)
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "CSConfig",
          definition = function(object) {
            cat("         CS minimizer options\n")
            cat("          iterations:", object@iterations, "\n")
            cat("iterations_same_cost:", object@iterations_same_cost, "\n")
            cat("     population_size:", object@population_size, "\n")
            cat("      discovery_rate:", object@discovery_rate, "\n")
            cat("           step_size:", object@step_size, "\n")
          }
)
