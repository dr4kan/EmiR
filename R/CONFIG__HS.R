setClass (
  "HSConfig",

  # Defining slot type
  slots = c(
    iterations           = "numeric",
    iterations_same_cost = "numeric",
    population_size      = "numeric",
    considering_rate     = "numeric",
    adjusting_rate       = "numeric",
    distance_bandwidth   = "numeric"
  ),

  # Initializing slots
  prototype = list(
    iterations           = as.integer(NULL),
    iterations_same_cost = as.integer(NULL),
    population_size      = as.integer(NULL),
    considering_rate     = as.double(NULL),
    adjusting_rate       = as.double(NULL),
    distance_bandwidth   = as.double(NULL)
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "HSConfig",
          definition = function(object) {
            cat("         BAT minimizer options\n")
            cat("          iterations:", object@iterations, "\n")
            cat("iterations same cost:", object@iterations_same_cost, "\n")
            cat("     population size:", object@population_size, "\n")
            cat("    considering rate:", object@hmcr, "\n")
            cat("      adjusting rate:", object@par, "\n")
            cat("  distance bandwidth:", object@bw, "\n")
          }
)
