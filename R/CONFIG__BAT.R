setClass (
  "BATConfig",

  # Defining slot type
  slots = c(
    iterations           = "numeric",
    iterations_same_cost = "numeric",
    population_size      = "numeric",
    initial_loudness     = "numeric",
    alpha                = "numeric",
    initial_pulse_rate   = "numeric",
    gamma                = "numeric",
    freq_min             = "numeric",
    freq_max             = "numeric"
  ),

  # Initializing slots
  prototype = list(
    iterations           = as.integer(NULL),
    iterations_same_cost = as.integer(NULL),
    population_size      = as.integer(NULL),
    initial_loudness     = as.double(NULL),
    alpha                = as.double(NULL),
    initial_pulse_rate   = as.double(NULL),
    gamma                = as.double(NULL),
    freq_min             = as.double(NULL),
    freq_max             = as.double(NULL)
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "BATConfig",
          definition = function(object) {
            cat("         BAT minimizer options\n")
            cat("          iterations:", object@iterations, "\n")
            cat("iterations same cost:", object@iterations_same_cost, "\n")
            cat("     population_size:", object@population_size, "\n")
            cat("    initial loudness:", object@initial_loudness, "\n")
            cat("               alpha:", object@alpha, "\n")
            cat("  initial pulse rate:", object@initial_pulse_rate, "\n")
            cat("               gamma:", object@gamma, "\n")
            cat("            freq min:", object@freq_min, "\n")
            cat("            freq max:", object@freq_max, "\n")
          }
)
