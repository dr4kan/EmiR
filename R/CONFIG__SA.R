setClass (
  "SAConfig",

  # Defining slot type
  slots = c(
    iterations           = "numeric",
    iterations_same_cost = "numeric",
    population_size      = "numeric",
    T0                   = "numeric",
    annealing_schedule   = "character"
  ),

  # Initializing slots
  prototype = list(
    iterations           = as.integer(NULL),
    iterations_same_cost = as.integer(NULL),
    population_size      = as.integer(NULL),
    T0                   = as.double(NULL),
    annealing_schedule   = as.character(NULL)
  )
)

# overriding the print function
setMethod(f = "show",
          signature = "SAConfig",
          definition = function(object) {
            cat("         SA minimizer options\n")
            cat("number of iterations:", object@iterations, "\n")
            cat("iterations same cost:", object@iterations_same_cost, "\n")
            cat("     population size:", object@population_size, "\n")
            cat(" initial temperature:", object@T0, "\n")
            cat("  annealing schedule:", object@annealing_schedule, "\n")
          }
)
