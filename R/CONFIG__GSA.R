setClass (
  "GSAConfig",

  # Defining slot type
  slots = c(
    iterations           = "numeric",
    iterations_same_cost = "numeric",
    population_size      = "numeric",
    gravitation          = "numeric",
    velocity_max         = "numeric"
  ),

  # Initializing slots
  prototype = list(
    iterations           = as.integer(NULL),
    iterations_same_cost = as.integer(NULL),
    population_size      = as.integer(NULL),
    gravitation          = as.double(NULL),
    velocity_max         = as.double(NULL)
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "GSAConfig",
          definition = function(object) {
            cat("         GSA minimizer options\n")
            cat("number of iterations:", object@iterations, "\n")
            cat("iterations same cost:", object@iterations_same_cost, "\n")
            cat("     population size:", object@population_size, "\n")
            cat(" gravitational constant:", object@gravitation, "\n")
            cat("  velocity max:", object@velocity_max, "\n")
          }
)
