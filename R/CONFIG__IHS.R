setClass (
  "IHSConfig",

  # Defining slot type
  slots = c(
    iterations             = "numeric",
    iterations_same_cost   = "numeric",
    population_size        = "numeric",
    considering_rate       = "numeric",
    min_adjusting_rate     = "numeric",
    max_adjusting_rate     = "numeric",
    min_distance_bandwidth = "numeric",
    max_distance_bandwidth = "numeric"
  ),

  # Initializing slots
  prototype = list(
    iterations             = as.integer(NULL),
    iterations_same_cost   = as.integer(NULL),
    population_size        = as.integer(NULL),
    considering_rate       = as.double(NULL),
    min_adjusting_rate     = as.double(NULL),
    max_adjusting_rate     = as.double(NULL),
    min_distance_bandwidth = as.double(NULL),
    max_distance_bandwidth = as.double(NULL)
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "IHSConfig",
          definition = function(object) {
            cat("          BAT minimizer options\n")
            cat("             iterations:", object@iterations, "\n")
            cat("   iterations same cost:", object@iterations_same_cost, "\n")
            cat("        population size:", object@population_size, "\n")
            cat("       considering rate:", object@hmcr, "\n")
            cat("     min adjusting rate:", object@min_adjusting_rate, "\n")
            cat("     max adjusting rate:", object@max_adjusting_rate, "\n")
            cat(" min distance bandwidth:", object@min_distance_bandwidth, "\n")
            cat(" max distance bandwidth:", object@max_distance_bandwidth, "\n")
          }
)
